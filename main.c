/*
	tiny13fanctrl - ATtiny13 based regulated fan control.
	Copyright (C) 2018-2018 Johannes Bauer

	This file is part of tiny13fanctrl.

	tiny13fanctrl is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; this program is ONLY licensed under
	version 3 of the License, later versions are explicitly excluded.

	tiny13fanctrl is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with tiny13fanctrl; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

	Johannes Bauer <JohannesBauer@gmx.de>
*/

#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "hal.h"
#include "ntc_adu2degc.h"

static void delay_micros(uint16_t micros) {
	while (micros--) {
		_delay_us(1);
	}
}

static void send_bit(bool bit) {
	DBG_SetConditional(bit);
	delay_micros(66);		/* approx. 104µs due to loop delay */
}

static void send_byte(uint8_t data) {
	send_bit(false);		/* Start bit */
	for (int8_t i = 0; i < 8; i++) {
		send_bit((data >> i) & 1);
	}
	send_bit(true);			/* Stop bit */
}

static uint8_t sample_adc(void) {
	/* 13 cycles at 150 kHz -> 87 µs */
	ADCSRA |= _BV(ADSC);
	while (ADCSRA & _BV(ADSC));
	return ADCH;	/* Result is left-adjusted, throw away the noisy 2 LSB */
}

static void init_adc(void) {
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);	/* 1/64 = 150 kHz ADC clock at 9.6 MHz */
	ADMUX = _BV(MUX1) | _BV(ADLAR);					/* Vref = Vcc, PB4 input, left adjust */
}

static void init_pwm_output(void) {
	TCCR0A = _BV(WGM00) | _BV(COM0A1);				/* PWM mode 1, phase-correct PWM to TOP = 0xff */
	TCCR0B = _BV(CS02) | _BV(CS00);					/* 1/1024 = 18.3 Hz PWM at 9.6 MHz */
	OCR0A = 0x0;
}

static int8_t get_pwm_modifier(int16_t rpm_error) {
	int8_t sign = (rpm_error < 0) ? -1 : 1;
	uint16_t abs_rpm_error = (rpm_error < 0) ? -rpm_error : rpm_error;
	if (abs_rpm_error < 2) {
		return 0;
	} else if (abs_rpm_error < 5) {
		return sign * 1;
	} else if (abs_rpm_error < 10) {
		return sign * 3;
	} else if (abs_rpm_error < 20) {
		return sign * 10;
	} else {
		return sign * 30;
	}
}

static void modify_pwm(int8_t step) {
	int16_t value = (int16_t)OCR0A + step;
	if (value < 0) {
		value = 0;
	} else if (value > 255) {
		value = 255;
	}
	OCR0A = value;
}

/* Approximately 800ms sampling period */
#define SAMPLE_COUNT_BITS						13
#define SAMPLE_COUNT							(1 << SAMPLE_COUNT_BITS)

/* Max fan speed gives this amount of impulses in the sampling period */
/* Arctic F8: 50% duty cycle, ~70Hz at 12V */
#define FAN_TACHO_PULSES_IN_SAMPLING_PERIOD		50

int main(void) {
	initHAL();
	init_adc();
	init_pwm_output();

	while (true) {
		uint32_t adc_sum = 0;
		bool last_tachometer_state = true;
		uint16_t fan_rotations = 0;
		uint16_t pwm_in_duty_cycle = 0;

		/* Collect samples */
		for (uint16_t i = 0; i < SAMPLE_COUNT; i++) {
			adc_sum += sample_adc();
			if (PWM_IN_IsActive()) {
				pwm_in_duty_cycle++;
			}
			bool current_tachometer_state = FAN_TACHO_IsActive();
			if (current_tachometer_state != last_tachometer_state) {
				if (current_tachometer_state) {
					fan_rotations++;
				}
				last_tachometer_state = current_tachometer_state;
			}
		}

		uint8_t avg_adc_value = adc_sum / SAMPLE_COUNT;
		int16_t temperature_deg_c = ntc_adu2degc(avg_adc_value);

		/* For full PWM input, add 16°C to our measurement */
		uint8_t temperature_added_by_pwm = pwm_in_duty_cycle / (SAMPLE_COUNT / 16);
		int16_t fan_target = temperature_deg_c + temperature_added_by_pwm - 10;
		if (fan_target < 0) {
			fan_target = 0;
		} else if (fan_target >= FAN_TACHO_PULSES_IN_SAMPLING_PERIOD) {
			/* Full blast */
			fan_target = FAN_TACHO_PULSES_IN_SAMPLING_PERIOD;
		}

		/* Determine how to modify output PWM to meet target */
		int16_t fan_error = fan_target - fan_rotations;
		uint8_t pwm_step = get_pwm_modifier(fan_error);
		if (fan_target == 0) {
			/* Off */
			OCR0A = 0;
		} else if (fan_target == FAN_TACHO_PULSES_IN_SAMPLING_PERIOD) {
			/* Max speed */
			OCR0A = 0xff;
		} else {
			modify_pwm(pwm_step);
		}
		send_byte(temperature_deg_c);
		send_byte(temperature_added_by_pwm);
		send_byte(fan_rotations);
		send_byte(fan_target);
		send_byte(OCR0A);
	}

	return 0;
}

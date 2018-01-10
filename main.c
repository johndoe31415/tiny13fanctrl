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

static void delay_micros(uint16_t micros) {
	while (micros--) {
		_delay_us(1);
	}
}

void send_bit(bool bit) {
	DBG_SetConditional(bit);
	delay_micros(66);		/* approx. 104µs due to loop delay */
}

void send_byte(uint8_t data) {
	send_bit(false);		/* Start bit */
	for (int8_t i = 0; i < 8; i++) {
		send_bit((data >> i) & 1);
	}
	send_bit(true);			/* Stop bit */
}

static uint8_t sample_adc(void) {
	ADCSRA |= _BV(ADSC);
	while (ADCSRA & _BV(ADSC));
	return ADCH;	/* Result is left-adjusted, throw away the noisy 2 LSB */
}

static void init_adc(void) {
	ADCSRA = _BV(ADEN) | _BV(ADPS2) | _BV(ADPS1);	/* 1/64 = 150 kHz ADC clock at 9.6 MHz */
	ADMUX = _BV(MUX1) | _BV(ADLAR);					/* Vref = Vcc, PB4 input, left adjust */
}

static void init_pwm_output(void) {
	TCCR0A = _BV(WGM00) | _BV(COM0A1);	/* PWM mode 1, phase-correct PWM to TOP = 0xff */
	TCCR0B = _BV(CS02) | _BV(CS00);		/* 1/1024 = 18.3 Hz PWM at 9.6 MHz */
	OCR0A = 0x0;
}

int main(void) {
	initHAL();
	init_adc();
	init_pwm_output();

	while (true) {
		send_byte(sample_adc());
//		send_byte(0x34);
//		send_byte(0x56);
		delay_micros(10000);
	}

	return 0;
}

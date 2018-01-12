/* Automatically generated HAL from hal.xml */
/* NEVER EDIT MANUALLY */

/* Generated on: 2018-01-11 21:19:04 */

#ifndef __HAL_H__
#define __HAL_H__

#include <avr/io.h>

#define nop()                                    __asm__ __volatile__("nop")

/* PWM_OUT -> PB0 (Output, Initially Inactive) */
#define PWM_OUT_BIT                              0
#define PWM_OUT_PIN                              PINB
#define PWM_OUT_PORT                             PORTB
#define PWM_OUT_DDR                              DDRB
#define PWM_OUT_ModeOutput()                     PWM_OUT_DDR |= _BV(PWM_OUT_BIT)
#define PWM_OUT_IsOutput()                       ((PWM_OUT_DDR & _BV(PWM_OUT_BIT)) != 0)
#define PWM_OUT_SetHIGH()                        PWM_OUT_PORT |= _BV(PWM_OUT_BIT)
#define PWM_OUT_SetLOW()                         PWM_OUT_PORT &= ~_BV(PWM_OUT_BIT)
#define PWM_OUT_Get()                            (PWM_OUT_PIN & _BV(PWM_OUT_BIT))
#define PWM_OUT_SetInactive()                    PWM_OUT_SetLOW()
#define PWM_OUT_SetActive()                      PWM_OUT_SetHIGH()
#define PWM_OUT_Toggle()                         PWM_OUT_PORT ^= _BV(PWM_OUT_BIT)
#define PWM_OUT_SetConditional(condition)        if (condition) PWM_OUT_SetActive(); else PWM_OUT_SetInactive()
#define PWM_OUT_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { PWM_OUT_SetActive(); } else if (conditionoff) { PWM_OUT_SetInactive(); } else if (conditiontoggle) { PWM_OUT_Toggle(); }
#define PWM_OUT_Pulse()                          { PWM_OUT_SetActive(); PWM_OUT_SetInactive(); }
#define PWM_OUT_PulseNop()                       { PWM_OUT_SetActive(); nop(); PWM_OUT_SetInactive(); }
#define PWM_OUT_IsInactive()                     (PWM_OUT_Get() == 0)
#define PWM_OUT_IsActive()                       (PWM_OUT_Get() != 0)
#define PWM_OUT_Init()                           { PWM_OUT_SetInactive(); PWM_OUT_ModeOutput(); }

/* TEMPERATURE -> PB4 (Input, Initially Pullup Off) */
#define TEMPERATURE_BIT                          4
#define TEMPERATURE_PIN                          PINB
#define TEMPERATURE_PORT                         PORTB
#define TEMPERATURE_DDR                          DDRB
#define TEMPERATURE_SetPullupActive()            TEMPERATURE_PORT |= _BV(TEMPERATURE_BIT)
#define TEMPERATURE_SetPullupInactive()          TEMPERATURE_PORT &= ~_BV(TEMPERATURE_BIT)
#define TEMPERATURE_ModeInput()                  TEMPERATURE_DDR &= ~_BV(TEMPERATURE_BIT)
#define TEMPERATURE_IsInput()                    ((TEMPERATURE_DDR & _BV(TEMPERATURE_BIT)) == 0)
#define TEMPERATURE_Get()                        (TEMPERATURE_PIN & _BV(TEMPERATURE_BIT))
#define TEMPERATURE_GetBit()                     (TEMPERATURE_Get() >> TEMPERATURE_BIT)
#define TEMPERATURE_IsInactive()                 (TEMPERATURE_Get() == 0)
#define TEMPERATURE_IsActive()                   (TEMPERATURE_Get() != 0)
#define TEMPERATURE_Init()                       { TEMPERATURE_SetPullupInactive(); TEMPERATURE_ModeInput(); }

/* PWM_IN -> PB3 (Input, Initially Pullup On) */
#define PWM_IN_BIT                               3
#define PWM_IN_PIN                               PINB
#define PWM_IN_PORT                              PORTB
#define PWM_IN_DDR                               DDRB
#define PWM_IN_SetPullupActive()                 PWM_IN_PORT |= _BV(PWM_IN_BIT)
#define PWM_IN_SetPullupInactive()               PWM_IN_PORT &= ~_BV(PWM_IN_BIT)
#define PWM_IN_ModeInput()                       PWM_IN_DDR &= ~_BV(PWM_IN_BIT)
#define PWM_IN_IsInput()                         ((PWM_IN_DDR & _BV(PWM_IN_BIT)) == 0)
#define PWM_IN_Get()                             (PWM_IN_PIN & _BV(PWM_IN_BIT))
#define PWM_IN_GetBit()                          (PWM_IN_Get() >> PWM_IN_BIT)
#define PWM_IN_IsInactive()                      (PWM_IN_Get() == 0)
#define PWM_IN_IsActive()                        (PWM_IN_Get() != 0)
#define PWM_IN_Init()                            { PWM_IN_SetPullupActive(); PWM_IN_ModeInput(); }

/* FAN_TACHO -> PB2 (Input, Initially Pullup On) */
#define FAN_TACHO_BIT                            2
#define FAN_TACHO_PIN                            PINB
#define FAN_TACHO_PORT                           PORTB
#define FAN_TACHO_DDR                            DDRB
#define FAN_TACHO_SetPullupActive()              FAN_TACHO_PORT |= _BV(FAN_TACHO_BIT)
#define FAN_TACHO_SetPullupInactive()            FAN_TACHO_PORT &= ~_BV(FAN_TACHO_BIT)
#define FAN_TACHO_ModeInput()                    FAN_TACHO_DDR &= ~_BV(FAN_TACHO_BIT)
#define FAN_TACHO_IsInput()                      ((FAN_TACHO_DDR & _BV(FAN_TACHO_BIT)) == 0)
#define FAN_TACHO_Get()                          (FAN_TACHO_PIN & _BV(FAN_TACHO_BIT))
#define FAN_TACHO_GetBit()                       (FAN_TACHO_Get() >> FAN_TACHO_BIT)
#define FAN_TACHO_IsInactive()                   (FAN_TACHO_Get() == 0)
#define FAN_TACHO_IsActive()                     (FAN_TACHO_Get() != 0)
#define FAN_TACHO_Init()                         { FAN_TACHO_SetPullupActive(); FAN_TACHO_ModeInput(); }

/* DBG -> PB1 (Output, Initially Inactive) */
#define DBG_BIT                                  1
#define DBG_PIN                                  PINB
#define DBG_PORT                                 PORTB
#define DBG_DDR                                  DDRB
#define DBG_ModeOutput()                         DBG_DDR |= _BV(DBG_BIT)
#define DBG_IsOutput()                           ((DBG_DDR & _BV(DBG_BIT)) != 0)
#define DBG_SetHIGH()                            DBG_PORT |= _BV(DBG_BIT)
#define DBG_SetLOW()                             DBG_PORT &= ~_BV(DBG_BIT)
#define DBG_Get()                                (DBG_PIN & _BV(DBG_BIT))
#define DBG_SetInactive()                        DBG_SetLOW()
#define DBG_SetActive()                          DBG_SetHIGH()
#define DBG_Toggle()                             DBG_PORT ^= _BV(DBG_BIT)
#define DBG_SetConditional(condition)            if (condition) DBG_SetActive(); else DBG_SetInactive()
#define DBG_SetConditionalToggle(conditionon, conditionoff, conditiontoggle) if (conditionon) { DBG_SetActive(); } else if (conditionoff) { DBG_SetInactive(); } else if (conditiontoggle) { DBG_Toggle(); }
#define DBG_Pulse()                              { DBG_SetActive(); DBG_SetInactive(); }
#define DBG_PulseNop()                           { DBG_SetActive(); nop(); DBG_SetInactive(); }
#define DBG_IsInactive()                         (DBG_Get() == 0)
#define DBG_IsActive()                           (DBG_Get() != 0)
#define DBG_Init()                               { DBG_SetInactive(); DBG_ModeOutput(); }

#define initHAL() {\
		PWM_OUT_Init();\
		TEMPERATURE_Init();\
		PWM_IN_Init();\
		FAN_TACHO_Init();\
		DBG_Init();\
}

#endif

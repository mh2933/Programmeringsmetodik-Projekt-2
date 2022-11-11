#ifndef HEADER_H_
#define HEADER_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/**** makro-Definition av LEDs och Knappar****/
#define LED1 0 // PORTB0 pin 8
#define LED2 1 // PORTB1 pin 9
#define LED3 2 // PORTB2 pin 10

#define RESET_BUTTON 2 //PORTD2 // INT0 pin 2
#define TWO_BACK_BUTTON 3 //PORTD3 // INT1 pin 3

#define ONE_BACK_BUTTON 3 //PORTB3 // PCI pin 11
#define ONE_FORWARD_BUTTON 4 //PORTB4 // PCI pin 12
#define TWO_FORWARD_BUTTON 5 //PORTB5 // PCI pin 13

#define LED1_ON PORTB |= (1 << LED1)
#define LED2_ON PORTB |= (1 << LED2)
#define LED3_ON PORTB |= (1 << LED3)

#define LED1_OFF PORTB &= ~(1 << LED1)
#define LED2_OFF PORTB &= ~(1 << LED2)
#define LED3_OFF PORTB &= ~(1 << LED3)

#define LEDS_ON PORTB |= (1 << LED1) | (1 << LED2) | (1 << LED3)
#define LEDS_OFF PORTB &= ~((1 << LED1) | (1 << LED2) | (1 << LED3))

#define RESET_BUTTON_PRESSED (PIND & (1 << RESET_BUTTON))
#define TWO_BACK_BUTTON_PRESSED (PIND & (1 << TWO_BACK_BUTTON))
#define ONE_BACK_BUTTON_PRESSED (PINB & (1 << ONE_BACK_BUTTON))
#define ONE_FORWARD_BUTTON_PRESSED (PINB & (1 << ONE_FORWARD_BUTTON))
#define TWO_FORWARD_BUTTON_PRESSED (PINB & (1 << TWO_FORWARD_BUTTON))

//enumeartioner, detta skapar en egendefinierad datatyp med valfritt namn, anv�nds typedef slipper man skriva enum varje g�ng datatypen anv�nds
//bool �r den enda enumerationen som �r borttagen fr�n �ndelsen _t d� detta �r en vanlig datatyp och �r inbyggd i m�nga spr�k
typedef enum { false = 0, true = 1 } bool;

// h�r har enumerationens namn/datatyp �ndelsen _t f�r att tydligg�r att det �r en typedef  
typedef enum 
{
	STATE_OFF,
	STATE_SLOW,
	STATE_MEDIUM,
	STATE_FAST,
	STATE_ON
} state_t;



//deklaration av externa funktioner:
void setup(void);

void fsm_reset(void);

void fsm_update(void);

void fsm_set_output(void);

void leds_blink(const volatile uint16_t* blink_speed_ms);

void delay_ms(const volatile uint16_t* delay_time_ms);

#endif /* HEADER_H_ */


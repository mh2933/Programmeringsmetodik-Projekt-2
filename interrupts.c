#include "header.h"

/* Avbrottsrutin som anropas vid uppsl�ppning av reset-knappen ansluten till pin 2 PORTD2.
   Vid reset s� �terst�lls tillst�ndsmaskinen till startl�get (lysdioderna sl�cks). */
ISR(INT0_vect)
{
    fsm_reset();
	return;
}

ISR (INT1_vect) // Pin 3 => uppdatera.
{
    fsm_update();
    return;
}

/* avbrottsrutin f�r PCI-avbrott */
// om pin 11 - 13 trycks ned s� uppdateras tillst�ndsmaskinens tillst�nd. 
ISR(PCINT0_vect) // Pin 11 - 13.
{
	if (ONE_BACK_BUTTON_PRESSED || ONE_FORWARD_BUTTON_PRESSED || TWO_FORWARD_BUTTON_PRESSED)
	{
		fsm_update();
	}
	return;
}


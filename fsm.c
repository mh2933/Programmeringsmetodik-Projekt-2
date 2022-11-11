/********************************************************************************
* fsm.c: Finite State Machine 
         Steg tv� �r att definiera funktionerna som f�rst var deklarerade i headerfilen. 
         Inneh�ller funktionalitet f�r implementering av tillst�ndsmaskinen
*        f�r styrning av lysdioderna. Pekare anv�nds vid passering av
*        blinkhastigheten f�r att direkt kunna avbryta en blinkning ifall
*        aktuellt tillst�nd �verg�r fr�n blinkande till annat tillst�nd.
*        F�rdr�jningstiden som refereras till nollst�lls n�r detta sker,
*        vilket medf�r att kvarvarande f�rdr�jningstid s�tts till noll.
********************************************************************************/



#include "header.h"

//static �r enbart lokal i denna fil, och den sparas i RAM-minnet den existerar hela programmets l�ngd, typ som en global variabel
static state_t state = STATE_OFF;
static uint16_t speed_ms = 0;

/* alla variabler som l�ggs inne i funktionerna sparas p� stacken och f�rsvinner n�r vi n�r return; f�rutom dom som �r definerade som static*/
void fsm_reset(void)
{
	state = STATE_OFF;
    speed_ms = 0;	
	LEDS_OFF;
	return;
}

// kollar vilket tillst�nd finite state machine befinner sig i
void fsm_update(void)
{
	switch (state)
	{
		case STATE_OFF:
		{
			if (TWO_BACK_BUTTON_PRESSED)
			{
				state = STATE_FAST;
			}
			else if (ONE_BACK_BUTTON_PRESSED)
			{
				state = STATE_ON;
			}
			else if (ONE_FORWARD_BUTTON_PRESSED)
			{
				state = STATE_SLOW;
			}
			else if (TWO_FORWARD_BUTTON_PRESSED)
			{
				state = STATE_MEDIUM;
			}

			break;
		}

		case STATE_SLOW:
		{
			if (TWO_BACK_BUTTON_PRESSED)
			{
				state = STATE_ON;
			}
			else if (ONE_BACK_BUTTON_PRESSED)
			{
				state = STATE_OFF;
			}
			else if (ONE_FORWARD_BUTTON_PRESSED)
			{
				state = STATE_MEDIUM;
			}
			else if (TWO_FORWARD_BUTTON_PRESSED)
			{
				state = STATE_FAST;
			}

			break;
		}

		case STATE_MEDIUM:
		{
			if (TWO_BACK_BUTTON_PRESSED)
			{
				state = STATE_OFF;
			}
			else if (ONE_BACK_BUTTON_PRESSED)
			{
				state = STATE_SLOW;
			}
			else if (ONE_FORWARD_BUTTON_PRESSED)
			{
				state = STATE_FAST;
			}
			else if (TWO_FORWARD_BUTTON_PRESSED)
			{
				state = STATE_ON;
			}

			break;
		}

		case STATE_FAST:
		{
			if (TWO_BACK_BUTTON_PRESSED)
			{
				state = STATE_SLOW;
			}
			else if (ONE_BACK_BUTTON_PRESSED)
			{
				state = STATE_MEDIUM;
			}
			else if (ONE_FORWARD_BUTTON_PRESSED)
			{
				state = STATE_ON;
			}
			else if (TWO_FORWARD_BUTTON_PRESSED)
			{
				state = STATE_OFF;
			}

			break;
		}

		case STATE_ON:
		{
			if (TWO_BACK_BUTTON_PRESSED)
			{
				state = STATE_MEDIUM;
			}
			else if (ONE_BACK_BUTTON_PRESSED)
			{
				state = STATE_FAST;
			}
			else if (ONE_FORWARD_BUTTON_PRESSED)
			{
				state = STATE_OFF;
			}
			else if (TWO_FORWARD_BUTTON_PRESSED)
			{
				state = STATE_SLOW;
			}

			break;
		}

		default: // om n�got g�r fel i koden s� har vi en default som resettar
		{
			fsm_reset();
			break;
		}
	}

	if (state == STATE_OFF) speed_ms = 0;
	else if (state == STATE_SLOW) speed_ms = 500;
	else if (state == STATE_MEDIUM) speed_ms = 250;
	else if (state == STATE_FAST) speed_ms = 50;
	else if (state == STATE_ON) speed_ms = 0;
	return;
}

void fsm_set_output(void) // uppdaterar lysdioderna efter det nya tillst�ndet. 
{
	LEDS_OFF;
	
	if (state == STATE_SLOW)  // 500 ms blinkhastighet
	{
		leds_blink(&speed_ms);
	}
	else if (state == STATE_MEDIUM) // 250 ms blinkhastighet
	{
		leds_blink(&speed_ms);
	}
	else if (state == STATE_FAST) // 50 ms blinkhastighet
	{
		leds_blink(&speed_ms);
	}
	else if (STATE_ON)
	{
		LEDS_ON;
	}
	else
	{
		fsm_reset();
	}
	return;
}


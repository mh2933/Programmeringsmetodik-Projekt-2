#include "header.h"


int main(void)
{
	setup();

// while kör kontinuerligt funktionen fsm_set_output för att blinkningen sker konstant
	while (1)
	{
		fsm_set_output();
	}
	
	return 0;
}

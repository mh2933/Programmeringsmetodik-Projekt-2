#include "header.h"


int main(void)
{
	setup();

// while k�r kontinuerligt funktionen fsm_set_output f�r att blinkningen sker konstant
	while (1)
	{
		fsm_set_output();
	}
	
	return 0;
}

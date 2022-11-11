#include "header.h"


/* static gör funktionen lokal till setup.c filen, inline klistrar in inehållet
och kan bara anropas i samma fil. Vid kompilering så kompileras varje fil för sig */

///deklarationer av statiska funktioner: static enbart synlig i denna fil, inline klistrar in koden i stället för att hoppa,
///om koden är liten så är det inte lönt att hoppa då klistrar man in koden istället detta spar tid
static inline void init_ports();
static inline void init_interrupts();

/* setup: initierar mikrodatorn vid start */
void setup(void)
{
	init_ports();
	init_interrupts();
	fsm_reset();
	return;
}

/* init_ports: sätter lysdiodernas pinnar till utportar och sätter tryckknapparnas pinnar till aktiva inportar
			   (insignalerna blir alltid 0 eller 1) underförstått är att pullup-resistorer aktiveras med kommandot PORT och ettställning */
static void init_ports(void)
{
	DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3); //PORTarna sätts till utport
	PORTB = (1 << ONE_BACK_BUTTON) | (1 << ONE_FORWARD_BUTTON) | (1 << TWO_FORWARD_BUTTON); // pullup resistorer aktiveras
	PORTD = (1 << RESET_BUTTON) | (1 << TWO_BACK_BUTTON);  // pullup resistorer aktiveras
	return;
}

/* Jag aktiverar först avbrottet på INT0 på fallande flank med ISC01. Tre rader ner så används |= för att aktivera 
   avbrott INT1 på stigande flank, detta kan implementeras på samma rad och är kankse att föredra men just nu så är det lite tydligare 
   för mig vad som sker */


/***************************** 
   EICRA = kontrollregister
   EIMSK = maskregister   
   PCICR = kontrollregister
   PCMSK = maskregister
 ****************************/

static void init_interrupts(void)
{
	asm("SEI"); // SET INTERRUPT FLAG aktiverar globalt avbrott assembler instruktion
	EICRA = (1 << ISC01); // ISC01 aktiverar avbrott på fallande flank. Läs 12-2 i datablad s.54 
	EIMSK = (1 << INT0);  // INT0 aktiverar avbrott pin 2

	EICRA |= ((1 << ISC11) | (1 << ISC10)); // aktiverar avbrott INT1 stigande flank. läs 12-2 i datablad s.54	// jag ändrar inte värdet från EICRA utan lägger till 
	EIMSK |= (1 << INT1); // INT1 aktiverar avbrott pin 3 

	PCICR = (1 << PCIE0); // PIN CHANGE INTERRUPT på PORT B = 0, C = 1, D = 2
	PCMSK0 = (1 << ONE_BACK_BUTTON) | (1 << ONE_FORWARD_BUTTON) | (1 << TWO_FORWARD_BUTTON); // PCI avbrott på pin 11, 12 och 13// går även att skriva PCINT3, PCINT4 och PCINT5 kolla pin ritning i början
	return;
}
#include "header.h"


/* static g�r funktionen lokal till setup.c filen, inline klistrar in ineh�llet
och kan bara anropas i samma fil. Vid kompilering s� kompileras varje fil f�r sig */

///deklarationer av statiska funktioner: static enbart synlig i denna fil, inline klistrar in koden i st�llet f�r att hoppa,
///om koden �r liten s� �r det inte l�nt att hoppa d� klistrar man in koden ist�llet detta spar tid
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

/* init_ports: s�tter lysdiodernas pinnar till utportar och s�tter tryckknapparnas pinnar till aktiva inportar
			   (insignalerna blir alltid 0 eller 1) underf�rst�tt �r att pullup-resistorer aktiveras med kommandot PORT och ettst�llning */
static void init_ports(void)
{
	DDRB = (1 << LED1) | (1 << LED2) | (1 << LED3); //PORTarna s�tts till utport
	PORTB = (1 << ONE_BACK_BUTTON) | (1 << ONE_FORWARD_BUTTON) | (1 << TWO_FORWARD_BUTTON); // pullup resistorer aktiveras
	PORTD = (1 << RESET_BUTTON) | (1 << TWO_BACK_BUTTON);  // pullup resistorer aktiveras
	return;
}

/* Jag aktiverar f�rst avbrottet p� INT0 p� fallande flank med ISC01. Tre rader ner s� anv�nds |= f�r att aktivera 
   avbrott INT1 p� stigande flank, detta kan implementeras p� samma rad och �r kankse att f�redra men just nu s� �r det lite tydligare 
   f�r mig vad som sker */


/***************************** 
   EICRA = kontrollregister
   EIMSK = maskregister   
   PCICR = kontrollregister
   PCMSK = maskregister
 ****************************/

static void init_interrupts(void)
{
	asm("SEI"); // SET INTERRUPT FLAG aktiverar globalt avbrott assembler instruktion
	EICRA = (1 << ISC01); // ISC01 aktiverar avbrott p� fallande flank. L�s 12-2 i datablad s.54 
	EIMSK = (1 << INT0);  // INT0 aktiverar avbrott pin 2

	EICRA |= ((1 << ISC11) | (1 << ISC10)); // aktiverar avbrott INT1 stigande flank. l�s 12-2 i datablad s.54	// jag �ndrar inte v�rdet fr�n EICRA utan l�gger till 
	EIMSK |= (1 << INT1); // INT1 aktiverar avbrott pin 3 

	PCICR = (1 << PCIE0); // PIN CHANGE INTERRUPT p� PORT B = 0, C = 1, D = 2
	PCMSK0 = (1 << ONE_BACK_BUTTON) | (1 << ONE_FORWARD_BUTTON) | (1 << TWO_FORWARD_BUTTON); // PCI avbrott p� pin 11, 12 och 13// g�r �ven att skriva PCINT3, PCINT4 och PCINT5 kolla pin ritning i b�rjan
	return;
}
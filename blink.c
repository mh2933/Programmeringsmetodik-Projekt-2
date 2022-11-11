
#include "header.h"

// blink.c implementerar blinksekvensen

void leds_blink(const volatile uint16_t* blink_speed_ms)
{
	LEDS_OFF;
	LED1_ON;
	delay_ms(blink_speed_ms);

	LED1_OFF;
	LED2_ON;
	delay_ms(blink_speed_ms);

	LED2_OFF;
	LED3_ON;
	delay_ms(blink_speed_ms);

	LED3_OFF;
	return;
}

void delay_ms(const volatile uint16_t* delay_time_ms)
{
	for (uint16_t i = 0; i < *delay_time_ms; ++i)
	{
		_delay_ms(1);
	}
	return;
}

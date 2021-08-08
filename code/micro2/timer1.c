/*
 * timer1.c
 *
 *  Created on: Jul 23, 2019
 *      Author: M e t r o
 */

#include"timer1.h"


volatile uint8 check=0;

void timer1_oco(void)
{
	SREG |=(1<<7);// to active interrupt

	TCCR1A =(1<<FOC1A);//to active non PWM

	/*WGM12=1 to active CTC
	 * CS12 and CS10 to active 1024 prescaler
	 */
	TCCR1B =(1<<WGM12)|(1<<CS12)|(1<<CS10);

	TCNT1 = 0;//start timer
	OCR1A =7500;//this value to 1 SEC
	TIMSK |=(1<<OCIE1A);//Output Compare A Match Interrupt Enable

}


ISR(TIMER1_COMPA_vect)
{
	check++;

}

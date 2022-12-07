#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "shiftOut.h"

#define SEGMENTS_DDR DDRB
#define SEGMENTS_PORT PORTB 
#define SEGMENTS_PIN PINB 
#define DATA_PIN 0
#define SHIFT_CLOCK_PIN 2
#define MEMORY_CLOCK_PIN 1
#define PUSH_BUTTON_PIN 6
#define COUNT_DELAY 1000

void outSeven(uint8_t led);
void count(int8_t *countStart, int8_t *countEnd, int delayTime);
int checkPushButton();

int main(){
	
	SEGMENTS_DDR |= (( 1 << DATA_PIN ) | ( 1 << SHIFT_CLOCK_PIN ) | (1 << MEMORY_CLOCK_PIN)); //define data,shift colock , memeory clock pins to be OUT pins
	SEGMENTS_DDR &= ~( 1 << PUSH_BUTTON_PIN ); //define push button pin to be IN pin
	SEGMENTS_PORT |= ( 1 << PUSH_BUTTON_PIN ); //configure pullup resistor on input pin
	int8_t countStart = 0; //counter start point
	int8_t countEnd = 9; //counter end point
	
	while(1)
	{
        count(&countStart, &countEnd, COUNT_DELAY);	
	}
	return 0;
}

//count function from countStart till countEnd with a delay delayTime between each 7 segemnt digit change.
void count(int8_t *countStart, int8_t *countEnd, int delayTime)
{
	const uint8_t  leds[] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246};
	for (int8_t i = *countStart ; i <= *countEnd ; i++)
	{
		outSeven(leds[abs(i)]);
		for(int y = 1 ; y <= delayTime ; y++)
		{
			_delay_ms(1); 
			if(checkPushButton())
			{
				int8_t  tmp = *countStart;
			    *countStart = -1 * (*countEnd);
				*countEnd = -1 * tmp;
				return;
			}
		}
	}
}

//function to change the shown digit of the 7 segment
void outSeven(uint8_t led)
{
	SEGMENTS_PORT &= ~( 1 << MEMORY_CLOCK_PIN);
	shiftOut(&SEGMENTS_PORT,DATA_PIN, SHIFT_CLOCK_PIN , led);
	SEGMENTS_PORT |= ( 1 << MEMORY_CLOCK_PIN);
}

		
int checkPushButton()
{
	if( SEGMENTS_PIN & ( 1 << PUSH_BUTTON_PIN))
	{
		return 0;
	}
	else
	{
        _delay_ms(300);
		return 1;
	}
}
				
#include <stdint.h>
#include "shiftOut.h"

void shiftOut(volatile uint8_t *port,uint8_t dataPin, uint8_t shiftClockPin,uint8_t led)
{
	
	for(int i =0 ; i<=7 ; i++)
	{
		
		*port &= ~( 1 << shiftClockPin); //take shift clock down
		char serialBit = led & ( 1 << i ); // mask each bit on each iteration
		if(serialBit)   //if serial bit is non-zero -> set serial dataPin to HIGH otherwise set it to LOW
		{
			*port |= ( 1 << dataPin );
		}
		else
		{
			*port &= ~( 1 << dataPin);
		}
		
		*port |= ( 1 << shiftClockPin); //raise shift clock up
	}	
}
#include <stdio.h>
#include <util/delay.h>

void DIO_init(){
  DIO_SetPinDirection('d',7,'i');

  DIO_SetPinDirection('d',6,'o');
}

void DIO_SetPinDirection(unsigned char port, int pin, unsigned char direction){ //function to set wether the pin is an input or output in
  if(port == 'd' & pin <= 7 & pin >= 0){ //make sure the bit is in register port D and from 0 to 7
    if (direction == 'o'){ //if output
      DDRD |= (1<<pin); //then shift 1 to the position of the bit and OR it with the register to preserve the other bits
    }else if(direction == 'i'){ //if input
      DDRD &= ~(1<<pin); //then shift the opposite of 1, a zero, to the position of the bit and and it with the register to preserve the other bits
    }
  }
}

void DIO_SetPinState(unsigned char port, int pin, unsigned char state){ //function to set the pinstate of the bits
  if(port == 'd' & pin <= 7 & pin >= 0){ //make sure the bit is in register port D and from 0 to 7
    if(state == 'h'){ //if state to set it equal to high
      PORTD |= (1<<pin); //then shift one to the PORTD to turn on the bit
    }else if(state == 'l'){ //if low
      PORTD &= ~(1<<pin); //then shift the zero bit to the position of the bit to turn off and AND it.
    }
  }
}
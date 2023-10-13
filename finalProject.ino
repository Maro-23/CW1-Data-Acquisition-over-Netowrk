#include <avr/io.h>
#include "project.h"
#include "dio.h"
#include <string.h>

int main(void){

  #define BAUD 9600 //defining the BAUD rate globally

  const int PUSH_BUTTON = 7; //push button at digital pin 7

  DIO_init();

  char button_onText[15] = "Button Pressed\n"; //char array for button on text
  char button_offText[19] = "Button not Pressed\n"; //char array for button off text
  char led_on[10] = "Led is on\n"; //char array for LED on text
  char led_off[11] = "Led is off\n"; //char array for LED off text
  char compare_onCmd[] = "led_on"; //char array for comparison for LED on
  char compare_offCmd[] = "led_off"; //char array for comparison for LED off
  char receive_string[25]; //empty string to store received characters
  int counter = 0; //counter for measuring length of string
  char received; //empty char variable to receive from the serial monitor input

  uart_init(BAUD); //initialize the BAUDRate setup

  int prevButton_state = digitalRead(PUSH_BUTTON); //put the previous state in a variable, used to read the rising edge signal of a button

  while(1){ //loop for running system
    if((UCSR0A)&(1<<RXC0)){//only enter if there is a bit to receive
      received = uart_receive();//store the received bit in a variable
      if(received != '\n'){//if the received bit isn't a new line, meaning not the end of the command as after the command is typed, enter is pressed
        receive_string[counter++] = received;//place the received bit into the string in position (counter) which starts at 0 and increments each time a char is added to the string
      }else{//once the received character is a newline, enter the comparison branch
        if( counter == 6 && strncmp(receive_string,compare_onCmd,6)==0 ){//if length of string is 6 and the comparison between string and led_on string is true
          uart_transmit_array("LED turned on\n",14);//transmit to the serial monitor that the led turned on
          DIO_SetPinState('d',6,'h'); //
        }
        else if( counter == 7 && strncmp(receive_string,compare_offCmd,7)==0){//if the length of the string is 7 and the comparison between string and led_off is true
          uart_transmit_array("LED turned off\n",15);//transmit to the serial monitor that the led turned off
          DIO_SetPinState('d',6,'l');
        }else{
          uart_transmit_array("Incorrect command\n",18); //if command is not led_on or led_off, transmit incorrect command for clarity
        }
        counter = 0; //reset the counter for checking the word length after finishing the loop
        memset(receive_string,' ',sizeof(receive_string));
      }

      
    }

    int Button_state = (digitalRead(PUSH_BUTTON)); //read button state (HAVE TO CHANGE IT)

    if(Button_state == HIGH && Button_state != prevButton_state){ //check for rising edge signal of the button click for turning on
      uart_transmit_array(button_onText,15); //transmit to the serial monitor button on text
    }else if (Button_state == LOW && Button_state != prevButton_state){  //check for falling edge signal of the button click for turning off
      uart_transmit_array(button_offText,19); //transmit to the serial monitor button off text
    }

    prevButton_state  = Button_state; //setting new previous button state for rising/falling edge detection
  }
  return 0;
}
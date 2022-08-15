
// Include Libraries
#include "Joystick.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


// Pin Definitions
// joystick 1
#define JOYSTICK_1_PIN_SW 2
#define JOYSTICK_1_PIN_VRX A0
#define JOYSTICK_1_PIN_VRY A1
// joystick 2
#define JOYSTICK_2_PIN_SW 3
#define JOYSTICK_2_PIN_VRX A2
#define JOYSTICK_2_PIN_VRY A3

//nrf module
#define NRF24_CE 9
#define NRF24_CSN 8


// Global variables and defines

// object initialization
// joysticks
Joystick joystick_1(JOYSTICK_1_PIN_VRX, JOYSTICK_1_PIN_VRY, JOYSTICK_1_PIN_SW, true);
Joystick joystick_2(JOYSTICK_2_PIN_VRX, JOYSTICK_2_PIN_VRY, JOYSTICK_2_PIN_SW, false);

//nrf module
RF24 radio(NRF24_CE, NRF24_CSN);

//address through which two module communicates
const byte address[6] = "00001";

// define vars for testing menu
const int timeout = 1000; // define timeout of 10 sec

// Setup the essentials for your circuit to work. It runs firs
//t every time your circuit is powered with electricity.
void setup()
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    radio.begin();
    //set the address
    radio.openWritingPipe(address);
  
    //Set module as transmitter
    radio.stopListening();
    while (!Serial)
        ; // wait for serial port to connect. Needed for native USB
    Serial.println("starting the test of the input of X Y joystick....");
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop()
{
    take_input();
    // delay for 1 seconds..
    delay(timeout);
}

// take the input from 2 joystick and print the values
void take_input()
{
    // PS2 X Y Axis Joystick Module #1 - Test Code
    // Read Joystick X,Y axis and press
    int joystick_1X = joystick_1.getX();
    int joystick_1Y = joystick_1.getY();
    int joystick_1SW = joystick_1.getSW();
    char input[] = "data : {joystick_1 : {x : XXXX,y : XXXX,sw : X},joystick_2 : {x : XXXX,y : XXXX,sw : X}}";
    
    convert_int_to_char(joystick_1X, input, 25, 4);
    convert_int_to_char(joystick_1Y, input, 34, 4);
    convert_int_to_char(joystick_1SW, input, 44, 1);
    

    // PS2 X Y Axis Joystick Module #2 - Test Code
    // Read Joystick X,Y axis and press
    int joystick_2X = joystick_2.getX();
    int joystick_2Y = joystick_2.getY();
    int joystick_2SW = joystick_2.getSW();
    
    convert_int_to_char(joystick_2X, input, 65, 4);
    convert_int_to_char(joystick_2Y, input, 74, 4);
    convert_int_to_char(joystick_2SW, input, 84, 1);
    Serial.println(input);
    radio.write(&input, sizeof(input));
}


void convert_int_to_char (int n, char* string, int pos, int count){
  while (count){
    int digit = n % 10;
    n /= 10;
    string[pos+count] = digit + '0';
    count--;
  }
  
}

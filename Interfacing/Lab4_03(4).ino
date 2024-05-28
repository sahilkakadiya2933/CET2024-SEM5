/**
Name: Sahil Kakadiya
Student Number: 041052919
Discription: Lab4_03 code
*/
// Including the Bounce2 library for button debouncing
#include <Bounce2.h>

void handleButtonPress();
void updateLED();
void Counter();

// Bounce2 library debouncer object
Bounce debouncer = Bounce();

// Pin used for the RED LED
int redPin = 14;
int pbIn = 7;

// Volatile variables for button handling
volatile int counter = 0;
volatile bool mode = 1;
volatile bool buttonPressed = false; // Flag to track if button press has been handled
volatile unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 100; // 

void setup() {  
  pinMode(redPin, OUTPUT); // Set green LED pin as output
  Serial.begin(9600); // Initialize serial communication
  debouncer.attach(pbIn, INPUT_PULLUP); // Attach the debouncer to pin 7
  debouncer.interval(5); // Use a debounce interval of 5 milliseconds
  
  // Attach interrupt to handle button press
  attachInterrupt(digitalPinToInterrupt(pbIn), handleButtonPress, FALLING);
}

void loop() {
  debouncer.update(); // Update the debouncer

  updateLED(); // Update the LED based on the current mode

  // Check if the button has been pressed and handle it
  if (buttonPressed) {
    Counter();
    buttonPressed = false; // Reset the button press flag
  }

  delay(100); // Small delay to avoid excessive loop iterations
}

void handleButtonPress() {
  // Check for debounce
  if (millis() - lastDebounceTime < debounceDelay) {
    return;
  }

  // If the button was pressed, toggle the mode and increment the counter
  mode = !mode;
  counter++;

  lastDebounceTime = millis(); // Save the last debounce time
  buttonPressed = true; // Set the button press flag
}

void updateLED() {
  // Set LED intensity to 100 (0 to 255 range) if mode is false, otherwise turn off the LED
  if (!mode) {
    analogWrite(redPin, 255);
  } else {
    analogWrite(redPin, 0);
  }
}

void Counter() {
  Serial.println(counter); // Print the counter value to serial for debugging
}

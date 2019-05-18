// Import Serial port library
#include <SoftwareSerial.h>

// Define BT module inputs
String command;
int TxD = 11;
int RxD = 10;

// Define toggle variables
int toggleY = 0;
int toggleB = 0;
int toggleR = 0;

// Instantiate BT module
SoftwareSerial bluetooth(TxD, RxD);

// Define ports 2, 3, 4 as output
void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  // Start serial communication at 9600bps
  Serial.begin(9600);
  bluetooth.begin(9600);
}

// Read and execute voice commands
void loop() {

 // If data has been sent, process it
 if (bluetooth.available()) {
    // Read command from BT module
    command = bluetooth.readString();
    
    // Print command
    Serial.println(command);

    // Turn all lights on
    if (command.indexOf("all", 0) >= 0){
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);  
    }

    // Turn all off
    if (command.indexOf("off", 0) >= 0){
      digitalWrite(2, LOW); 
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);       
    }

    // Turn Yellow light on/off
    if (command.indexOf("yellow", 0) >= 0){
      if (toggleY == 1) {
        digitalWrite(2, LOW);
        toggleY = 0;
      }
      else {
        digitalWrite(2, HIGH); 
        toggleY = 1;
      }
    }

    // Turn Red light on/off
    if (command.indexOf("red", 0) >= 0){
      if (toggleR == 1) {
        digitalWrite(3, LOW);
        toggleR = 0;
      }
      else {
        digitalWrite(3, HIGH); 
        toggleR = 1;
      }
    }

    // Turn blue light on/off
    if (command.indexOf("blue", 0) >= 0){
      if (toggleB == 1) {
        digitalWrite(4, LOW);
        toggleB = 0;
      }
      else {
        digitalWrite(4, HIGH); 
        toggleB = 1;
      }
    }

    // Add 1
    if (command.indexOf("add", 0) >= 0){
      if (toggleB == 0) {
        digitalWrite(4, HIGH);
        toggleB = 1;
      }
      else if (toggleR == 0) {
        digitalWrite(3, HIGH);
        digitalWrite(4, LOW);
        toggleR = 1;
        toggleB = 0;
      }
      else if (toggleY == 0) {
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        toggleY = 1;
        toggleR = 0;
        toggleB = 0;
      }
      else {
      }
    }
    
    // Subtract 1
    if (command.indexOf("subtract", 0) >= 0){
      if (toggleB == 1) {
        digitalWrite(4, LOW);
        toggleB = 0;
      }
      else if (toggleR == 1) {
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        toggleR = 0;
        toggleB = 1;
      }
      else if (toggleY == 1) {
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
        digitalWrite(4, HIGH);
        toggleY = 0;
        toggleR = 1;
        toggleB = 1;
      }
      else {
      }
     }

     // Program streak
     if (command.indexOf("police car", 0) >= 0){
        // first reset
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        
        // streak 10 times
        for (int i=0; i<10; i++) {
            digitalWrite(2, HIGH);
            delay(100);
            digitalWrite(2, LOW);
            delay(100);
            digitalWrite(3, HIGH);
            delay(100);
            digitalWrite(3, LOW);
            delay(100);
            digitalWrite(4, HIGH);
            delay(100);
            digitalWrite(4, LOW);
            delay(100);
        }
     }
   }
}

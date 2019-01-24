/*
  Button
  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

*/
//#define ESP8266 1

// constants won't change. They're used here to set pin numbers:
#ifdef ESP8266
const int buttonPin = 0;     // the number of the pushbutton pin
const int ledPin =  2;      // the number of the LED pin
#else
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
#endif

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int lastButtonState = 0;
String inputString = "";
bool stringComplete = false;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  inputString.reserve(200);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW && lastButtonState == HIGH) { 
    Serial.println("led\n");
  }

  lastButtonState = buttonState;

   if (stringComplete) {
    if(inputString.equals("led\n")){
      digitalWrite(ledPin, HIGH);  
    }else{
      digitalWrite(ledPin, LOW);
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

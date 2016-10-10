// LED PINS
#define redLedPin 3
#define greenLedPin 5
#define blueLedPin 6

// BUTTON PINS
#define buttonPin1 16
#define buttonPin2 14
#define buttonPin3 15

// ENCODER PINS
#define encoder1Pin1 2
#define encoder1Pin2 4
#define encoder2Pin1 7
#define encoder2Pin2 8

// LED current color
unsigned short redLed = 255;
unsigned short greenLed = 255;
unsigned short blueLed = 255;

// LED current mode
// 0 - color
// 1 - breathing
// 2 - rainbow
unsigned short ledMode = 0;

// LED brightnes
float ledBrightnes = 1;
float brightnesStep = -0.05;

void setup() {
  // pin setup for LED strip
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  // pin setup for BUTTONs
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
}

void loop() {
  switch(ledMode) {
    case 1: { // 1 - breathing
      ledBrightnes += brightnesStep;
      if(brightnesStep > 0) {
        if (ledBrightnes >= 1) {
          brightnesStep = -1*brightnesStep;
        }
      } else {
        if (ledBrightnes <= 0) {
          brightnesStep = -1*brightnesStep;
        }
      }
      analogWrite(redLedPin, redLed*ledBrightnes);
      analogWrite(greenLedPin, greenLed*ledBrightnes);
      analogWrite(blueLedPin, blueLed*ledBrightnes);
    } break;
    case 2: { // 2 - rainbow
      
    }
  }
//  delay(30);
}

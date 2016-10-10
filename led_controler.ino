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
#define encoder3Pin1 9
#define encoder3Pin2 10

// LED current color
unsigned short redLed = 255;
unsigned short greenLed = 255;
unsigned short blueLed = 255;

// Encoder variables
  // Encoder 1
  short encoder1Last = low;
  short encoder1New = low;
  // Encoder 2
  short encoder2Last = low;
  short encoder2New = low;
  // Encoder 3
  short encoder3Last = low;
  short encoder3New = low;

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

  // pin setup for ENCODERs
  pinMode(encoder1Pin1, INPUT);
  pinMode(encoder1Pin2, INPUT);
  pinMode(encoder2Pin1, INPUT);
  pinMode(encoder2Pin2, INPUT);
  pinMode(encoder3Pin1, INPUT);
  pinMode(encoder3Pin2, INPUT);

}

void loop() {
  encoder1New = digitalRead(encoder1Pin1);
  if(encoder1Last == LOW && encoder1New == HIGH) {
    if(digitalRead(encoder1Pin2) == LOW) {
      // rotated back
    } else {
      // rotated forward
    }
    encoder1Last = encoder1New;
    continue; //TODO: that works ? 
  }
  encoder2New = digitalRead(encoder2Pin1);
  if(encoder2Last == LOW && encoder2New == HIGH) {
    if(digitalRead(encoder2Pin2) == LOW) {
      // rotated back
    } else {
      // rotated forward
    }
    encoder2Last = encoder2New;
  }
  encoder3New = digitalRead(encoder3Pin1);
  if(encoder3Last == LOW && encoder3New == HIGH) {
    if(digitalRead(encoder3Pin2) == LOW) {
      // rotated back
    } else {
      // rotated forward
    }
    encoder3Last = encoder3New;
  }
  switch(ledMode) { // LED controlls
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

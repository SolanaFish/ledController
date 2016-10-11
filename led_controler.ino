// LED PINS
#define redLedPin 3
#define greenLedPin 5
#define blueLedPin 6

// LED COLORS
#define RED 0
#define GREEN 1
#define BLUE 2

// BUTTON PINS
#define buttonPin2 14
#define buttonPin3 15
#define buttonPin1 16

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
  short encoder1Last = LOW;
  short encoder1New = LOW;
  // Encoder 2
  short encoder2Last = LOW;
  short encoder2New = LOW;
  // Encoder 3
  short encoder3Last = LOW;
  short encoder3New = LOW;

// LED current mode
#define MODECOLOR 0
#define MODEBREATHING 1
#define MODERAINBOW 2

unsigned short ledMode = MODECOLOR;

// LED brightnes
float ledBrightnes = 1;
float brightnesStep = -0.05;
float brightnesStepManual = 0.05;
unsigned short ledColorStepManual = 10;
unsigned short encoder1Color = RED;

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
///////////////////////////////////////////////////////////////
//ENCODER CONTROL
///////////////////////////////////////////////////////////////
// LED COLOR CONTROL
  encoder1New = digitalRead(encoder1Pin1);
  if(encoder1Last == LOW && encoder1New == HIGH) {
    if(digitalRead(encoder1Pin2) == LOW) {
     switch (encoder1Color) {
         case RED: {
             redLed -= ledColorStepManual;
         } break;
         case GREEN: {
             greenLed -= ledColorStepManual;
         } break;
         case BLUE: {
             blueLed -= ledColorStepManual;
         } break;
     }
    } else {
        switch (encoder1Color) {
            case RED: {
                redLed += ledColorStepManual;
            } break;
            case GREEN: {
                greenLed += ledColorStepManual;
            } break;
            case BLUE: {
                blueLed += ledColorStepManual;
            } break;
        }
    }
    encoder1Last = encoder1New;

    analogWrite(redLedPin, redLed*ledBrightnes);
    analogWrite(greenLedPin, greenLed*ledBrightnes);
    analogWrite(blueLedPin, blueLed*ledBrightnes);

    return;
  }
  // LED brightness control
  encoder2New = digitalRead(encoder2Pin1);
  if(encoder2Last == LOW && encoder2New == HIGH) {
    if(digitalRead(encoder2Pin2) == LOW) {
        if(ledBrightnes > brightnesStepManual){
            ledBrightnes -= brightnesStepManual;
        }
    } else {
        if (ledBrightnes < 1 - brightnesStepManual) {
            ledBrightnes += brightnesStepManual;
        }
    }
    encoder2Last = encoder2New;

    analogWrite(redLedPin, redLed*ledBrightnes);
    analogWrite(greenLedPin, greenLed*ledBrightnes);
    analogWrite(blueLedPin, blueLed*ledBrightnes);

    return;
  }
  // Volume control
  encoder3New = digitalRead(encoder3Pin1);
  if(encoder3Last == LOW && encoder3New == HIGH) {
    if(digitalRead(encoder3Pin2) == LOW) {
      // rotated back
    } else {
      // rotated forward
    }
    encoder3Last = encoder3New;
    return;
  }
///////////////////////////////////////////////////////////////
//BUTTON CONTROL
///////////////////////////////////////////////////////////////
  if(digitalRead(buttonPin1) == HIGH) {
    while (digitalRead(buttonPin1) == HIGH) {
      delay(1); // TODO: try without delay
    }
    // button action
    return;
  }

  if(digitalRead(buttonPin2) == HIGH) {
    while (digitalRead(buttonPin2) == HIGH) {
      delay(1); // TODO: try without delay
    }
    if(ledMode == MODERAINBOW) {
        ledMode = MODECOLOR;
    } else {
        ledMode++;
    }
    return;
  }

  if(digitalRead(buttonPin1) == HIGH) {
    while (digitalRead(buttonPin2) == HIGH) {
      delay(1); // TODO: try without delay
    }
    if(encoder1Color == BLUE) {
        encoder1Color = RED;
    } else {
        encoder1Color++;
    }
    return;
  }
///////////////////////////////////////////////////////////////
//LED CONTROL
///////////////////////////////////////////////////////////////
  switch(ledMode) { // LED controls
    case MODEBREATHING: { // 1 - breathing
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
    case MODERAINBOW: { // 2 - rainbow

    }
  }
//  delay(30);
}

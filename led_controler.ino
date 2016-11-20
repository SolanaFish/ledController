// LED PINS
#define redLedPin 9
#define greenLedPin 5
#define blueLedPin 6

// LED COLORS
#define RED 0
#define GREEN 1
#define BLUE 2

// BUTTON PINS
#define buttonPin2 14
// #define buttonPin3 15
#define buttonPin1 16

// ENCODER PINS
#define encoder1Pin1 2
#define encoder1Pin2 4
#define encoder2Pin1 7
#define encoder2Pin2 8
#define encoder3Pin1 3
#define encoder3Pin2 10

// RGB INDICATOR PINS
#define INDICATOR_POWER 15
#define INDICATOR_R A0
#define INDICATOR_G A1
#define INDICATOR_B A2


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
float brightnesStep = -0.005;
float brightnesStepManual = 0.01;
unsigned short ledColorStepManual = 5;
unsigned short encoder1Color = RED;

// Rainbowmode
unsigned long lastUpdate = millis();
unsigned int changeEvery = 5*1000; // In milis
unsigned short lastR = 0;
unsigned short lastG = 0;
unsigned short lastB = 0;

void setup() {
  // pin setup for LED strip
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  // pin setup for BUTTONs
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  // pinMode(buttonPin3, INPUT);

  // pin setup for ENCODERs
  pinMode(encoder1Pin1, INPUT);
  pinMode(encoder1Pin2, INPUT);
  pinMode(encoder2Pin1, INPUT);
  pinMode(encoder2Pin2, INPUT);
  pinMode(encoder3Pin1, INPUT);
  pinMode(encoder3Pin2, INPUT);

  // pin setup for INDICATOR led
  pinMode(INDICATOR_POWER, OUTPUT);
  pinMode(INDICATOR_R, OUTPUT);
  pinMode(INDICATOR_G, OUTPUT);
  pinMode(INDICATOR_B, OUTPUT);
  digitalWrite(INDICATOR_POWER, HIGH);
  // Set red as a default color for INDICATOR led
  digitalWrite(INDICATOR_R, LOW);
  digitalWrite(INDICATOR_G, HIGH);
  digitalWrite(INDICATOR_B, HIGH);

  // lightup leds in default color
  analogWrite(redLedPin, redLed*ledBrightnes);
  analogWrite(greenLedPin, greenLed*ledBrightnes);
  analogWrite(blueLedPin, blueLed*ledBrightnes);

  // rainbow mode setup
  randomSeed(analogRead(A3));

  Serial.begin(9600);
}

void loop() {
///////////////////////////////////////////////////////////////
//ENCODER CONTROL
///////////////////////////////////////////////////////////////
  encoder1New = digitalRead(encoder1Pin1);
  encoder2New = digitalRead(encoder2Pin1);
  encoder3New = digitalRead(encoder3Pin1);
  // LED COLOR CONTROL
  if(encoder1New == LOW) {
      while(digitalRead(encoder1Pin1) == LOW){
      }

      if(digitalRead(encoder1Pin2) == LOW) {
       switch (encoder1Color) {
           case RED: {
               if(redLed > ledColorStepManual) {
                   redLed -= ledColorStepManual;
               }
           } break;
           case GREEN: {
               if(greenLed > ledColorStepManual) {
                   greenLed -= ledColorStepManual;
               }
           } break;
           case BLUE: {
               if(blueLed > ledColorStepManual) {
                   blueLed -= ledColorStepManual;
               }
           } break;
       }
      } else {
          switch (encoder1Color) {
              case RED: {
                  if(redLed < 255 - ledColorStepManual) {
                      redLed += ledColorStepManual;
                  }
              } break;
              case GREEN: {
                  if(greenLed < 255 - ledColorStepManual) {
                      greenLed += ledColorStepManual;
                  }
              } break;
              case BLUE: {
                  if(blueLed < 255 - ledColorStepManual) {
                      blueLed += ledColorStepManual;
                  }
              } break;
          }
      }
      analogWrite(redLedPin, redLed*ledBrightnes);
      analogWrite(greenLedPin, greenLed*ledBrightnes);
      analogWrite(blueLedPin, blueLed*ledBrightnes);
      return;
  }

  // LED brightness
  if(encoder2New == LOW) {
      while(digitalRead(encoder2Pin1) == LOW){
      }
      if(ledMode == MODECOLOR) {
          if(digitalRead(encoder2Pin2) == LOW) {
              if(ledBrightnes > brightnesStepManual){
                  ledBrightnes -= brightnesStepManual;
              }
          } else {
              if (ledBrightnes < 1 - brightnesStepManual) {
                  ledBrightnes += brightnesStepManual;
              }
          }
          analogWrite(redLedPin, redLed*ledBrightnes);
          analogWrite(greenLedPin, greenLed*ledBrightnes);
          analogWrite(blueLedPin, blueLed*ledBrightnes);
          return;
      }
      if(ledMode == MODEBREATHING) {
          if(digitalRead(encoder2Pin2) == LOW) {
              brightnesStep = brightnesStep*0.9;
          } else {
              brightnesStep = brightnesStep*1.1;
          }
          return;
      }

  }

  // Volume control
  // if(encoder3New == LOW) {
  //     while(digitalRead(encoder3Pin1) == LOW){
  //     }
  //     while(true) {
  //         Serial.println("test");
  //         delay(50);
  //     }
  //     if(digitalRead(encoder3Pin2) == LOW) {
  //       // rotated back
  //     } else {
  //       // rotated forward
  //     }
  //     return;
  // }

///////////////////////////////////////////////////////////////
//BUTTON CONTROL
///////////////////////////////////////////////////////////////

// Active color
    if(digitalRead(buttonPin1) == HIGH) {
        while (digitalRead(buttonPin1) == HIGH) {
        }
        if(ledMode == MODECOLOR) {
            if(encoder1Color == BLUE) {
                encoder1Color = RED;
            } else {
                encoder1Color++;
            }
            // Change color of indicator led
            switch(encoder1Color) {
                case RED: {
                    digitalWrite(INDICATOR_R, LOW);
                    digitalWrite(INDICATOR_G, HIGH);
                    digitalWrite(INDICATOR_B, HIGH);
                }break;
                case GREEN: {
                    digitalWrite(INDICATOR_R, HIGH);
                    digitalWrite(INDICATOR_G, LOW);
                    digitalWrite(INDICATOR_B, HIGH);
                }break;
                case BLUE: {
                    digitalWrite(INDICATOR_R, HIGH);
                    digitalWrite(INDICATOR_G, HIGH);
                    digitalWrite(INDICATOR_B, LOW);
                }break;
            }
        }
        if(ledMode == MODERAINBOW) {
            lastUpdate -= changeEvery;
        }
        // delay for debouncing (500 is a lot, and you can't spam button)
        delay(500);
        while (digitalRead(buttonPin1) == HIGH) {
        }
        return;
    }
// LED mode
  if(digitalRead(buttonPin2) == HIGH) {
    while (digitalRead(buttonPin2) == HIGH) {
    }
    if(ledMode == MODERAINBOW) {
        ledMode = MODECOLOR;
        encoder1Color = RED;
        digitalWrite(INDICATOR_R, LOW);
        digitalWrite(INDICATOR_G, HIGH);
        digitalWrite(INDICATOR_B, HIGH);
        analogWrite(redLedPin, redLed*ledBrightnes);
        analogWrite(greenLedPin, greenLed*ledBrightnes);
        analogWrite(blueLedPin, blueLed*ledBrightnes);
    } else {
        if(ledMode == MODECOLOR) {
            ledMode = MODEBREATHING;
            digitalWrite(INDICATOR_R, HIGH);
            digitalWrite(INDICATOR_G, LOW);
            digitalWrite(INDICATOR_B, LOW);
        } else {
            if(ledMode == MODEBREATHING) {
                ledMode = MODERAINBOW;
                digitalWrite(INDICATOR_R, LOW);
                digitalWrite(INDICATOR_G, LOW);
                digitalWrite(INDICATOR_B, LOW);
            }
        }
    }
  // delay for debouncing
  delay(500);
    return;
  }

  // if(digitalRead(buttonPin3) == HIGH) {
  //   while (digitalRead(buttonPin3) == HIGH) {
  //   }
  //   if(encoder1Color == BLUE) {
  //       encoder1Color = RED;
  //   } else {
  //       encoder1Color++;
  //   }
  // delay for debouncing
  // delay(500);
  //   return;
  // }
///////////////////////////////////////////////////////////////
//LED CONTROL
///////////////////////////////////////////////////////////////
    if(ledMode != MODECOLOR) {
        switch(ledMode) { // LED controls
            case MODEBREATHING: { // 1 - breathing
                ledBrightnes += brightnesStep;
                if(brightnesStep > 0) {
                    if (ledBrightnes >= 1) {
                        brightnesStep = -1*brightnesStep;
                        ledBrightnes = 1;
                    }
                } else {
                    if (ledBrightnes <= 0) {
                        brightnesStep = -1*brightnesStep;
                        ledBrightnes = 0;
                    }
                }
                analogWrite(redLedPin, redLed*ledBrightnes);
                analogWrite(greenLedPin, greenLed*ledBrightnes);
                analogWrite(blueLedPin, blueLed*ledBrightnes);
                delay(10);
            } break;
            case MODERAINBOW: { // 2 - rainbow
                if(millis() - lastUpdate > changeEvery) {
                    transmition(lastR,lastG,lastB,random(256),random(256),random(256));
                    lastUpdate = millis();
                }
            }
        }
    }
}

void transmition(short oldR, short oldG, short oldB, short newR, short newG, short newB) {
    short difR = oldR - newR;
    short difG = oldG - newG;
    short difB = oldB - newB;
    double stepR = difR / 20;
    double stepG = difG / 20;
    double stepB = difB / 20;
    lastR = newR;
    lastG = newG;
    lastB = newB;
    for(int i = 0; i < 20; ++i ) {
        analogWrite(redLedPin, (int)(oldR - (i*stepR)));
        analogWrite(greenLedPin, (int)(oldG - (i*stepG)));
        analogWrite(blueLedPin, (int)(oldG - (i*stepG)));
        delay(25);
    }
    analogWrite(redLedPin, newR);
    analogWrite(greenLedPin, newG);
    analogWrite(blueLedPin, newB);
}

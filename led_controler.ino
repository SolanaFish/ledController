// INCLUDES
    #include <DS1307RTC.h>
    #include <ArduinoJson.h>
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
    // #define buttonPin3 15 // currently used as an indicator power
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

// LED current mode
    #define MODECOLOR 0
    #define MODEBREATHING 1
    #define MODERAINBOW 2
    unsigned short ledMode = MODECOLOR;

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



// Mode color
    float ledBrightnes = 1;
    float brightnesStepManual = 0.01;
    unsigned short ledColorStepManual = 5;
    unsigned short encoder1Color = RED;

// Mode breathing
    float brightnesStep = -0.005;


// Rainbowmode
    unsigned long lastUpdate = millis();
    unsigned int changeEvery = 5*1000; // In milis
    unsigned short lastG = 0;
    unsigned short lastR = 0;
    unsigned short lastB = 0;
    unsigned int transitionSteps = 500;

// Alarm
    unsigned short alarmH;
    unsigned short alarmM;
    boolean alarmSet = false;
    unsigned short alarmMode = MODECOLOR;
    unsigned short alarmR = 255;
    unsigned short alarmG = 255;
    unsigned short alarmB = 255;

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

    // serial setup
        Serial.begin(9600);
}

void loop() {
///////////////////////////////////////////////////////////////
//Main switc of the program
///////////////////////////////////////////////////////////////
    encoder1New = digitalRead(encoder1Pin1);
    encoder2New = digitalRead(encoder2Pin1);
    encoder3New = digitalRead(encoder3Pin1);

    // Change functionality depending on mode we are currently in
    switch(ledMode) {
        case MODECOLOR: {
            // Encoder 1
            if(encoder1New == LOW) {
                while(digitalRead(encoder1Pin1) == LOW){
                }

                // LED COLOR CONTROL
                if(digitalRead(encoder1Pin2) == LOW) { // Rotated counter-clockwise
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
                } else { // Rotated clockwise
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
            // Encoder 2
            if(encoder2New == LOW) {
                while(digitalRead(encoder2Pin1) == LOW){
                }
                // LED brightness
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
            // Button 1
            if(digitalRead(buttonPin1) == HIGH) {
                while (digitalRead(buttonPin1) == HIGH) {
                }
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
                // delay for debouncing (500 is a lot, and you can't spam button)
                delay(500);
                while (digitalRead(buttonPin1) == HIGH) {
                }
                return;
            }
        } break;
        case MODEBREATHING: {
            // Encoder 1
            if(encoder1New == LOW) {
                while(digitalRead(encoder1Pin1) == LOW){
                }
                analogWrite(redLedPin, redLed);
                analogWrite(greenLedPin, greenLed);
                analogWrite(blueLedPin, blueLed);

                // LED COLOR CONTROL
                if(digitalRead(encoder1Pin2) == LOW) { // Rotated counter-clockwise
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
                } else { // Rotated clockwise
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
                analogWrite(redLedPin, redLed);
                analogWrite(greenLedPin, greenLed);
                analogWrite(blueLedPin, blueLed);
                return;
            }
            // Encoder 2
            if(encoder2New == LOW) {
                while(digitalRead(encoder2Pin1) == LOW){
                }
                // BREATHING speed
                if(digitalRead(encoder2Pin2) == LOW) {
                    brightnesStep = brightnesStep*0.9;
                } else {
                    brightnesStep = brightnesStep*1.1;
                }
                return;
            }
            // Button 1
            if(digitalRead(buttonPin1) == HIGH) {
                while (digitalRead(buttonPin1) == HIGH) {
                }
                if(encoder1Color == BLUE) {
                    encoder1Color = RED;
                } else {
                    encoder1Color++;
                }
                // delay for debouncing (500 is a lot, and you can't spam button)
                delay(500);
                while (digitalRead(buttonPin1) == HIGH) {
                }
                return;
            }
        } break;
        case MODERAINBOW: {
            // Encoder 1
            if(encoder1New == LOW) {
                while(digitalRead(encoder1Pin1) == LOW){
                }
                // BREATHING speed
                if(digitalRead(encoder1Pin2) == LOW) {
                    changeEvery = changeEvery*0.9;
                } else {
                    changeEvery = changeEvery*1.1;
                }
                return;
            }
            // Encoder 2
            if(encoder2New == LOW) {
                while(digitalRead(encoder2Pin1) == LOW){
                }
                // BREATHING speed
                if(digitalRead(encoder2Pin2) == LOW) {
                    transitionSteps = transitionSteps*0.9;
                } else {
                    transitionSteps = transitionSteps*1.1;
                }
                return;
            }
            // Button 1
            if(digitalRead(buttonPin1) == HIGH) {
                while (digitalRead(buttonPin1) == HIGH) {
                }
                // Update now
                lastUpdate -= changeEvery;
                // delay for debouncing (500 is a lot, and you can't spam button)
                delay(500);
                while (digitalRead(buttonPin1) == HIGH) {
                }
                return;
            }
        } break;
    }
///////////////////////////////////////////////////////////////
// Controls that don't depend on mode
///////////////////////////////////////////////////////////////

  // ENCODER 3
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

// Button 1 control - change led mode
  if(digitalRead(buttonPin2) == HIGH) {
    while (digitalRead(buttonPin2) == HIGH) {
    }
    if(ledMode == MODERAINBOW) {
        ledMode = MODECOLOR;
        encoder1Color = RED;
        ledBrightnes = 1;
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

    ///////////////////////////////////////////////////////////////
    // Alarm control
    ///////////////////////////////////////////////////////////////
    if(alarmSet) {
        if(hour() == alarmH) {
            if(minute() >= alarmM) { // if past the time of alarm
                alarmSet = false;
                if(alarmMode == MODECOLOR) {
                    ledMode = MODECOLOR;
                    encoder1Color = RED;
                    ledBrightnes = 1;
                    redLed = alarmR;
                    greenLed = alarmG;
                    blueLed = alarmB;
                    digitalWrite(INDICATOR_R, LOW);
                    digitalWrite(INDICATOR_G, HIGH);
                    digitalWrite(INDICATOR_B, HIGH);
                    analogWrite(redLedPin, redLed*ledBrightnes);
                    analogWrite(greenLedPin, greenLed*ledBrightnes);
                    analogWrite(blueLedPin, blueLed*ledBrightnes);
                } else {
                    if(alarmMode == MODEBREATHING) {
                        ledMode = MODEBREATHING;
                        redLed = alarmR;
                        greenLed = alarmG;
                        blueLed = alarmB;
                        digitalWrite(INDICATOR_R, HIGH);
                        digitalWrite(INDICATOR_G, LOW);
                        digitalWrite(INDICATOR_B, LOW);
                    } else {
                        if(alarmMode == MODERAINBOW) {
                            ledMode = MODERAINBOW;
                            digitalWrite(INDICATOR_R, LOW);
                            digitalWrite(INDICATOR_G, LOW);
                            digitalWrite(INDICATOR_B, LOW);
                        }
                    }
                }
            }
        }
    }

    ///////////////////////////////////////////////////////////////
    //Serial control
    ///////////////////////////////////////////////////////////////
    if(Serial.available()) {
        String command = Serial.readStringUntil(' ');
        if(command == "mode") { // Changing mode
            String incomingMode = Serial.readStringUntil(' ');
            if(incomingMode == "color") {
                ledMode = MODECOLOR;
                encoder1Color = RED;
                ledBrightnes = 1;
                digitalWrite(INDICATOR_R, LOW);
                digitalWrite(INDICATOR_G, HIGH);
                digitalWrite(INDICATOR_B, HIGH);
                analogWrite(redLedPin, redLed*ledBrightnes);
                analogWrite(greenLedPin, greenLed*ledBrightnes);
                analogWrite(blueLedPin, blueLed*ledBrightnes);
                Serial.println("ok mode color");
            } else if(incomingMode == "breathing") {
                ledMode = MODEBREATHING;
                digitalWrite(INDICATOR_R, HIGH);
                digitalWrite(INDICATOR_G, LOW);
                digitalWrite(INDICATOR_B, LOW);
                Serial.println("ok mode breathing");
            } else if(incomingMode == "random") {
                ledMode = MODERAINBOW;
                digitalWrite(INDICATOR_R, LOW);
                digitalWrite(INDICATOR_G, LOW);
                digitalWrite(INDICATOR_B, LOW);
                Serial.println("ok mode random");
            } else {
                Serial.println("err mode " + incomingMode);
            }
        } else if(command == "color"){ // changing current color
            String sr = Serial.readStringUntil(' ');
            String sg = Serial.readStringUntil(' ');
            String sb = Serial.readStringUntil(' ');
            int r = sr.toInt();
            int g = sg.toInt();
            int b = sb.toInt();
            if(r >= 0 && g >= 0 && b >= 0) {
                redLed = r;
                greenLed = g;
                blueLed = b;
                if(ledMode == MODECOLOR) {
                    analogWrite(redLedPin, redLed*ledBrightnes);
                    analogWrite(greenLedPin, greenLed*ledBrightnes);
                    analogWrite(blueLedPin, blueLed*ledBrightnes);
                }
                Serial.println("ok set color");
            } else {
                Serial.println("err set color");
            }
        } else if(command == "brightnes"){ // setting brightnes
            String sb = Serial.readStringUntil(' ');
            float b = sb.toFloat();
            if (b >= 0 && b <= 1) {
                ledBrightnes = (double)b;
                if(ledMode == MODECOLOR) {
                    analogWrite(redLedPin, redLed*ledBrightnes);
                    analogWrite(greenLedPin, greenLed*ledBrightnes);
                    analogWrite(blueLedPin, blueLed*ledBrightnes);
                }
                Serial.println("ok set brightnes");
            } else {
                Serial.println("err set brightnes");
            }
        } else if(command == "alarm"){ // setting alarm
            String state = Serial.readStringUntil(' ');
            if(state = "on") { // read if on or off
                String sh = Serial.readStringUntil(' '); // read hours
                String sm = Serial.readStringUntil(' '); // read minutes
                int h = sh.toInt();
                int m = sm.toInt();
                if(h >= 0 && m >= 0 && h < 24 && m < 60) { // if time ok
                    String alarmS = Serial.readStringUntil(' '); // read mode of alarm
                    unsigned short newAlarmMode = alarmS.toInt();
                    if(newAlarmMode >= 0 && newAlarmMode <= 3) { // if mode ok
                        String sr = Serial.readStringUntil(' '); // read red
                        String sg = Serial.readStringUntil(' '); // read green
                        String sb = Serial.readStringUntil(' '); // read blue
                        unsigned short ir = sr.toInt();
                        unsigned short ig = sg.toInt();
                        unsigned short ib = sb.toInt();
                        if(ir > 0 && ir < 256 && ig > 0 && ig < 256 && ib > 0 && ib < 256) { // if colors ok
                            // set alarm
                            alarmH = h;
                            alarmM = m;
                            alarmR = ir;
                            alarmG = ig;
                            alarmB = ib;
                            alarmMode = newAlarmMode;
                            alarmSet = true;
                            Serial.println("ok set alarm on");
                        } else {
                            Serial.println("err set alarm on colors");
                            Serial.println(ir);
                            Serial.println(ig);
                            Serial.println(ib);
                        }
                    } else {
                        Serial.println("err set alarm on mode");
                    }
                } else {
                    Serial.println("err set alarm on time");
                }
                if(timeStatus() == timeNotSet && alarmSet) { // If time wasn't set...
                    Serial.println("time"); // Send reqest for current time and...
                    while(!Serial.available()) { // Wait for response
                    }
                    long currentTime = Serial.parseInt();
                    if(currentTime > 0) {
                        setTime(currentTime);
                        Serial.println("ok set time");
                    } else {
                        Serial.println("err set time");
                    }
                }
            } else {
                alarmSet = false;
                Serial.println("ok set alarm off");
            }
        } else if(command == "json") {
            StaticJsonBuffer<512> jsonBuffer;
            JsonObject& root = jsonBuffer.createObject();
            root["mode"] = ledMode;
            root["brightnes"] = ledBrightnes;
            root["brightnesStep"] = brightnesStep;
            JsonObject& colorData = root.createNestedObject("colors");
            colorData["red"] = redLed;
            colorData["green"] = greenLed;
            colorData["blue"] = blueLed;
            JsonObject& rainbowData = root.createNestedObject("rainbow");
            rainbowData["lastUpdate"] = lastUpdate;
            rainbowData["changeEvery"] = changeEvery;
            rainbowData["transitionSteps"] = transitionSteps;
            if(alarmSet) {
                JsonObject& alarmData = root.createNestedObject("alarm");
                alarmData["hour"] = alarmH;
                alarmData["minute"] = alarmM;
                alarmData["alarmMode"] = alarmMode;
                JsonObject& alarmColors = alarmData.createNestedObject("colors");
                alarmData["red"] = alarmR;
                alarmData["green"] = alarmG;
                alarmData["blue"] = alarmB;
            } else {
                root["alarm"] = false;
            }
            root.printTo(Serial);
        } else {
            Serial.println("err " + command);
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

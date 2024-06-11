#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>

float delaySpeed = 1000;
int ranLED;
int currentLED;
int pointTotal = 0;
bool slowDown = false;
float saveSpeed = 0;
int lifeLineCount = 3;
int correctFreq = 300;

int switchPin = 7;
int rightButtonPin = 4;
int leftButtonPin = 5;

volatile bool buttonFlag = false;
volatile bool switchFlag = false;
bool whileFlag = false;

bool switchState = false;

const uint8_t spFAIL[] PROGMEM = { 0x04, 0x98, 0x3E, 0x8D, 0x03, 0x1C, 0xD0, 0x80, 0x07, 0x4A, 0xBF, 0x54, 0x9B, 0x3A, 0x79, 0x9C, 0xCD, 0xAA, 0x9B, 0x0F, 0x31, 0x8F, 0x37, 0xB7, 0xBE, 0xCD, 0x6A, 0x47, 0x2A, 0x66, 0xB3, 0xB7, 0xB3, 0xDB, 0x6B, 0x5F, 0xC7, 0x56, 0x44, 0x58, 0x8E, 0x76, 0xAA, 0x7B, 0xD8, 0x33, 0xB9, 0x32, 0xD7, 0x3C, 0xF9, 0x0C, 0x67, 0xD4, 0x13, 0x9E, 0x98, 0xC7, 0x5F, 0xEE, 0x49, 0x7C, 0xAA, 0x8D, 0xF3, 0xF9, 0xF7, 0xFF, 0x01 };

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
  randomSeed(analogRead(0));
  attachInterrupt(digitalPinToInterrupt(rightButtonPin), buttonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(leftButtonPin), buttonISR, RISING);
  attachInterrupt(digitalPinToInterrupt(switchPin), switchISR, CHANGE);
}

void loop() {
  ranLED = random(10);  //Selects the random LED

  CircuitPlayground.setPixelColor(ranLED, 255, 0, 0);

  delay(250);

  while (true) {  //While loop to repeat the for loop
    for (int i = 0; i < 10; i++) {  //For loop for the circling LED
      currentLED = i;
      CircuitPlayground.setPixelColor(ranLED, 255, 0, 0);
      CircuitPlayground.setPixelColor(i, 0, 0, 255);
      delay(delaySpeed);
      CircuitPlayground.clearPixels();

      if (buttonFlag) {  //Sets up the break out of the while loop if button pressed
        buttonFlag = false;
        whileFlag = true;
        break;
      }

      if (switchFlag) {  //Sets up the break out of the while loop if switch changed
        switchFlag = false;

        if (lifeLineCount > 0) {  //Slows down the circling LED
          lifeLineCount--;
          slowDown = true;
          saveSpeed = delaySpeed;
          delaySpeed *= 2;
        }
      }

      if (i == 9) {
        i = -1;
      }
    }

    if (whileFlag) {
      break;
    }
  }

  if (slowDown) {  //Resets speed after using the switch
    slowDown = false;
    delaySpeed = saveSpeed;
  }

  if (currentLED == ranLED) {  //Keeps track of the game score
    pointTotal++;
    correctFreq += 5;
    Serial.print("Points: ");
    Serial.println(pointTotal);
    CircuitPlayground.playTone(correctFreq, 100);
    delaySpeed *= 0.9;
  } else {  //Ends the game when the player fails
    CircuitPlayground.speaker.say(spFAIL);
    Serial.println("GAME OVER");
    Serial.print("Final Score: ");
    Serial.println(pointTotal);
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("Press reset to try again!");
    Serial.println();
    Serial.println();
    Serial.println();

    while (true) {  //Infinite loop indicating the end of the game
      for (int i = 0; i < 10; i++) {
        CircuitPlayground.setPixelColor(i, 0, 255, 0);
        delay(delaySpeed);
        CircuitPlayground.clearPixels();
      }
    }
  }
}

void buttonISR() {  //Button interupt
  buttonFlag = true;
}

void switchISR() {  //Switch interupt
  switchFlag = true;
}
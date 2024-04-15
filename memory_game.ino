// ALL CODE COPYRIGHT SING DEVELOPMENTS. PLEASE ASK THE OWNER TO DISTRUBUTE!

#include <Arduino.h>

const int buttonRed = 2;
const int buttonGreen = 3;
const int buttonBlue = 4;
const int buttonYellow = 5;

const int ledRed = 6;
const int ledGreen = 7;
const int ledBlue = 8;
const int ledYellow = 9;

int sequence[100];
int sequenceLength = 0;
int currentIndex = 0;

bool playerInput = false;

void setup() {
  pinMode(buttonRed, INPUT_PULLUP);
  pinMode(buttonGreen, INPUT_PULLUP);
  pinMode(buttonBlue, INPUT_PULLUP);
  pinMode(buttonYellow, INPUT_PULLUP);

  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledYellow, OUTPUT);

  addRandomLight();
}

void loop() {
  if (!playerInput) {
    displaySequence();
    delay(1000); 
    playerInput = true;
  } else {
    // Player input
    if (checkInput()) {
      if (currentIndex == sequenceLength) {
        addRandomLight(); 
        playerInput = false; 
        currentIndex = 0; 
      }
    } else {
      gameOver();
    }
  }
}

void generateSequence() {
  for (int i = 0; i < sizeof(sequence) / sizeof(sequence[0]); i++) {
    sequence[i] = random(4); 
  }
  sequenceLength = 1;
}

void displaySequence() {
  for (int i = 0; i < sequenceLength; i++) {
    switch (sequence[i]) {
      case 0:
        digitalWrite(ledRed, HIGH);
        delay(500);
        digitalWrite(ledRed, LOW);
        delay(200);
        break;
      case 1:
        digitalWrite(ledGreen, HIGH);
        delay(500);
        digitalWrite(ledGreen, LOW);
        delay(200);
        break;
      case 2:
        digitalWrite(ledBlue, HIGH);
        delay(500);
        digitalWrite(ledBlue, LOW);
        delay(200);
        break;
      case 3:
        digitalWrite(ledYellow, HIGH);
        delay(500);
        digitalWrite(ledYellow, LOW);
        delay(200);
        break;
    }
    delay(100); 
  }
}

bool checkInput() {
  if (digitalRead(buttonRed) == LOW && sequence[currentIndex] == 0) {
    currentIndex++;
    delay(200); 
    return true;
  } else if (digitalRead(buttonGreen) == LOW && sequence[currentIndex] == 1) {
    currentIndex++;
    delay(200); 
    return true;
  } else if (digitalRead(buttonBlue) == LOW && sequence[currentIndex] == 2) {
    currentIndex++;
    delay(200); 
    return true;
  } else if (digitalRead(buttonYellow) == LOW && sequence[currentIndex] == 3) {
    currentIndex++;
    delay(200); 
    return true;
  }
  
  return false; 
}

void addRandomLight() {
  sequence[sequenceLength] = random(4); 
  sequenceLength++;
}

void gameOver() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledBlue, HIGH);
    digitalWrite(ledYellow, HIGH);
    delay(500);
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledBlue, LOW);
    digitalWrite(ledYellow, LOW);
    delay(500);
  }
  sequenceLength = 0;
  currentIndex = 0;
  playerInput = false;
}

// ALL CODE COPYRIGHT SING DEVELOPMENTS. PLEASE ASK THE OWNER TO DISTRUBUTE!

#include <Arduino.h>

// Define button pins
const int buttonRed = 2;
const int buttonGreen = 3;
const int buttonBlue = 4;
const int buttonYellow = 5;

// Define LED pins
const int ledRed = 6;
const int ledGreen = 7;
const int ledBlue = 8;
const int ledYellow = 9;

// Define array to store the sequence
int sequence[100];
int sequenceLength = 0;
int currentIndex = 0;

// Flag to indicate if it's player's turn to input
bool playerInput = false;

void setup() {
  // Initialize button pins as inputs
  pinMode(buttonRed, INPUT_PULLUP);
  pinMode(buttonGreen, INPUT_PULLUP);
  pinMode(buttonBlue, INPUT_PULLUP);
  pinMode(buttonYellow, INPUT_PULLUP);

  // Initialize LED pins as outputs
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(ledYellow, OUTPUT);

  // Generate a random sequence
  addRandomLight();
}

void loop() {
  if (!playerInput) {
    // Display sequence to the player
    displaySequence();
    delay(1000); // Delay between displaying sequence and waiting for user input
    playerInput = true;
  } else {
    // Player input
    if (checkInput()) {
      // Player successfully mimics the sequence
      if (currentIndex == sequenceLength) {
        // If the entire sequence is matched
        addRandomLight(); // Add a new random light to the sequence
        playerInput = false; // Switch back to displaying sequence
        currentIndex = 0; // Reset currentIndex for the new sequence
      }
    } else {
      // Player made a mistake
      // Game over
      gameOver();
    }
  }
}

void generateSequence() {
  // Generate random sequence
  for (int i = 0; i < sizeof(sequence) / sizeof(sequence[0]); i++) {
    sequence[i] = random(4); // Random number between 0 and 3
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
    delay(100); // Pause between lights
  }
}

bool checkInput() {
  if (digitalRead(buttonRed) == LOW && sequence[currentIndex] == 0) {
    currentIndex++;
    delay(200); // Debounce delay
    return true;
  } else if (digitalRead(buttonGreen) == LOW && sequence[currentIndex] == 1) {
    currentIndex++;
    delay(200); // Debounce delay
    return true;
  } else if (digitalRead(buttonBlue) == LOW && sequence[currentIndex] == 2) {
    currentIndex++;
    delay(200); // Debounce delay
    return true;
  } else if (digitalRead(buttonYellow) == LOW && sequence[currentIndex] == 3) {
    currentIndex++;
    delay(200); // Debounce delay
    return true;
  }
  
  return false; // If any wrong button is pressed
}

void addRandomLight() {
  sequence[sequenceLength] = random(4); // Random number between 0 and 3
  sequenceLength++;
}

void gameOver() {
  // Game over logic
  // Reset the game or display final score
  // For now, let's just blink all LEDs to indicate game over
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
  // Reset sequence and start over
  sequenceLength = 0;
  currentIndex = 0;
  playerInput = false;
}

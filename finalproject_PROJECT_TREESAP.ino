#include "LedControl.h"
const int SW_pin = 36;
boolean grid[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

boolean bState = 0;
boolean lbState = 0;
unsigned long lastCheck = 0;
int checkInt = 20;
int tempo = 0;
int currentStep = 0;
boolean stepState[8] = { false, false, false, false, false, false, false, false };

LedControl lc = LedControl(12, 11, 10, 1); //10 is to CLOCK, 9 = CS, 8=DIN//

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
  lc.shutdown(0, false); // turn off power saving, enables display
  lc.setIntensity(0, 8); // sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
}

void loop() {
  const int SW_pin = 36;
  const int UD = analogRead(A16);
  const int LR = analogRead(A15);
  int x_translate = map(LR, 1023, 0, 7, -1); //This maps the values//
  int y_translate = map(UD, 0, 1023, 0, 7);
  sequence();
  drawGrid();
  checkButton();
  lc.setLed(0, x_translate, y_translate, true);
  delay(20); //Mess with this delay to get your joystick correct//
  lc.setLed(0, x_translate, y_translate, false);
  delay(20); //Mess with this delay to get your joystick correct//
}

void drawGrid() {
  for (int i = 0; i <= 7; i++) {
    for (int j = 0; j <= 7; j++) {
      if (j == currentStep) {
        lc.setLed(0, i, j, true);
      }
      else{
      lc.setLed(0, i, j, grid[i][j]);
      }
    }
  }
}

void checkButton() {
  const int UD = analogRead(A16);
  const int LR = analogRead(A15);
  int x_translate = map(LR, 1023, 0, 7, -1); //This maps the values//
  int y_translate = map(UD, 0, 1023, 0, 7);
  //  if (millis() < lastCheck + checkInt) return;
  //
  //  lastCheck = millis();

  lbState = bState;
  bState = digitalRead(SW_pin);
  if (lbState == LOW && bState == HIGH) {
    grid[x_translate][y_translate] = !grid[x_translate][y_translate];
  }
}

void sequence() {
  tempo = 150;
  if (millis() > lastCheck + (55350 / (tempo*2))) {  //if its time to go to the next step...
    currentStep = currentStep + 1;         //increment to the next step
    if (currentStep > 7) {
      currentStep = 0;
    }
    if (grid[0][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(60, 127, 1);
    }
    else {
      usbMIDI.sendNoteOff(60, 127, 1);
    }
    if (grid[1][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(61, 127, 1);
    }
    else {
      usbMIDI.sendNoteOff(61, 127, 1);
    }
    if (grid[2][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(62, 127, 1);
    }
    else {
      usbMIDI.sendNoteOff(62, 127, 1);
    }
    if (grid[3][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(63, 127, 1);
    }
    else {
      usbMIDI.sendNoteOff(63, 127, 1);
    }
    if (grid[4][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(64, 127, 1);
    }
    else {
      usbMIDI.sendNoteOff(64, 127, 1);
    }
    if (grid[5][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(65, 127, 1);
    }
    else {
      usbMIDI.sendNoteOff(65, 127, 1);
    }
    if (grid[6][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(66, 127, 1);
    }
    else {
      usbMIDI.sendNoteOff(66, 127, 1);
    }
    if (grid[7][currentStep] == HIGH) {
      usbMIDI.sendNoteOn(67, 127, 1);
    }
    else {
      usbMIDI.sendNoteOff(67, 127, 1);
    }
    lastCheck = millis();               //set lastStepTime to the current time
  }
}

/* Project: LED Cube Code
   Written by: Chloe Trinh
   Date created: 2025.06.12
   Date updated: 2025.06.13
   Description: This code will cycle through different unique led sequences based on the push button pushed
 */

//declare variables for pins
const int columnPins[9] = {5, 7, 8, 9, 10, 11, 12, 13, A3};
const int layerPins[3] = {A0, A1, A2};
const int buttonPins[3] = {2, 3, 4};

//variable to track active sequence
//0 = none, 1 = sequenceOne, 2 = sequenceTwo, 3 = sequenceThree
int activeSequence = 0;

void setup() {
  //setup all column pins as output and low (off)
  for (int i = 0; i < 9; i++) {
    pinMode(columnPins[i], OUTPUT);
    digitalWrite(columnPins[i], LOW);
  }

  //setup all layer pins as output and high (inactive)
  for (int i = 0; i < 3; i++) {
    pinMode(layerPins[i], OUTPUT);
    digitalWrite(layerPins[i], HIGH);
  }

  //setup all button pins 
  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  
   //turns off all LEDs at start
  clearAll();
}

void loop() {
  //checks for button presses using delay then sets sequence if pressed
  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      delay(50);
      //double check - had to add this because it wasn't registering button presses properly
      if (digitalRead(buttonPins[i]) == LOW) {
        activeSequence = i + 1;
        clearAll();
      }
      while (digitalRead(buttonPins[i]) == LOW);
    }
  }

  //runs active sequence
  switch (activeSequence) {
    case 1:
      sequenceOne();
      break;
    case 2:
      sequenceTwo();
      break;
    case 3:
      sequenceThree();
      break;
    default:
      clearAll();
      break;
  }
}

//function to turn off all leds
void clearAll() {
  for (int i = 0; i < 9; i++) digitalWrite(columnPins[i], LOW);
  for (int i = 0; i < 3; i++) digitalWrite(layerPins[i], HIGH);
}

//helps to turn on leds one by one
void light(int layer, int col) {
  clearAll();
  digitalWrite(layerPins[layer], LOW);
  digitalWrite(columnPins[col], HIGH);
}

/*sequence one
this sequence turns on all the corners 
then the edges (not including corners) on layer by layer
then the middle layer by layer
*/
void sequenceOne() {
  //corner pins and center pin
  const int corners[] = {0, 1, 7, 8};
  const int edges[] = {2, 3, 5, 6};
  const int center = 4;
  
  //repeats sequence while active
  while (activeSequence == 1) {
    clearAll();

    //corners
    digitalWrite(layerPins[0], LOW);
    digitalWrite(layerPins[2], LOW);
    for (int i = 0; i < 4; i++) {
      digitalWrite(columnPins[corners[i]], HIGH);
      if (checkButtonPress()) return;
    }

    delay(500);
    clearAll();
    if (checkButtonPress()) return;

    //edges layer by layer
    for (int layer = 0; layer < 3; layer++) {
      digitalWrite(layerPins[layer], LOW);
      for (int i = 0; i < 4; i++) {
        digitalWrite(columnPins[edges[i]], HIGH);
        if (checkButtonPress()) return;
      }
      delay(500);
      clearAll();
      if (checkButtonPress()) return;
    }

    //center LEDS
    for (int layer = 0; layer < 3; layer++) {
      light(layer, center);
      delay(500);
      clearAll();
      if (checkButtonPress()) return;
    }
  }
}

/*sequence 2
some random sequence
*/
void sequenceTwo() {
  //arrays for each face column pins used
  const int topFace[] = {0,1,2,3,4,5,6,7,8};
  const int bottomFace[] = {0,1,2,3,4,5,6,7,8};
  const int leftFace[] = {6,7,8};
  const int rightFace[] = {0,1,2};
  const int frontFace[] = {0,3,6};
  const int backFace[] = {2,5,8};
  
  while (activeSequence == 2) {
    // Top face (layer 2)
    clearAll();
    digitalWrite(layerPins[2], LOW); // Activate top layer
    for (int i = 0; i < 9; i++) {
      digitalWrite(columnPins[topFace[i]], HIGH);
      if (checkButtonPress()) return;
    }
    delay(500);
    if (checkButtonPress()) return;
    
    // Bottom face (layer 0)
    clearAll();
    digitalWrite(layerPins[0], LOW); // Activate bottom layer
    for (int i = 0; i < 9; i++) {
      digitalWrite(columnPins[bottomFace[i]], HIGH);
      if (checkButtonPress()) return;
    }
    delay(500);
    if (checkButtonPress()) return;

    // Left face (all layers)
    clearAll();
    for (int l = 0; l < 3; l++) {
      digitalWrite(layerPins[l], LOW); // Activate all layers
    }
    for (int i = 0; i < 3; i++) {
      digitalWrite(columnPins[leftFace[i]], HIGH);
      if (checkButtonPress()) return;
    }
    delay(500);
    if (checkButtonPress()) return;

    // Right face (all layers)
    clearAll();
    for (int l = 0; l < 3; l++) {
      digitalWrite(layerPins[l], LOW); // Activate all layers
    }
    for (int i = 0; i < 3; i++) {
      digitalWrite(columnPins[rightFace[i]], HIGH);
      if (checkButtonPress()) return;
    }
    delay(500);
    if (checkButtonPress()) return;

    // Front face (all layers)
    clearAll();
    for (int l = 0; l < 3; l++) {
      digitalWrite(layerPins[l], LOW); // Activate all layers
    }
    for (int i = 0; i < 3; i++) {
      digitalWrite(columnPins[frontFace[i]], HIGH);
      if (checkButtonPress()) return;
    }
    delay(500);
    if (checkButtonPress()) return;
    
    // Back face (all layers)
    clearAll();
    for (int l = 0; l < 3; l++) {
      digitalWrite(layerPins[l], LOW); // Activate all layers
    }
    for (int i = 0; i < 3; i++) {
      digitalWrite(columnPins[backFace[i]], HIGH);
      if (checkButtonPress()) return;
    }
    delay(500);
    
    // Light center (layer 1)
    clearAll();
    light(1, 4); // Middle layer, center column
    delay(500);
    if (checkButtonPress()) return;
    
    // Light all LEDs
    clearAll();
    for (int l = 0; l < 3; l++) {
      digitalWrite(layerPins[l], LOW); // Activate all layers
      for (int c = 0; c < 9; c++) {
        digitalWrite(columnPins[c], HIGH); // Light all columns
      }
    }
    delay(500);
    if (checkButtonPress()) return;
  }
}

/*sequence 3
flows downwards through all pins
*/
void sequenceThree() {
  const int flowOrder[] = {4,1,3,5,7,0,2,6,8}; // Center to edges
  while (activeSequence == 3) {
    for (int i = 0; i < 9; i++) {
      for (int l = 0; l < 3; l++) {
        light(l, flowOrder[i]);
        if (checkButtonPress()) return;
        delay(100);
      }
    }
  }
}

//checks for button presses in the middle of sequence
bool checkButtonPress() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      delay(50);
      if (digitalRead(buttonPins[i]) == LOW) {
        activeSequence = i + 1;
        clearAll();
        //if button is pressed
        return true;
      }
    }
  }
  //no button pressed
  return false;
}

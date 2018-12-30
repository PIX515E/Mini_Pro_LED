/*
Created by: PIX515E
Last Edited: 5/12/2013 4:26 PM CST
*/

/* INTENT/TO-DO:
 Mini Pro LED: Functions the same as a professional AV LED would.
 Full spectrum color, less white. (RGB)
 Each LED color (RGB) will be independent and adjustable.
 Ability to strobe at any brightness level visible to the human eye.
 User will be able to program at least one user defined mode.
 Will have at least one automated mode. */

/* Define pin assignments here.
 RGB pins */
const int LED_R = 9;  // Define pin 9 as Red LED.
const int LED_G = 10; // Define pin 10 as Green LED.
const int LED_B = 11; // Define pin 11 as Blue LED.

/*        Button pins */
const int btnOn = 2;     // Define pin 2 as On/Off Button.
const int btnSelect = 4; // Define pin 4 as Select/Menu Button.
const int btnUp = 7;     // Define pin 7 as Up.
const int btnDown = 8;   // Define pin 8 as Down.
const int btnMode = 12;  // Define pin 12 as Mode.

/* Define variables for project use.
 Add variables for additional functions as project evolves here. */

/* The following int variables will be used to define the
 Brightness of each LED color. For additional functionality multiple
 variables are defined by letter(s) and number(s) for each
 color. */

/* brt_X0 will be used as current settings
 for the color and will later be used to
 define the colors for users saved modes. */
int brt_R0 = 255;     // Brightness of Red: Current settings.
int brt_R1 = 255;     // Brightness of Red: Mode 1 settings.
int brt_R2 = 0;       // Brightness of Red: Mode 2 settings.
int brt_R3 = 0;       // Brightness of Red: Mode 3 settings.
int brt_R4 = 128;     // Brightness of Red: Mode 4 settings.
int brt_RS0 = 255;    // Brightness of Red: Strobe brightness for ON settings.
int brt_RS1 = 0;      // Brightness of Red: Strobe brightness for OFF settings.
int brt_RSR = 100;    // Strobe Rate for Red.
int brt_RF0 = 0;      // Brightness of Red: Fade FROM settings.
int brt_RF1 = 255;    // Brightness of Red: Fade TO settings.
int brt_RFR = 1000;     // Fade Rate for Red.

int brt_G0 = 255;     // Brightness of Green: Current settings.
int brt_G1 = 0;       // Brightness of Green: Mode 1 settings.
int brt_G2 = 255;     // Brightness of Green: Mode 2 settings.
int brt_G3 = 0;       // Brightness of Green: Mode 3 settings.
int brt_G4 = 128;     // Brightness of Green: Mode 4 settings.
int brt_GS0 = 255;    // Brightness of Green: Strobe brightness for ON settings.
int brt_GS1 = 0;      // Brightness of Green: Strobe brightness for OFF settings.
int brt_GSR = 100;    // Strobe Rate for Green.
int brt_GF0 = 0;      // Brightness of Green: Fade FROM settings.
int brt_GF1 = 255;    // Brightness of Green: Fade TO settings.
int brt_GFR = 1;     // Fade Rate for Green.

int brt_B0 = 255;     // Brightness of Blue: Current settings.
int brt_B1 = 0;       // Brightness of Blue: Mode 1 settings.
int brt_B2 = 0;       // Brightness of Blue: Mode 2 settings.
int brt_B3 = 255;     // Brightness of Blue: Mode 3 settings.
int brt_B4 = 128;     // Brightness of Blue: Mode 4 settings.
int brt_BS0 = 255;    // Brightness of Blue: Strobe brightness for ON settings.
int brt_BS1 = 0;      // Brightness of Blue: Strobe brightness for OFF settings.
int brt_BSR = 100;    // Strobe Rate for Blue.
int brt_BF0 = 64;      // Brightness of Blue: Fade FROM settings.
int brt_BF1 = 196;    // Brightness of Blue: Fade TO settings.
int brt_BFR = 10;     // Fade Rate for Blue.

int brt_WS0 = 255;    // Brightness of White: Strobe brightness for ON settings.
int brt_WS1 = 0;      // Brightness of White: Strobe brightness for OFF settings.
int brt_WSR = 100;    // Strobe Rate for White.
int brt_WF0 = 0;      // Brightness of White: Fade FROM settings.
int brt_WF1 = 255;    // Brightness of White: Fade TO settings.
int brt_WFR = 10;     // Fade Rate for White.

int valOn = 0;            // Value of On/Off Button.
int valSelect = 0;        // Value of Select/Menu Button.
int valUp = 0;            // Value of Up Button.
int valDown = 0;          // Value of Down Button.
int valMode = 0;          // Value of Mode Button.

int old_valOn = 0;        // old_Value of On/Off Button.
int old_valSelect = 0;    // old_Value of Select/Menu Button.
int old_valUp = 0;        // old_Value of Up Button.
int old_valDown = 0;      // old_Value of Down Button.
int old_valMode = 0;      // old_Value of Mode Button.

int state = 0;            // On/Off state.

int mode = 0;             // Mode state: 0 = User 1-4 = Predefined modes.

int select0 = 0;          /* Select State 1: On/Off
 0 = Off, 1 = On; choose a Color (RGBW). */
int select1 = 0;          /* Select State 2: On/Off
 0 = Off, 1 = On; choose a Modifier Type. */
int select2 = 0;          /* Select State 3: On/Off
 0 = Off, 1 = On; choose between Strobe/Fade Modifiers. */

int level0 = 0;          /* Level 1 Select State: Color (RGBW)
 0 = Off, 1 = Red, 2 = Green, 3 = Blue, 4 = White */
int level1 = 0;          /* Level 2 Select State: Modifier Type
 0 = Off, 1 = Brightness, 2 = Strobe, 3 = Fade */
int level2 = 0;          /* Level 3 Select State: Strobe/Fade Modifiers
 0 = Off, 1 = Strobe On Time, 2 = Strobe Off Time,
 3 = Fade From Color, 4 = Fade To Color, 5 = Fade Time */

const int n = 100;
int t = 0;
int iR = 0;
int iG = 0;
int iB = 0;
int iW = 0;

int i = 0;
float x = 0.003921569;

unsigned long startTime = 0; // Used to determine how long button is held down.

void setup() {
  pinMode(LED_R, OUTPUT); // Defines LED_R as an OUTPUT pin.
  pinMode(LED_G, OUTPUT); // Defines LED_G as an OUTPUT pin.
  pinMode(LED_B, OUTPUT); // Defines LED_B as an OUTPUT pin.

  pinMode(btnOn, INPUT);      // Defines btnOn as an INPUT pin.
  pinMode(btnSelect, INPUT);  // Defines btnSelect as an INPUT pin.
  pinMode(btnUp, INPUT);      // Defines btnUp as an INPUT pin.
  pinMode(btnDown, INPUT);    // Defines btnDown as an INPUT pin.
  pinMode(btnMode, INPUT);    // Defines btnMode as an INPUT pin.
}

// Functions to be called in the loop.
void red() {
  analogWrite(LED_R, 255);
  analogWrite(LED_G, 0);
  analogWrite(LED_B, 0);
}

void green() {
  analogWrite(LED_R, 0);
  analogWrite(LED_G, 255);
  analogWrite(LED_B, 0);
}

void blue() {
  analogWrite(LED_R, 0);
  analogWrite(LED_G, 0);
  analogWrite(LED_B, 255);
}

void white() {
  analogWrite(LED_R, 255);
  analogWrite(LED_G, 255);
  analogWrite(LED_B, 255);
}

void black() {
  analogWrite(LED_R, 0);
  analogWrite(LED_G, 0);
  analogWrite(LED_B, 0);
}

int kickWhile = 0;
int TEST = 0;
void test() {
  valOn = 0;
  valSelect = 0;
  valUp = 0;
  valDown = 0;
  valMode = 0;
  valOn = digitalRead(btnOn);         // Read and store the value of btnOn.
  valSelect = digitalRead(btnSelect); // Read and store the value of btnSelect.
  valUp = digitalRead(btnUp);         // Read and store the value of btnUp.
  valDown = digitalRead(btnDown);     // Read and store the value of btnDown.
  valMode = digitalRead(btnMode);     // Read and store the value of btnMode.
  TEST = valOn + valSelect + valUp + valDown + valMode;
  if (TEST > 0) {
    kickWhile = 1;
  }
}




void mode0() {
  test();
  if (kickWhile == 0) {
    for (i = 0; i < 255; i++) {
      test();
      if (kickWhile == 0) {
        brt_R0 = i*x*(brt_RF1-brt_RF0)*(i/brt_RFR*x+1)+brt_RF1-(brt_RF1-brt_RF0)*(i/brt_RFR*x+1);
        brt_G0 = i*x*(brt_GF1-brt_GF0)*(i/brt_GFR*x+1)+brt_GF1-(brt_GF1-brt_GF0)*(i/brt_GFR*x+1);
        brt_B0 = i*x*(brt_BF1-brt_BF0)*(i/brt_BFR*x+1)+brt_BF1-(brt_BF1-brt_BF0)*(i/brt_BFR*x+1);
        analogWrite(LED_R, brt_R0);
        analogWrite(LED_G, brt_G0);
        analogWrite(LED_B, brt_B0);
        QA();
      }
    }
    for (i = 255; i > 0; i--) {
      test();
      if (kickWhile == 0) {
        brt_R0 = i*x*(brt_RF1-brt_RF0)*(i/brt_RFR*x+1)+brt_RF1-(brt_RF1-brt_RF0)*(i/brt_RFR*x+1);
        brt_G0 = i*x*(brt_GF1-brt_GF0)*(i/brt_GFR*x+1)+brt_GF1-(brt_GF1-brt_GF0)*(i/brt_GFR*x+1);
        brt_B0 = i*x*(brt_BF1-brt_BF0)*(i/brt_BFR*x+1)+brt_BF1-(brt_BF1-brt_BF0)*(i/brt_BFR*x+1);
        analogWrite(LED_R, brt_R0);
        analogWrite(LED_G, brt_G0);
        analogWrite(LED_B, brt_B0);
        QA();
      }
    }
  }
}

void mode1() {
  analogWrite(LED_R, brt_R1);
  analogWrite(LED_G, brt_G1);
  analogWrite(LED_B, brt_B1);
}

void mode2() {
  analogWrite(LED_R, brt_R2);
  analogWrite(LED_G, brt_G2);
  analogWrite(LED_B, brt_B2);
}

void mode3() {
  analogWrite(LED_R, brt_R3);
  analogWrite(LED_G, brt_G3);
  analogWrite(LED_B, brt_B3);
}

void mode4() {
  analogWrite(LED_R, brt_R4);
  analogWrite(LED_G, brt_G4);
  analogWrite(LED_B, brt_B4);
}

void modeOFF() {
  black();       // Calls color function of black to turn off LEDs.
  selectReset(); // Reset all select and level variables to 0.
  startTime = 0; // Reset startTimer when the device is turned off.
}

// Function to check and call each mode.
void modeCheck() {
  if (mode > 4) { // Device only has 5 modes (0-4); if mode > 4 go back to 0.
    mode = 0;     // Go back to 0.
  }
  if (mode == 0) {
    mode0();      // Call mode0 Function.
  }
  if (mode == 1) {
    mode1();      // Call mode1 Function.
  }
  if (mode == 2) {
    mode2();      // Call mode2 Function.
  }
  if (mode == 3) {
    mode3();      // Call mode3 Function.
  }
  if (mode == 4) {
    mode4();      // Call mode4 Function.
  }
}

/* This is used to change the delay between colors to make "flash(es)"
 in/during each selection. */
void selectDelay() {
  delay(n+t); /* Changing this will change how long LED(s) will turn
   on or off in order to make them "flash". */
}

void selectR() { // Select the red channel to modify.
  red();         // Channel/color selected.
  selectDelay(); // Blink to show channel selected.
  black();       // Blink to black.
  selectDelay(); // Blink to show channel selected.
  red();         // Channel/color selected.
  selectDelay(); // Blink to show channel selected.
}

void selectG() { // Select the green channel to modify.
  green();       // Channel/color selected.
  selectDelay(); // Blink to show channel selected.
  black();       // Blink to black.
  selectDelay(); // Blink to show channel selected.
  green();       // Channel/color selected.
  selectDelay(); // Blink to show channel selected.
}

void selectB() { // Select the blue channel to modify.
  blue();        // Channel/color selected.
  selectDelay(); // Blink to show channel selected.
  black();       // Blink to black.
  selectDelay(); // Blink to show channel selected.
  blue();        // Channel/color selected.
  selectDelay(); // Blink to show channel selected.
}

void selectW() { // Select the "white"(RGB) channel to modify.
  white();       // Channel/color selected.
  selectDelay(); // Blink to show channel selected.
  black();       // Blink to black.
  selectDelay(); // Blink to show channel selected.
  white();       // Channel/color selected.
  selectDelay(); // Blink to show channel selected.
}

void selectBRT() {
  t = 650;
  level0Check();
  t = 0;
}

void selectSTRB() {
  t = -50;
  level0Check();
  t = 0;
}

void selectFADE() {
  if (level0 == 1) {
    for (iR = brt_RF0; iR < brt_RF1; iR++) {
      analogWrite(LED_R, iR);
      analogWrite(LED_G, iG);
      analogWrite(LED_B, iB);
      delay(brt_RFR);
    }
    for (iR = brt_RF1; iR > brt_RF0; iR--) {
      analogWrite(LED_R, iR);
      analogWrite(LED_G, iG);
      analogWrite(LED_B, iB);
      delay(brt_RFR);
    }
  }
  if (level0 == 2) {
    for (iG = brt_GF0; iG < brt_GF1; iG++) {
      analogWrite(LED_R, iR);
      analogWrite(LED_G, iG);
      analogWrite(LED_B, iB);
      delay(brt_GFR);
    }
    for (iG = brt_GF1; iG > brt_GF0; iG--) {
      analogWrite(LED_R, iR);
      analogWrite(LED_G, iG);
      analogWrite(LED_B, iB);
      delay(brt_GFR);
    }
  }
  if (level0 == 3) {
    for (iB = brt_BF0; iB < brt_BF1; iB++) {
      analogWrite(LED_R, iR);
      analogWrite(LED_G, iG);
      analogWrite(LED_B, iB);
      delay(brt_BFR);
    }
    for (iB = brt_BF1; iB > brt_BF0; iB--) {
      analogWrite(LED_R, iR);
      analogWrite(LED_G, iG);
      analogWrite(LED_B, iB);
      delay(brt_BFR);
    }
  }
  if (level0 == 4) {
    for (iW = brt_WF0; iW < brt_WF1; iW++) {
      analogWrite(LED_R, iW);
      analogWrite(LED_G, iW);
      analogWrite(LED_B, iW);
      delay(brt_WFR);
    }
    for (iW = brt_WF1; iW > brt_WF0; iW--) {
      analogWrite(LED_R, iW);
      analogWrite(LED_G, iW);
      analogWrite(LED_B, iW);
      delay(brt_WFR);
    }
  }
}

/* Select State 1: On/Off
 0 = Off, 1 = On; choose a Color (RGBW). */
void select0Check() {
  if (mode != 0) {  // Mode 0 is user programmable. Make sure it is being used.
    mode = 0;       // Force change to mode 0.
  }
  if (level0 == 0) {  // If level0 is on exit leave selection mode.
    if (select0 > 1) { // If select0 is on turn it off.
      select0 = 0;     // Go back to 0.
    }
  }
  if (select0 > 1) { // If select0 goes over 1 go back to 1.
    select0 = 1;     // Go back to 1.
  }
}

/* Select State 2: On/Off
 0 = Off, 1 = On; choose a Modifier Type. */
void select1Check() {
  if (mode != 0) {  // Mode 0 is user programmable. Make sure it is being used.
    mode = 0;       // Force change to mode 0.
  }
  if (level1 == 0) {  // If level1 is on exit leave selection mode.
    if (select1 > 1) { // If select1 is on turn it off.
      select1 = 0;     // Go back to 0.
    }
  }
  if (select1 > 1) { // If select1 goes over 1 go back to 1.
    select1 = 1;     // Go back to 1.
  }
}

/* Select State 3: On/Off
 0 = Off, 1 = On; choose between Strobe/Fade Modifiers. */
void select2Check() {
  if (mode != 0) {  // Mode 0 is user programmable. Make sure it is being used.
    mode = 0;       // Force change to mode 0.
  }
  if ((level2 == 0) or (level1 == 1)) {  /* If level2 is on exit or if level1 is on
                                          Brightness leave selection mode. */
    if (select2 > 1) { // If select2 is on turn it off.
      select2 = 0;     // Go back to 0.
    }
  }
  if (select2 > 1) { // If select2 goes over 1 go back to 1.
    select2 = 1;     // Go back to 1.
  }
}

/* Level 1 Select State: Color (RGBW)
 0 = Off, 1 = Red, 2 = Green, 3 = Blue, 4 = White */
void level0Check() {
  if (level0 > 4) { // If level0 goes over 4 start over.
    level0 = 0;     // Start over at 0 this time.
  }
  if (level0 < 0) { // If level0 goes below 0 start over at the end.
    level0 = 4;     // Start over at 4 this time.
  }
  if (level0 == 0) {
    selectR();      // Over flash to show exit.
    selectR();      // Over flash to show exit.
    selectR();      // Over flash to show exit.
  }
  if (level0 == 1) {
    selectR();      // Select the red channel to modify.
  }
  if (level0 == 2) {
    selectG();      // Select the green channel to modify.
  }
  if (level0 == 3) {
    selectB();      // Select the blue channel to modify.
  }
  if (level0 == 4) {
    selectW();      // Select the "white"(RGB) channel to modify.
  }
}

/* Level 2 Select State: Modifier Type
 0 = Off, 1 = Brightness, 2 = Strobe, 3 = Fade */
void level1Check() {
  if (level1 > 3) { // If level1 goes over 3 start over.
    level1 = 0;     // Start over at 0 this time.
  }
  if (level1 < 0) { // If level1 goes below 0 start over at the end.
    level1 = 3;     // Start over at 3 this time.
  }
  if (level1 == 0) {
    selectR();      // Over flash to show exit.
    selectR();      // Over flash to show exit.
    selectR();      // Over flash to show exit.
  }
  if (level1 == 1) {
    selectBRT();    // Modify brightness.
  }
  if (level1 == 2) {
    selectSTRB();   // Modify strobe.
  }
  if (level1 == 3) {
    selectFADE();   // Modify fade.
  }
}

void level2Check() {
  if (level2 > 3) {
    level2 = 0;
  }
  if (level2 < 0) {
    level2 = 3;
  }
  if (level2 == 0) {
    selectR();      // Over flash to show exit.
    selectR();      // Over flash to show exit.
    selectR();      // Over flash to show exit.
  }
  if (level1 == 2) {
    if (level2 == 1) {
    }
    if (level2 == 2) {
    }
    if (level2 == 3) {
    }
  }
  if (level1 == 3) {
    if (level2 == 1) {
    }
    if (level2 == 2) {
    }
    if (level2 == 3) {
    }
  }
}

void brt_Check() {
  if (brt_R0 > 255) {
    brt_R0 = 0;
  }
  if (brt_R0 < 0) {
    brt_R0 = 255;
  }
  if (brt_G0 > 255) {
    brt_G0 = 0;
  }
  if (brt_G0 < 0) {
    brt_G0 = 255;
  }
  if (brt_B0 > 255) {
    brt_B0 = 0;
  }
  if (brt_B0 < 0) {
    brt_B0 = 255;
  }
}

// Reset all select and level variables to 0.
void selectReset() {
  select0 = 0;   // Reset select0 state to 0.
  select1 = 0;   // Reset select1 state to 0.
  select2 = 0;   // Reset select2 state to 0.
  level0 = 0;    // Reset level0 state to 0.
  level1 = 0;    // Reset level1 state to 0.
  level2 = 0;    // Reset level2 state to 0.
}

// This is used to show that the time has expired for the selection.
void selectTimer() {
  if (select0 != 0 && (millis() - startTime) > 3000) { /* If something is selected
   and 3 seconds has passed
   reset select state. */
    selectReset(); // Reset all select and level variables to 0.
    selectR();     // Flashes to show reset.
    selectG();     // Flashes to show reset.
    selectB();     // Flashes to show reset.
    selectW();     // Flashes to show reset.
    selectW();     // Flashes to show reset.
    startTime = 0; // Reset startTime to 0. This is not necessary, but good practice.
  }
}

// Used to change the Quality Assurance Delay used throughout the entire project.
void QA() {
  delay(10); // Delay for 10ms for quality assurance.
}
// This runs everything.
void loop() {
  valOn = digitalRead(btnOn);         // Read and store the value of btnOn.
  valSelect = digitalRead(btnSelect); // Read and store the value of btnSelect.
  valUp = digitalRead(btnUp);         // Read and store the value of btnUp.
  valDown = digitalRead(btnDown);     // Read and store the value of btnDown.
  valMode = digitalRead(btnMode);     // Read and store the value of btnMode.
  // This is the On/Off Button. Switches state On or Off so device will work.
  if ((valOn == HIGH) && (old_valOn == LOW)) {
    state = 1 - state; /* Math statement to switch state turning the device
                       On or Off. */
    QA();              // Delay for 10ms for quality assurance.
  }
  old_valOn = valOn; // Store the old value of valOn.
  /* Main encapsulation. Checks to see if the device is on. If device is on
   everything works properly. */
  if (state == 1) {
    // This is the Select Button. Turns select on or off.
    if ((valSelect == HIGH) && (old_valSelect == LOW)) {
      if (select1 == 0) {
        select0++;            // Math statement to turn select0 on or off.
        select0Check();       // Check if select0 is on or off and fix errors.
      }
      if ((select2 == 0) && (level0 > 0)) {
        select1++;            // Math statement to turn select1 on or off.
        select1Check();       // Check if select1 is on or off and fix errors.
      }
      if (level1 > 0) {
        select2++;
        select2Check();
      }
      QA();                   // Delay for quality assurance.
      startTime = millis();   /* This line remembers when the button
                               was last pressed) */
    }
    old_valSelect = valSelect; // Store the old value of valSelect.
    // This is the Up Button. Scrolls Up through selections.
    if (select0 == 1) {
      if ((valUp == HIGH) && (old_valUp == LOW)) {
        if (select1 == 0) {
          level0++;               // Math statement to cycle through RGBW channels.
          level0Check();          /* Check which RGBW channel is selected and call
                                 its' function. */
        }
        if ((select1 == 1) && (select2 == 0)) {
          level1++;
          level1Check();
        }
        if (select2 == 1) {
          if (level1 == 1) {
            if (level0 == 1) {
              brt_R0++;
              brt_Check();
            }
            if (level0 == 2) {
              brt_G0++;
              brt_Check();
            }
            if (level0 == 3) {
              brt_B0++;
              brt_Check();
            }
            if (level0 == 4) {
              brt_R0++;
              brt_G0++;
              brt_B0++;
              brt_Check();
            }
          }
          if(level1 != 1) {
            level2++;
            level2Check();
          }
        }
        QA();                   // Delay for quality assurance.
        startTime = millis();   /* This line remembers when the button
                                 was last pressed) */
      }
      old_valUp = valUp; // Store the old value of valUp.
      // This is the Down Button. Scrolls Down through selections.
      if ((valDown == HIGH) && (old_valDown == LOW)) {
        if (select1 == 0) {
          level0--;               // Math statement to cycle through RGBW channels.
          level0Check();          /* Check which RGBW channel is selected and call
                                 its' function. */
        }
        if ((select1 == 1) && (select2 == 0)) {
          level1--;
          level1Check();
        }
        if (select2 == 1) {
          if (level1 == 1) {
            if (level0 == 1) {
              brt_R0--;
              brt_Check();
            }
            if (level0 == 2) {
              brt_G0--;
              brt_Check();
            }
            if (level0 == 3) {
              brt_B0--;
              brt_Check();
            }
            if (level0 == 4) {
              brt_R0--;
              brt_G0--;
              brt_B0--;
              brt_Check();
            }
          }
          if(level1 != 1) {
            level2--;
            level2Check();
          }
        }
        QA();                   // Delay for quality assurance.
        startTime = millis();   /* This line remembers when the button
                                 was last pressed) */
      }
      old_valDown = valDown; // Store the old value of valDown.
    }
    // This is the Mode Button. Pressing this button cycles through each mode.
    if ((valMode == HIGH) && (old_valMode == LOW)) {
      mode++;        // Math statement to cycle through modes.
      selectReset(); // Reset all select and level variables to 0.
      QA();          // Delay for quality assurance.
    }
    old_valMode = valMode; // Store the old value of valMode.
    kickWhile = 0;
    modeCheck();   // Check which mode is selected and call its' function.
    selectTimer(); // Resets select timer after idle time passes.
  }
  else {
    modeOFF(); // Turn off the device.
  }
}

#include <U8g2lib.h>
#include <Bounce2.h>

byte button_pins[] = {2, 3, 5}; // button pins, 4,5 = up/down, 6 = select
#define NUMBUTTONS sizeof(button_pins)
Bounce * buttons = new Bounce[NUMBUTTONS];

U8X8_SSD1306_128X64_NONAME_HW_I2C display(U8X8_PIN_NONE);

#define MENU_SIZE 5
char *menu[MENU_SIZE] = { "Option 1", "Option 2", "Option 3", "Option 4", "Option 5" };

int cursor = 0;

void setup() {
  Serial.begin(9600);

  // Make input & enable pull-up resistors on switch pins
  for (int i = 0; i < NUMBUTTONS; i++) {
    buttons[i].attach( button_pins[i], INPUT_PULLUP); // setup the bounce instance for the current button
    buttons[i].interval(25); // interval in ms
  }

  display.begin();
  // display.setPowerSave(0);
  // display.setFont(u8x8_font_pxplusibmcgathin_f);

  showMenu();
}

void loop() {
  // process button press:
  for (int i = 0; i < NUMBUTTONS; i++) {
    buttons[i].update(); // Update the Bounce instance
    if ( buttons[i].fell() ) { // If it fell
      if (i == 2) { // select
        display.clearLine(7);
        display.setCursor(0, 7);
        display.print(">>");
        display.print(menu[cursor]);
        executeChoice(cursor);
      }
      else {
        // erase previous cursor:
        display.setCursor(0, cursor);
        display.print(' ');
        if (i == 0) { // up
          cursor++;
          if (cursor > (MENU_SIZE - 1)) cursor = 0;
        }
        else { // down
          cursor--;
          if (cursor < 0) cursor = (MENU_SIZE - 1);
        }
        // show cursor at new line:
        display.setCursor(0, cursor);
        display.print('>');
      }
    } // end if button fell...
  } // end for-loop of button check
}

/**
  Clear display and show the menu.
*/
void showMenu() {
  cursor = 0;
  display.clearDisplay();
  // show menu items:
  for (int i = 0; i < MENU_SIZE; i++) {
    display.drawString(2, i, menu[i]);
  }
  display.setCursor(0, 0);
  display.print('>');
}

/**
  Execute the task which matches the chosen menu item.
*/
void executeChoice(int choice) {
  switch (choice) {
    case 0 :
      Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
      break;
    case 1 :
      Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
      break;
    case 2 :
      Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
      break;
    case 3 :
      Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
      break;
    case 4 :
      Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
      break;
    default :
      Serial.print("Execute choice "); Serial.print(choice); Serial.print(" - "); Serial.println(menu[choice]);
      break;
  }

}

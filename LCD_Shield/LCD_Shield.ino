#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  // Initialize LCD

void setup() {
  lcd.begin(16, 2);            // 16x2 LCD
  lcd.setCursor(0, 0);
  lcd.print("  TechToTinker  ");
  lcd.setCursor(0, 1);
  lcd.print("Press Key:");
}

void loop() {
  int x = analogRead(A0);      // Read button voltage

  lcd.setCursor(10, 1);        // Position for key name
  lcd.print("       ");        // Clear old text (7 spaces)
  lcd.setCursor(10, 1);        // Reset cursor again

  if (x < 60) {
    lcd.print("Right");
  }
  else if (x < 200) {
    lcd.print("Up");
  }
  else if (x < 400) {
    lcd.print("Down");
  }
  else if (x < 600) {
    lcd.print("Left");
  }
  else if (x < 800) {
    lcd.print("Select");
  }
  else {
    lcd.print("None");
  }

  delay(200);  // debounce delay
}

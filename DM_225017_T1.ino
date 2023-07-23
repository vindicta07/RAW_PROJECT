/*
 * SFIT RAW PROJECT TASK 1
 * Divyanshu Modi <divyan.m05@student.sfit.ac.in>
 */

#include <Adafruit_LiquidCrystal.h>

// Enable debugging
#define DEBUG 

#define LCD_X 16
#define LCD_Y 2

// define the thermal sensor read pin
#define TSENS_PIN A0

Adafruit_LiquidCrystal lcd(0);

void setup()
{
  Serial.begin(9600);
  // Initialise the lcd
  lcd.begin(LCD_X, LCD_Y);
}

/*
 * The code is written in accordance
 * to the tmp36 thermal sensor
 * Offering a range of -40*c to 125*c.
 */
void loop()
{
  // Make sure the panel is cleared
  lcd.clear();
  // Read the analog input from tsens pin
  int vout = analogRead(TSENS_PIN);
  /*
   * Map the temperature in accordance to
   * Ananlog input measured
   */
  float temp = map(vout, 20, 358, -40, 125);

#ifdef DEBUG
  Serial.print("Vout: ");
  Serial.println(vout);
  Serial.print("\n");

  Serial.print("Temperature: ");
  Serial.println(temp);
  Serial.print("*C\n");
#endif

  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
  lcd.setCursor(0, 1);
  lcd.print(temp, 1);
  lcd.print(" \xB0""C");
  delay(1500);
}
/*
 * fuel indicator 
 * original sketch by Nicu FLORICA (niq_ro)
 * Craiova, 24.7.2019
 * http://www.arduinotehniq.com
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define pinsenzor A0

int nivel, nivel1;

float R1 = 330;
float vref = 1100;  // 1.1V = 1100mV
int rmin = 54;
int rmax = 291;

float tensiune, curent, plutitor;
int procent;

void setup()
{
  analogReference(INTERNAL);  // set reference voltage at 1.1V
  
	lcd.begin();  // initialize the LCD

	lcd.backlight();  // Turn on the blacklight and print a message.
  lcd.setCursor(3,0);
	lcd.print("Fuel level");
  lcd.setCursor(1,1);
  lcd.print("indicator v.0");
  delay(3000);
  lcd.clear();
}

void loop()
{

nivel1 = 0;
 for (int i = 0; i <10; i++) 
  {
   nivel = analogRead(pinsenzor);  // read value on 
   nivel1 = nivel1 + nivel;
   delay(50);
  }
  nivel = nivel1/10;

  tensiune = (float)vref * nivel /1024.;  // voltage on R1
  curent = (float)tensiune/R1;  //current thtu divider
  plutitor = (float)(vref - tensiune) / curent;  // resistance of fuel sensor
  procent = map(plutitor, rmin, rmax, 0, 100);

  lcd.setCursor(0,0);
  lcd.print("Fuel level: ");
  lcd.setCursor(12,0);
  if (procent <10) lcd.print(" ");
  if (procent <100) lcd.print(" ");
  lcd.print(procent);
  lcd.print("%");
  delay(500); 
} // end loop

#include <LiquidCrystal.h>
//#include <phi_super_font.h>
#include <phi_big_font.h>
LiquidCrystal lcd(8,9,4,5,6,7); //RS 12,EN 11,D4 7,D5 8,D6 9,D7 10
int sensorPin = A1;
int sensorValue = 0;
int tonecount = 0;

void setup()
{
  pinMode(2, INPUT_PULLUP); // mA/%
  pinMode(11, OUTPUT); //lcd led
  pinMode(10, OUTPUT); //lcdbacklight
  pinMode(13, OUTPUT); //duda
  lcd.begin(16, 2);
  //init_super_font(&lcd);
  init_big_font(&lcd);
  lcd.clear();
  analogWrite(10,50);
  lcd.write("viztorony"); 
  lcd.setCursor(0,1);
  lcd.write("Toth Tamas"); 
  delay(1200);
  lcd.clear();
}

void loop()
{
  lcd_clear();
  sensorValue = analogRead(sensorPin);
  int miliamp = map(sensorValue, 0, 1023, 0, 20);  // map the result to 200 - 1000:
  sensorValue = sensorValue / 10 ,
  lcd.setCursor(0,0);
  if (digitalRead(2) == LOW) 
  {
    //render_super_number(miliamp,0,0);
    render_big_number(miliamp,0,0);
    lcd.setCursor(18,4);
    lcd.write("mA");
  } 
  else 
  {
    //render_super_number(sensorValue,0,0);
    render_big_number(sensorValue,0,0);
    lcd.setCursor(8,1);
    lcd.write("%");
  }

  if ((sensorValue) < 60 or (sensorValue) > 103)
  {
    digitalWrite(11,HIGH);
    if ((tonecount) < 3 )
    {
      tone(13, 440, 500);
      tonecount++;
    } 
  } 
  else 
  {
    digitalWrite(11,LOW);
    if ((tonecount)> 0)
    {
      tonecount=0;
      tone(13, 1100, 300);
    }
  }
    if ((miliamp) < 4)
  {
    lcd.setCursor(8,1);
    lcd.write("SZENZOR HIBA");
  }
  delay(500);
  digitalWrite(11,LOW);
  delay(500);

}

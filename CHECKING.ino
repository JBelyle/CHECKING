#include <Adafruit_NeoPixel.h>
#include "OneButton.h"
#include <LiquidCrystal.h>

#define PIN 13
Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, PIN, NEO_GRB + NEO_KHZ800);

//lcd display
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
String space = " ";


//encoder
const int clkPin = 10; //the clk attach to pin 10
const int dtPin = 11; //the dt pin attach to pin 11
const int swPin = 9 ; //the sw pin attach to pin 9
int encoderVal = 0;
int absResult;


//colors and led strip
int r = 0;
int g = 0;
int b = 0;
int color[4];
int brightness = 255;



//Variables
int x = 0;




void setup() {
  // put your setup code here, to run once:
  //encoder
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT);
  digitalWrite(swPin, HIGH);

  //led strip
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();

  //lcd
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();



}

void loop() {
  // put your main code here, to run repeatedly:

  int change = getEncoderTurn();//
  encoderVal = encoderVal + change;
  color[x] = encoderVal;
  updating();
  if (digitalRead(swPin) == LOW)
  {
    x++;

  }
  if(x == 4)
  {
    x = 0;
  }
  r = color[0];
  g = color[1];
  b = color[2];
  brightness = color[3];

  //debugging
  Serial.print(color[0] + space);
  //delay();
  Serial.print(color[1] + space);
  //delay(50);
  Serial.print(color[2] + space);
  //delay(100);
  Serial.print(color[3] + space);
  Serial.print(x);
  Serial.println();
  //end dubugging
  
}

int getEncoderTurn(void)
{
  static int oldA = HIGH; //set the oldA as HIGH
  static int oldB = HIGH; //set the oldB as HIGH
  int result = 0;
  int newA = digitalRead(clkPin);//read the value of clkPin to newA
  int newB = digitalRead(dtPin);//read the value of dtPin to newB
  if (newA != oldA || newB != oldB) //if the value of clkPin or the dtPin has changed
  {
    // something has changed
    if (oldA == HIGH && newA == LOW)
    {
      result = (oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;


  return result;
}
void updating()
{

  //update leds
  for ( int pn = 0; pn < 30; pn++)
  {
    strip.setPixelColor(pn, r, g, b);
  }
  strip.show();

  //update lcd
  String lcdOut = r + space + g + space + space + space + b + space + brightness;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RED GRN BLUE BRI");
  lcd.setCursor(0, 1);
  lcd.print(lcdOut);
  delay(10);


}



/*
  CODE BY: https://github.com/anakidandaa/ArduinoUno-FishFeeder
  FOR : AUTOMATIC FISH FEEDER
  BOARD : ARDUINO UNO R3
  SENSOR : -
  TOOLS : I2c 16x2 LCD, Servo
  HOW IT WORKS : Set timer for the servo to open the tube of the fish food. No more forgetting to feed the fish.
*/


//Library Include
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h> //wire library for I2C
#include <Servo.h> //servo library



// Define LCD pinout & I2C Address - change if reqiuired
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;

//Define tools
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
Servo motor;

//Set data
long hour = 5, minute = 59, second = 59; //Setting countdown time
long countdown_time = (hour * 3600) + (minute * 60) + second;
static unsigned long startTime = millis();

void setup() {
  //Define servo pin
  motor.attach(7);
  motor.write(0);

  //Set LCD (change if you use 20x4)
  lcd.begin(16, 2);
  lcd.backlight();

  //Set LCD Display
  lcd.setCursor(0, 0);
  lcd.print("  FISH  FEEDER  ");

}

void loop() {
  long countdowntime_seconds = countdown_time - ((millis() - startTime) / 1000); //To see how long the timer has been running

  //Starting Countdown
  if (countdowntime_seconds >= 0) {
    long countdown_hour = countdowntime_seconds / 3600; //Hour Setting
    long countdown_minute = ((countdowntime_seconds / 60) % 60); //Minute Setting
    long countdown_sec = countdowntime_seconds % 60; //Second Setting

    //Set LCD display
    lcd.setCursor(4, 1);
    if (countdown_hour < 10) {
      lcd.print("0");
    }
    lcd.print(countdown_hour);
    lcd.print(":");
    if (countdown_minute < 10) {
      lcd.print("0");
    }
    lcd.print(countdown_minute);
    lcd.print(":");
    if (countdown_sec < 10) {
      lcd.print("0");
    }
    lcd.print(countdown_sec); //Displaying Countdown
  }

  else
  {
    motor.write(300); //Opening tube (servo)
    delay(500);
    motor.write(0); //Closing tube (servo)
    delay(500);
    startTime = millis();  // Restart countdown
  }
}

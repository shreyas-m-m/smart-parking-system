#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// I2C LCD
LiquidCrystal_I2C lcd(0x27,16,2);

// Servo Motor
Servo gate;

// PIR Sensor
int pirSensor = 9;

// LEDs
int greenLED = 6;
int redLED = 7;

// Ultrasonic Sensor 1
int trig1 = 10;
int echo1 = 13;

// Ultrasonic Sensor 2
int trig2 = A0;
int echo2 = A1;

// Ultrasonic Sensor 3
int trig3 = A2;
int echo3 = A3;

void setup()
{
  // LCD
  lcd.begin();
  lcd.backlight();

  // PIR
  pinMode(pirSensor, INPUT);

  // LEDs
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  // Ultrasonic Sensors
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(trig3, OUTPUT);
  pinMode(echo3, INPUT);

  // Servo
  gate.attach(8);

  // Initial gate position
  gate.write(0);

  // Initial LEDs
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);

  // Welcome Message
  lcd.setCursor(0,0);
  lcd.print("SMART PARKING");

  lcd.setCursor(0,1);
  lcd.print("SYSTEM");

  delay(2000);

  lcd.clear();
}

// Function for ultrasonic distance
float getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  float distance = duration * 0.034 / 2;

  return distance;
}

void loop()
{
  int availableSlots = 3;

  // Read slot distances
  float d1 = getDistance(trig1, echo1);
  float d2 = getDistance(trig2, echo2);
  float d3 = getDistance(trig3, echo3);

  // Slot occupied check
  if(d1 < 20)
  {
    availableSlots--;
  }

  if(d2 < 20)
  {
    availableSlots--;
  }

  if(d3 < 20)
  {
    availableSlots--;
  }

  // LCD Display
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Slots Left:");

  lcd.setCursor(0,1);
  lcd.print(availableSlots);

  // Car detection at entry
  if(digitalRead(pirSensor) == HIGH)
  {
    if(availableSlots > 0)
    {
      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print("Car Detected");

      lcd.setCursor(0,1);
      lcd.print("Gate Opening");

      // LEDs
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, LOW);

      // Open gate
      gate.write(90);

      delay(3000);

      // Close gate
      gate.write(0);

      // LEDs reset
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, HIGH);

      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print("Gate Closed");

      delay(1000);
    }
    else
    {
      lcd.clear();

      lcd.setCursor(0,0);
      lcd.print("PARKING FULL");

      lcd.setCursor(0,1);
      lcd.print("NO SPACE");

      delay(2000);
    }
  }

  delay(500);
}

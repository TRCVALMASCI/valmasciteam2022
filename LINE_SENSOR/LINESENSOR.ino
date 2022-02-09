#include <QTRSensors.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define scrwid 128
#define scrhei 64
#define scradr 0x3C
#define DELAY 500

QTRSensors qtr_front;
QTRSensors qtr_back;
QTRSensors qtr_left;
QTRSensors qtr_right;

const uint8_t SensorCount = 4;
uint16_t sensorValues[SensorCount];

Adafruit_SSD1306 display(scrwid, scrhei, &Wire, -1);

void setupLineSensors()
{
  const uint16_t def_timeout = 500;
  Serial.println("initializing line sensors . . .");

  qtr_front.setTimeout(def_timeout);
  qtr_front.setTypeRC();
  qtr_front.setSensorPins((const uint8_t[]) {
    A0, A1, A2, A3
  }, SensorCount);
  qtr_front.setEmitterPin(33);

  qtr_back.setTimeout(def_timeout);
  qtr_back.setTypeRC();
  qtr_back.setSensorPins((const uint8_t[]) {
    A15, A14, A13, A12
  }, SensorCount);
  qtr_back.setEmitterPin(32);

  qtr_left.setTimeout(def_timeout);
  qtr_left.setTypeRC();
  qtr_left.setSensorPins((const uint8_t[]) {
    A7, A6, A5, A4
  }, SensorCount);
  qtr_left.setEmitterPin(30);

  qtr_right.setTimeout(def_timeout);
  qtr_right.setTypeRC();
  qtr_right.setSensorPins((const uint8_t[]) {
    A8, A9, A10, A11
  }, SensorCount);
  qtr_right.setEmitterPin(31);
}

void setup()
{
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, scradr)){
    Serial.println(F("SSD12306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  
  setupLineSensors();
  calibrate_sensor(qtr_front);
  

}

void loop()
{
  uint16_t position = qtr_front.readLineBlack(sensorValues);

  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println(position);

  delay(250);
}

void calibrate_sensor(QTRSensors &lineSensor)
{
  Serial.println("Calibrating . . .");
  Serial.println("Slowly move the sensor across the electrical tape");
  for (uint16_t i = 0; i < 400; i++)
  {
    lineSensor.calibrate();
  }
  Serial.println();

  Serial.print("Minimum Values: ");
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(lineSensor.calibrationOn.minimum[i]);
    Serial.print(' ');
  }
  Serial.println();

  Serial.print("Maximum Values: ");
  for (uint8_t i = 0; i < SensorCount; i++)
  {
    Serial.print(lineSensor.calibrationOn.maximum[i]);
    Serial.print(' ');
  }

  for (int x = 0; x < SensorCount; x++){
    display.print("sensor ");
    display.print(x+1);
    display.print(": ");
    display.print(lineSensor.calibrationOn.minimum[x]);
    display.print("()");
    display.print(lineSensor.calibrationOn.maximum[x]);
    display.display();
  }

  Serial.println();
  Serial.println("Done calibrating!");
  delay(500);
  Serial.println();
}

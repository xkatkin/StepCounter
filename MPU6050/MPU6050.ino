#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>

int     addressMPU  = 0x68;
int     addressOLED = 0x3C;
int16_t accelX, accelY, accelZ;
float   stepVector;
int     stepCount = 0;

Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

void setMPU6050() {
  mpu.begin();
}

void setOLED() {
  display.begin(SSD1306_SWITCHCAPVCC, addressOLED);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.display();
  delay(500);
}

void getAccel() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  accelX = a.acceleration.x;
  accelY = a.acceleration.y;
  accelZ = a.acceleration.z;
}

void showStep() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("WELCOME!");
  display.setCursor(0, 12);
  display.println("StepCounter v1.0");
  display.println("----------------");
  display.display();

  display.setTextSize(2);
  display.setCursor(0, 30);
  display.println("Steps: ");
  display.println(stepCount);
  display.display();
}

void countStep() {  
  float vector = sqrt((accelX * accelX) + (accelY * accelY) + (accelZ * accelZ));
  if(vector - stepVector > 1) {
    stepCount++;
    showStep();
  }
  stepVector = vector;
  delay(600);
}
 
void setup() {
  Wire.begin();
  setMPU6050();
  setOLED();
}

void loop() {
  getAccel();
  countStep();
}


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int     addressMPU = 0x68;
int     addressOLED = 0x3C;
int16_t accelX, accelY, accelZ;
float   stepVector;
int     stepCount = 0;

Adafruit_SSD1306 display(128, 64);

void setMPU6050() {
  Wire.beginTransmission(addressMPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void setOLED() {
  display.begin(SSD1306_SWITCHCAPVCC, addressOLED);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void getAccel() {
  Wire.beginTransmission(addressMPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(addressMPU, 6, true);
  accelX = Wire.read() << 8 | Wire.read();
  accelY = Wire.read() << 8 | Wire.read();
  accelZ = Wire.read() << 8 | Wire.read();
}

void showStep() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("WELCOME!");
  display.setCursor(0, 17);
  display.println("StepCounter v1.0");
  display.display();

  display.setTextSize(2);
  display.setCursor(0, 33);
  display.println("Steps: ");
  display.println(stepCount);
  display.display();
}

void countStep() {  
  float vector = sqrt((accelX * accelX) + (accelY * accelY) + (accelZ * accelZ));
  if(vector - stepVector > 6) {
    stepCount++;
    showStep();
  }
  stepVector = vector;
  delay(600);
}
 
void setup()
{
  Wire.begin();
  setMPU6050();
  setOLED();
}
 
 
void loop()
{
  getAccel();
  countStep();
}

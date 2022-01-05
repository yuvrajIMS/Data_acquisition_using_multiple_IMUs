#include <Wire.h> 
#include <I2Cdev.h> 
#include <MPU6050.h>

#define TCAADDR 0x70


extern "C"
  {
     #include "utility/twi.h"
  }


MPU6050 accelgyroRH;
const int MPU1_addrRH=0x68;


float accX=0, accY=0, accZ=0, gyroX=0, gyroY=0, gyroZ=0;

void tcaselect(uint8_t i) 
  {
    if (i > 7) return;
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << i);
    Wire.endTransmission();
  }

void TCA9548A(uint8_t busfd)
{
    Wire.beginTransmission(0x70); // TCA9548A address is 0x70
    Wire.write(1 << busfd);
    Wire.endTransmission(); 
}


void setup() 
{
    Serial.begin(230400);
    Wire.begin();
    
  
    TCA9548A(1);
    Wire.beginTransmission(MPU1_addrRH);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);

    accelgyroRH.setXGyroOffset(0);
    accelgyroRH.setYGyroOffset(0);
    accelgyroRH.setZGyroOffset(0);
  
    Serial.println("axrh,ayrh,azrh,gxrh,gyrh,gzrh");
}

void accelgyroRH_read()
{
  accX = accelgyroRH.getAccelerationX();
  accY = accelgyroRH.getAccelerationY();
  accZ = accelgyroRH.getAccelerationZ();
  gyroX = accelgyroRH.getRotationX();
  gyroY = accelgyroRH.getRotationY();
  gyroZ = accelgyroRH.getRotationZ();
}



void loop() 
{
     accelgyroRH_read();
  // print the data in CSV format
     Serial.print(accX); 
     Serial.print(',');
     Serial.print(accY);
     Serial.print(',');
     Serial.print(accZ); 
     Serial.print(',');
     Serial.print(gyroX);
     Serial.print(',');
     Serial.print(gyroY);
     Serial.print(',');
     Serial.print(gyroZ);
     Serial.println();
}

#include <Wire.h>
#include <I2Cdev.h>
extern "C" 
{ 
#include "utility/twi.h"  
}
#include <MPU6050.h>
#define TCAADDR 0x70

const int MPU1_addr=0x68;
int16_t AcX1,AcY1,AcZ1,Tmp1,GyX1,GyY1,GyZ1;

const int MPU2_addr=0x68;
int16_t AcX2,AcY2,AcZ2,Tmp2,GyX2,GyY2,GyZ2;

const int MPU3_addr=0x68;
int16_t AcX3,AcY3,AcZ3,Tmp3,GyX3,GyY3,GyZ3;

int ADXL345 = 0x53;
 
int minVal1=265;
int maxVal1=402;
int minVal2=265;
int maxVal2=402;
int minVal3=265;
int maxVal3=402;
 
double x1,x2,x3;
double y1,y2,y3;
double z1,z2,z3;

float X_out, Y_out, Z_out;

long lastMillis = 0;
long loops = 0;
long counter = 0;

void tcaselect(uint8_t i) 
{
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}



void TCA9548A(uint8_t bus)
{
  Wire.beginTransmission(0x70);  // TCA9548A address is 0x70
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}
 
void setup()
{
  
  Wire.begin();
  Serial.begin(1000000);
  

  TCA9548A(0);
  Wire.beginTransmission(MPU1_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  TCA9548A(2);
  Wire.beginTransmission(MPU2_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  TCA9548A(3);
  Wire.beginTransmission(MPU3_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  TCA9548A(4);
  Wire.beginTransmission(ADXL345);  
  Wire.write(0x2D); 
  Wire.write(8);  
  Wire.endTransmission();

  while (!Serial);
    delay(1000);
    Wire.begin();
    
    Serial.begin(1000000);
    Serial.println("\nTCAScanner ready!");
    
    for (uint8_t t=0; t<8; t++) 
    {
      tcaselect(t);
      Serial.print("TCA Port #"); 
      Serial.println(t);

      for (uint8_t addr = 0; addr<=127; addr++) 
      {
        if (addr == TCAADDR)
         
         continue;
      
        uint8_t data;
        if (! twi_writeTo(addr, &data, 0, 1, 1)) 
        {
           Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
          
        }
      }
    }
    Serial.println("\ndone");
    delay(5000);
    
}

void loop()

{

long currentMillis = millis();
loops++;
  
TCA9548A(0);
Wire.beginTransmission(MPU1_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU1_addr,14,true);
AcX1=Wire.read()<<8|Wire.read();
AcY1=Wire.read()<<8|Wire.read();
AcZ1=Wire.read()<<8|Wire.read();
int xAng1 = map(AcX1,minVal1,maxVal1,-90,90);
int yAng1 = map(AcY1,minVal1,maxVal1,-90,90);
int zAng1 = map(AcZ1,minVal1,maxVal1,-90,90);
 
x1= RAD_TO_DEG * (atan2(-yAng1, -zAng1)+PI);
y1= RAD_TO_DEG * (atan2(-xAng1, -zAng1)+PI);
z1= RAD_TO_DEG * (atan2(-yAng1, -xAng1)+PI);

Serial.print("F1->");
Serial.print("X=");
Serial.print(x1);
Serial.print(" ");
Serial.print("Y=");
Serial.print(y1);
Serial.print(" ");
Serial.print("Z=");
Serial.print(z1);
Serial.print("    ");



TCA9548A(2);
Wire.beginTransmission(MPU2_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU2_addr,14,true);
AcX2=Wire.read()<<8|Wire.read();
AcY2=Wire.read()<<8|Wire.read();
AcZ2=Wire.read()<<8|Wire.read();
int xAng2 = map(AcX2,minVal2,maxVal2,-90,90);
int yAng2 = map(AcY2,minVal2,maxVal2,-90,90);
int zAng2 = map(AcZ2,minVal2,maxVal2,-90,90);
 
x2= RAD_TO_DEG * (atan2(-yAng2, -zAng2)+PI);
y2= RAD_TO_DEG * (atan2(-xAng2, -zAng2)+PI);
z2= RAD_TO_DEG * (atan2(-yAng2, -xAng2)+PI);

Serial.print("F2->");
Serial.print("X=");
Serial.print(x2);
Serial.print(" ");
Serial.print("Y=");
Serial.print(y2);
Serial.print(" ");
Serial.print("Z=");
Serial.print(z2);
Serial.print("    ");

 
TCA9548A(3);
Wire.beginTransmission(MPU3_addr);
Wire.write(0x3B);
Wire.endTransmission(false);
Wire.requestFrom(MPU3_addr,14,true);
AcX3=Wire.read()<<8|Wire.read();
AcY3=Wire.read()<<8|Wire.read();
AcZ3=Wire.read()<<8|Wire.read();
int xAng3 = map(AcX3,minVal3,maxVal3,-90,90);
int yAng3 = map(AcY3,minVal3,maxVal3,-90,90);
int zAng3 = map(AcZ3,minVal3,maxVal3,-90,90);
 
x3= RAD_TO_DEG * (atan2(-yAng3, -zAng3)+PI);
y3= RAD_TO_DEG * (atan2(-xAng3, -zAng3)+PI);
z3= RAD_TO_DEG * (atan2(-yAng3, -xAng3)+PI);

Serial.print("F3->");
Serial.print("X=");
Serial.print(x3);
Serial.print(" ");
Serial.print("Y=");
Serial.print(y3);
Serial.print(" ");
Serial.print("Z=");
Serial.print(z3);
Serial.print("    ");

TCA9548A(4);
Wire.beginTransmission(ADXL345);
Wire.write(0x32); 
Wire.endTransmission(false);
Wire.requestFrom(ADXL345, 6, true); 
X_out = ( Wire.read()| Wire.read() << 8); 
X_out = X_out/256; 
Y_out = ( Wire.read()| Wire.read() << 8); 
Y_out = Y_out/256;
Z_out = ( Wire.read()| Wire.read() << 8); 
Z_out = Z_out/256;
Serial.print(" Hand Accel X= ");
Serial.print(Z_out);
Serial.print("   Y= ");
Serial.print(Y_out);
Serial.print("   Z= ");
Serial.print(X_out);
Serial.print("    ");

Serial.print("        Reading#");
counter++;
Serial.print("  ");
Serial.print(counter);


if(currentMillis - lastMillis >1000)
{ 
    Serial.print("Frequency:");
    Serial.print(loops);
    lastMillis = currentMillis;
    loops = 0;
}
Serial.println("");

}

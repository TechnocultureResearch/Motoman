#include<Arduino.h>

#define minVal 265
#define maxVal 402

#include "board.h"
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;


void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(SERIAL_1_BAUD_RATE);
}

void getMotion6(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy,
                int16_t* gz) {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
  *ax = Wire.read() << 8 |
        Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  *ay = Wire.read() << 8 |
        Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  *az = Wire.read() << 8 |
        Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  // Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  *gx = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  *gy = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  *gz = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

int getRollerAngle(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx,
                     int16_t *gy, int16_t *gz) {
                       // getVerticalAngle
  int i = 0;
  long x = 0;
  long y = 0;
  long z = 0;

  int repeatCount = 10;

  //
  for (i = 0; i < repeatCount; ++i) {
    getMotion6(ax, ay, az, gx, gy, gz);

    x = x + *ax; //
    y = y + *ay; //
    z = z + *az; //
  }

  double avX = x / repeatCount;
  double avY = y / repeatCount;
  double avZ = z / repeatCount;

  // int verticalAngle = atan2(avX - 507, avY - 520) / 3.14159 * 180.0;
  // Serial.println(verticalAngle);
  // return verticalAngle;

  int xAng = avX - 507;//map(AcX,minVal,maxVal,-90,90);
  int yAng = avY - 520;//map(AcY,minVal,maxVal,-90,90);
  int zAng = avZ - 500;//map(AcZ,minVal,maxVal,-90,90);
  
  int _x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  int _y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  int _z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  Serial.println(_x);
  Serial.println(_y);
  Serial.println(_z);

  // double verticalAngle = atan2(avX - 507, avY - 520);
  return _z;//(RAD_TO_DEG * verticalAngle);
}

void loop(){
  // getMotion6(AcX&, AcY&, AcZ&, GyX&, GyY&, GyZ&);
  Serial.println(getRollerAngle(&AcX, &AcY, &AcZ, &GyX, &GyY, &GyZ));

  delay(3);
}
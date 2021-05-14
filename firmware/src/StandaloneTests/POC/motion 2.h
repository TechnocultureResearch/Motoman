#ifndef MOTION_H__
#define MOTION_H__

#include <Wire.h>

const int MPU_addr = 0x68; // I2C address of the MPU-6050

void getMotion6(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy,
                int16_t *gz) {
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
  // Tmp = Wire.read() << 8 | Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42
  // (TEMP_OUT_L)
  *gx =
      Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  *gy =
      Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  *gz =
      Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
}

double getRollerAngle() {
  int16_t ax, ay, az, gx, gy, gz;

  // getVerticalAngle
  int i = 0;
  long x = 0;
  long y = 0;
  long z = 0;

  int repeatCount = 5;

  //
  for (i = 0; i < repeatCount; ++i) {
    getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    x = x + ax; //
    y = y + ay; //
    z = z + az; //
  }

  double avX = x / repeatCount;
  double avY = y / repeatCount;

  double verticalAngle = atan2(avX - 507, avY - 520);
  return (RAD_TO_DEG * verticalAngle) + 20.0; // 20 is a magic offset
}

void setup_mpu6050() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0);    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}

#endif
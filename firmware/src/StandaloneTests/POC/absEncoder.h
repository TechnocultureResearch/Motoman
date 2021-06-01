#ifndef ABS_ENCODER_H___
#define ABS_ENCODER_H___


#include <Arduino.h>
#include <SPI.h>

#include "util.hpp"

#define ABS_ENC_CS 2 // Chip or Slave select

uint16_t ABSposition = 0;
// uint16_t ABSposition_last = 0;
uint8_t temp[2]; // This one.

float deg = 0.00;

void setup_absEncoder() {
  pinMode(ABS_ENC_CS, OUTPUT); // Slave Select
  digitalWrite(ABS_ENC_CS, HIGH);
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV32);
  Serial.flush();
  delay(2000);
  SPI.end();
}

uint8_t SPI_T(uint8_t msg) // Repetive SPI transmit sequence
{
  uint8_t msg_temp = 0;         // vairable to hold recieved data
  digitalWrite(ABS_ENC_CS, LOW);        // select spi device
  msg_temp = SPI.transfer(msg); // send and recieve
  digitalWrite(ABS_ENC_CS, HIGH);       // deselect spi device
  return (msg_temp);            // return recieved byte
}

double getRotaryAngle() {
  delay(10);               // wait a bit till next check

  uint8_t recieved = 0xA5; // just a temp vairable
  ABSposition = 0;         // reset position vairable

  SPI.begin(); // start transmition
  digitalWrite(ABS_ENC_CS, LOW);

  SPI_T(0x10); // issue read command

  recieved = SPI_T(0x00); // issue NOP to check if encoder is ready to send

  while (recieved != 0x10) // loop while encoder is not ready to send
  {
    recieved = SPI_T(0x00); // cleck again if encoder is still working
    delay(2);               // wait a bit
  }

  temp[0] = SPI_T(0x00); // Recieve MSB
  temp[1] = SPI_T(0x00); // recieve LSB

  digitalWrite(ABS_ENC_CS, HIGH); // just to make sure
  SPI.end();              // end transmition

  temp[0] &= ~0xF0; // mask out the first 4 bits

  ABSposition = temp[0] << 8; // shift MSB to correct ABSposition in ABSposition message
  ABSposition += temp[1]; // add LSB to ABSposition message to complete message

  deg = (float) ABSposition;
  deg = deg * 0.08789; // aprox 360/4096
  Serial.println(deg); // send position in degrees

  return deg;
}

#endif
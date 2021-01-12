#define I2C_SCAN


#include <Arduino.h>
#include <Wire.h>


#ifdef I2C_SCAN 
  void I2CSetup() {
    Wire.begin(); // Wire communication begin
    Serial.begin(9600); // The baudrate of Serial monitor is set in 9600
    while (!Serial); // Waiting for Serial Monitor
    Serial.println("\nI2C Scanner");
  }
  void I2CScan() {
     byte error, address; //variable for error and I2C address
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000); // wait 5 seconds for the next I2C scan
  }
  #define SCAN_SETUP() I2CSetup()
  #define SCAN() I2CScan()
#else
  #define SCAN_SETUP()
  #define SCAN()
#endif

void setup() {
  // put your setup code here, to run once:
  SCAN_SETUP();
}

void loop() {
  // put your main code here, to run repeatedly:
  SCAN();
}
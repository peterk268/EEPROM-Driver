#include <Wire.h>

#define EEPROM_SIZE 128 * 1024 // 1 Mbit = 128 KB
#define EEPROM_ADDR 0xA0

// Call in setup()
void i2c_setup() {
    Wire.begin();
}

void write_EEPROM(int address, byte data) {
    // Start communication with the EEPROM
    Wire.beginTransmission(EEPROM_ADDR);

    // Send the memory address to write to
    Wire.write((byte)(address >> 8));  // High byte
    Wire.write((byte)(address & 0xFF));  // Low byte

    // Send the data to write
    Wire.write(data);

    // End the transmission
    Wire.endTransmission();

    // STM datasheet specifies write is completed within 5ms.
    delay(5);
}

byte read_EEPROM(int address) {
    byte data = 0;

    // Start communication with the EEPROM
    Wire.beginTransmission(EEPROM_ADDR);

    // Send the memory address to read from
    Wire.write((byte)(address >> 8));  // address advanced by a byte to get end byte
    Wire.write((byte)(address & 0xFF));  // address int converted to byte to get start byte

    // End the transmission
    Wire.endTransmission();

    // Request data from the EEPROM
    Wire.requestFrom(EEPROM_ADDR, 1);

    // Read the data from the EEPROM
    if (Wire.available()) {
        data = Wire.read();
    }

    return data;
}

// Example: Write data to EEPROM
//   for (int i = 0; i < EEPROM_SIZE; i++) {
//     writeEEPROM(i, i); // Writing incrementing values for testing
//   }

// Example: Read data from EEPROM and print to Serial Monitor
//   for (int i = 0; i < EEPROM_SIZE; i++) {
//     byte value = readEEPROM(i);
//     Serial.print("Address ");
//     Serial.print(i);
//     Serial.print(": ");
//     Serial.println(value);
//   }
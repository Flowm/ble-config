#include "HmBle.hpp"

#define SerialCmd Serial
#define SerialBle Serial1

HmBle ble(&SerialCmd, &SerialBle);
char inChar;

void setup() {
  SerialCmd.begin(9600);
  SerialBle.begin(9600);

  delay(1000);
  ble.usage();
  SerialBle.print("AT");
}

void loop() {
  ble.read();
  ble.handleInput();
}

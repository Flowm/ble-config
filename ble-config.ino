#include "HmBle.hpp"

#define SerialCmd Serial
#define SerialBle Serial1

HmBle ble(&SerialCmd, &SerialBle);

void setup() {
  SerialCmd.begin(9600);
  SerialBle.begin(9600);

  delay(1000);
  ble.usage();
}

void loop() {
  ble.handleInput();
}

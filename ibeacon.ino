#include "jnhuamao_hm_ble.h"

#define SerialCmd Serial
#define SerialBle Serial1

HmBle ble;
char inChar;

void setup() {
  SerialCmd.begin(9600);
  SerialBle.begin(9600);

  delay(1000);
  ble.usage();
  SerialBle.println();
}

void loop() {
  ble.read();
  ble.handleInput();
}

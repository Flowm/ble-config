#define SerialCmd Serial
#define SerialBle Serial1

char inChar;

void setup() {
  SerialCmd.begin(9600);
  SerialBle.begin(9600);
}

void loop() {
  if (SerialBle.available() > 0) {
    inChar = SerialBle.read();
    SerialCmd.write(inChar);
  }

  if (SerialCmd.available() > 0) {
    inChar = SerialCmd.read();
    SerialCmd.println();
    switch (inChar) {
      case '1':
        SerialBle.print("AT+VERR?");
        break;
      case '2':
        SerialBle.print("AT+RENEW");
        break;
      case '3':
        SerialBle.print("AT+RESET");
        break;
      case '4':
        SerialBle.print("AT");
        break;
      case '5':
        SerialBle.print("AT+MARJ0x0A00");
        break;
      case '6':
        SerialBle.print("AT+MINO0x00A0");
        break;
      case '7':
        SerialBle.print("AT+ADVI5");
        break;
      case '8':
        SerialBle.print("AT+NAMEFMHOME");
        break;
      case '9':
        SerialBle.print("AT+ADTY3");
        break;
      case 'a':
        SerialBle.print("AT+IBEA1");
        break;
      case 'b':
        SerialBle.print("AT+DELO2");
        break;
      case 'c':
        SerialBle.print("AT+PWRM0");
        break;
      case 'd':
        SerialBle.print("AT+RESET");
        break;
      default:
        SerialCmd.print(
            "1 AT+VERR?\n"
            "2 AT+RENEW\n"
            "3 AT+RESET\n"
            "4 AT\n"
            "5 AT+MARJ0xA001\n"
            "6 AT+MINO0xB001\n"
            "7 AT+ADVI5\n"
            "8 AT+NAMEHMKI\n"
            "9 AT+ADTY3\n"
            "a AT+IBEA1\n"
            "b AT+DELO2\n"
            "c AT+PWRM0\n"
            "d AT+RESET\n"
            );
        break;
    }
  }
}

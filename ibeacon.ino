#define SerialCmd Serial
#define SerialBle Serial1

char inChar;

void setup() {
  SerialCmd.begin(9600);
  SerialBle.begin(9600);

  delay(1000);
  usage();
  SerialBle.println();
}

void loop() {
  readBle();

  if (SerialCmd.available() > 0) {
    inChar = SerialCmd.read();
    SerialCmd.println();
    switch (inChar) {
      case 'i':
        sendCmd("AT+VERR?");
        sendCmd("AT+ADDR?");
        sendCmd("AT+BAUD?");
        break;
      case '1':
        sendCmd("AT+VERR?");
        break;
      case '2':
        sendCmd("AT+RENEW");
        break;
      case '3':
        sendCmd("AT+RESET");
        break;
      case '4':
        sendCmd("AT");
        break;
      case '5':
        sendCmd("AT+MARJ0x0A00");
        break;
      case '6':
        sendCmd("AT+MINO0x00A0");
        break;
      case '7':
        sendCmd("AT+ADVI5");
        break;
      case '8':
        sendCmd("AT+NAMEFMHOME");
        break;
      case '9':
        sendCmd("AT+ADTY3");
        break;
      case 'a':
        sendCmd("AT+IBEA1");
        break;
      case 'b':
        sendCmd("AT+DELO2");
        break;
      case 'c':
        sendCmd("AT+PWRM0");
        break;
      case 'd':
        sendCmd("AT+RESET");
        break;
      default:
        usage();
        break;
    }
  }
}

void usage() {
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
}

void sendCmd(const char* cmd) {
  SerialCmd.printf("> %s\n", cmd);
  SerialBle.print(cmd);
  delay(100);
  readBle();
  SerialCmd.println();
}

void readBle() {
  while (SerialBle.available() > 0) {
    inChar = SerialBle.read();
    SerialCmd.write(inChar);
  }
}

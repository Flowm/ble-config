#include "jnhuamao_hm_ble.h"

void HmBle::read() {
	while (SerialBle.available() > 0) {
		char inChar = SerialBle.read();
		SerialCmd.write(inChar);
	}
}

void HmBle::send(const char* cmd, bool echo) {
	if (echo) {
		SerialCmd.printf("> %s\n", cmd);
	}
	SerialBle.print(cmd);
	delay(100);
	read();
	SerialCmd.println();
}

void HmBle::handleInput() {
	if (SerialCmd.available() <= 0) {
		return;
	}
	SerialCmd.println();
	char input = SerialCmd.read();
	switch (input) {
		case 'i': // Info
			send("AT+VERR?");
			send("AT+ADDR?");
			send("AT+BAUD?");
			break;
		case '1':
			send("AT+VERR?");
			break;
		case '2':
			send("AT+RENEW");
			break;
		case '3':
			send("AT+RESET");
			break;
		case '4':
			send("AT");
			break;
		case '5':
			send("AT+MARJ0x0A00");
			break;
		case '6':
			send("AT+MINO0x00A0");
			break;
		case '7':
			send("AT+ADVI5");
			break;
		case '8':
			send("AT+NAMEFMHOME");
			break;
		case '9':
			send("AT+ADTY3");
			break;
		case 'a':
			send("AT+IBEA1");
			break;
		case 'b':
			send("AT+DELO2");
			break;
		case 'c':
			send("AT+PWRM0");
			break;
		case 'd':
			send("AT+RESET");
			break;
		default:
			usage();
			break;
	}
}

void HmBle::usage() {
	SerialCmd.print(
			"Commands\n"
			"i Info\n"
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

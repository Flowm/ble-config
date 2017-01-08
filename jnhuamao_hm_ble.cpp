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

void HmBle::usage() {
	SerialCmd.print(
			"Commands\n"
			"i - Info\n"
			"r - Reboot\n"
			"f - Factory reset\n"
			"b - Configure beacon\n"
	);
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
			send("AT+MODE?");
			send("AT+BAUD?");
			break;
		case 'r': // Reboot
			send("AT+RESET");
			break;
		case 'f': // Factory reset
			send("AT+RENEW");
			break;
		case 'b': // Configure Beacon
			configureBeacon();
			break;
		default:
			usage();
			break;
	}
}

void HmBle::configureBeacon() {
	send("AT+RENEW");	   // Factory reset
	send("AT+RESET");	   // Reboot
	delay(5000);		   // Wait after reboot
	send("AT");      	   // Should return OK
	send("AT+MARJ0x0A00"); // iBeacon Major number
	send("AT+MINO0x00A0"); // iBeacon Minor number
	send("AT+ADVI5");	   // Advertising interval
	send("AT+NAMEFMHOME"); // Set Name
	send("AT+ADTY3");	   // Disable connection
	send("AT+IBEA1");	   // Enable iBeacon mode
	send("AT+DELO2");	   // Broadcast-only
	send("AT+PWRM0");	   // Enable auto-sleep
	send("AT+RESET");	   // Reboot
}

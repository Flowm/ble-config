#include "HmBle.hpp"

void HmBle::read() {
	while (bleSerial->available() > 0) {
		char inChar = bleSerial->read();
		cmdSerial->write(inChar);
	}
}

void HmBle::send(const char* cmd, bool echo) {
	if (echo) {
		cmdSerial->printf("> %s\r\n", cmd);
	}
	bleSerial->print(cmd);
	delay(100);
	read();
	cmdSerial->println();
}

void HmBle::usage() {
	cmdSerial->print(
			"Commands\r\n"
			"i - Info\r\n"
			"r - Reboot\r\n"
			"f - Factory reset\r\n"
			"b - Configure beacon\r\n"
			"c - Console\r\n"
	);
}

void HmBle::handleInput() {
	if (cmdSerial->available() <= 0) {
		return;
	}
	cmdSerial->println();
	char input = cmdSerial->read();
	switch (input) {
		case 'i': // Info
			send("AT");
			send("AT+VERR?");
			send("AT+ADDR?");
			send("AT+MODE?");
			send("AT+BAUD?");
			break;
		case 'c': // Console
			console();
			break;
		case 'r': // Reboot
			send("AT+RESET");
			break;
		case 'f': // Factory reset
			factoryReset();
			break;
		case 'b': // Configure Beacon
			configureBeacon();
			break;
		case '[': // Configure Slave
			configureSlave();
			break;
		case ']': // Configure Master
			configureMaster();
			break;
		default:
			usage();
			break;
	}
}

void HmBle::factoryReset() {
	send("AT+RENEW");           // Factory reset
	send("AT+RESET");           // Reboot
	delay(5000);                // Wait for reboot
	send("AT");                 // Check status
}

void HmBle::configureBeacon() {
	factoryReset();
	send("AT+MARJ0x0A00");      // iBeacon Major number
	send("AT+MINO0x00A0");      // iBeacon Minor number
	send("AT+ADVI5");           // Advertising interval
	send("AT+NAMEFMHOME");      // Set Name
	send("AT+ADTY3");           // Disable connection
	send("AT+IBEA1");           // Enable iBeacon mode
	send("AT+DELO2");           // Broadcast-only
	send("AT+PWRM0");           // Enable auto-sleep
	send("AT+RESET");           // Reboot
	/*
	send("AT+IBE074278BDA");    // Set Beacon UUID1
	send("AT+IBE1B6444520");    // Set Beacon UUID2
	send("AT+IBE28F0C720E");    // Set Beacon UUID3
	send("AT+IBE3AF059935");    // Set Beacon UUID4
	*/
}

void HmBle::configureSlave() {
	factoryReset();
	send("AT+CONF0C77F9484EF"); // Connect
	send("AT+ROLE1");           // Set role
}

void HmBle::configureMaster() {
	factoryReset();
	send("AT+CONF0C77F94808A"); // Connect
	send("AT+ROLE0");           // Set role
}

void HmBle::console() {
	char inChar;
	while (true) {
		if (bleSerial->available() > 0) {
			inChar = bleSerial->read();
			if (inChar == '\r') {
				cmdSerial->write('\n');
			}
			cmdSerial->write(inChar);
		}
		if (cmdSerial->available() > 0) {
			inChar = cmdSerial->read();
			bleSerial->write(inChar);
		}
	}
}

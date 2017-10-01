#include "HmBle.hpp"

void HmBle::readAll() {
	if (bleSerial->available() > 0) {
		do {
			cmdSerial->write(bleSerial->read());
		} while (bleSerial->available() > 0);
		cmdSerial->println();
	}
}

void HmBle::send(const char* cmd, bool echo) {
	if (echo) {
		cmdSerial->printf("> %s\r\n", cmd);
	}
	bleSerial->print(cmd);
	delay(200);
	readAll();
}

void HmBle::sendf(const char* fmt, ...) {
	char buf[32];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args);
	va_end(args);
	send(buf);
}

void HmBle::usage() {
	cmdSerial->print(
			"Commands:\r\n"
			"info           Show info\r\n"
			"wakeup         Wakup device from sleep mode\r\n"
			"reboot         Reboot\r\n"
			"factory        Perform factory reset\r\n"
			"beacon         Configure as beacon\r\n"
			"slave          Configure as peripheral device\r\n"
			"master [addr]  Configure as central device and connect to addr\r\n"
			"console        Serial console\r\n"
	);
}

void HmBle::handleInput() {
	char *line, *cmd, *args;

	if (cmdSerial->available() <= 0) {
		// No input
		return;
	}

	if (!(line = conEmu.read_key(cmdSerial->read()))) {
		// Line not complete (yet)
		return;
	}

	// Tokenize string to get command
	if (!(cmd = strtok(line, " "))) {
		promt();
		return;
	}

	switch (str2int(cmd)) {
		case str2int("info"):
		case str2int("i"):
			info();
			break;

		case str2int("wakeup"):
		case str2int("w"):
			wakeup();
			break;

		case str2int("reboot"):
		case str2int("r"):
			send("AT+RESET");
			break;

		case str2int("factory"):
		case str2int("f"):
			factoryReset();
			break;

		case str2int("beacon"):
		case str2int("b"):
			if ((args = strtok(NULL, "")))
				configureBeacon(args);
			break;

		case str2int("slave"):
		case str2int("s"):
			configureSlave();
			break;

		case str2int("master"):
		case str2int("m"):
			if ((args = strtok(NULL, "")))
				configureMaster(args);
			break;

		case str2int("console"):
		case str2int("c"):
			console();
			break;

		case str2int("help"):
		case str2int("h"):
			usage();
			break;

		default:
			if (strlen(cmd) >= 2 && !strncmp(cmd, "AT", 2)) {
				// Send AT command
				send(cmd);
			} else {
				usage();
			}
			break;
	}

	// Print promt
	promt();
}

void HmBle::info() {
	send("AT");
	send("AT+VERR?");
	send("AT+ADDR?");
	send("AT+NAME?");
	send("AT+MODE?");
	send("AT+ROLE?");
	send("AT+IBEA?");
	send("AT+BAUD?");
	send("AT+RADD?");
}

void HmBle::wakeup() {
	// Send a long string (length > 80 or more) to wakeup the device
	send("I am iron man, I am iron man, I am iron man, I am iron man, I am iron man, I am iron man...");
}

void HmBle::factoryReset() {
	send("AT+RENEW");           // Factory reset
	send("AT+RESET");           // Reboot
	delay(5000);                // Wait for reboot
	send("AT");                 // Check status
}

void HmBle::configureBeacon(char* args) {
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
	send("AT+ROLE0");           // Set role to peripheral
	send("AT+ADDR?");           // Show addr
}

void HmBle::configureMaster(char* args) {
	factoryReset();
	send("AT+ROLE1");           // Set role to central
	sendf("AT+CON%s", args);    // Set device to connect to
}

void HmBle::console() {
	char key;

	while (true) {
		if (bleSerial->available() > 0) {
			key = bleSerial->read();
			if (key == '\r') {
				cmdSerial->write('\n');
			}
			cmdSerial->write(key);
		}
		if (cmdSerial->available() > 0) {
			key = cmdSerial->read();
			bleSerial->write(key);
		}
	}
}

void HmBle::promt() {
	cmdSerial->write("\r\n# ");
}

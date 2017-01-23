#pragma once

#include "Wire.h"

class HmBle {
	public:
		HmBle(Stream* cmdSerial, Stream* bleSerial) : cmdSerial(cmdSerial), bleSerial(bleSerial) {}

		void read();
		void send(const char* cmd, bool echo=true);

		void usage();
		void handleInput();

		void factoryReset();
		void configureBeacon();
		void configureSlave();
		void configureMaster();

		void console();
	private:
		Stream* cmdSerial;
		Stream* bleSerial;
};

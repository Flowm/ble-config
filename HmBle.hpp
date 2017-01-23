#pragma once

#include "Wire.h"
#include "ConEmu.hpp"

class HmBle {
	public:
		HmBle(Stream* cmdSerial, Stream* bleSerial) : cmdSerial(cmdSerial), bleSerial(bleSerial), conEmu(cmdSerial) {}

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

		ConEmu conEmu;
};

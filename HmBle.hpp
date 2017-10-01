#pragma once

#include "Wire.h"
#include "ConEmu.hpp"

class HmBle {
	public:
		HmBle(Stream* cmdSerial, Stream* bleSerial) : cmdSerial(cmdSerial), bleSerial(bleSerial), conEmu(cmdSerial) {}

		void readAll();
		void send(const char* cmd, bool echo=true);
		void sendf(const char* fmt, ...);

		void usage();
		void handleInput();

		void info();
		void wakeup();
		void factoryReset();
		void configureBeacon(char* args);
		void configureBeaconPowersave();
		void configureSlave();
		void configureMaster(char* args);

		void console();
	private:
		Stream* cmdSerial;
		Stream* bleSerial;

		ConEmu conEmu;

		void promt();
};

// Compile time bernstein hash function
constexpr unsigned int str2int(const char* str, int h = 0) {
	return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}

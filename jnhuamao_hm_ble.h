#pragma once

#define SerialCmd Serial
#define SerialBle Serial1

#include "Wire.h"

class HmBle {
	public:
		HmBle() {}

		void read();
		void send(const char* cmd, bool echo=true);

		void usage();
		void handleInput();
		void configureBeacon();
	private:
};

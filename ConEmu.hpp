#pragma once

#include "Wire.h"

#define PRINTBUF_SZ 256
#define KBD_BUFFSZ 256

class ConEmu {
  public:
    ConEmu(Stream* con): con(con) {}

    void printf(const char* fmt, ...);
    void clear();
    void delete_chars(int len);
    void clear_line();
    void ansi_esc(const char* seq);

    char* read_key(const char key);

  private:
    Stream* con;
    char kbd_buff[KBD_BUFFSZ];
    int kbd_idx = 0;
    int crs_idx = 0;

    uint16_t special_char_to_keycode(char key);
    uint16_t escape_sequence_to_keycode(char key);
};

#include "ConEmu.hpp"

void ConEmu::printf(const char* fmt, ...) {
  char buff[PRINTBUF_SZ];
  va_list args;
  va_start (args, fmt);
  vsnprintf(buff, sizeof(buff), fmt, args);
  va_end (args);
  con->print(buff);
}

void ConEmu::clear() {
  ansi_esc("2J");
  ansi_esc("H");
}

void ConEmu::delete_chars(int len) {
  for (int i = 0; i < len; i++) {
    ansi_esc("D");
  }
  ansi_esc("0J");
}

void ConEmu::clear_line() {
  ansi_esc("1G");
  ansi_esc("0J");
}

void ConEmu::ansi_esc(const char* seq) {
  char buff[10];
  snprintf(buff, sizeof(buff), "[%s", seq);
  con->write(27);
  con->print(buff);
}

char* ConEmu::read_key(const char key) {
  uint16_t keycode = special_char_to_keycode(key);

  if (keycode) {
    // Handle some special keys for minimal console emulation
    switch (keycode) {
      case KEY_ENTER:
        con->printf("\r\n");
        kbd_buff[kbd_idx] = '\0';
        crs_idx = kbd_idx;
        kbd_idx = 0;
        return kbd_buff;
        break;
      case KEY_BACKSPACE:
        if (crs_idx == kbd_idx) {
          // TODO: Currently only supports deleting characters at the end of
          // the line, as deleting in the middle would require all following
          // characters to be moved
          delete_chars(1);
          if (kbd_idx>0) kbd_idx--;
          if (crs_idx>0) crs_idx--;
        }
        break;
      case KEY_LEFT:
        if (crs_idx>0) {
          ansi_esc("1D");
          crs_idx--;
        }
        break;
      case KEY_RIGHT:
        if (crs_idx<kbd_idx) {
          ansi_esc("1C");
          crs_idx++;
        }
        break;
      case KEY_UP:
        while (crs_idx>kbd_idx) {
          if (!kbd_buff[kbd_idx])
            kbd_buff[kbd_idx] = ' ';
          con->write(kbd_buff[kbd_idx++]);
        }
        break;
    }
  } else if (key == 3) {
    clear_line();
    crs_idx = kbd_idx;
    kbd_idx = 0;
  } else if (kbd_idx >= KBD_BUFFSZ-1) {
    // End line once buffer is full
    read_key('\n');
  } else if (key <= 26) {
    // Ignore unhandled control chars
  } else {
    // Echo and append key to buffer
    con->write(key);
    if (crs_idx > kbd_idx) crs_idx = kbd_idx;
    kbd_buff[crs_idx++] = key;
    if (kbd_idx < crs_idx) kbd_idx++;
  }
  return NULL;
}

uint16_t ConEmu::special_char_to_keycode(char key) {
  uint16_t keycode = 0;

  switch (key) {
    case 10:  // LF
    case 13:  // CR
      keycode = KEY_ENTER;
      break;
    case 8:   // BS
    case 127: // DEL
      keycode = KEY_BACKSPACE;
      break;
    case 9:   // HT
      keycode = KEY_TAB;
      break;
    case 27:
      key = con->read();
      keycode = escape_sequence_to_keycode(key);
      break;
  }
  return keycode;
}

uint16_t ConEmu::escape_sequence_to_keycode(char key) {
  uint16_t keycode = 0;

  if (key == 255) {
    keycode = KEY_ESC;
  } else if (key == 91) {
    char key = con->peek();
    if (key >= 65 && key <= 68) {
      con->read();
      if (key == 65)
        keycode = KEY_UP;
      if (key == 66)
        keycode = KEY_DOWN;
      if (key == 67)
        keycode = KEY_RIGHT;
      if (key == 68)
        keycode = KEY_LEFT;
    } else if (key == 51) {
      con->read();
      key = con->peek();
      if (key == 126) {
        con->read();
        keycode = KEY_DELETE;
      }
    }
  }
  return keycode;
}

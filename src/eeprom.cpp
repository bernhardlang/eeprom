/* eeprom.h
 *
 * Copyright (C) 2018-2019 Bernhard Lang, www.b-lang.ch
 *
 * Based on code by Dominique Lovy, 2013-2015, Université de Genève
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or (at
 * your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "eeprom.h"
#include "command-parser.h"

bool check_eeprom_address(int address, int max, c_command_parser *p) {
  if ((address >= 0) && (address < max)) return true;
  p->respond("Invalid EEPROM address %d (%d..%d)", address, 0, max - 1);
  return false;
}

/**  eeprom command : read or write EEPROM content **/
int8_t eeprom8(uint8_t argc, char **argv, c_command_parser *p) {
  int address;
  uint8_t value;

  address = atoi(argv[1]);
  if (!check_eeprom_address(address, eeprom->max_address(), p)) return -1;

  if (argc > 2) {
     value = atoi(argv[2]);
     eeprom->write(address, value);
  } else {
    eeprom->read(address, value);
    p->respond("%d", value);
  }

  return 0;
}

/**  eeprom16 command : read or write EEPROM 16 bits content **/
int8_t eeprom16(uint8_t argc, char **argv, c_command_parser *p) {
  int address;
 uint16_t value;

  address = atoi(argv[1]);
  if (!check_eeprom_address(address, eeprom->max_address() - 1, p)) return 1;

  if (argc > 2) {
    value = atoi(argv[2]);
    eeprom->write(address, value);
  } else {
    eeprom->read(address, value);
    p->respond("%d", value);
  }

  return 0;
}

/**  eeprom32 command : read or write EEPROM 32 bits content **/
int8_t eeprom32(uint8_t argc, char **argv, c_command_parser *p) {
  int address;
  uint32_t value;

  address = atoi(argv[1]);
  if (!check_eeprom_address(address, eeprom->max_address() - 3, p)) return 1;
  if (argc > 2) {
    value = atoi(argv[2]);
    eeprom->write(address, value);
  } else {
    eeprom->read(address, value);
    p->respond("%ld", value);
  }

  return 0;
}

char to_c(uint8_t data) {
  return ((data < 32) || (data > 127)) ? '.' : data;
}

int8_t dump_eeprom(uint8_t argc, char **argv, c_command_parser *p) {
  uint16_t from = atoi(argv[1]), to = atoi(argv[2]);
  uint32_t i = from & 0xFFF0;
  uint8_t data[8];
  
  memset(data, 0, 8);
  while (i < to) {
    eeprom->read(i, data, 8);
    p->respond("0x%04lX: 0x%02X 0x%02X 0x%02X 0x%02X"
               "  0x%02X 0x%02X 0x%02X 0x%02X %c%c%c%c%c%c%c%c",
               i, data[0], data[1], data[2], data[3], data[4], data[5], data[6],
               data[7], to_c(data[0]), to_c(data[1]), to_c(data[2]),
               to_c(data[3]), to_c(data[4]), to_c(data[5]), to_c(data[6]),
               to_c(data[7]));
    i += 8;
  }

  return 0;
}

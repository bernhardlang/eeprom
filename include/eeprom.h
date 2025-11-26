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

#ifndef _eeprom_h_
#define _eeprom_h_

#include "twi-eeprom.h"

class c_command_parser;

/**  eeprom command : read or write EEPROM content **/
int8_t eeprom8(uint8_t argc, char **argv, c_command_parser *p);
/**  eeprom16 command : read or write EEPROM 16 bits content **/
int8_t eeprom16(uint8_t argc, char **argv, c_command_parser *p);
/**  eeprom32 command : read or write EEPROM 32 bits content **/
int8_t eeprom32(uint8_t argc, char **argv, c_command_parser *p);
int8_t dump_eeprom(uint8_t argc, char **argv, c_command_parser *p);

#endif // _eeprom_h_

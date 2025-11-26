/* eeprom-24lc16.h
 *
 * Copyright (C) 2018 Bernhard Lang, www.b-lang.ch
 *
 * Based on code by Dominique Lovy, 2013-2105, Université de Genève
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

#ifndef _eeprom_24lc16_h_
#define _eeprom_24lc16_h_

#include <stdint.h>
#include <cstddef>
#include "twi-eeprom.h"

class c_eeprom_24lc16: public c_twi_eeprom {
 public:
  
  //! Instantiate.
  c_eeprom_24lc16(int write_protect_pin);

  int8_t begin(void);

  ssize_t write(size_t address, const void *, size_t len);
  ssize_t read(size_t address, void *, size_t len);
  ssize_t read(size_t address, uint8_t *);

  ssize_t read(uint16_t address, size_t max_len, char *);
  ssize_t max_address(void) const { return 2048; };

 private:
  static const uint8_t device_address;
  const int write_protect_pin;
};

#endif // _eeprom_24lc16_h_

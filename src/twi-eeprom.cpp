/* twi-eeprom.cpp
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

#include "twi-eeprom.h"
#include <Wire.h>

c_twi_eeprom::c_twi_eeprom(size_t _page_size)
  : c_persistent_storage(), page_size(_page_size), twi_freq(100000UL) {
}

int8_t c_twi_eeprom::begin(uint32_t freq) {
  twi_freq = freq;
  return begin();
}

int8_t c_twi_eeprom::begin(void) {
  Wire.begin();
#if defined(ARDUINO) && (ARDUINO >= 158)
  if (twi_freq > 0)
    Wire.setClock(twi_freq);
#endif

  return 0;
}

void c_twi_eeprom::end(void) {
  Wire.end();
}

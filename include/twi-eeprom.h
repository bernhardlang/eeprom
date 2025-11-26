/* twi-eeprom.h
 *
 * Copyright (C) 2018 Bernhard Lang, www.b-lang.ch
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

#ifndef _twi_eeprom_h_
#define _twi_eeprom_h_

#include "persistent-storage.h"

class c_twi_eeprom: public c_persistent_storage {
 public:
  //! Instantiate.
  c_twi_eeprom(size_t page_size);

  //! Instantiate with TWI freq.
  int8_t begin(uint32_t twi_freq);
  int8_t begin(void);
  void end(void);
    
 protected:
  size_t page_size;
  uint32_t twi_freq;
};

#endif // _twi_eeprom_h_

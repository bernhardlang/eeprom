/* eeprom_24lc16.cpp
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

#include "eeprom-24lc16.h"
#include "Wire.h"

const uint8_t c_eeprom_24lc16::device_address = 0x50;

c_eeprom_24lc16::c_eeprom_24lc16(int _write_protect_pin)
  : c_twi_eeprom(255), write_protect_pin(_write_protect_pin) {
}

int8_t c_eeprom_24lc16::begin(void) {
  pinMode(write_protect_pin, OUTPUT);
  digitalWrite(write_protect_pin,HIGH); // activate write protection
  return c_twi_eeprom::begin();
}

ssize_t c_eeprom_24lc16::write(size_t address, const void *_buf, size_t len) {
  uint8_t twi_address, i;
  const uint8_t *buf = (const uint8_t *) _buf;
  
  twi_address = ((address >> 8) & 0x07) | device_address;
  
  digitalWrite(write_protect_pin, LOW);
  Wire.beginTransmission(twi_address);
  Wire.write(address & 0xff);
  for (i = 0; i < len; i++)
    Wire.write(buf[i]);
  Wire.endTransmission();
  digitalWrite(write_protect_pin, HIGH);
  delay(5);

  return len;
}

ssize_t c_eeprom_24lc16::read(size_t address, uint8_t *byte) {
  uint8_t twi_address = ((address >> 8) & 0x07) | device_address;
  Wire.beginTransmission(twi_address);
  Wire.write((uint8_t) (address & 0xFF));  // random read
  Wire.endTransmission();
  delay(5);
  Wire.requestFrom(twi_address, (uint8_t) 1);
  if (!Wire.available()) return -1;
  *byte = Wire.read();
  return 1;
}

ssize_t c_eeprom_24lc16::read(size_t address, void *_buf, size_t len) {
  uint8_t *buf = (uint8_t*) _buf;
  size_t i;

  for (i = 0; i < len; i++)
    if (read(address + i, buf + i) < 0) return i - 1;
  return len;
}

ssize_t c_eeprom_24lc16::read(uint16_t address, size_t max_len, char *buf) {
  ssize_t bytes_read = read(address, buf, max_len);
  if (bytes_read >= 0) buf[bytes_read] = 0;
  return bytes_read;
}

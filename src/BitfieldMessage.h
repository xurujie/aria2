/* <!-- copyright */
/*
 * aria2 - The high speed download utility
 *
 * Copyright (C) 2006 Tatsuhiro Tsujikawa
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * In addition, as a special exception, the copyright holders give
 * permission to link the code of portions of this program with the
 * OpenSSL library under certain conditions as described in each
 * individual source file, and distribute linked combinations
 * including the two.
 * You must obey the GNU General Public License in all respects
 * for all of the code used other than OpenSSL.  If you modify
 * file(s) with this exception, you may extend this exception to your
 * version of the file(s), but you are not obligated to do so.  If you
 * do not wish to do so, delete this exception statement from your
 * version.  If you delete this exception statement from all source
 * files in the program, then also delete it here.
 */
/* copyright --> */
#ifndef _D_BITFIELD_MESSAGE_H_
#define _D_BITFIELD_MESSAGE_H_

#include "SimplePeerMessage.h"

class BitfieldMessage : public SimplePeerMessage {
private:
  unsigned char* bitfield;
  int bitfieldLength;
  // for check
  int pieces;

  char* msg;
  int msgLength;

  void init() {
    bitfield = 0;
    bitfieldLength = 0;
    pieces = 0;
    msg = 0;
    msgLength = 0;
  }
public:
  BitfieldMessage()
    :SimplePeerMessage()
  {
    init();
  }

  BitfieldMessage(const unsigned char* bitfield,
		  int bitfieldLength)
    :SimplePeerMessage()
  {
    init();
    setBitfield(bitfield, bitfieldLength);
  }

  virtual ~BitfieldMessage() {
    if(bitfield != NULL) {
      delete [] bitfield;
    }
    if(msg != NULL) {
      delete [] msg;
    }
  }

  enum ID_t {
    ID = 5
  };

  void setBitfield(const unsigned char* bitfield, int bitfieldLength);
  const unsigned char* getBitfield() const { return bitfield; }

  int getBitfieldLength() const { return bitfieldLength; }

  void setPieces(int pieces) {
    this->pieces = pieces;
  }
  int getPieces() const { return pieces;}

  static BitfieldMessage* create(const char* data, int dataLength);

  virtual int getId() const { return ID; }
  virtual void receivedAction();
  virtual const char* getMessage();
  virtual int getMessageLength();
  virtual void check() const;
  virtual string toString() const;
};

#endif // _D_BITFIELD_MESSAGE_H_

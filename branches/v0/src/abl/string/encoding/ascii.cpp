#include "abl/string/encoding/ascii.hpp"
#include "abl/string/string.hpp"


namespace abl 
{


  const char* ascii_encoding_c::_names[] =
    {
      "ASCII",
      NULL
    };


  const text_encoding_c::CharacterMap ascii_encoding_c::_charMap = 
    {
      /* 00 */	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
      /* 10 */	0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 
      /* 20 */	0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 
      /* 30 */	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 
      /* 40 */	0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 
      /* 50 */	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, 
      /* 60 */	0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 
      /* 70 */	0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f, 
      /* 80 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
      /* 90 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
      /* a0 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
      /* b0 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
      /* c0 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
      /* d0 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
      /* e0 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
      /* f0 */	  -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, 
    };


  ascii_encoding_c::ascii_encoding_c()
  {
  }


  ascii_encoding_c::~ascii_encoding_c()
  {
  }


  const char* ascii_encoding_c::canonicalName() const
  {
    return _names[0];
  }


  bool ascii_encoding_c::isA(const std::string& encodingName) const
  {
    for (const char** name = _names; *name; ++name)
      {
	if (abl::icompare(encodingName, *name) == 0)
	  return true;
      }
    return false;
  }


  const text_encoding_c::CharacterMap& ascii_encoding_c::characterMap() const
  {
    return _charMap;
  }


  int ascii_encoding_c::convert(const unsigned char* bytes) const
  {
    return _charMap[*bytes];
  }


  int ascii_encoding_c::convert(int ch, unsigned char* bytes, int length) const
  {
    if (ch >= 0 && ch <= 127)
      {
	if (bytes && length >= 1)
	  *bytes = (unsigned char) ch;
	return 1;
      }
    else return 0;
  }


  int ascii_encoding_c::queryConvert(const unsigned char* bytes, int length) const
  {
    if (1 <= length)
      return _charMap [*bytes];
    else
      return -1;
  }


  int ascii_encoding_c::sequenceLength(const unsigned char* bytes, int length) const
  {
    return 1;
  }


} 
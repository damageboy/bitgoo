#include "bitgoo.h"


int32_t CountBits::Vanilla(uint64_t *bits, int32_t bitLength, int64_t offset)
{
  auto b = 0;
  auto value = bits[0];
  auto leftInULong = 64;

  auto i = 0;

  while (b++ < offset) {
    if ((value & 0x1) == 1)
      i++;
    value >>= 1;
    leftInULong--;

    if (leftInULong != 0)
      continue;
    leftInULong = 64;
    value = *(++bits);
  }

  if ((value & 0x1) == 1)
    i++;
  else return -1;

  return i;
}
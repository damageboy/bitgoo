#include "bitgoo.h"

int32_t GetNthBitOffset::Naive(uint64_t *bits, int32_t bitLength, int64_t n)
{
  auto b = 0;
  auto value = *bits;
  auto inChunk = 64;

  auto i = 0;

  while (i < bitLength) {
    if (value & 0x1)
      i++;
    if (i == n)
      break;
    value >>= 1;
    inChunk--;
    b++;

    if (inChunk != 0)
      continue;
    inChunk = 64;
    value = *(++bits);
  }

  return b;
}
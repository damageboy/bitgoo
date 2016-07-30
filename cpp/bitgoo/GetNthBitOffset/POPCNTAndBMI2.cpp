#include "bitgoo.h"

int32_t GetNthBitOffset::POPCNTAndBMI2(uint64_t *bits, int32_t bitLength, int64_t n)
{
  auto p64 = bits;
  // As long as we are still looking for more than 64 bits
  int32_t prevIndex;
  do {
    IACA_START
    prevIndex = n;
    n -= _mm_popcnt_u64(*(p64++));
  } while (n > 0);
  IACA_END

  p64--;
  auto pos = _tzcnt_u64(_pdep_u64(1ULL << (prevIndex - 1), *p64));
  return ((p64 - bits) * 64) + pos;
}
#include "bitgoo.h"

#include <assert.h>

int32_t GetNthBitOffset::POPCNTAndBMI2Unrolled(uint64_t *bits, int32_t bitLength, int64_t n)
{
  auto p64 = bits;
  for (; n >= 256; p64 += 4) {
    IACA_START
    n -= _mm_popcnt_u64(p64[0]) +
         _mm_popcnt_u64(p64[1]) +
         _mm_popcnt_u64(p64[2]) +
         _mm_popcnt_u64(p64[3]);
  }
  IACA_END
  // As long as we are still looking for more than 64 bits
  auto prevN = n;
  while (n > 0) {
    prevN = n;
    n -= _mm_popcnt_u64(*(p64++));
  }

  p64--;

  auto pos = _tzcnt_u64(_pdep_u64(1ULL << (prevN - 1), *p64));
  return ((p64 - bits) * 64) + pos;
}
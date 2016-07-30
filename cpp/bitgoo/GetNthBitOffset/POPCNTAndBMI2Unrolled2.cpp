#include "bitgoo.h"

int32_t GetNthBitOffset::POPCNTAndBMI2Unrolled2(uint64_t *bits, int32_t bitLength, int64_t n)
{
  auto p64 = bits;

  uint64_t cnt1,cnt2,cnt3,cnt4;
  for (; n >= 256; p64 += 4) {
      IACA_START
      cnt1 = cnt2 = cnt3 = cnt4 = 0;
      cnt1 += _mm_popcnt_u64(p64[0]);
      cnt2 += _mm_popcnt_u64(p64[1]);
      cnt3 += _mm_popcnt_u64(p64[2]);
      cnt4 += _mm_popcnt_u64(p64[3]);
      n -= cnt1 + cnt2 + cnt3 + cnt4;
  }
  IACA_END

  // As long as we are still looking for more than 64 bits
  auto prevIndex = n;
  while (n > 0) {
    prevIndex = n;
    n -= _mm_popcnt_u64(*(p64++));
  }

  p64--;

  auto pos = _tzcnt_u64(_pdep_u64(1ULL << (prevIndex - 1), *p64));
  return ((p64 - bits) * 64) + pos;
}
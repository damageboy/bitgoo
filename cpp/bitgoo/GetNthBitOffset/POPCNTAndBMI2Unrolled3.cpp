#include "bitgoo.h"

int32_t GetNthBitOffset::POPCNTAndBMI2Unrolled3(__uint64_t *bits, __int32_t bitLength, __int64_t n)
{
  auto p64 = bits;

  __uint64_t cnt1,cnt2,cnt3,cnt4;
  int unrolled_len;

  // unrolled_len == how many 256bit/32b complete chunks we have to scan
  // This will be used for the optimized/unrolled loop
  // We shove this into a while, because if the
  while ((unrolled_len = (n >> 8) << 2) >= MEGA_UNROLL_MIN) {
    cnt1 = cnt2 = cnt3 = cnt4 = 0;
    auto i = 0;
    for (; i < unrolled_len; i += 4) {
      cnt1 += _mm_popcnt_u64(bits[i + 0]);
      cnt2 += _mm_popcnt_u64(bits[i + 1]);
      cnt3 += _mm_popcnt_u64(bits[i + 2]);
      cnt4 += _mm_popcnt_u64(bits[i + 3]);
    }
    n -= cnt1 + cnt2 + cnt3 + cnt4;
    p64 += i;
  }
  for (; n >= 256; p64 += 4)
    n -= _mm_popcnt_u64(p64[0]) +
         _mm_popcnt_u64(p64[1]) +
         _mm_popcnt_u64(p64[2]) +
         _mm_popcnt_u64(p64[3]);

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
#include "bitgoo.h"

int32_t GetNthBitOffset::POPCNTAndBMI1Unrolled(uint64_t *q, int32_t bitLength, int64_t n)
{
  for (; n >= 256; q += 4)
    n -= _mm_popcnt_u64(q[0]) + _mm_popcnt_u64(q[1]) + _mm_popcnt_u64(q[2]) + _mm_popcnt_u64(q[3]);

  // As long as we are still looking for more than 64 bits
  auto prevIndex = n;
  while (n > 0) {
    prevIndex = n;
    n -= _mm_popcnt_u64(*(q++));
  }

  auto p2 = (uint32_t *) (q - 1);
  n = prevIndex - _mm_popcnt_u32(*p2);
  if (n > 0) {
    prevIndex = n;
    p2++;
  }

  auto prevValue = *p2;
  auto pos = (p2 - (uint32_t *) q) * 32;
  while (prevIndex > 0) {
    auto bp = __builtin_ffs(prevValue);
    pos += bp;// - 1;
    prevIndex--;
    prevValue >>= bp;
  }

  return pos - 1;
}
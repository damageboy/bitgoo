#include "bitgoo.h"

int32_t CountBits::IntrinsicsUnrolled2(uint64_t *bits, int32_t bitLength, int64_t offset)
{
  __uint64_t c1,c2,c3,c4;
  c1 = c2 = c3 = c4 = 0;

  if (is_bit_set(bits, offset))
    return -1;

  auto index = 0;

  // Bits -> longs -> "complete" groups of 4 longs
  auto n = ((offset / 64) / 4) * 4;
  for (auto i = 0; i < n; i += 4)
    c1 += _mm_popcnt_u64(bits[i + 0]), c2 += _mm_popcnt_u64(bits[i + 1]), c3 += _mm_popcnt_u64(bits[i + 2]), c4 += _mm_popcnt_u64(bits[i + 3]);
  index += c1 + c2 + c3 + c4;
  offset -= n * 64;
  bits += n;

  while (offset >= 63) {
    index += _mm_popcnt_u64(*(bits++));
    offset -= 64;
  }

  return index + _mm_popcnt_u64(*bits & ((1ULL << (offset + 1)) - 1));
}
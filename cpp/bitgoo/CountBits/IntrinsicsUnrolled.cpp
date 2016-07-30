#include "bitgoo.h"

int32_t CountBits::IntrinsicsUnrolled(uint64_t *bits, int32_t bitLength, int64_t offset)
{
  if (is_bit_set(bits, offset))
    return -1;

  auto index = 0ULL;

  // Bits -> longs -> "complete" groups of 4 longs
  auto n = ((offset / 64) / 4) * 4;
  for (auto i = 0; i < n; i += 4) {
    IACA_START
    index += _mm_popcnt_u64(bits[i + 0]) + _mm_popcnt_u64(bits[i + 1]) + _mm_popcnt_u64(bits[i + 2]) + _mm_popcnt_u64(bits[i + 3]);
  }
  IACA_END
  offset -= n * 64;
  bits += n;

  while (offset >= 63) {
    index += _mm_popcnt_u64(*(bits++));
    offset -= 64;
  }

  return offset >= 0 ?
         index + _mm_popcnt_u64(*bits & ((1ULL << (offset + 1)) - 1)) :
         index;
}
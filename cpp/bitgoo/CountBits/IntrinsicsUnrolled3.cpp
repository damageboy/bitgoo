#include "bitgoo.h"

int32_t CountBits::IntrinsicsUnrolled3(uint64_t *q, int32_t bitLength, int64_t key)
{
  if (is_bit_set(q, key))
    return -1;

  auto index = 0;

  // Bits -> longs -> "complete" groups of 4 longs
  while (key >= 255) {
    IACA_START
    index += _mm_popcnt_u64(q[0]) + _mm_popcnt_u64(q[1]) + _mm_popcnt_u64(q[2]) + _mm_popcnt_u64(q[3]);
    q += 4;
    key -= 256;
  }
  IACA_END

  while (key >= 63) {
    index += _mm_popcnt_u64(*(q++));
    key -= 64;
  }

  return index + _mm_popcnt_u64(*q & ((1ULL << (key + 1)) - 1));
}
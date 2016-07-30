#include "bitgoo.h"

int32_t CountBits::AsmUnrolled(uint64_t *q, int32_t bitLength, int64_t key)
{
  if (is_bit_set(q, key))
    return -1;

  auto index = 0ULL;

  // Bits -> longs -> "complete" groups of 4 longs
  auto n = ((key / 64) / 4) * 4;
  for (auto i = 0; i < n; i += 4) {
    IACA_START
    __asm__(
    "popcnt %1, %1  \n\t"
    "popcnt %2, %2  \n\t"
    "popcnt %3, %3  \n\t"
    "popcnt %4, %4  \n\t"
    "add %1, %0     \n\t"
    "add %2, %0     \n\t"
    "add %3, %0     \n\t"
    "add %4, %0     \n\t" // +r means input/output, r means intput
    : "+r" (index)
    : "r" (q[i + 0]), "r" (q[i + 1]), "r" (q[i + 2]), "r" (q[i + 3]));
  }
  IACA_END
  key -= n * 64;
  q += n;

  while (key >= 63) {
    index += _mm_popcnt_u64(*(q++));
    key -= 64;
  }

  return index + _mm_popcnt_u64(*q & ((1ULL << (key + 1)) - 1));
}
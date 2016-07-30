#include "bitgoo.h"

int32_t GetNthBitOffset::POPCNTAndBMI2ASMUnrolled3(uint64_t *bits, int32_t bitLength, int64_t n)
{
  auto q_start = bits;

  uint64_t p1, p2, p3, p4;
  uint64_t cnt[4];
  uint64_t *q_end;
  int unrolled_len;

  // unrolled_len == how many 256bit/32b complete chunks we have to scan
  // This will be used for the optimized/unrolled loop
  // We shove this into a while, because if the
  while ((unrolled_len = (n >> 8))) {
    cnt[0] = cnt[1] = cnt[2] = cnt[3] = 0;
    q_end = bits + (unrolled_len * 4);
    for (; bits < q_end; bits += 4) {
      IACA_START
      __asm__(
      "popcnt %8,  %4  \n\t"
      "popcnt %9,  %5  \n\t"
      "popcnt %10, %6  \n\t"
      "popcnt %11, %7  \n\t"
      "add %4, %0      \n\t"
      "add %5, %1      \n\t"
      "add %6, %2      \n\t"
      "add %7, %3      \n\t"
      : "+r" (cnt[0]), "+r" (cnt[1]), "+r" (cnt[2]), "+r" (cnt[3]),
        "=r" (p1), "=r" (p2), "=r" (p3), "=r" (p4)
      : "m"  (bits[0]), "m"  (bits[1]), "m"  (bits[2]), "m"  (bits[3]));
    }
    IACA_END
    n -= cnt[0] + cnt[1] + cnt[2] + cnt[3];
  }


  for (; n >= 256; bits += 4) {
    __asm__(
      "popcnt %1, %1  \n\t"
      "popcnt %2, %2  \n\t"
      "popcnt %3, %3  \n\t"
      "popcnt %4, %4  \n\t"
      "sub %1, %0     \n\t"
      "sub %2, %0     \n\t"
      "sub %3, %0     \n\t"
      "sub %4, %0     \n\t" // +r means input/output, r means intput
    : "+r" (n)
    : "r"  (bits[0]), "r"  (bits[1]), "r"  (bits[2]), "r"  (bits[3]));
  }

  // As long as we are still looking for more than 64 bits
  auto prevIndex = n;
  while (n > 0) {
    prevIndex = n;
    n -= _mm_popcnt_u64(*(bits++));
  }

  auto pos = _tzcnt_u64(_pdep_u64(1ULL << (prevIndex - 1), *(bits - 1)));
  return ((bits - 1 - q_start) << CHUNKMASK_SHIFT) + pos;

}

#include "bitgoo.h"

int32_t GetNthBitOffset::NoIntrinsics(uint64_t *bits, int32_t bitLength, int64_t n)
{
  auto p = bits;

  // As long as we are still looking for more than 64 bits
  auto prevIndex = n;
  while (n > 0) {
    prevIndex = n;
    n -= BitCount64(*(p++));
  }

  auto p2 = (uint32_t *) (p - 1);
  n = prevIndex - BitCount32(*p2);
  if (n > 0) {
    prevIndex = n;
    p2++;
  }

  auto prevValue = *p2;
  auto pos = (p2 - (uint32_t *) bits) * 32;
  while (prevIndex > 0) {
    auto bp = __builtin_ffs(prevValue);
    pos += bp;// - 1;
    prevIndex--;
    prevValue >>= bp;
  }

  return pos - 1;
}
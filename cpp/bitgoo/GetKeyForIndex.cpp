//
// Created by dans on 30/7/2016.
//

#include <cassert>
#include <immintrin.h>
#include <x86intrin.h>


#ifdef AVX2
const auto lookup = _mm256_setr_epi8(
  /* 0 */ 0, /* 1 */ 1, /* 2 */ 1, /* 3 */ 2,
  /* 4 */ 1, /* 5 */ 2, /* 6 */ 2, /* 7 */ 3,
  /* 8 */ 1, /* 9 */ 2, /* a */ 2, /* b */ 3,
  /* c */ 2, /* d */ 3, /* e */ 3, /* f */ 4,

  /* 0 */ 0, /* 1 */ 1, /* 2 */ 1, /* 3 */ 2,
  /* 4 */ 1, /* 5 */ 2, /* 6 */ 2, /* 7 */ 3,
  /* 8 */ 1, /* 9 */ 2, /* a */ 2, /* b */ 3,
  /* c */ 2, /* d */ 3, /* e */ 3, /* f */ 4
);

uint64_t popcnt_avx2_lookup(const uint8_t *data, const size_t n) {

  size_t i = 0;


  const auto low_mask = _mm256_set1_epi8(0x0f);

  auto acc = _mm256_setzero_si256();

#define ITER { \
        const __m256i vec = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(data + i)); \
        const __m256i lo  = _mm256_and_si256(vec, low_mask); \
        const __m256i hi  = _mm256_and_si256(_mm256_srli_epi16(vec, 4), low_mask); \
        const __m256i popcnt1 = _mm256_shuffle_epi8(lookup, lo); \
        const __m256i popcnt2 = _mm256_shuffle_epi8(lookup, hi); \
        local = _mm256_add_epi8(local, popcnt1); \
        local = _mm256_add_epi8(local, popcnt2); \
        i += 32; \
    }

  while (i + 8*32 <= n) {
    auto local = _mm256_setzero_si256();
    ITER ITER ITER ITER
    ITER ITER ITER ITER
    acc = _mm256_add_epi64(acc, _mm256_sad_epu8(local, _mm256_setzero_si256()));
  }

  auto local = _mm256_setzero_si256();

  while (i + 32 <= n) {
    ITER;
  }

  acc = _mm256_add_epi64(acc, _mm256_sad_epu8(local, _mm256_setzero_si256()));

#undef ITER

  uint64_t result = 0;

  result += static_cast<uint64_t>(_mm256_extract_epi64(acc, 0));
  result += static_cast<uint64_t>(_mm256_extract_epi64(acc, 1));
  result += static_cast<uint64_t>(_mm256_extract_epi64(acc, 2));
  result += static_cast<uint64_t>(_mm256_extract_epi64(acc, 3));
  return result;
}

int32_t GetKeyForIndexAVX2(int64_t index)
{
  index++;
  auto p = (uint64_t *) q;
  auto pb = (uint8_t *) p;
  size_t byte_len;
  while ((byte_len = (index >> 16) << 8) > 256) {
    index -= popcnt_avx2_lookup(pb, byte_len);
    p += byte_len;
  }

  for (; index >= 256; p += 4)
    index -= _mm_popcnt_u64(p[0]) + _mm_popcnt_u64(p[1]) + _mm_popcnt_u64(p[2]) + _mm_popcnt_u64(p[3]);


}
#endif




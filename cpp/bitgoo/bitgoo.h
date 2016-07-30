//
// Created by dans on 30/7/2016.
//

#ifndef BITGOO_PROJECT_H
#define BITGOO_PROJECT_H

#include <stdint.h>
#include <immintrin.h>

#if USE_IACA
#include "iacaMarks.h"
#else
#define IACA_START
#define IACA_END
#endif


static const int32_t CHUNKMASK_SHIFT = 6;

static inline uint64_t BitCount64(uint64_t b) {
  b -= (b >> 1) & 0x5555555555555555;
  b = (b & 0x3333333333333333) + ((b >> 2) & 0x3333333333333333);
  b = (b + (b >> 4)) & 0x0f0f0f0f0f0f0f0f;
  return (b * 0x0101010101010101) >> 56;
}
/* For 32-bit, an 8-bit table may or may not be a little faster */
static inline uint32_t BitCount32(uint32_t b) {
  b -= (b >> 1) & 0x55555555;
  b = (b & 0x33333333) + ((b >> 2) & 0x33333333);
  b = (b + (b >> 4)) & 0x0f0f0f0f;
  return (b * 0x01010101) >> 24;
}

inline bool is_bit_set(const uint64_t *p, int64_t key) { return (p[key >> CHUNKMASK_SHIFT] & (1ULL << (key & 0x3F))) == 0; }


const int32_t MEGA_UNROLL_MIN = 16;

class CountBits {
public:
  //extern "C" int32_t GetKeyForIndexAVX2(uint64_t *q, int32_t bitLength, int64_t index);
    static int32_t Vanilla(uint64_t *bits, int32_t bitLength, int64_t offset);
    static int32_t NoPopcnt(uint64_t *bits, int32_t bitLength, int64_t offset);
    static int32_t Intrinsics(uint64_t *bits, int32_t bitLength, int64_t offset);
    static int32_t IntrinsicsUnrolled(uint64_t *bits, int32_t bitLength, int64_t offset);
    static int32_t IntrinsicsUnrolled2(uint64_t *bits, int32_t bitLength, int64_t offset);
    static int32_t IntrinsicsUnrolled3(uint64_t *q, int32_t bitLength, int64_t index);
    static int32_t AsmUnrolled(uint64_t *q, int32_t bitLength, int64_t index);
};

class GetNthBitOffset {
public:
    static int32_t Naive(uint64_t *bits, int32_t bitLength, int64_t n);
    static int32_t NoIntrinsics(uint64_t *bits, int32_t bitLength, int64_t n);
    static int32_t POPCNTAndBMI1(uint64_t *bits, int32_t bitLength, int64_t n);
    static int32_t POPCNTAndBMI2(uint64_t *bits, int32_t bitLength, int64_t n);
    static int32_t POPCNTAndBMI1Unrolled(uint64_t *q, int32_t bitLength, int64_t n);
    static int32_t POPCNTAndBMI2Unrolled(uint64_t *bits, int32_t bitLength, int64_t n);
    static int32_t POPCNTAndBMI2Unrolled2(uint64_t *bits, int32_t bitLength, int64_t n);
    static int32_t POPCNTAndBMI2Unrolled3(uint64_t *bits, int32_t bitLength, int64_t n);
    static int32_t POPCNTAndBMI2ASMUnrolled2(uint64_t *bits, int32_t bitLength, int64_t n);
    static int32_t POPCNTAndBMI2ASMUnrolled3(uint64_t *bits, int32_t bitLength, int64_t n);
    static int32_t POPCNTAndBMI2ASMUnrolled2Bad(uint64_t *bits, int32_t bitLength, int64_t n);
};
#endif //BITGOO_PROJECT_H

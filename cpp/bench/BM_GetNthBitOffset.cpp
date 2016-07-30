#include <bitgoo.h>
#include "bench.h"

#define BM_GNBO(__func)                                          \
static void BM_GNBO__##__func(benchmark::State &state) { \
  uint64_t sum = 0;                                              \
  for (auto _ : state)                                           \
    for (long i = 0, i_end = state.range(0); i < i_end; i++)     \
      sum += GetNthBitOffset::__func(bits, BitCount, i + 1);     \
}                                                                \
BENCHMARK(BM_GNBO__##__func)->RangeMultiplier(4)->Range(1, 2 << 15);

BM_GNBO(Naive)
BM_GNBO(NoIntrinsics)
BM_GNBO(POPCNTAndBMI1)
BM_GNBO(POPCNTAndBMI2)
BM_GNBO(POPCNTAndBMI1Unrolled)
BM_GNBO(POPCNTAndBMI2Unrolled)
BM_GNBO(POPCNTAndBMI2Unrolled2)
BM_GNBO(POPCNTAndBMI2Unrolled3)
//BM_GNBO(AVX2)
BM_GNBO(POPCNTAndBMI2ASMUnrolled2)
BM_GNBO(POPCNTAndBMI2ASMUnrolled3)
BM_GNBO(POPCNTAndBMI2ASMUnrolled2Bad)
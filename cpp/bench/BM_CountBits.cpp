#include <bitgoo.h>
#include "bench.h"

#define BM_CB(__func)                                          \
static void BM_CB__##__func(benchmark::State &state) {         \
  uint64_t sum = 0;                                              \
  for (auto _ : state)                                           \
    for (long i = 0, i_end = state.range(0); i < i_end; i++)     \
      sum += CountBits::__func(bits, BitCount, i);     \
}                                                                \
BENCHMARK(BM_CB__##__func)->RangeMultiplier(4)->Range(1, 2 << 15);

BM_CB(Vanilla)
BM_CB(NoPopcnt)
BM_CB(Intrinsics)
BM_CB(IntrinsicsUnrolled2)
BM_CB(IntrinsicsUnrolled3)
BM_CB(AsmUnrolled)
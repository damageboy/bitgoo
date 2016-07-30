#include <x86intrin.h>
#include <random>
#include "bench.h"
#include "benchmark/benchmark.h"

using namespace std;

uint64_t bits[LongCount] __attribute__((aligned(32)));

void generate_random_ulong(uint64_t *a, int n) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<uint64_t> dis(0, numeric_limits<uint64_t>::max());

  for (auto i = 0; i < n; i++)
    a[i] = dis(gen);
}

int main(int argc, char** argv)
{
  __builtin_cpu_init();
  auto isBMI2Supported = __builtin_cpu_supports("bmi2");
  generate_random_ulong(bits, LongCount);
  ::benchmark::Initialize(&argc, argv);
  ::benchmark::RunSpecifiedBenchmarks();
}
using BenchmarkDotNet.Attributes;

namespace BitGoo.Bench
{
    [Config(typeof(LocalCoreClrConfig))]
    public class CountBitsBenchmarks : BitmapBenchmarkBase
    {
        [Benchmark]
        public unsafe int Vanilla()
        {
            int sum = 0;
            for (var i = 0; i < N; i++)
                sum += CountBits.Vanilla(_bits, N, i);
            return sum;
        }

        [Benchmark]
        public unsafe int NoPopcnt()
        {
            int sum = 0;
            for (var i = 0; i < N; i++)
                sum += CountBits.NoIntrinsics(_bits, N, i);
            return sum;
        }

        [Benchmark]
        public unsafe int Intrinsics()
        {
            int sum = 0;
            for (var i = 0; i < N; i++)
                sum += CountBits.POPCNT(_bits, N, i);
            return sum;
        }


        [Benchmark]
        public unsafe int IntrinsicsUnrolled()
        {
            int sum = 0;
            for (var i = 0; i < N; i++)
                sum += CountBits.POPCNTUnrolled(_bits, N, i);
            return sum;
        }

        [Benchmark]
        public unsafe int IntrinsicsUnrolled2()
        {
            int sum = 0;
            for (var i = 0; i < N; i++)
                sum += CountBits.POPCNTUnrolled2(_bits, N, i);
            return sum;
        }
    }



}

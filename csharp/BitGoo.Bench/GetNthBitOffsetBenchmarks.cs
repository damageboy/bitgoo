using BenchmarkDotNet.Attributes;

namespace BitGoo.Bench
{
    [Config(typeof(LocalCoreClrConfig))]
    public class GetNthBitOffsetBenchmarks : BitmapBenchmarkBase
    {
        [Benchmark(Baseline=false)]
        public unsafe int Naive()
        {
            int sum = 0;
            for (var i = 1; i <= N; i++)
                sum += GetNthBitOffset.Naive(_bits, N, i);
            return sum;
        }

        [Benchmark(Baseline=false)]
        public unsafe int NoIntrinsics()
        {
            int sum = 0;
            for (var i = 1; i <= N; i++)
                sum += GetNthBitOffset.NoIntrinsics(_bits, N, i);
            return sum;
        }

        [Benchmark(Baseline=false)]
        public unsafe int POPCNTAndBMI1()
        {
            int sum = 0;
            for (var i = 1; i <= N; i++)
                sum += GetNthBitOffset.POPCNTAndBMI1(_bits, N, i);
            return sum;
        }

        [Benchmark(Baseline=true)]
        public unsafe int Intrinsics()
        {
            int sum = 0;
            for (var i = 1; i <= N; i++)
                sum += GetNthBitOffset.POPCNTAndBMI2(_bits, N, i);
            return sum;
        }


        [Benchmark(Baseline=false)]
        public unsafe int IntrinsicsUnrolled()
        {
            int sum = 0;
            for (var i = 1; i <= N; i++)
                sum += GetNthBitOffset.POPCNTAndBMI2Unrolled(_bits, N, i);
            return sum;
        }
    }



}

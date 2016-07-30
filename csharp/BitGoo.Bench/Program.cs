using System;
using System.Linq;
using System.Runtime.InteropServices;
using BenchmarkDotNet.Attributes;
using BenchmarkDotNet.Configs;
using BenchmarkDotNet.Jobs;
using BenchmarkDotNet.Running;
using BenchmarkDotNet.Exporters;
using BenchmarkDotNet.Toolchains.CustomCoreClr;

namespace BitGoo.Bench
{
    class Program
    {
        static void Main(string[] args) => 
            BenchmarkSwitcher.FromAssembly(typeof(Program).Assembly).Run(args);

        
    }

    public class LocalCoreClrConfig : ManualConfig
    {
        public LocalCoreClrConfig()
        {
            Add(Job.ShortRun.With(
                CustomCoreClrToolchainBuilder.Create()
                    .UseCoreClrDefault()
                    .UseCoreFxDefault()
                    .DisplayName("3.0.100-alpha1-20180720-2")
                    .TargetFrameworkMoniker("netcoreapp3.0")
                    .ToToolchain()));

            Add(MarkdownExporter.GitHub);
        }
    }

    public class BitmapBenchmarkBase
    {
        const int KB = 1024;
        [Params(1, 4, 16, 64, 256, 1 * KB, 4 * KB, 16 * KB, 64 * KB)]
        public int N {get;set;}

        Random _r = new Random((int) DateTime.UtcNow.Ticks);

        protected unsafe ulong *_bits;

        [GlobalSetup]
        public unsafe void GlobalSetup()
        {
            var numUlongs = ((N / 64) * 4);
            _bits = (ulong *) Marshal.AllocHGlobal(sizeof(ulong) * numUlongs).ToPointer();
            for (var i = 0; i < numUlongs; i++)
                _bits[i] = unchecked(((ulong)_r.Next()) << 32 | ((ulong) _r.Next()));
        }
    }



}

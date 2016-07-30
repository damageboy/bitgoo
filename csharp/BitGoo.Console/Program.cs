using System;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;

namespace BitGoo.Bench
{
    class Program
    {
        const int N = 1024;
        static Random _r = new Random((int) DateTime.UtcNow.Ticks);
        static unsafe ulong *_bits;

        static unsafe void Main(string[] args) {
            var numUlongs = ((N / 64) * 4);
            _bits = (ulong *) Marshal.AllocHGlobal(sizeof(ulong) * numUlongs).ToPointer();
            for (var i = 0; i < numUlongs; i++)
                _bits[i] = unchecked(((ulong)_r.Next()) << 32 | ((ulong) _r.Next()));

            for (var i = 0; i < 1_000_0; i++)
                GetNthBitOffsetDriver(_bits);
        }

        // unsafe static void CountBitsDriver(ulong *_bits)
        // {
        //     Vanilla();
        //     NoPopcnt();
        //     Intrinsics();
        //     IntrinsicsUnrolled();
        //     IntrinsicsUnrolled2();
        // }
        
        unsafe static void GetNthBitOffsetDriver(ulong *_bits)
        {
            Naive(666);
            NoIntrinsics(666);
            POPCNTAndBMI1(666);
            POPCNTAndBMI2(666);
            POPCNTAndBMI2Unrolled(666);
            //IntrinsicsUnrolled2();
        }


#if NO
        unsafe static int Vanilla()
        {
            int sum = 0;
            for (var i = 0; i < N; i++)
                sum += CountBits.Vanilla(_bits, N, i);
            return sum;
        }

        unsafe static int NoPOPCNT()
        {
            int sum = 0;
            for (var i = 0; i < N; i++)
                sum += CountBits.NoPopcnt(_bits, N, i);
            return sum;
        }

        unsafe static int Intrinsics()
        {
            int sum = 0;
            for (var i = 0; i < N; i++)
                sum += CountBits.Intrinsics(_bits, N, i);
            return sum;
        }

        unsafe static int IntrinsicsUnrolled()
        {
            int sum = 0;
            for (var i = 0; i < N; i++)
                sum += CountBits.IntrinsicsUnrolled(_bits, N, i);
            return sum;
        }

        unsafe static int IntrinsicsUnrolled2()
        {
            int sum = 0;
            for (var i = 0; i < N; i++)
                sum += CountBits.IntrinsicsUnrolled2(_bits, N, i);
            return sum;
        }
#endif

        [MethodImpl(MethodImplOptions.NoInlining)]
        unsafe static int Naive(int i) => GetNthBitOffset.Naive(_bits, N, i);

        [MethodImpl(MethodImplOptions.NoInlining)]
        unsafe static int NoIntrinsics(int i) => GetNthBitOffset.NoIntrinsics(_bits, N, i);

        [MethodImpl(MethodImplOptions.NoInlining)]
        unsafe static int POPCNTAndBMI1(int i) => GetNthBitOffset.POPCNTAndBMI1(_bits, N, i);

        [MethodImpl(MethodImplOptions.NoInlining)]
        unsafe static int POPCNTAndBMI2(int i) => GetNthBitOffset.POPCNTAndBMI2(_bits, N, i);

        [MethodImpl(MethodImplOptions.NoInlining)]
        unsafe static int POPCNTAndBMI2Unrolled(int i) => GetNthBitOffset.POPCNTAndBMI2Unrolled(_bits, N, i);
    }
}

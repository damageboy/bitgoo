using static System.Runtime.Intrinsics.X86.Popcnt;
using static System.Runtime.Intrinsics.X86.Bmi1;
using static System.Runtime.Intrinsics.X86.Bmi2;
using System;
using System.Runtime.CompilerServices;

namespace BitGoo
{
    public partial class GetNthBitOffset
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe int POPCNTAndBMI2(ulong* bits, int numBits, int n)
        {
            var p64 = bits;
            int prevN;
            do {
                prevN = n;
                n -= (int) PopCount(*p64);
                p64++;
            } while (n > 0);

            p64--;
            // Here, we know for sure that 1 .. prevN .. 64 (including)
            var pos = (int) TrailingZeroCount(ParallelBitDeposit(1UL << (prevN - 1), *p64));
            return (int) ((p64 - bits) * 64) + pos;
        }
    }
}

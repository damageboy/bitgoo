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
        public static unsafe int POPCNTAndBMI2Unrolled(ulong* bits, int numBits, int n)
        {
            var p64 = bits;
            for (; n >= 256; p64 += 4) {
                n -= (int) (
                    PopCount(p64[0]) +
                    PopCount(p64[1]) +
                    PopCount(p64[2]) +
                    PopCount(p64[3]));
            }
            var prevN = n;
            while (n > 0) {
                prevN = n;
                n -= (int) PopCount(*p64);
                p64++;
            }

            p64--;

            var pos = (int) TrailingZeroCount(ParallelBitDeposit(1UL << (prevN - 1), *p64));
            return (int) ((p64 - bits) * 64) + pos;
        }
    }
}

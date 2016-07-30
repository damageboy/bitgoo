using static System.Runtime.Intrinsics.X86.Popcnt;
using static System.Runtime.Intrinsics.X86.Bmi1;
using System;
using System.Runtime.CompilerServices;

namespace BitGoo
{
    public partial class GetNthBitOffset
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe int POPCNTAndBMI1(ulong* bits, int numBits, int n)
        {
            var p64 = bits;
            int prevN;
            do {
                prevN = n;
                n -= (int) PopCount(*p64);
                p64++;
            } while (n > 0);

            var p32 = (uint *) (p64 - 1);
            n = prevN - PopCount(*p32);
            if (n > 0) {
                prevN = n;
                p32++;
            }

            var prevValue = *p32;
            var pos = (p32 - (uint *) bits) * 32;
            while (prevN > 0) {
                var bp = TrailingZeroCount(prevValue) + 1;
                pos += bp;
                prevN--;
                prevValue >>= (int) bp;
            }

            return (int) pos - 1;
        }
    }
}


using System.Runtime.CompilerServices;
using System.Runtime.Intrinsics.X86;
using static System.Runtime.Intrinsics.X86.Popcnt;

namespace BitGoo
{
    public partial class CountBits
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe int NoIntrinsics(ulong* bits, int numBits, int offset)
        {
            if (HackersDelight.IsBitSet(bits, offset))
                return -1;

            var index = 0;
            while (offset >= 63)
            {
                //IACA_START
                index  += HackersDelight.PopCount(*(bits++));
                offset -= 64;
            }
            //IACA_END

            return offset >= 0 ? index + HackersDelight.PopCount(*bits & ((1UL << (offset + 1)) - 1)) : index;
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe int POPCNT(ulong* bits, int numBits, int offset)
        {
            if (HackersDelight.IsBitSet(bits, offset))
                return -1;

            var index = 0L;
            while (offset >= 63)
            {
                //IACA_START
                index  += PopCount(*(bits++));
                offset -= 64;
            }
            //IACA_END

            return (int) (offset >= 0 ? index + PopCount(*bits & ((1UL << (offset + 1)) - 1)) : index);
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe int POPCNTUnrolled(ulong* bits, int bitLength, int offset)
        {
            if (HackersDelight.IsBitSet(bits, offset))
                return -1;

            var index = 0L;
            

            // Bits -> longs -> "complete" groups of 4 longs
            var n = ((offset / 64) / 4) * 4;
            for (var i = 0; i < n; i+=4, bits += 4)
            {
                //IACA_START
                index += PopCount(bits[0]) + PopCount(bits[1]) + PopCount(bits[2]) + PopCount(bits[3]);
            }

            //IACA_END
            offset -= n * 64;
            //bits   += n;

            while (offset >= 63)
            {
                index  += PopCount(*(bits++));
                offset -= 64;
            }

            return (int) (offset >= 0 ? index + PopCount(*bits & ((1UL << (offset + 1)) - 1)) : index);
        }


        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe int POPCNTUnrolled2(ulong* bits, int bitLength, int offset)
        {
            long c1, c2, c3, c4;
            c1 = c2 = c3 = c4 = 0;

            if (HackersDelight.IsBitSet(bits, offset))
                return -1;

            var index = 0L;

            // Bits -> longs -> "complete" groups of 4 longs
            var n = ((offset / 64) / 4) * 4;
            for (var i = 0; i < n; i += 4, bits += 4)
            {
                c1 += PopCount(bits[0]);
                c2 += PopCount(bits[1]);
                c3 += PopCount(bits[2]);
                c4 += PopCount(bits[3]);
            }

            index  += c1 + c2 + c3 + c4;
            offset -= n * 64;

            while (offset >= 63)
            {
                index  += PopCount(*(bits++));
                offset -= 64;
            }

            return (int) (index + PopCount(*bits & ((1UL << (offset + 1)) -1)));
        }
    }
}
using System.Runtime.CompilerServices;

namespace BitGoo
{
    public class HackersDelight
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static int PopCount(ulong b)
        {
            b -= (b >> 1) & 0x5555555555555555;
            b =  (b & 0x3333333333333333) + ((b >> 2) & 0x3333333333333333);
            b =  (b + (b >> 4)) & 0x0f0f0f0f0f0f0f0f;
            return unchecked((int) ((b * 0x0101010101010101) >> 56));
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static int PopCount(uint b)
        {
            b -= (b >> 1) & 0x55555555;
            b =  (b & 0x33333333) + ((b >> 2) & 0x33333333);
            b =  (b + (b >> 4)) & 0x0f0f0f0f;
            return unchecked((int) ((b * 0x01010101) >> 24));
        }

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static int TrailingZeroCount(uint x) => PopCount(~x & (x - 1));

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe bool IsBitSet(ulong* p, int key) =>
            (p[key >> 6] & (1UL << (0x3F & key))) == 0;
    }
}

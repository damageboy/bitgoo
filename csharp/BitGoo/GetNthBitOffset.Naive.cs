using System;
using System.Runtime.CompilerServices;

namespace BitGoo
{
    public partial class GetNthBitOffset
    {
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe int Naive(ulong* bits, int numBits, int n)
        {
            var b = 0;
            var value = bits[0];
            var leftInULong = 64;

            var i = 0;

            while (i < numBits)
            {
                if ((value & 0x1UL) == 0x1UL)
                    i++;
                if (i == n)
                    break;
                value >>= 1;
                leftInULong--;
                b++;

                if (leftInULong != 0)
                    continue;
                leftInULong = 64;
                value = *(++bits);
            }

            return b;
        }
    }
}
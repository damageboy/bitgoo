using System.Runtime.CompilerServices;

namespace BitGoo
{
    public partial class CountBits
    {

        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe int Vanilla(ulong* bits, int numBits, int offset)
        {
            if (offset < 0)
                return -1;

            var value = *bits;
            var leftInULong = 64;

            var i = 0;
            while (offset-- > 0)
            {
                if ((value & 0x1) == 1)
                    i++;
                value >>= 1;
                leftInULong--;

                if (leftInULong != 0)
                    continue;
                leftInULong = 64;
                value       = *(++bits);
            }

            if ((value & 0x1) == 1)
                i++;
            else return -1;

            return i;
        }
    }
}
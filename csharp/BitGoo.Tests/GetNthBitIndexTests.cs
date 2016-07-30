using System;
using System.Collections;
using System.Reflection;
using NUnit.Framework;

namespace BitGoo.Tests
{
  public class GetNthBitOffsetTests
  {
    public unsafe delegate int GetNthBitOffsetDelegate(ulong* bits, int numBits, int offset);

    static IEnumerable GetNthBitIndexVariants()
    {
      foreach (var mi in typeof(GetNthBitOffset).GetMethods(BindingFlags.Static | BindingFlags.Public))
        yield return new TestCaseData(CreateDelegate<GetNthBitOffsetDelegate>(mi)).SetName($"{{M}}.{mi.Name}");

      T CreateDelegate<T>(MethodInfo methodInfo) where T : Delegate =>
        (T) Delegate.CreateDelegate(typeof(T), null, methodInfo);
    }

    [Test]
    [TestCaseSource(nameof(GetNthBitIndexVariants))]
    public unsafe void OneLongAllBitsLit(GetNthBitOffsetDelegate variant)
    {
      var q = 0xFFFFFFFFFFFFFFFFUL;
      for (var i = 0; i < 64; i++)
      {
        Assert.That(variant(&q, 64, i+1), Is.EqualTo(i), $"i=={i}");
      }
    }

    [Test]
    [TestCaseSource(nameof(GetNthBitIndexVariants))]
    public unsafe void Upper32BitsLit(GetNthBitOffsetDelegate variant)
    {
      var q = 0xFFFFFFFF00000000UL;
      for (var i = 0; i < 32; i++)
      {
        Assert.That(variant(&q, 64, i+1), Is.EqualTo(i + 32), $"i=={i}");
      }
    }

    [Test]
    [TestCaseSource(nameof(GetNthBitIndexVariants))]
    public unsafe void BitGapAtEnd(GetNthBitOffsetDelegate variant)
    {
      var q = stackalloc ulong[16]
      {
          0x0FFFFFFFFFFFFFFF,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0x0000000000000000,
          0xF000000000000000,
      };
      Assert.That(variant(q, 1024, 64), Is.EqualTo(1023));
    }


    [Test]
    [TestCaseSource(nameof(GetNthBitIndexVariants))]
    public unsafe void OneKLongAllBitsLit(GetNthBitOffsetDelegate variant)
    {
      var q = stackalloc ulong[16]
      {
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
        0xFFFFFFFFFFFFFFFF,
      };
      for (var i = 0; i < 1024; i++)
        Assert.That(variant(q, 1024, i+1), Is.EqualTo(i), $"i=={i}");
    }


    [Test]
    [TestCaseSource(nameof(GetNthBitIndexVariants))]
    public unsafe void TwoKLongCheckered1(GetNthBitOffsetDelegate variant)
    {
      var q = stackalloc ulong[32]
      {
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
        0xFFFFFFFFFFFFFFFF, 0x0000000000000000,
      };
      for (var i = 0; i < 1024; i++)
      {
        var expected = ((i / 64 * 2) * 64) + (i % 64);
        Assert.That(variant(q, 2048, i+1), Is.EqualTo(expected), $"i=={i}");
      }
    }

    [Test]
    [TestCaseSource(nameof(GetNthBitIndexVariants))]
    public unsafe void TwoKLongCheckered2(GetNthBitOffsetDelegate variant)
    {
      var q = stackalloc ulong[32]
      {
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
        0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,
      };
      for (var i = 0; i < 1024; i++)
      {
        var expected = ((i / 4 * 2) * 4) + (i % 4);
        Assert.That(variant(q, 2048, i+1), Is.EqualTo(expected), $"i=={i}");
      }
    }


    [Test]
    [TestCaseSource(nameof(GetNthBitIndexVariants))]
    public unsafe void TwoKLongCheckered3(GetNthBitOffsetDelegate variant)
    {
      var q = stackalloc ulong[32]
      {
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
        0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,
      };
      for (var i = 0; i < 1024; i++)
      {
        var expected = ((i / 4 * 2) * 4) + 4 + (i % 4);
        Assert.That(variant(q, 2048, i+1), Is.EqualTo(expected), $"i=={i}");
      }
    }
  }
}

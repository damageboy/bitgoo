using System;
using System.Collections;
using System.Reflection;
using NUnit.Framework;

namespace BitGoo.Tests
{
  public class CountBitsTests
  {
    public unsafe delegate int CountBitsDelegate(ulong* bits, int numBits, int offset);

    static IEnumerable CountBitsVariants()
    {
      foreach (var mi in typeof(CountBits).GetMethods(BindingFlags.Static | BindingFlags.Public))
        yield return new TestCaseData(CreateDelegate<CountBitsDelegate>(mi)).SetName($"{{M}}.{mi.Name}");

      T CreateDelegate<T>(MethodInfo methodInfo) where T : Delegate =>
        (T) Delegate.CreateDelegate(typeof(T), null, methodInfo);
    }

    [Test]
    [TestCaseSource(nameof(CountBitsVariants))]
    public unsafe void OneLongAllBitsLit(CountBitsDelegate variant)
    {
      var q = 0xFFFFFFFFFFFFFFFFUL;
      for (var i = 0; i < 64; i++)
      {
        Assert.That(variant(&q, 64, i), Is.EqualTo(i + 1), $"i=={i}");
      }
    }

    [Test]
    [TestCaseSource(nameof(CountBitsVariants))]
    public unsafe void Upper32BitsLit(CountBitsDelegate variant)
    {
      var q = 0xFFFFFFFF00000000UL;
      for (var i = 0; i < 32; i++)
      {
        Assert.That(variant(&q, 64, i + 32), Is.EqualTo(i + 1), $"i=={i}");
      }
    }

    [Test]
    [TestCaseSource(nameof(CountBitsVariants))]
    public unsafe void OneKLongAllBitsLit(CountBitsDelegate variant)
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
        Assert.That(variant(q, 1024, i), Is.EqualTo(i + 1), $"i=={i}");
    }


    [Test]
    [TestCaseSource(nameof(CountBitsVariants))]
    public unsafe void TwoKLongCheckered1(CountBitsDelegate variant)
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
      for (var i = 0; i < 2048; i++)
      {
        var expected = ((i / 64) % 2 == 1) ? -1 : ((i / (64 * 2)) * 64) + (i % 64) + 1;
        Assert.That(variant(q, 2048, i), Is.EqualTo(expected), $"i== {i}");
      }
    }

    [Test]
    [TestCaseSource(nameof(CountBitsVariants))]
    public unsafe void TwoKLongCheckered2(CountBitsDelegate variant)
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
      for (var i = 0; i < 2048; i++)
      {
        var expected = ((i / 4) % 2 == 1) ? -1 : ((i / (4 * 2)) * 4) + (i % 4) + 1;
        Assert.That(variant(q, 2048, i), Is.EqualTo(expected), $"i== {i}");
      }
    }


    [Test]
    [TestCaseSource(nameof(CountBitsVariants))]
    public unsafe void TwoKLongCheckered3(CountBitsDelegate variant)
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
        var expected = ((i / 4) % 2 == 0) ? -1 : ((i / (4 * 2)) * 4) + (i % 4) + 1;
        Assert.That(variant(q, 2048, i), Is.EqualTo(expected), $"i== {i}");
      }
    }
  }
}

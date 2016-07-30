#include "gtest/gtest.h"

#include <bitgoo.h>


#define TEST1(variant)                    \
TEST(GNBO__##variant, OneLongAllBitsLit) {\
  uint64_t q = 0xFFFFFFFFFFFFFFFF;        \
  for (auto i = 0; i < 64; i++)           \
    EXPECT_EQ(GetNthBitOffset::variant(&q, 64, i + 1), i)      \
      << "i==" << i;                      \
}


#define TEST2(variant)                    \
TEST(GNBO__##variant, Upper32BitsLit) {   \
  uint64_t q = 0xFFFFFFFF00000000;        \
  for (auto i = 0; i < 32; i++)           \
    EXPECT_EQ(GetNthBitOffset::variant(&q, 64, i + 1), i + 32) \
      << "i==" << i;                      \
}

#define TEST3(variant)                    \
TEST(GNBO__##variant, BitGapAtEnd) {   \
  uint64_t q[16] = {          \
          0x0FFFFFFFFFFFFFFF, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0x0000000000000000, \
          0xF000000000000000, \
  };                          \
  EXPECT_EQ(GetNthBitOffset::variant(q, 1024, 64), 1023); \
}

#define TEST4(variant)                      \
TEST(GNBO__##variant, OneKLongAllBitsLit) { \
  uint64_t q[16] = {          \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
          0xFFFFFFFFFFFFFFFF, \
  };                          \
  for (auto i = 0; i < 1024; i++)     \
    EXPECT_EQ(GetNthBitOffset::variant(q, 1024, i + 1), i) \
      << "i==" << i;                  \
}

#define TEST5(variant)                              \
TEST(GNBO__##variant, TwoKLongCheckered1) {                 \
  uint64_t q[32] = {                                \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
          0xFFFFFFFFFFFFFFFF, 0x0000000000000000,   \
  };                                                \
  for (auto i = 0; i < 1024; i++) {                 \
    auto expected = ((i / 64 * 2) * 64) + (i % 64); \
    EXPECT_EQ(GetNthBitOffset::variant(q, 2048, i + 1), expected)        \
      << "i==" << i;                                \
  }                                                 \
}

#define TEST6(variant)                              \
TEST(GNBO__##variant, TwoKLongCheckered2) {                 \
  uint64_t q[32] = {                                \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
          0x0F0F0F0F0F0F0F0F, 0x0F0F0F0F0F0F0F0F,   \
  };                                                \
  for (auto i = 0; i < 1024; i++) {                 \
    auto expected = ((i / 4 * 2) * 4) + (i % 4);    \
    EXPECT_EQ(GetNthBitOffset::variant(q, 2048, i + 1),  \
              expected)                             \
      << "i==" << i;                                \
  }                                                 \
}

#define TEST7(variant)                              \
TEST(GNBO__##variant, TwoKLongCheckered3) {                 \
  uint64_t q[32] = {                                \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
          0xF0F0F0F0F0F0F0F0, 0xF0F0F0F0F0F0F0F0,   \
  };                                                \
  for (auto i = 0; i < 1024; i++) {                 \
    auto expected = ((i / 4 * 2) * 4) + 4 + (i % 4);\
    EXPECT_EQ(GetNthBitOffset::variant(q, 2048, i + 1),  \
              expected)                             \
      << "i==" << i;                                \
  }                                                 \
}

#define TEST_ALL(test_name) \
test_name(Naive) \
test_name(NoIntrinsics) \
test_name(POPCNTAndBMI1)   \
test_name(POPCNTAndBMI2) \
test_name(POPCNTAndBMI2Unrolled) \
test_name(POPCNTAndBMI2Unrolled2) \
test_name(POPCNTAndBMI2Unrolled3) \
test_name(POPCNTAndBMI2ASMUnrolled2) \
test_name(POPCNTAndBMI2ASMUnrolled2Bad) \
test_name(POPCNTAndBMI2ASMUnrolled3)

TEST_ALL(TEST1)
TEST_ALL(TEST2)
TEST_ALL(TEST3)
TEST_ALL(TEST4)
TEST_ALL(TEST5)
TEST_ALL(TEST6)
TEST_ALL(TEST7)
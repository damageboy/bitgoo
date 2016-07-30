#include "gtest/gtest.h"

#include <bitgoo.h>

#define TEST1(variant)                      \
TEST(CB__##variant, OneLongAllBitsLit) {    \
  uint64_t q = 0xFFFFFFFFFFFFFFFF;          \
  for (auto i = 0; i < 64; i++) {           \
    EXPECT_EQ(CountBits::variant(&q, 64, i), i + 1)    \
      << "i==" << i;                        \
  }                                         \
}

#define TEST2(variant)                       \
TEST(CB__####variant, Upper32BitsLit) {      \
  uint64_t q = 0xFFFFFFFF00000000;           \
  for (auto i = 0; i < 32; i++)              \
    EXPECT_EQ(CountBits::variant(&q, 64, i+32), i + 1)  \
      << "i==" << i;                         \
}

#define TEST3(variant)                     \
TEST(CB__##variant, OneKLongAllBitsLit) {  \
  uint64_t q[16] = {                       \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
          0xFFFFFFFFFFFFFFFF,              \
  };                                       \
  for (auto i = 0; i < 1024; i++)          \
    EXPECT_EQ(CountBits::variant(q, 1024, i), i + 1)  \
      << "i==" << i;                       \
}

#define TEST4(variant)                              \
TEST(CB__##variant, TwoKLongCheckered1) {           \
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
  for (auto i = 0; i < 2048; i++) {                 \
      auto expected = ((i / 64) % 2 == 1) ?         \
        -1 :                                        \
        ((i / (64 * 2)) * 64) + (i % 64) + 1;       \
    EXPECT_EQ(CountBits::variant(q, 2048, i), expected)        \
      << "i==" << i;                                \
  }                                                 \
}

#define TEST5(variant)                              \
TEST(CB__##variant, TwoKLongCheckered2) {           \
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
  for (auto i = 0; i < 2048; i++) {                 \
      auto expected = ((i / 4) % 2 == 1) ?          \
        -1 :                                        \
        ((i / (4 * 2)) * 4) + (i % 4) + 1;          \
    EXPECT_EQ(CountBits::variant(q, 2048, i), expected)        \
      << "i==" << i;                                \
  }                                                 \
}

#define TEST6(variant)                              \
TEST(CB__##variant, TwoKLongCheckered3) {           \
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
      auto expected = ((i / 4) % 2 == 0) ?          \
        -1 :                                        \
        ((i / (4 * 2)) * 4) + (i % 4) + 1;          \
    EXPECT_EQ(CountBits::variant(q, 2048, i), expected)        \
      << "i==" << i;                                \
  }                                                 \
}

#define TEST_ALL(test_name) \
test_name(Vanilla) \
test_name(NoPopcnt) \
test_name(Intrinsics) \
test_name(IntrinsicsUnrolled)

TEST_ALL(TEST1)

TEST_ALL(TEST2)

TEST_ALL(TEST3)

TEST_ALL(TEST4)

TEST_ALL(TEST5)

TEST_ALL(TEST6)


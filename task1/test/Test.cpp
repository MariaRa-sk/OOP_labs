#include <gtest/gtest.h>
#include "BitArray.h"

TEST(BitArrayTest, DefaultConstructor) {
    BitArray b;
    EXPECT_EQ(b.size(), 0);
    EXPECT_EQ(b.empty(), true);
}

TEST(BitArrayTest, ParameterizedConstructor) {
    BitArray b(12, 0x0F);
    EXPECT_EQ(b.size(), 12);
    EXPECT_EQ(b.count(), 4);
    EXPECT_EQ(b.to_string(), "000000001111");
}

TEST(BitArrayTest, CopyConstructor) {
    const BitArray original(8, 0b11001100);
    const BitArray copy(original);
    EXPECT_TRUE(original == copy);
}

TEST(BitArrayTest, CopyConstructorFromEmpty) {
    BitArray original;
    BitArray copy(original);
    EXPECT_EQ(copy.size(), 0);
    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(copy.to_string(), "");
}

TEST(BitArrayTest, Destructor) {
    {
        BitArray ba(100);
    }
    EXPECT_TRUE(true);
}

TEST(BitArrayTest, AssignmentOperator) {
    BitArray b1(8, 0xAA);
    BitArray b2;
    b2 = b1;
    EXPECT_EQ(b2.size(), b1.size());
    EXPECT_EQ(b2.count(), b1.count());
    EXPECT_EQ(b2.to_string(), b1.to_string());
}

TEST(BitArrayTest, AssignmentOperatorToNonEmpty) {
    BitArray a(5, 0x1F);
    BitArray b(3, 0x02);
    a = b;
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a.count(), 1);
    EXPECT_EQ(a.to_string(), b.to_string());
}

TEST(BitArrayTest, Swap) {
    BitArray a(5, 0x1F);
    BitArray b(3, 0x02);
    BitArray a_copy = a;
    BitArray b_copy = b;
    a.swap(b);
    EXPECT_EQ(a.size(), b_copy.size());
    EXPECT_EQ(a.count(), b_copy.count());
    EXPECT_EQ(a.to_string(), b_copy.to_string());
    EXPECT_EQ(b.size(), a_copy.size());
    EXPECT_EQ(b.count(), a_copy.count());
    EXPECT_EQ(b.to_string(), a_copy.to_string());
}

TEST(BitArrayTest, ResizeToLarger) {
    BitArray b(4, 0x0F);
    b.resize(8, true);
    EXPECT_EQ(b.size(), 8);
    EXPECT_EQ(b.count(), 8);
    EXPECT_EQ(b.to_string(), "11111111");
}

TEST(BitArrayTest, ResizeToLargerWithFalse) {
    BitArray b(4, 0x0F);
    b.resize(8, false);
    EXPECT_EQ(b.size(), 8);
    EXPECT_EQ(b.count(), 4);
    EXPECT_EQ(b.to_string(), "00001111");
}

TEST(BitArrayTest, ResizeToSmaller) {
    BitArray b(8, 0xFF);
    b.resize(4, true);
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(b.count(), 4);
    EXPECT_EQ(b.to_string(), "1111");
}

TEST(BitArrayTest, ResizeWithReallocate) {
    const size_t size = 20;
    const size_t newSize = 2 * size;
    BitArray b(size, 0xFFFFF);
    b.resize(newSize, true);
    EXPECT_EQ(b.size(), newSize);
    EXPECT_EQ(b.count(), 40);
}

TEST(BitArrayTest, ResizeWithOldCapacity) {
    const size_t size = 20;
    const size_t newSize = 30;
    BitArray b(size, 0xFFFFF);
    b.resize(newSize, true);
    EXPECT_EQ(b.size(), newSize);
    EXPECT_EQ(b.count(), 30);
}

TEST(BitArrayTest, Clear) {
    BitArray b(10, 0x3FF);
    b.clear();
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
    EXPECT_EQ(b.count(), 0);
    EXPECT_EQ(b.to_string(), "");
}

TEST(BitArrayTest, ClearEmpty) {
    BitArray b;
    b.clear();
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
    EXPECT_EQ(b.count(), 0);
    EXPECT_EQ(b.to_string(), "");
}

TEST(BitArrayTest, PushBackToNonEmpty) {
    BitArray b(2, 0x02);
    b.push_back(true);
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(b.count(), 2);
    EXPECT_EQ(b.to_string(), "110");
}

TEST(BitArrayTest, MultiplePushBack) {
    BitArray b;
    for (size_t i = 0; i < 100; ++i) {
        b.push_back(i % 2 == 0);
    }
    EXPECT_EQ(b.size(), 100);
    EXPECT_EQ(b.count(), 50);
}

TEST(BitArrayTest, AssignmentChain) {
    BitArray a(3, 0x07);
    BitArray b(2, 0x02);
    BitArray c(4, 0x0F);
    a = b = c;
    EXPECT_EQ(a.size(), 4);
    EXPECT_EQ(b.size(), 4);
    EXPECT_EQ(c.size(), 4);
    EXPECT_EQ(a.to_string(), c.to_string());
    EXPECT_EQ(b.to_string(), c.to_string());
}

TEST(BitArrayTest, InvalidResize) {
    BitArray ba(5);
    EXPECT_THROW(ba.resize(-1), std::invalid_argument);
}

TEST(BitArrayTest, BitwiseANDAssignment) {
    BitArray a(8, 0xAA);
    BitArray b(8, 0x0F);
    a &= b;

    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a.count(), 2);
    EXPECT_EQ(a.to_string(), "00001010");
}

TEST(BitArrayTest, BitwiseORAssignment) {
    BitArray a(8, 0xAA);
    BitArray b(8, 0x0F);
    a |= b;

    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a.count(), 6);
    EXPECT_EQ(a.to_string(), "10101111");
}

TEST(BitArrayTest, BitwiseXORAssignment) {
    BitArray a(8, 0xAA);
    BitArray b(8, 0x0F);
    a ^= b;

    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a.count(), 4);
    EXPECT_EQ(a.to_string(), "10100101");
}

TEST(BitArrayTest, BitwiseOperationsWithSelf) {
    BitArray a(8, 0xFF);
    a &= a;
    EXPECT_EQ(a.count(), 8);

    a |= a;
    EXPECT_EQ(a.count(), 8);

    a ^= a;
    EXPECT_EQ(a.count(), 0);
}

TEST(BitArrayTest, LeftShiftAssignment) {
    BitArray a(8, 0x0F);
    a <<= 2;
    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a.count(), 4);
    EXPECT_EQ(a.to_string(), "00111100");
}

TEST(BitArrayTest, LeftShiftAssignmentLargeShift) {
    BitArray a(8, 0xFF);
    a <<= 10;

    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a.count(), 0);
    EXPECT_EQ(a.to_string(), "00000000");
}

TEST(BitArrayTest, RightShiftAssignment) {
    BitArray a(8, 0xF0);
    a >>= 2;

    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a.count(), 4);
    EXPECT_EQ(a.to_string(), "00111100");
}

TEST(BitArrayTest, RightShiftAssignmentWithOnes) {
    BitArray a(8, 0xFF);
    a >>= 4;

    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a.count(), 4);
    EXPECT_EQ(a.to_string(), "00001111");
}

TEST(BitArrayTest, LeftShiftOperator) {
    BitArray a(8, 0x0F);
    BitArray result = a << 3;

    EXPECT_EQ(result.size(), 8);
    EXPECT_EQ(result.count(), 4);
    EXPECT_EQ(result.to_string(), "01111000");

    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a.count(), 4);
    EXPECT_EQ(a.to_string(), "00001111");
}

TEST(BitArrayTest, RightShiftOperator) {
    BitArray a(8, 0xF0);
    BitArray result = a >> 2;

    EXPECT_EQ(result.size(), 8);
    EXPECT_EQ(result.count(), 4);
    EXPECT_EQ(result.to_string(), "00111100");

    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a.count(), 4);
    EXPECT_EQ(a.to_string(), "11110000");
}

TEST(BitArrayTest, ZeroShift) {
    BitArray a(8, 0xAA);
    BitArray b = a << 0;
    BitArray c = a >> 0;

    EXPECT_EQ(b.to_string(), a.to_string());
    EXPECT_EQ(c.to_string(), a.to_string());
}

TEST(BitArrayTest, NegativeShift) {
    BitArray a(8, 0xAA);
    EXPECT_THROW(a << -1, std::invalid_argument);
    EXPECT_THROW(a >> -1, std::invalid_argument);
}

TEST(BitArrayTest, ChainOperations) {
    BitArray a(8, 0xAA);
    BitArray b(8, 0x0F);
    BitArray c(8, 0xF0);
    a &= b;
    a |= c;
    a ^= b;

    EXPECT_EQ(a.count(), 6);
    EXPECT_EQ(a.to_string(), "11110101");
}

TEST(BitArrayTest, ShiftChain) {
    BitArray a(8, 0x01);
    a <<= 1;
    a <<= 2;
    a >>= 1;

    EXPECT_EQ(a.count(), 1);
    EXPECT_EQ(a.to_string(), "00000100");
}

TEST(BitArrayTest, DifferentSizesBitwiseOperations) {
    BitArray a(6, 0x3F);
    BitArray b(8, 0xFF);

    EXPECT_THROW(a &= b, std::invalid_argument);
    EXPECT_THROW(a |= b, std::invalid_argument);
    EXPECT_THROW(a ^= b, std::invalid_argument);
}

TEST(BitArrayTest, EmptyArrayOperations) {
    BitArray a;
    BitArray b(8, 0xFF);
    EXPECT_THROW(a &= b, std::invalid_argument);
    EXPECT_THROW(a |= b, std::invalid_argument);
    EXPECT_THROW(a ^= b, std::invalid_argument);
}

TEST(BitArrayTest, SetSingleBit) {
    BitArray ba(8, 0x00);
    ba.set(0);
    EXPECT_TRUE(ba[0]);
    EXPECT_EQ(ba.count(), 1);
}

TEST(BitArrayTest, SetWithFalseValue) {
    BitArray ba(8, 0xFF);
    ba.set(2, false);
    EXPECT_FALSE(ba[2]);
    EXPECT_EQ(ba.count(), 7);
}

TEST(BitArrayTest, SetAllBits) {
    BitArray ba(8, 0x00);
    ba.set();
    EXPECT_EQ(ba.count(), 8);
    BitArray ba2(8, 0x0F);
    ba2.set();
    EXPECT_EQ(ba2.count(), 8);
}

TEST(BitArrayTest, ResetSingleBit) {
    BitArray ba(8, 0xFF);
    ba.reset(0);
    EXPECT_FALSE(ba[0]);
    EXPECT_EQ(ba.count(), 7);
}

TEST(BitArrayTest, ResetFalseBit) {
    BitArray ba(8, 0xFE);
    ba.reset(0);
    EXPECT_FALSE(ba[0]);
    EXPECT_EQ(ba.count(), 7);
}

TEST(BitArrayTest, ResetAllBits) {
    BitArray ba(8, 0xFF);
    ba.reset();
    EXPECT_EQ(ba.count(), 0);
    for (int i = 0; i < 8; ++i) {
        EXPECT_FALSE(ba[i]);
    }
}

TEST(BitArrayTest, AnyMethod) {
    BitArray empty(8, 0x00);
    BitArray withOneBit(8, 0x01);
    BitArray withMultipleBits(8, 0x0A);
    BitArray full(8, 0xFF);

    EXPECT_FALSE(empty.any());
    EXPECT_TRUE(withOneBit.any());
    EXPECT_TRUE(withMultipleBits.any());
    EXPECT_TRUE(full.any());
}

TEST(BitArrayTest, NoneMethod) {
    BitArray empty(8, 0x00);
    BitArray withOneBit(8, 0x01);
    BitArray withMultipleBits(8, 0x0A);
    BitArray full(8, 0xFF);

    EXPECT_TRUE(empty.none());
    EXPECT_FALSE(withOneBit.none());
    EXPECT_FALSE(withMultipleBits.none());
    EXPECT_FALSE(full.none());
}

TEST(BitArrayTest, OperatorNot) {
    BitArray ba1(8, 0x00);
    BitArray result1 = ~ba1;
    EXPECT_EQ(result1.count(), 8);
    EXPECT_EQ(result1.to_string(), "11111111");

    BitArray ba2(8, 0xFF);
    BitArray result2 = ~ba2;
    EXPECT_EQ(result2.count(), 0);
    EXPECT_EQ(result2.to_string(), "00000000");

    BitArray ba3(8, 0x0F);
    BitArray result3 = ~ba3;
    EXPECT_EQ(result3.count(), 4);
    EXPECT_EQ(result3.to_string(), "11110000");
    EXPECT_EQ(ba3.count(), 4);
    EXPECT_EQ(ba3.to_string(), "00001111");
}

TEST(BitArrayTest, CountMethod) {
    BitArray empty(8, 0x00);
    EXPECT_EQ(empty.count(), 0);

    BitArray full(8, 0xFF);
    EXPECT_EQ(full.count(), 8);

    BitArray mixed(8, 0xAA);
    EXPECT_EQ(mixed.count(), 4);

    BitArray single(8, 0x01);
    EXPECT_EQ(single.count(), 1);
}

TEST(BitArrayTest, OperatorBracket) {
    const BitArray empty(8, 0x00);
    for (int i = 0; i < 8; ++i) {
        EXPECT_FALSE(empty[i]);
    }

    const BitArray full(8, 0xFF);
    for (int i = 0; i < 8; ++i) {
        EXPECT_TRUE(full[i]);
    }

    const BitArray mixed(8, 0xA5);
    EXPECT_TRUE(mixed[0]);
    EXPECT_FALSE(mixed[1]);
    EXPECT_TRUE(mixed[2]);
    EXPECT_FALSE(mixed[3]);
    EXPECT_FALSE(mixed[4]);
    EXPECT_TRUE(mixed[5]);
    EXPECT_FALSE(mixed[6]);
    EXPECT_TRUE(mixed[7]);
}

TEST(BitArrayTest, SizeMethod) {
    BitArray ba1(0);
    EXPECT_EQ(ba1.size(), 0);

    BitArray ba3(8);
    EXPECT_EQ(ba3.size(), 8);

    BitArray ba5(100);
    EXPECT_EQ(ba5.size(), 100);
}

TEST(BitArrayTest, EmptyMethod) {
    BitArray ba1(0);
    EXPECT_TRUE(ba1.empty());

    BitArray ba4(100);
    EXPECT_FALSE(ba4.empty());
}

TEST(BitArrayTest, ToStringMethod) {
    BitArray zero_size(0);
    EXPECT_EQ(zero_size.to_string(), "");

    BitArray empty(8, 0x00);
    EXPECT_EQ(empty.to_string(), "00000000");

    BitArray full(8, 0xFF);
    EXPECT_EQ(full.to_string(), "11111111");

    BitArray mixed(8, 0xAA);
    EXPECT_EQ(mixed.to_string(), "10101010");

    BitArray large(12, 0xAAA);
    EXPECT_EQ(large.to_string(), "101010101010");
}

TEST(BitArrayTest, OperatorEqual) {
    BitArray ba1(8, 0xAA);
    BitArray ba2(8, 0xAA);
    BitArray ba3(8, 0x55);
    BitArray ba4(4, 0xAA);

    EXPECT_TRUE(ba1 == ba2);
    EXPECT_FALSE(ba1 == ba3);
    EXPECT_FALSE(ba1 == ba4);

    BitArray empty1(0);
    BitArray empty2(0);
    EXPECT_TRUE(empty1 == empty2);

    BitArray non_empty(8, 0xFF);
    EXPECT_FALSE(empty1 == non_empty);
}

TEST(BitArrayTest, OperatorNotEqual) {
    BitArray ba1(8, 0xAA);
    BitArray ba2(8, 0xAA);
    BitArray ba3(8, 0x55);
    BitArray ba4(4, 0xAA);

    EXPECT_FALSE(ba1 != ba2);
    EXPECT_TRUE(ba1 != ba3);
    EXPECT_TRUE(ba1 != ba4);
}

TEST(BitArrayTest, OperatorAnd) {
    BitArray ba1(8, 0xAA);
    BitArray ba2(8, 0x0F);
    BitArray result = ba1 & ba2;

    EXPECT_EQ(result.to_string(), "00001010");
    EXPECT_EQ(result.count(), 2);

    BitArray self_and = ba1 & ba1;
    EXPECT_TRUE(self_and == ba1);

    BitArray full(8, 0xFF);
    BitArray and_with_full = ba1 & full;
    EXPECT_TRUE(and_with_full == ba1);

    BitArray empty(8, 0x00);
    BitArray and_with_empty = ba1 & empty;
    EXPECT_TRUE(and_with_empty == empty);
}

TEST(BitArrayTest, OperatorOr) {
    BitArray ba1(8, 0xAA);
    BitArray ba2(8, 0x0F);
    BitArray result = ba1 | ba2;

    EXPECT_EQ(result.to_string(), "10101111");
    EXPECT_EQ(result.count(), 6);

    BitArray self_or = ba1 | ba1;
    EXPECT_TRUE(self_or == ba1);

    BitArray full(8, 0xFF);
    BitArray or_with_full = ba1 | full;
    EXPECT_TRUE(or_with_full == full);

    BitArray empty(8, 0x00);
    BitArray or_with_empty = ba1 | empty;
    EXPECT_TRUE(or_with_empty == ba1);
}

TEST(BitArrayTest, OperatorXor) {
    BitArray ba1(8, 0xAA);
    BitArray ba2(8, 0x0F);
    BitArray result = ba1 ^ ba2;

    EXPECT_EQ(result.to_string(), "10100101");
    EXPECT_EQ(result.count(), 4);

    BitArray self_xor = ba1 ^ ba1;
    EXPECT_EQ(self_xor.count(), 0);
    EXPECT_EQ(self_xor.to_string(), "00000000");

    BitArray full(8, 0xFF);
    BitArray xor_with_full = ba1 ^ full;
    BitArray not_ba1 = ~ba1;
    EXPECT_TRUE(xor_with_full == not_ba1);

    BitArray empty(8, 0x00);
    BitArray xor_with_empty = ba1 ^ empty;
    EXPECT_TRUE(xor_with_empty == ba1);
}

TEST(BitArrayTest, ComplexBitwiseExpressions) {
    BitArray a(8, 0xAA);
    BitArray b(8, 0x0F);
    BitArray c(8, 0x33);

    BitArray result1 = (a & b) | c;
    EXPECT_EQ(result1.to_string(), "00111011");

    BitArray result2 = (a | b) & c;
    EXPECT_EQ(result2.to_string(), "00100011");

    BitArray result3 = a ^ b ^ c;
    EXPECT_EQ(result3.to_string(), "10010110");
}

TEST(BitArrayTest, BitwiseOperationsWithDifferentSizes) {
    BitArray large(8, 0xFF);
    BitArray small(4, 0xFF);

    EXPECT_THROW(large & small, std::invalid_argument);
    EXPECT_THROW(large | small, std::invalid_argument);
    EXPECT_THROW(large ^ small, std::invalid_argument);
    EXPECT_THROW(small & large, std::invalid_argument);
    EXPECT_THROW(small | large, std::invalid_argument);
    EXPECT_THROW(small ^ large, std::invalid_argument);
}

TEST(BitArrayTest, BasicReadWrite) {
    BitArray ba(10);
    ba[0] = true;
    ba[5] = true;
    ba[9] = true;

    EXPECT_TRUE(ba[0]);
    EXPECT_TRUE(ba[5]);
    EXPECT_TRUE(ba[9]);
    EXPECT_FALSE(ba[1]);
    EXPECT_FALSE(ba[6]);
}

TEST(BitArrayTest, MultipleAssignments) {
    BitArray ba(8);
    ba[3] = true;
    EXPECT_TRUE(ba[3]);

    ba[3] = false;
    EXPECT_FALSE(ba[3]);

    ba[3] = true;
    EXPECT_TRUE(ba[3]);
}

TEST(BitArrayTest, ChainedAssignment) {
    BitArray ba(10);
    ba[0] = ba[1] = ba[2] = true;

    EXPECT_TRUE(ba[0]);
    EXPECT_TRUE(ba[1]);
    EXPECT_TRUE(ba[2]);
    EXPECT_FALSE(ba[3]);
}

TEST(BitArrayTest, ConstAccess) {
    BitArray ba(10);
    ba[3] = true;
    ba[7] = true;
    const BitArray& const_ba = ba;

    EXPECT_TRUE(const_ba[3]);
    EXPECT_TRUE(const_ba[7]);
    EXPECT_FALSE(const_ba[0]);
    EXPECT_FALSE(const_ba[5]);
}

TEST(BitArrayTest, BoundaryConditions) {
    BitArray ba(16);
    ba[0] = true;
    ba[15] = true;

    EXPECT_TRUE(ba[0]);
    EXPECT_TRUE(ba[15]);
    EXPECT_FALSE(ba[1]);
    EXPECT_FALSE(ba[14]);
}

TEST(BitArrayTest, AssignmentFromOtherBits) {
    BitArray ba(8);
    ba[0] = true;
    ba[4] = true;
    ba[1] = ba[0];
    ba[2] = ba[3];
    ba[5] = ba[4];

    EXPECT_TRUE(ba[0]);
    EXPECT_TRUE(ba[1]);
    EXPECT_FALSE(ba[2]);
    EXPECT_FALSE(ba[3]);
    EXPECT_TRUE(ba[4]);
    EXPECT_TRUE(ba[5]);
}

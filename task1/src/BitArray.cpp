#include "BitArray.h"

#include <algorithm>
#include <stdexcept>
#include <iostream>

static void checkArgument(int arg){
    if (arg < 0) {
        throw std::invalid_argument("Argument must be non-negative.");
    }
}

void BitArray::checkSizeMatch(const BitArray &other) const{
    if (other.size() != bitSize) {
        throw std::invalid_argument("Size mismatch");
    }
}

void BitArray::checkBitPos(int bitPos) const {
    if (bitPos < 0 || static_cast<size_t>(bitPos) > bitSize) {
        throw std::out_of_range("Index out of range");
    }
}

void BitArray::checkNotEmpty() const {
    if (bitSize == 0) {
        throw std::out_of_range("BitArray is empty.");
    }
}

unsigned long BitArray::getMask() const{
    size_t lastBlockSize = bitSize % BITS_PER_LONG;
    return (lastBlockSize == 0) ? ~0UL : (1UL << lastBlockSize) - 1;
}

BitArray::BitArray(): array(nullptr), bitSize(0), capacity(0) {};

BitArray::~BitArray() {
        delete[] array;
}

BitArray::BitArray(int size, unsigned long value) {
    checkArgument(size);
    if (size == 0) {
        bitSize = 0;
        capacity = 0;
        array = nullptr;
        return;
    }

    bitSize = size;
    capacity = (bitSize + BITS_PER_LONG - 1)/BITS_PER_LONG;
    array = new unsigned long[capacity]();
    array[0] = value & getMask();
}

BitArray::BitArray(const BitArray &other): array(nullptr), bitSize(other.bitSize), capacity(other.capacity) {
    if (capacity > 0) {
        array = new unsigned long[capacity]();
        for (size_t i = 0; i < capacity; ++i) {
            array[i] = other.array[i];
        }
    }
}

BitArray::BitProxy::BitProxy(BitArray& bitArray, int bitPos) : bitArray(bitArray), bitPos(bitPos) {};

BitArray::BitProxy::operator bool() const {
    return static_cast<const BitArray&>(bitArray).operator[](bitPos);
}

BitArray::BitProxy& BitArray::BitProxy::operator=(bool value) {
    bitArray.set(bitPos, value);
    return *this;
}

BitArray::BitProxy BitArray::operator[](int bitPos) {
    checkNotEmpty();
    checkBitPos(bitPos);
    return BitProxy(*this, bitPos);
}

BitArray::BitProxy& BitArray::BitProxy::operator=(const BitProxy& other) {
    const bool value = static_cast<bool>(other);
    bitArray.set(bitPos, value);
    return *this;
}

void BitArray::swap(BitArray& other) {
    std::swap(array, other.array);
    std::swap(bitSize, other.bitSize);
    std::swap(capacity, other.capacity);
}

BitArray& BitArray::operator=(const BitArray& other) {
    if (this ==  &other) {
        return *this;
    }
    BitArray tmp(other);
    swap(tmp);
    return *this;
}

void BitArray::clear() {
    delete[] array;
    bitSize = 0;
    capacity = 0;
    array = nullptr;
}

BitArray& BitArray::set(int bitPos, bool value) {
    checkArgument(bitPos);
    size_t arrIndex = bitPos / BITS_PER_LONG;
    size_t bitIndex = bitPos % BITS_PER_LONG;
    if (value) {
        array[arrIndex] |= 1UL << bitIndex;
    }
    else {
        array[arrIndex] &= ~(1UL << bitIndex);
    }
    return *this;
}

BitArray& BitArray::set() {
    if (array == nullptr) {
        return *this;
    }
    for (size_t i = 0; i < capacity; ++i) {
        array[i] = ~0UL;
    }
    array[capacity - 1] &= getMask();
    return *this;
}

BitArray& BitArray::reset(int bitPos) {
    return set(bitPos, false);
}

BitArray& BitArray::reset() {
    if (array == nullptr) {
        return *this;
    }
    for (size_t i = 0; i < capacity; ++i) {
        array[i] = 0UL;
    }
    return *this;
}

void BitArray::reallocate(const size_t newCapacity, const size_t newSize, const bool value) {
    auto newArray = new unsigned long[newCapacity]();
    if (array != nullptr) {
        for (size_t i = 0; i < capacity; ++i) {
            newArray[i] = array[i];
        }
        delete[] array;
    }
    if (value) {
        size_t newBits = newSize - bitSize;
        size_t oldLastBlockSize = bitSize % BITS_PER_LONG;
        if (oldLastBlockSize > 0) {
            newArray[capacity - 1] |= ~0UL << oldLastBlockSize;
        }
        for (size_t i = capacity; i < newCapacity; ++i) {
            newArray[i] = ~0UL;
        }
        size_t lastBlockBits = (newBits - (BITS_PER_LONG - oldLastBlockSize)) % BITS_PER_LONG;
        newArray[newCapacity - 1] >>= BITS_PER_LONG - lastBlockBits;
    }
    array = newArray;
    bitSize = newSize;
    capacity = newCapacity;
}

void BitArray::resize(int newSize, bool value) {
    checkArgument(newSize);
    if (newSize == 0) {
        clear();
        return;
    }
    if (newSize == bitSize) {
        return;
    }
    if (newSize < bitSize) {
        for (size_t i = newSize; i < bitSize; ++i) {
            reset(static_cast<int>(i));
        }
        bitSize = newSize;
        return;
    }
    size_t newCapacity = (newSize + BITS_PER_LONG - 1) / BITS_PER_LONG;
    if (newCapacity > capacity) {
        reallocate(newCapacity, newSize, value);
        return;
    }
    if (value) {
        for (size_t i = bitSize; i < newSize; ++i) {
            set(static_cast<int>(i), value);
        }
    }
    bitSize = newSize;
}

void BitArray::push_back(const bool bit) {
    const size_t newBitSize = bitSize + 1;
    const size_t newCapacity = (newBitSize + BITS_PER_LONG - 1) / BITS_PER_LONG;
    if (newCapacity > capacity) {
        reallocate(newCapacity, newBitSize, false);
    }
    else {
        bitSize = newBitSize;
    }
    set(static_cast<int>(bitSize - 1), bit);
}

BitArray& BitArray::operator&=(const BitArray& other) {
    checkSizeMatch(other);
    for (size_t i = 0; i < capacity; ++i) {
        array[i] &= other.array[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& other) {
    checkSizeMatch(other);
    for (size_t i = 0; i < capacity; ++i) {
        array[i] |= other.array[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& other) {
    checkSizeMatch(other);
    for (size_t i = 0; i < capacity; ++i) {
        array[i] ^= other.array[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int shift) {
    checkArgument(shift);
    if (shift == 0) {
        return *this;
    }
    if (shift >= bitSize) {
        for (size_t i = 0; i < capacity; ++i) {
            array[i] = 0;
        }
        return *this;
    }
    size_t blockShift = shift / BITS_PER_LONG;
    size_t bitShift = shift % BITS_PER_LONG;
    if (blockShift > 0) {
        for (size_t i = capacity - 1; i >= blockShift; --i) {
            array[i] = array[i - blockShift];
        }
        for (size_t i = 0; i < blockShift; ++i) {
            array[i] = 0;
        }
    }
    if (bitShift > 0) {
        unsigned long carry = 0;
        for (size_t i = 0; i < capacity; ++i) {
            unsigned long tmp = array[i];
            array[i] = tmp << bitShift | carry;
            carry = tmp >> (BITS_PER_LONG - bitShift);
        }
    }
    return *this;
}

BitArray& BitArray::operator>>=(int shift) {
    checkArgument(shift);
    if (shift == 0) {
        return *this;
    }
    if (shift >= bitSize) {
        for (size_t i = 0; i < capacity; ++i) {
            array[i] = 0;
        }
        return *this;
    }
    size_t blockShift = shift / BITS_PER_LONG;
    size_t bitShift = shift % BITS_PER_LONG;
    if (blockShift > 0) {
        for (size_t i = 0; i < capacity - blockShift; ++i) {
            array[i] = array[i + blockShift];
        }
        for (size_t i = capacity - blockShift; i < capacity; ++i) {
            array[i] = 0;
        }
    }
    if (bitShift > 0) {
        unsigned long carry = 0;
        for (size_t i = capacity; i > 0; --i) {
            unsigned long tmp = array[i - 1];
            array[i - 1] = tmp >> bitShift | carry;
            carry = tmp << (BITS_PER_LONG - bitShift);
        }
    }
    return *this;
}

BitArray BitArray::operator<<(int shift) const {
    BitArray copy(*this);
    return copy<<=shift;
}

BitArray BitArray::operator>>(int shift) const {
    BitArray copy(*this);
    return copy>>=shift;
}

bool BitArray::any() const{
    if (array == nullptr) {
        return false;
    }
    for (size_t i = 0; i < capacity; ++i) {
        if (array[i] != 0) {
            return true;
        }
    }
    return false;
}

bool BitArray::none() const {
    return !any();
}

BitArray BitArray::operator~() const {
    BitArray res(*this);
    for (size_t i = 0; i < capacity; ++i) {
        res.array[i] = ~array[i];
    }
    if (res.capacity > 0) {
        res.array[capacity - 1] &= getMask();
    }
    return res;
}

int BitArray::count() const {
    int res = 0;
    for (size_t i = 0; i < capacity; ++i) {
        unsigned long value = array[i];
        while (value) {
            if (value & 1UL) {
                res++;
            }
            value>>=1;
        }
    }
    return res;
}

bool BitArray::operator[](int bitPos) const {
    checkNotEmpty();
    checkBitPos(bitPos);
    size_t arrIndex = bitPos / BITS_PER_LONG;
    size_t bitIndex = bitPos % BITS_PER_LONG;
    return array[arrIndex] & (1UL << bitIndex);
}

int BitArray::size() const {
    return static_cast<int>(bitSize);
}

bool BitArray::empty() const {
    return bitSize == 0;
}

std::string BitArray::to_string() const {
    std::string str;
    str.reserve(bitSize);
    for (size_t i = 0; i < bitSize; ++i) {
        str += (operator[](static_cast<int>(i)) ? '1' : '0');
    }
    std::reverse(str.begin(), str.end());
    return str;
}

bool operator==(const BitArray & a, const BitArray & b) {
    if (a.size() != b.size()) {
        return false;
    }
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[static_cast<int>(i)] != b[static_cast<int>(i)]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const BitArray & a, const BitArray & b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2) {
    BitArray arr= b1;
    arr &= b2;
    return arr;
}

BitArray operator|(const BitArray& b1, const BitArray& b2) {
    BitArray arr= b1;
    arr |= b2;
    return arr;
}

BitArray operator^(const BitArray& b1, const BitArray& b2) {
    BitArray arr= b1;
    arr ^= b2;
    return arr;
}

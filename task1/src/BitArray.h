#ifndef BITARRAY_H
#define BITARRAY_H

#include <string>

class BitArray {
private:
  unsigned long* array;
  size_t bitSize;
  size_t capacity;
  static const size_t BITS_PER_LONG = sizeof(unsigned long) * 8;
  void checkSizeMatch(const BitArray &other) const;
  void checkNotEmpty() const;
  void checkBitPos (int bitPos) const;
  unsigned long getMask () const;
  void reallocate(size_t newCapacity, size_t newSize, bool value);

  class BitProxy {
  private:
    BitArray& bitArray;
    int bitPos;
  public:
    BitProxy(BitArray& bitArray, int bitPos);
    operator bool() const;
    BitProxy& operator=(bool value);
    BitProxy& operator=(const BitProxy& other);
  };

public:
  BitArray();
  ~BitArray();

  //Constructs an array that stores the specified number of bits.
  //The first sizeof(long) bits can be initialized using the value parameter.
  explicit BitArray(int size, unsigned long value = 0);
  BitArray(const BitArray& other);

  //Swaps the values of two bit arrays.
  void swap(BitArray& other);

  BitArray& operator=(const BitArray& other);

  //Changes the size of the array. If it expands
  //the new elements are initialized with the value.
  void resize(int newSize, bool value = false);


  //Clears the array.
  void clear();

  //Adds a new bit to the end of the array.
  //If necessary, memory is reallocated
  void push_back(bool bit);

  //Only work on arrays of the same size.
  BitArray& operator&=(const BitArray& other);
  BitArray& operator|=(const BitArray& other);
  BitArray& operator^=(const BitArray& other);
  BitArray& operator<<=(int shift);
  BitArray& operator>>=(int shift);
  BitArray operator<<(int shift) const;
  BitArray operator>>(int shift) const;

  //Sets the bit with index n to the value val.
  BitArray& set(int bitPos, bool value = true);
  //Fills the array with the truth.
  BitArray& set();

  //Sets the bit with index n to false.
  BitArray& reset(int bitPos);
  //Fills the array with a false.
  BitArray& reset();

  //true if the array contains a true bit.
  bool any() const;
  //true if all bits of the array are false.
  bool none() const;

  BitArray operator~() const;

  //Counts the number of single bits.
  int count() const;

  //Returns the value of the bit at index i. For constant objects (read-only).
  bool operator[](int bitPos) const;
  // For non-constant objects (reading and writing)
  BitProxy operator[](int bitPos);

  int size() const;
  bool empty() const;

  //Returns a string representation of the array.
  std::string to_string() const;
};

bool operator==(const BitArray & a, const BitArray & b);
bool operator!=(const BitArray & a, const BitArray & b);

BitArray operator&(const BitArray& b1, const BitArray& b2);
BitArray operator|(const BitArray& b1, const BitArray& b2);
BitArray operator^(const BitArray& b1, const BitArray& b2);

#endif

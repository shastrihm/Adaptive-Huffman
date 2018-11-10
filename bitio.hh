/*
 * A simple class to perform stream I/O on individual bits.
 * Before reading any bits, ensure your input stream still has valid inputs.
 */
#include <iostream>
#include <cassert>

class BitIO {
 public:
  // Construct with one of either an input stream or output (the other null)
  BitIO(std::ostream* os, std::istream* is);

  // Flushes out any remaining output bits and trailing zeros, if any:
  ~BitIO();

  BitIO(const BitIO&) = default;
  BitIO(BitIO&&) = default;
  BitIO& operator=(const BitIO&) = default;
  BitIO& operator=(BitIO&&) = default;

  // Output a single bit (buffered)
  void output_bit(bool bit);
    // manipulate c_
    // increment next_bit_pos
    // if next_bit_pos == 8, output to stream
    // reset next_bit_pos to 0

  // Read a single bit (or trailing zero)
  bool input_bit();
    // manipulate c_
    // decrement next_bit_pos
    // if next_bit_pos = 0, 

 private:
  std::ostream* os_;
  std::istream* is_;
  int next_bit_pos_;
  char c_;
};

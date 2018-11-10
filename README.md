# Adaptive-Huffman
An implementation of the Adaptive Huffman coding algorithm for file compression/decompression.


Name: Hrishee Shastri

HForest and HTree classes taken from the [assignment page](https://moodle.reed.edu/mod/assign/view.php?id=90579)



# Overview:

> huffman.hh + huffman.cc + test_huffman.cc

Declaration, definition, and testing of the Huffman class. 
Maintains a hufftree and a frequency table, modeled as a vector with 257 entries-- one for each ASCII value. For encode(c), we build a hufftree from scratch according to the 
frequency table, find the path to char c from the root, and then output a 
std::vector<bool> of bits such that true = branch right and false = branch left.
Then we increment c's entry in frequency table.
For decode(bit), we traverse the hufftree -- if 1, branch right. If 0, branch left. Once 
we reach a leaf node, we increment the key (ASCII value) count in the frequency table
and rebuild the huffman tree.

> bitio.hh + bitio.cc + test_bitio.cc

Declaration, definition, and testing of the BitIO class.
output_bit outputs a bit to the ostream. Once the number of fed bits 
reaches a multiple of 8, a char is put into ostream. 
If output_bit stops getting called at a non byte boundary,
the remaining bits are flushed and then outputted to the ostream.
input_bit reads bits in from istream and returns true if the bit is 1, else false.

> encoder.cc

Main file that takes input files, compresses them, and outputs them with a .comp suffix.
It reads in a character at a time from the input file and encodes it. The encoded bits 
are then streamed to the output file. 

> decoder.cc

Main file that takes input .comp files, decompresses them, and outputs them with a 
.plaintext suffix. It reads in a bit at a time and outputs an ASCII value when the 
huffman tree reaches a leaf node. 


Compression Tests:
-------------------
|File name       |  Raw Size (bytes) | Compressed Size (bytes) | Original Matches Decoded File? |
| :------------: |  :--------------: | :---------------------: | :----------------------------: |
|bitio.cc        |     1480          |         1120            |   yes                          |
|ascii_art.txt   |     238           |         104             |   yes                          |
|ASCII_Table.txt |     2580          |         1620            |   yes                          | 
|ISO.txt         |     6070          |         3390            |   yes                          |
|assignment.txt  |     9510          |         5890            |   yes                          |




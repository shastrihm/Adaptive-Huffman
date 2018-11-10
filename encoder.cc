#include <fstream>
#include "bitio.hh"
#include "huffman.hh"
#include <string>

int main(int argc,char** argv)
{   
    assert(argc >= 2);

    for(int file = 1; file < argc; ++file)
    {
        // set up read from file
        std::ifstream inpfile(argv[file]);
        

        // set up write to file
        std::string outname(argv[file]);
        outname = outname + ".comp";
        std::ofstream outfile(outname);


        std::cout<<"encoding to "<< outname << "\n";

        BitIO bitio(&outfile,nullptr);

        char c; 

        Huffman encode_tree;

        Huffman::bits_t bits;

        while(inpfile.get(c))
        {
            bits = encode_tree.encode(c);
            for(auto i : bits)
            {
                bitio.output_bit(i);
            }
        }

        // encode HEOF
        for(auto i : encode_tree.encode(encode_tree.HEOF))
        {
            bitio.output_bit(i);
        }        
    }


    return 0;
} 




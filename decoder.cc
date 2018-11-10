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
        outname = outname + ".plaintext";
        std::ofstream outfile(outname);


        std::cout<< "decoding to " << outname << "\n";

        BitIO bitio(nullptr, &inpfile);

        int key = -1;
        Huffman decode_tree;
        while(key != decode_tree.HEOF)
        {
            key = -1;
            while(key == -1)
            {   
                // read bit by bit
                auto bit = bitio.input_bit();
                key = decode_tree.decode(bit);            
            }
            if(key != decode_tree.HEOF)
            {
                outfile.put(key);        
            }
        }        
    }



    return 0;
} 
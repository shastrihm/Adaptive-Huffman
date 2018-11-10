#include "bitio.hh"

BitIO::~BitIO()
{   
    // flush 
    if(this->os_ != nullptr)
    {   
        while(this->next_bit_pos_ != 0)
        {
            this->output_bit(false);
        }
    }
}

BitIO::BitIO(std::ostream* os, std::istream* is)
{
    assert(!(os and is) and (os or is));
    if(is == nullptr)
    {
        this->is_ = nullptr;
        this->os_ = os;
        this->next_bit_pos_ = 0;
    }

    else if(os == nullptr)
    {
        this->os_ = nullptr;
        this->is_ = is;
        this->next_bit_pos_ = 0;//
        (this->is_)->get(this->c_);
    }
}
    
void BitIO::output_bit(bool bit)
{
    assert(this->os_ != nullptr);

    if(bit == true)
    {
        // shift left and set LSB to 1
        this->c_ <<= 1;
        this->c_ |= 0x1;  
    }
    else if(bit == false)
    {
        // shift left set LSB to 0
        this->c_ <<= 1; 
        this->c_ &= 0xfe;
        // this->c_ &= 0xfe;
    }
    ++(this->next_bit_pos_);
    if(this->next_bit_pos_ == 8)//
    {
        (this->os_)->put(this->c_);
        this->c_ = 0;
        this->next_bit_pos_ = 0;            
    }
}

bool BitIO::input_bit()
{
    assert(this->is_ != nullptr);

    // shift right 1, get msb
    auto msb = this->c_ & 0b10000000;
    msb = msb >> 7;

    this->c_ <<= 1; 
    ++this->next_bit_pos_;

    if(this->next_bit_pos_ == 8)
    {
        this->next_bit_pos_ = 0;
        (this->is_)->get(this->c_);
    }

    return msb;
}
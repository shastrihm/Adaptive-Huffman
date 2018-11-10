/*
 * Huffman: a class to encode and decode symbols based on adaptive Huffman coding
 * https://en.wikipedia.org/wiki/Huffman_coding
 */

#include "huffman.hh"
#include <cmath>
#include <iostream>

Huffman::~Huffman()
{
    this->hufftree_->HTree::~HTree();
}

HTree::tree_ptr_t Huffman::create_huffman_tree()
{
    HForest forest;

    // add nodes to forest with key of symbol and value of symbol's count
    for(uint64_t i = 0; i < this->table_.size(); ++i)
    {
        forest.add_tree(HTree::tree_ptr_t(new HTree(i,this->table_[i])));
    }    

    // iterate until 1 node in forest
    while(forest.size() > 1)
    {
        auto node1 = forest.pop_top();
        auto node2 = forest.pop_top();
        auto total = node1->get_value() + node2->get_value();
        forest.add_tree(HTree::tree_ptr_t(new HTree(-1,total,node1,node2)));
    }
    assert(forest.size() == 1);
    return forest.pop_top();
}

Huffman::bits_t Huffman::encode(int symbol)
{
    this->hufftree_ = Huffman::create_huffman_tree();

    auto path_to_symb = this->hufftree_->HTree::path_to(symbol);

    Huffman::bits_t bits;
    for(auto dir : path_to_symb)
    {
        if(dir == HTree::Direction::LEFT)
        {
            bits.push_back(false);
        }
        else 
        {
            bits.push_back(true);
        }
    }

    //increment entry c of freq table 
    ++(this->table_[symbol]);

    return bits;
}

int Huffman::decode(bool bit)
{
    if(this->hufftree_ == nullptr)
    {
        this->hufftree_ = Huffman::create_huffman_tree();
    }

    // go right
    if(bit == true)
    {
        this->hufftree_ = this->hufftree_->HTree::get_child(HTree::Direction::RIGHT);
    }
    // go left
    else
    {
        this->hufftree_ = this->hufftree_->HTree::get_child(HTree::Direction::LEFT);
    }

    auto this_key = this->hufftree_->get_key();
   
    if(this_key > -1)
    {
        ++(this->table_[this_key]);
        this->hufftree_ = Huffman::create_huffman_tree();
        return this_key;
    }

    return -1;
}
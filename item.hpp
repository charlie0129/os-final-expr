#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>

enum class ITEM
{
    MILK,
    PANCAKE
};

class Item
{
    private:
        std::vector<std::map<std::string, int>*> itemPropertyList;

    public:
        Item();

        void test();

        void print();


        ~Item();
};
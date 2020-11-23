#pragma once
#include <vector>
#include <map>
#include <string>
#include <iostream>


class Item
{
    private:
        std::map<std::string, int> itemList {
            {"milk", 0},
            {"sd", 1}
        };
        std::vector<std::map<std::string, int>*> itemPropertyList;

    public:
        Item();

        void test();

        void print();

        void addQuantity(std::string itemCategory, int offset);

        ~Item();
};
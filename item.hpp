#pragma once
#include <map>
#include <string>
#include <iostream>
#include <mutex>
#include <stdexcept>


class Item
{
    private:
        std::map<std::string, std::map<std::string, int>> itemList;
        std::mutex mtx_itemList;

    public:
        Item();

        int addItem(std::string name);
        int addProperty(std::string itemName, std::string propertyName);
        int changePropertyValue(std::string itemName, std::string propertyName, int value);
        int getPropertyValue(std::string itemName, std::string propertyName);
        int increaseQuantity(std::string itemName, int offset = 1);
        int decreaseQuantity(std::string itemName, int offset = -1);
        int getQuantity(std::string itemName);

        ~Item();
};
#pragma once
#include <map>
#include <string>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <ostream>
#include <istream>
#include <vector>
#include <condition_variable>

class Item
{
    private:
        std::map<std::string, std::map<std::string, int>> itemList;
        std::map<std::string, std::condition_variable*> conditionVarList;
        std::map<std::string, std::mutex*> mtx_cvList;
        std::mutex mtx_itemList;

    public:
        Item();
        Item(std::istream& inputStream);

        int addItem(const std::string& name);
        int addProperty(const std::string& itemName, const std::string& propertyName);
        int changePropertyValue(const std::string& itemName, const std::string& propertyName, int value);
        int getPropertyValue(const std::string& itemName, const std::string& propertyName);
        int increaseQuantity(const std::string& itemName, int offset = 1);
        int decreaseQuantity(const std::string& itemName, int offset = -1);
        int getQuantity(const std::string& itemName);
        std::condition_variable* getConditionalVariable(const std::string& itemName);
        std::mutex* getMutex(const std::string& itemName);
        std::vector <std::string> getItemNameList();

        void writeObject(std::ostream& outputStream);
        void readObject(std::istream& inputStream);

        ~Item();
};
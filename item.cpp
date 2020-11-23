#include "item.hpp"
Item::Item()
{

}

int Item::addItem(std::string name)
{
    if (itemList.find(name) != itemList.end())
        return -1;
    mtx_itemList.lock();
    itemList.insert({name, std::map<std::string, int>{}});
    mtx_itemList.unlock();
    return 0;
}

int Item::addProperty(std::string itemName, std::string propertyName)
{
    std::map<std::string, std::map<std::string, int>>::iterator it;
    if ((it = itemList.find(itemName)) == itemList.end())
        return -1;
    if (it->second.find(propertyName) != it->second.end())
        return -1;
    mtx_itemList.lock();
    it->second.insert({propertyName, 0});
    mtx_itemList.unlock();
    return 0;
}

int Item::changePropertyValue(std::string itemName, std::string propertyName, int value)
{
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
        return -1;
    if ((it_propertyList = it_itemList->second.find(propertyName)) == it_itemList->second.end())
        return -1;
    mtx_itemList.lock();
    it_propertyList->second = value;
    mtx_itemList.unlock();
    return 0;
}

int Item::getProperty(std::string itemName, std::string propertyName)
{
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
        return -1;
    if ((it_propertyList = it_itemList->second.find(propertyName)) == it_itemList->second.end())
        return -1;
    return it_propertyList->second;
}

int Item::increaseQuantity(std::string itemName, int offset)
{
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
        return -1;
    if ((it_propertyList = it_itemList->second.find("quantity")) == it_itemList->second.end())
        return -1;
    mtx_itemList.lock();
    it_propertyList->second += offset;
    mtx_itemList.unlock();
    return 0;
}

int Item::decreaseQuantity(std::string itemName, int offset)
{
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
        return -1;
    if ((it_propertyList = it_itemList->second.find("quantity")) == it_itemList->second.end())
        return -1;
    mtx_itemList.lock();
    it_propertyList->second -= offset;
    mtx_itemList.unlock();
    return 0;
}

int Item::getQuantity(std::string itemName)
{
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
        return -1;
    if ((it_propertyList = it_itemList->second.find("quantity")) == it_itemList->second.end())
        return -1;
    return it_propertyList->second;
}

Item::~Item()
{

}
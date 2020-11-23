#include "item.hpp"
Item::Item()
{

}

int Item::addItem(std::string name)
{
    mtx_itemList.lock();
    if (itemList.find(name) != itemList.end())
        goto err;
    itemList.insert({name, std::map<std::string, int>{}});
    mtx_itemList.unlock();
    return 0;
err:
    mtx_itemList.unlock();
    return -1;
}

int Item::addProperty(std::string itemName, std::string propertyName)
{
    mtx_itemList.lock();
    std::map<std::string, std::map<std::string, int>>::iterator it;
    if ((it = itemList.find(itemName)) == itemList.end())
        goto err;
    if (it->second.find(propertyName) != it->second.end())
        goto err;
    it->second.insert({propertyName, 0});
    mtx_itemList.unlock();
    return 0;
err:
    mtx_itemList.unlock();
    return -1;
}

int Item::changePropertyValue(std::string itemName, std::string propertyName, int value)
{
    mtx_itemList.lock();
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
        goto err;
    if ((it_propertyList = it_itemList->second.find(propertyName)) == it_itemList->second.end())
        goto err;
    it_propertyList->second = value;
    mtx_itemList.unlock();
    return 0;
err:
    mtx_itemList.unlock();
    return -1;
}

int Item::getPropertyValue(std::string itemName, std::string propertyName)
{
    mtx_itemList.lock();
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
        goto err;
    if ((it_propertyList = it_itemList->second.find(propertyName)) == it_itemList->second.end())
        goto err;
    mtx_itemList.unlock();
    return it_propertyList->second;
err:
    mtx_itemList.unlock();
    return -1;
}

int Item::increaseQuantity(std::string itemName, int offset)
{
    mtx_itemList.lock();
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
        goto err;
    if ((it_propertyList = it_itemList->second.find("quantity")) == it_itemList->second.end())
        goto err;
    it_propertyList->second += offset;
    mtx_itemList.unlock();
    return 0;
err:
    mtx_itemList.unlock();
    return -1;
}

int Item::decreaseQuantity(std::string itemName, int offset)
{
    mtx_itemList.lock();
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
        goto err;
    if ((it_propertyList = it_itemList->second.find("quantity")) == it_itemList->second.end())
        goto err;
    it_propertyList->second -= offset;
    mtx_itemList.unlock();
    return 0;
err:
    mtx_itemList.unlock();
    return -1;
}

int Item::getQuantity(std::string itemName)
{
    mtx_itemList.lock();
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
        goto err;
    if ((it_propertyList = it_itemList->second.find("quantity")) == it_itemList->second.end())
        goto err;
    mtx_itemList.unlock();
    return it_propertyList->second;
err:
    mtx_itemList.unlock();
    return -1;
}

Item::~Item()
{

}
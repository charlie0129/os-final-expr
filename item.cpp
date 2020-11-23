#include "item.hpp"
Item::Item()
{
}

int Item::addItem(std::string name)
{
    mtx_itemList.lock();
    if (itemList.find(name) != itemList.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The item you are trying to add already exists."};
        goto err;
    }
    itemList.insert({name, std::map<std::string, int>{}});
    mtx_itemList.unlock();
    return 0;
err:
    return -1;
}

int Item::addProperty(std::string itemName, std::string propertyName)
{
    mtx_itemList.lock();
    std::map<std::string, std::map<std::string, int>>::iterator it;
    if ((it = itemList.find(itemName)) == itemList.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The item you referred to does not exist."};
        goto err;
    }
    if (it->second.find(propertyName) != it->second.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The property you are trying to add already exists."};
        goto err;
    }
    it->second.insert({propertyName, 0});
    mtx_itemList.unlock();
    return 0;
err:
    return -1;
}

int Item::changePropertyValue(std::string itemName, std::string propertyName, int value)
{
    mtx_itemList.lock();
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The item you referred to does not exist."};
        goto err;
    }
    if ((it_propertyList = it_itemList->second.find(propertyName)) == it_itemList->second.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The property you referred to does not exist."};
        goto err;
    }
    it_propertyList->second = value;
    mtx_itemList.unlock();
    return 0;
err:
    return -1;
}

int Item::getPropertyValue(std::string itemName, std::string propertyName)
{
    mtx_itemList.lock();
    std::map<std::string, std::map<std::string, int>>::iterator it_itemList;
    std::map<std::string, int>::iterator it_propertyList;
    if ((it_itemList = itemList.find(itemName)) == itemList.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The item you referred to does not exist."};
        goto err;
    }
    if ((it_propertyList = it_itemList->second.find(propertyName)) == it_itemList->second.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The property you referred to does not exist."};
        goto err;
    }
    mtx_itemList.unlock();
    return it_propertyList->second;
err:
    return -1;
}

int Item::increaseQuantity(std::string itemName, int offset)
{
    return changePropertyValue(itemName,
                               "quantity",
                               getPropertyValue(itemName, "quantity") + offset);
}

int Item::decreaseQuantity(std::string itemName, int offset)
{
    return increaseQuantity(itemName, offset);
}

int Item::getQuantity(std::string itemName)
{
    return getPropertyValue(itemName, "quantity");
}

Item::~Item()
{
}
#include "item.hpp"
Item::Item()
{
}

Item::Item(std::istream &inputStream)
{
    readObject(inputStream);
}

int Item::addItem(const std::string &name)
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

int Item::addProperty(const std::string &itemName, const std::string &propertyName)
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

int Item::changePropertyValue(const std::string &itemName, const std::string &propertyName, int value)
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

int Item::getPropertyValue(const std::string &itemName, const std::string &propertyName)
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

int Item::increaseQuantity(const std::string &itemName, int offset)
{
    return changePropertyValue(itemName,
                               "quantity",
                               getPropertyValue(itemName, "quantity") + offset);
}

int Item::decreaseQuantity(const std::string &itemName, int offset)
{
    return increaseQuantity(itemName, offset);
}

int Item::getQuantity(const std::string &itemName)
{
    return getPropertyValue(itemName, "quantity");
}

void Item::writeObject(std::ostream &outputStream)
{
    mtx_itemList.lock();
    outputStream << "{\n";
    for (auto &i : itemList)
    {
        outputStream << "  \"" << i.first << "\": {\n";
        for (std::map<std::string, int>::iterator j = i.second.begin();
             j != i.second.end();
             j++)
            outputStream << "    \"" << j->first << "\": " << j->second << "\n";
        outputStream << "  }\n";
    }
    outputStream << "}";
    mtx_itemList.unlock();
}

void Item::readObject(std::istream &inputStream)
{
    std::string jstr = "";
    std::string tmp;
    while (std::getline(inputStream, tmp))
        jstr += (tmp + "\n");
    int idx1 = 0;
    int idx2 = 0;
    while (true)
    {
        while (jstr[idx2 = ++idx1] != '\"');
        while (jstr[++idx2] != '\"');
        if (jstr[idx2 + 3] == '{')
        {
            std::string obj = jstr.substr(idx1 + 1, idx2 - idx1 - 1);
            addItem(obj);
            idx1 = idx2;
            int idx_end = idx1;
            while (jstr[++idx_end] != '}');
            while (idx1 < idx_end && idx2 < idx_end)
            {
                while (jstr[idx2 = ++idx1] != '\"');
                while (jstr[++idx2] != '\"');
                std::string key = jstr.substr(idx1 + 1, idx2 - idx1 - 1);
                addProperty(obj, key);
                idx1 = idx2 + 3;
                while (jstr[idx2] != '\n')
                    idx2++;
                if (jstr[idx2 - 1] == ',')
                    changePropertyValue(obj, key, atoi(jstr.substr(idx1, idx2 - idx1 - 1).c_str()));
                else
                    changePropertyValue(obj, key, atoi(jstr.substr(idx1, idx2 - idx1).c_str()));
                idx2 += 3;
            }
            idx2 = idx_end + 2;
            if (jstr[idx2] == '}')
                break;
        }
    }
}

Item::~Item()
{
}
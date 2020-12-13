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
        return -1;
    }

    itemList.insert({name, std::map<std::string, int>{}});
    std::condition_variable *v = new std::condition_variable;
    conditionVarList.insert({name, v});
    std::mutex *x = new std::mutex;
    mtx_cvList.insert({name, x});
    mtx_itemList.unlock();
    return 0;
}

int Item::addProperty(const std::string &itemName, const std::string &propertyName)
{
    mtx_itemList.lock();

    std::map<std::string, std::map<std::string, int>>::iterator it;

    if ((it = itemList.find(itemName)) == itemList.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The item you referred to does not exist."};
        return -1;
    }
    if (it->second.find(propertyName) != it->second.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The property you are trying to add already exists."};
        return -1;
    }

    it->second.insert({propertyName, 0});

    mtx_itemList.unlock();
    return 0;
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
        return -1;
    }
    if ((it_propertyList = it_itemList->second.find(propertyName)) == it_itemList->second.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The property you referred to does not exist."};
        return -1;
    }

    it_propertyList->second = value;

    mtx_itemList.unlock();
    return 0;
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
        return -1;
    }
    if ((it_propertyList = it_itemList->second.find(propertyName)) == it_itemList->second.end())
    {
        mtx_itemList.unlock();
        throw std::runtime_error{"The property you referred to does not exist."};
        return -1;
    }

    mtx_itemList.unlock();

    return it_propertyList->second;
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

std::condition_variable *Item::getConditionalVariable(const std::string &itemName)
{
    std::map<std::string, std::condition_variable *>::iterator it;
    if ((it = conditionVarList.find(itemName)) == conditionVarList.end())
    {
        throw std::runtime_error{"The item you referred to does not exist."};
        return nullptr;
    }

    return it->second;
}

std::mutex *Item::getMutex(const std::string &itemName)
{
    std::map<std::string, std::mutex *>::iterator it;
    if ((it = mtx_cvList.find(itemName)) == mtx_cvList.end())
    {
        throw std::runtime_error{"The item you referred to does not exist."};
        return nullptr;
    }

    return it->second;
}

std::vector <std::string> Item::getItemNameList()
{
    std::vector<std::string>itemNameList{};
    for (auto &i : itemList)
    {
        itemNameList.push_back(i.first);
    }
    return itemNameList;
}

void Item::writeObject(std::ostream &outputStream)
{
    mtx_itemList.lock();

    outputStream << "{\n";

    int idx_ = 1;
    for (std::map<std::string, std::map<std::string, int>>::iterator i = itemList.begin();
         i != itemList.end();
         i++, idx_++)
    {
        outputStream << "  \"" << i->first << "\": {\n";

        int idx = 1;
        for (std::map<std::string, int>::iterator j = i->second.begin();
             j != i->second.end();
             j++, idx++)
        {
            if (idx <= i->second.size() - 1)
            {
                outputStream << "    \"" << j->first << "\": " << j->second << ",\n";
            }
            else
            {
                outputStream << "    \"" << j->first << "\": " << j->second << "\n";
            }
        }

        if (idx_ <= itemList.size() - 1)
        {
            outputStream << "  },\n";
        }
        else
        {
            outputStream << "  }\n";
        }
    }

    outputStream << "}";

    mtx_itemList.unlock();
}

void Item::readObject(std::istream &inputStream)
{
    std::string jstr = "";
    std::string tmp;
    while (std::getline(inputStream, tmp))
    {
        jstr += (tmp + "\n");
    }

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
                {
                    idx2++;
                }

                if (jstr[idx2 - 1] == ',')
                {
                    changePropertyValue(obj, key, std::stoi(jstr.substr(idx1, idx2 - idx1 - 1)));
                }
                else
                {
                    changePropertyValue(obj, key, std::stoi(jstr.substr(idx1, idx2 - idx1)));
                }

                idx2 += 3;
            }

            idx2 = idx_end + 2;

            if (jstr[idx2] == '}')
            {
                break;
            }
        }
    }
}

Item::~Item()
{
    for (auto &i : conditionVarList)
        delete i.second;
}
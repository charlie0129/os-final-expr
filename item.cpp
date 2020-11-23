#include "item.hpp"
Item::Item()
{
    
}
void Item::test()
{
    std::map<std::string, int> *map_tmp = new std::map<std::string, int>();
    (*map_tmp).insert(std::pair<std::string, int>("category", static_cast<int>(ITEM::MILK)));
    (*map_tmp).insert(std::pair<std::string, int>("quantity", 8));
    (*map_tmp).insert(std::pair<std::string, int>("priority", 2));
    itemPropertyList.push_back(map_tmp);
}
void Item::print()
{
    std::cout << itemPropertyList[0]->find("quantity")->second;
}


Item::~Item()
{
    delete itemPropertyList[0];
}
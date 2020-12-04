#include "customer.hpp"

extern Item itemRepository;

class customer
{
    Item* i;
    std::string ItemList;
    customer(Item& item)
    {
        this->i=&item;
        std::thread shopping();
    }
    void buy()
    {
    }
}



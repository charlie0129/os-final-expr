#include "customer.hpp"

extern Item itemRepository;

class customer
{
    Item* i;
    std::vector<std::string> itemname;
    int *stuff;
    customer(Item& item)
    {
        this->i=&item;
        this->itemname=this->i->getItemNameList();
        this->stuff=(int*)malloc(sizeof(int)*(this->itemname.size()));
        Quantity(stuff,(this->itemname.size()));
        std::thread shopping(buy);
    }
    void buy()
    {
        
    }
    void Quantity(int *stuff,int stuffnum)
    {
        for(int i=0;i<stuffnum;i++)
        {
            *(stuff+i)=rand()%10;
        }
    }

}



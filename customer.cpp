#include "customer.hpp"

extern Item itemRepository;
extern std::mutex ReSupply;//通知补获锁
extern std::mutex Check;//顾客结账锁
class customer
{
    Item* i;
    std::vector<std::string> itemname;
    int *stuff;
    customer(Item& item)
    {
        this->i=&item;
        this->itemname=this->i->getItemNameList();//获取商品名
        this->stuff=(int*)malloc(sizeof(int)*(this->itemname.size()));//获取商品数量
        Quantity(stuff,(this->itemname.size()));//随机创建数量
        std::thread shopping(INOUT);//建立购买线程
    }
    void INOUT()
    {
        int RemainToBuy=this->itemname.size(); //？？？
        int count=0;//从第一个商品开始购买
        int PresentGoodValue;//检查当前商品数量
        while(RemainToBuy>=count)
        {
            PresentGoodValue=itemRepository.getPropertyValue(this->itemname.back(),"quantity");
            if(PresentGoodValue<this->stuff[count])
            {
                ReSupply.lock();
            /*
                wait for WHT mutex
            */
            
            }


            count++;
        }
    }
    void Quantity(int *stuff,int stuffnum)
    {
        for(int i=0;i<stuffnum;i++)
        {
            *(stuff+i)=rand()%10;
        }
    }

};

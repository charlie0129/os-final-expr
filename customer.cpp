#include "customer.hpp"

Customer::Customer(Item& item,std::vector<Supplier*>& spp,Checker* a)
{
    this->i=&item;
    srand(time(NULL));
    int itemIdx = rand() % i->getItemNameList().size();
    goodNum =rand()%10  + 1;
    this->itemname={i->getItemNameList()[itemIdx],goodNum};//获取商品名
    myChecker=a;
    for(auto j:spp)
    {
        if(j->getItem_name()==this->itemname.first)
        {
            this->mySpp=j;
        }
    }
    customerThread = new std::thread{&Customer::IN, this};
}

Customer::~Customer()
{
    customerThread->join();
    delete customerThread;
}

void Customer::IN()
{
    int count=0;//从第一个商品开始购买
    int PresentGoodValue;//检查当前商品数量
    std::unique_lock<std::mutex> lock(* i->getMutex(itemname.first));
    PresentGoodValue=i->getQuantity(this->itemname.first);
    #ifdef DEBUG
        std::cout << "customer need: " << itemname.first << "," << goodNum << std::endl;
    #endif
    while((PresentGoodValue=i->getQuantity(this->itemname.first)) < this->goodNum)
    {
        mySpp->setNeedSupply(true);
        i->getConditionalVariable(itemname.first)->notify_all();
        #ifdef DEBUG
            std::cout << "customer notifyAll."<< std::endl;
        #endif
        i->getConditionalVariable(itemname.first)->wait(lock);
    }
    
    //lock.lock();
    i->decreaseQuantity(this->itemname.first,-(this->goodNum));//拿走商品
    //lock.unlock();
    #ifdef DEBUG
        std::cout << "customer get goods: " << itemname.first << "," << goodNum << std::endl;
    #endif
    //进结账队列
    myChecker->addWaitingLine(this->itemname);
}

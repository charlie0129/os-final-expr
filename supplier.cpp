#include "item.hpp"
#include "supplier.hpp"


Supplier::Supplier()
{
}

Supplier::Supplier(std::string name, Item& i){
    this->item = &i;
    this->item_name = name;
    this->supply_nums = 10;
    this->supply_time = 1;
    this->alive = true;
    this->needSupply = false;
    supply_thread = new std::thread(&Supplier::supplyItem, this);
}

Supplier::~Supplier(){
    supply_thread->join();
    delete supply_thread;
    supply_thread = nullptr;
}

std::string Supplier::getItem_name(){
    return item_name;
}

std::thread* Supplier::getSupply_thread(){
    return supply_thread;
}

bool Supplier::isNeedSupply(){
    return needSupply;
}

bool Supplier::isAlive(){
    return alive;
}

void Supplier::setAlive(bool a){
    this->alive = a;
}

void Supplier::setNeedSupply(bool need){
    this->needSupply = need;
}

int Supplier::getSupply_nums(){
    return supply_nums;
}

int Supplier::getSupply_time(){
    return supply_time;
}

void Supplier::setSupply_nums(int nums){
    this->supply_nums = nums;
}

void Supplier::setSupply_time(int time){
    this->supply_time = time;
}

void Supplier::supplyItem(){
    #ifdef DEBUG
            std::cout << "supply_thread started. " << std::endl;
    #endif
    std::unique_lock<std::mutex> lock(item->getMutex());
    while(alive){
        #ifdef DEBUG
        std::cout << isAlive() << std::endl;
        #endif
        while(!isNeedSupply())
            item->getConditionalVariable(item_name)->wait(lock);
        sleep(getSupply_time());
        item->increaseQuantity(item_name,supply_nums);
        needSupply = false;
        item->getConditionalVariable(item_name)->notify_all();
        lock.unlock();
    }   
    #ifdef DEBUG
        std::cout << "supply_thread no longer alive. " << std::endl;
    #endif
    return;
}

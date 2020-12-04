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
    supply_thread = new std::thread(Supplier::supplyItem);
    supply_thread->join();
}

Supplier::~Supplier(){
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
    while(alive){
        if(needSupply){
            sleep(supply_time);
            item->increaseQuantity(item_name,supply_nums);
            needSupply = false;
        }
    }   
    #ifdef DEBUG
        std::cout << "supply_thread no longer alive. " << std::endl;
    #endif
}
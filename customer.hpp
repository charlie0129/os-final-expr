#pragma once
#include <thread>
#include "item.hpp"
#include <cmath>
#include <ctime>
#include "checker.hpp"
#include "supplier.hpp"

class Customer
{
    Item* i;
    std::pair<std::string,int> itemname;
    int *stuff;
    Supplier* mySpp;
    int goodNum=0;
    std::thread * customerThread = nullptr;
    Checker* myChecker;
    public:
    Customer(Item& item,std::vector<Supplier*>& spp,Checker* a);
    ~Customer();
    void IN();
};
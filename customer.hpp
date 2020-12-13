#pragma once
#include <thread>
#include "item.hpp"
#include<cmath>
#include <ctime>
#include"checker.hpp"

class Customer
{
    Item* i;
    std::pair<std::string,int> itemname;
    int *stuff;
    Supplier* mySpp;
    int goodNum=rand()%10;
    std::thread * customerThread = nullptr;
    Checker* myChecker;
    public:
    Customer(Item& item,std::vector<Supplier*>& spp,Checker* a);
    ~Customer();
    void IN();
};
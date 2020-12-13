#pragma once
#include "item.hpp"
#include <map>
#include <unistd.h>
#include <string>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <atomic>


class Supplier
{
    private:
        Item *item;
        std::string item_name;
        bool needSupply;
        std::atomic<bool> alive{ false };
        int supply_nums;
        int supply_time;
        std::thread *supply_thread = nullptr;
    public:
        Supplier();
        ~Supplier();
        Supplier(std::string name, Item &i);

        std::thread *getSupply_thread();
        std::string getItem_name();
        bool isNeedSupply();
        bool isAlive();
        void setAlive(bool a);
        void setNeedSupply(bool need);
        int getSupply_nums();
        int getSupply_time();
        void setSupply_nums(int nums);
        void setSupply_time(int time);
        void lunch();
        void supplyItem();
};
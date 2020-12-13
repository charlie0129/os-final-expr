/*
 * File: supplier.cpp
 * Author: WHT (wanghaotian@bupt.edu.cn)
 * -----
 * Copyright (c) 2020 WHT
 */

#include "item.hpp"
#include "supplier.hpp"

Supplier::Supplier()
{
}

Supplier::Supplier(std::string name, Item &i)
{
    this->item = &i;
    this->item_name = name;
    this->supply_nums = 10;
    this->supply_time = 1;
    this->alive = true;
    this->needSupply = false;
    supply_thread = new std::thread(&Supplier::supplyItem, this);
}

Supplier::~Supplier()
{
    setAlive(false);
    item->getConditionalVariable(item_name)->notify_all();
    supply_thread->join();
    delete supply_thread;
    supply_thread = nullptr;
}

std::string Supplier::getItem_name()
{
    return item_name;
}

std::thread *Supplier::getSupply_thread()
{
    return supply_thread;
}

bool Supplier::isNeedSupply()
{
    return needSupply;
}

bool Supplier::isAlive()
{
    return alive;
}

void Supplier::setAlive(bool a)
{
    this->alive = a;
}

void Supplier::setNeedSupply(bool need)
{
    this->needSupply = need;
}

int Supplier::getSupply_nums()
{
    return supply_nums;
}

int Supplier::getSupply_time()
{
    return supply_time;
}

void Supplier::setSupply_nums(int nums)
{
    this->supply_nums = nums;
}

void Supplier::setSupply_time(int time)
{
    this->supply_time = time;
}

void Supplier::supplyItem()
{
    #ifdef DEBUG
    std::cout << "supply_thread started. " << std::endl;
    #endif
    std::unique_lock<std::mutex> lock(*item->getMutex(item_name));
    while (alive)
    {
        #ifdef DEBUG
        std::cout << "[" << item_name << "]" << "supply_thread: " << isAlive() << std::endl;
        #endif
        while (!isNeedSupply())
        {
            #ifdef DEBUG
            std::cout << "[" << item_name << "]" << "supplier is waiting." << std::endl;
            #endif
            item->getConditionalVariable(item_name)->wait(lock);
            if (!alive)
                return;
        }
        //lock.lock();
        sleep(getSupply_time());
        item->increaseQuantity(item_name, supply_nums);
        printf(YELLOW_LEADING_ARROW YELLOW_BOLD_TEXT "补货：" REMOVE_TEXT_ATTR
               "商品：" YELLOW_TEXT "%15s" REMOVE_TEXT_ATTR
               ", 补" YELLOW_TEXT "%2d" REMOVE_TEXT_ATTR
               "个货后, 现有" YELLOW_TEXT "%3d" REMOVE_TEXT_ATTR
               "个\n",
               item_name.c_str(),
               getSupply_nums(),
               item->getQuantity(item_name));
        #ifdef DEBUG
        std::cout << "[" << item_name << "]" << "supply done. now have: " << item->getQuantity(item_name) << std::endl;
        #endif
        needSupply = false;
        item->getConditionalVariable(item_name)->notify_all();
        #ifdef DEBUG
        std::cout << "[" << item_name << "]" << "supplier notify_all." << std::endl;
        #endif
        //lock.unlock();
    }
    #ifdef DEBUG
    std::cout << "supply_thread no longer alive. " << std::endl;
    #endif
    return;
}

#pragma once
#include "customer.hpp"
#include "item.hpp"
#include <map>
#include <unistd.h>
#include <queue>
#include <string>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>

class Checker{
    private:
        int id; // 结账机器人的编号
        Item* item; // 仓库类对象
        std::queue<int> waiting_cus; // 结账的顾客队列
    public:
        Checker();
        Checker(int id, Item& i, std::queue<int>& c);
        int getId();
        void setId(int i);

};
#pragma once
#include "customer.hpp"
#include "item.hpp"
#include "final.hpp"
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
        std::atomic<bool> alive{ false };
        std::mutex check_mtx; // 结账锁
        std::queue< std::pair< std::string, int > > waiting_cus; // 等待结账的物品队列
        std::thread * checker_thread = nullptr;
    public:
        Checker();
        ~Checker();
        Checker(int id, Item& i);
        void addWaitingLine(std::pair<std::string, int> p);
        void doCheckout();
        bool isAlive();
        void setAlive(bool a);
        std::mutex& getCheck_mtx();
        int getId();
        void setId(int i);

};
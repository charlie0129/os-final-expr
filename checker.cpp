/*
 * File: checker.hpp
 * Author: WHT (wanghaotian@bupt.edu.cn)
 * -----
 * Copyright (c) 2020 WHT
 */

#include "checker.hpp"

Checker::Checker()
{

}

Checker::Checker(int id, Item &i)
{
    this->id = id;
    this->item = &i;
    alive = true;
    checker_thread = new std::thread(&Checker::doCheckout, this);
}

Checker::~Checker()
{
    checker_thread->join();
    delete checker_thread;
    checker_thread = nullptr;
}

void Checker::addWaitingLine(std::pair<std::string, int> p)
{
    check_mtx.lock();
    this->waiting_cus.push(p);
    check_mtx.unlock();
}


void Checker::doCheckout()
{
    #ifdef DEBUG
    std::cout << "checker_thread started. " << std::endl;
    #endif
    while (alive)
    {
        #ifdef DEBUG
        std::cout << "checker_thread: " << isAlive() << std::endl;
        #endif
        while (waiting_cus.empty())
        {
            sleep(1);
        }
        check_mtx.lock();
        std::pair<std::string, int> cus = waiting_cus.front();
        int m = item->getPropertyValue(cus.first, "price");
        printf(BLUE_LEADING_ARROW BLUE_BOLD_TEXT "结账：" REMOVE_TEXT_ATTR
               "商品：" YELLOW_TEXT "%15s" REMOVE_TEXT_ATTR
               ", 数量：" YELLOW_TEXT "%3d" REMOVE_TEXT_ATTR
               " , 总价：" YELLOW_TEXT "%3d" REMOVE_TEXT_ATTR "\n",
               cus.first.c_str(),
               cus.second,
               m * cus.second
              );
        waiting_cus.pop();
        check_mtx.unlock();
    }
    #ifdef DEBUG
    std::cout << "checker no longer alive. " << std::endl;
    #endif

}

bool Checker::isAlive()
{
    return alive;
}

void Checker::setAlive(bool a)
{
    this->alive = a;
}

std::mutex &Checker::getCheck_mtx()
{
    return check_mtx;
}

int Checker::getId()
{
    return id;
}

void Checker::setId(int i)
{
    id = i;
}

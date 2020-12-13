/*
 * File: final.cpp
 * Author: Charlie Chiang (charlie_c_0129@outlook.com)
 * -----
 * Copyright (c) 2020 Charlie Chiang
 */

#include "final.hpp"

Item itemRepository{};
std::vector<Supplier *> suppliers;
std::vector<Customer *> customers;

void signal_handler(int sig)
{
    printf(RED_BOLD_TEXT "\n收到 signal: %d, 关闭所有补货与结账线程\n" REMOVE_TEXT_ATTR, sig);
    for (Supplier *i : suppliers)
        delete i;
    for (Customer *i : customers)
        delete i;

    puts(RED_BOLD_TEXT "保存数据库..." REMOVE_TEXT_ATTR);
    std::ofstream ofs{"test.json"};
    itemRepository.writeObject(ofs);
    ofs.close();
    exit(0);
    return;
}

void printUsage()
{
    fprintf(stderr,
            "DESCRIPTION:\n"
            "    A store simulator.\n"
            "SYNOPSIS:\n"
            "    smc_fan_util [--database db_file] [--customer num]\n"
            "OPTIONS:\n"
            "    --database <db_file>: assign database file.\n"
            "    --customer <num>: set the number of customers.\n"\
            "EXAMPLES:\n"
            "    final --database test.json --customer 5\n");
}

int main(int argc, char **argv)
{
    if (argc != 5
        || strcmp(argv[1], "--database")
        || strcmp(argv[3], "--customer"))
    {
        puts(RED_BOLD_TEXT "参数错误！" REMOVE_TEXT_ATTR);
        printUsage();
        return 1;
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    std::ifstream ifs{argv[2]};
    if (ifs.fail())
    {
        puts(RED_BOLD_TEXT "请先创建数据库！" REMOVE_TEXT_ATTR);
        return 1;
    }
    itemRepository.readObject(ifs);
    ifs.close();

    Checker checker{1, itemRepository};

    for (size_t i = 0; i < itemRepository.getItemNameList().size(); i++)
    {
        Supplier *tmp = new Supplier{(itemRepository.getItemNameList())[i], itemRepository};
        suppliers.push_back(tmp);
    }

    for (size_t i = 0; i < atoi(argv[4]); i++)
    {
        Customer *tmp = new Customer{itemRepository, suppliers, &checker};
        customers.push_back(tmp);
        sleep(1);
    }

    sleep(INT_MAX);
    return 0;
}

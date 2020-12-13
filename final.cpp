#include "final.hpp"

Item itemRepository{};
std::vector<Supplier *> suppliers;
std::vector<Customer *> customers;

void signal_handler(int sig)
{
    printf(RED_BOLD_TEXT "收到 signal: %d, 关闭所有补货与结账线程\n" REMOVE_TEXT_ATTR, sig);
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

int main(int argc, char **argv)
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    std::ifstream ifs{"test.json"};
    itemRepository.readObject(ifs);
    ifs.close();

    Checker checker{1, itemRepository};

    for (size_t i = 0; i < itemRepository.getItemNameList().size(); i++)
    {
        Supplier *tmp = new Supplier{(itemRepository.getItemNameList())[i], itemRepository};
        suppliers.push_back(tmp);
    }

    for (size_t i = 0; i < 5; i++)
    {
        Customer *tmp = new Customer{itemRepository, suppliers, &checker};
        customers.push_back(tmp);
        sleep(1);
    }

    sleep(INT_MAX);
    return 0;
}

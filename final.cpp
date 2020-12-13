#include "final.hpp"

Item itemRepository{};
std::vector<Supplier*> suppliers;
std::vector<Customer*> customers;

void test()
{
    // -------- Code for Testing Purposes ---------
    std::cout << BLUE_BOLD_TEXT "Created an item list.\n" REMOVE_TEXT_ATTR;
    Item i{};
    // Add some properties to "i"
    i.addItem("milk");
    i.addProperty("milk", "quantity");
    i.addProperty("milk", "priority");
    i.changePropertyValue("milk", "quantity", 10);
    i.changePropertyValue("milk", "priority", 10);
    i.decreaseQuantity("milk", -2);

    i.addItem("pancake");
    i.addProperty("pancake", "quantity");
    i.addProperty("pancake", "priority");
    i.changePropertyValue("pancake", "quantity", 10);
    i.changePropertyValue("pancake", "priority", 10345);
    i.increaseQuantity("pancake");
    // It will have the structure below:
    // -----------------
    // {
    //   "milk": {
    //     "priority": 10,
    //     "quantity": 8
    //   },
    //   "pancake": {
    //     "priority": 10345,
    //     "quantity": 11
    //   }
    // }
    // -----------------

    // Serialize to stdout
    std::cout << BLUE_BOLD_TEXT "Serialize to json-like:\n" REMOVE_TEXT_ATTR;
    i.writeObject(std::cout);
    putchar('\n');
    // Change an unknown property
    std::cout << BLUE_BOLD_TEXT "Exception test:\n" REMOVE_TEXT_ATTR;
    try
    {
        i.increaseQuantity("sd");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    // Serialize to file
    std::ofstream ofs{"test.json"};
    i.writeObject(ofs);
    ofs.close();

    // Deserialize from file, to "ii"
    std::ifstream ifs{"test.json"};
    Item ii{ifs};
    ifs.close();
    // Serialize to stdout
    std::cout << BLUE_BOLD_TEXT "Deserialize from file:\n" REMOVE_TEXT_ATTR;
    ii.writeObject(std::cout);
    putchar('\n');

    std::cout << BLUE_BOLD_TEXT "Get quantity of milk: " REMOVE_TEXT_ATTR << ii.getQuantity("milk") << "\n";
    std::cout << BLUE_BOLD_TEXT "Get quantity of pancake: " REMOVE_TEXT_ATTR << ii.getQuantity("pancake") << "\n";
    // -------- Code for Testing Purposes ---------
}


void supplierTest()
{
    // Supplier sup{"cake",itemRepository};
    // sleep(2);
    // sup.setAlive(false);
    // sleep(2);
}

void testcreat()
{
    std::thread t1(test);
    std::thread t2(test);
    t1.join();
    t2.join();
}

void signal_handler(int signal)
{
    for (Supplier* i : suppliers)
        i->setAlive(false);
    for (Supplier* i : suppliers)
        delete i;
    for (Customer* i : customers)
        delete i;
    puts("stopped threads");

    std::ofstream ofs{"test.json"};
    itemRepository.writeObject(ofs);
    ofs.close();

    puts("saved file");

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
        Supplier* tmp=new Supplier{(itemRepository.getItemNameList())[i],itemRepository};
        suppliers.push_back(tmp);
    }

<<<<<<< HEAD
    for (size_t i = 0; i < 5; i++)
=======
    for (size_t i = 0; i < 6; i++)
>>>>>>> refs/remotes/origin/CVandMutex
    {
        Customer* tmp=new Customer{itemRepository, suppliers, &checker};
        customers.push_back(tmp);
        sleep(1);
    }

    sleep(INT_MAX);
    return 0;
}

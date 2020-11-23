#include "final.hpp"


int main(int argc, char **argv)
{
    // -------- Code for Testing Purposes ---------
    Item i{};
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

    std::cout << BLUE_BOLD_TEXT "Serialize to json-like:\n" REMOVE_TEXT_ATTR;
    i.writeObject(std::cout);
    putchar('\n');

    std::cout << BLUE_BOLD_TEXT "Exception test:\n" REMOVE_TEXT_ATTR;
    try
    {
        i.increaseQuantity("sd");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::ofstream ofs{"test.txt"};
    i.writeObject(ofs);
    ofs.close();

    std::ifstream ifs{"test.txt"};
    Item ii{ifs};
    ifs.close();

    std::cout << BLUE_BOLD_TEXT "Deserialize from file:\n" REMOVE_TEXT_ATTR;
    ii.writeObject(std::cout);
    putchar('\n');

    std::cout << BLUE_BOLD_TEXT "Quantities:\n" REMOVE_TEXT_ATTR;
    std::cout << ii.getQuantity("milk") << " " << ii.getQuantity("pancake") << std::endl;
    // -------- Code for Testing Purposes ---------
    return 0;
}

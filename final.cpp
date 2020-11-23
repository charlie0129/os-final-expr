#include "final.hpp"


int main(int argc, char **argv)
{
    // -------- Code for Testing Purposes ---------
    Item i{};
    i.addItem("milk");
    i.addProperty("milk", "quantity");
    i.changePropertyValue("milk", "quantity", 10);
    i.decreaseQuantity("milk", -2);

    i.addItem("pancake");
    i.addProperty("pancake", "quantity");
    i.changePropertyValue("pancake", "quantity", 10);
    i.increaseQuantity("pancake");

    try
    {
        i.increaseQuantity("sd");
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    std::cout << i.getQuantity("milk") << " " << i.getQuantity("pancake") << std::endl;
    // -------- Code for Testing Purposes ---------
    return 0;
}

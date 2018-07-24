#include "interface.h"
#include "product_stack.h"
#include "feature_queue.h"

struct shopping_intro : public menu_item
{
    const char* option() const
    {
        return 
        "============================================================="
        "\n"
        "\n"
        "\n"
        "\n"
        "\n          Now, lets evaluate some computers"
        "\n        and compare them against your wishlist!"
        "\n"
        "\n"
        "\n"
        "\n"
        "\n"
        "=============================================================\n";
    }

    void action()
    {
        Interface::pause_console();
        Interface::clear_screen();
        return;
    }
};

struct evaluate_product : public menu_item
{

    Feature_Queue* queue;
    Product_Stack* stack;

    Product product;

    evaluate_product(Feature_Queue* queue, Product_Stack* stack) 
        : queue(queue), stack(stack) {}
    
    const char* option() const
    {
        return "Evaluate a Computer";

    }

    void action()
    {
        
        return;
    }
};

struct exit_shopping_menu : public exit_item
{
    exit_shopping_menu() : exit_item() {}

    bool operator()() { return exit; }

    const char* option() const { return "Exit"; }

    void action()
    {
        exit = true;
    }
};


/*
File: wishlist_menu.cpp

Description: wishlist_menu holds all the menu_item concrete implementations as 
             well as the model for the Interface class

Author: Alexander DuPree

Class: CS163

Assignment: program1

Date: 07/11/2018
*/


#include "interface.h"
#include "feature_queue.h"

struct intro : public menu_item
{
    const char* option() const
    {
        return 
        "============================================================="
        "\n"
        "\n"
        "\n"
        "\n"
        "\n                         Program 2"
        "\n"
        "\n"
        "\n                 Author: Alexander DuPree"
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

struct wishlist_intro : public menu_item
{
    const char* option() const
    {
        return 
        "============================================================="
        "\n"
        "\n"
        "\n"
        "\n"
        "\n          First lets build your dream computer!"
        "\n     Add any and all desired features to the wishlist"
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

struct queue_features : public menu_item
{
    Feature_Queue* queue;

    queue_features(Feature_Queue* queue) : queue(queue) {}

    const char* option() const
    {
        return "Queue features";
    }

    void action()
    {
        SString feature;
        do
        {
            Interface::get_input(feature, "\nEnter the feature to add your wishlist: ");

            queue->enqueue(feature); 
            std::cout << "\n\t'" << feature << "' feature added!" << std::endl;

        } while (Interface::repeat_loop("\nEnter another Feature? Y/N"));

        return;
    }
};


struct display_features : public menu_item
{
    Feature_Queue* queue;

    display_features(Feature_Queue* queue) : queue(queue) {}

    const char* option() const
    {
        return "Display Wishlist";
    }

    void action()
    {
        queue->display();
        Interface::pause_console();
    }

};

struct clear_wishlist : public menu_item
{
    Feature_Queue* queue;

    clear_wishlist(Feature_Queue* queue) : queue(queue) {}

    const char* option() const
    {
        return "Clear Wishlist";
    }

    void action()
    {
        if (queue->clear_queue())
        {
            std::cout << "\nWishlist is now empty!";
        }
        else
        {
            std::cout << "\nYour wishlist is already empty.";
        }

        Interface::pause_console();
    }

};

struct exit_wishlist_menu : public exit_item
{
    Feature_Queue* queue;

    exit_wishlist_menu(Feature_Queue* queue) : exit_item(), queue(queue) {}

    bool operator()() { return exit; }

    const char* option() const
    {
        return "Finish Building Wishlist";
    }

    void action()
    {
        if (queue->empty())
        {
            std::cout << "\nYour wishlist is empty! Please add some features "
                         "first.\n";
            Interface::pause_console();
        }
        else
        {
            exit = true;
        }
    }

};

class wishlist_menu_model : public basic_model
{
  public:

    wishlist_menu_model() 
        : basic_model(), queue(Feature_Queue()) {}

    ~wishlist_menu_model()
    {
        clear_menu();
    }

    const Feature_Queue* get_wishlist() const
    {
        return &queue;
    }

  private:

    unsigned size() const
    {
        return SIZE;
    }
    
    void build()
    {
        intro it;
        std::cout << it.option();
        it.action();

        wishlist_intro wi;
        std::cout << wi.option();
        wi.action();

        if (_options)
        {
            clear_menu();
        }

        _options = new menu_item*[SIZE];
        _exit = new exit_wishlist_menu(&queue);

        _options[0] = new queue_features(&queue);
        _options[1] = new display_features(&queue);
        _options[2] = new clear_wishlist(&queue);
        _options[3] = _exit;

        return;
    }

    static const int SIZE = 4;

    Feature_Queue queue;
};


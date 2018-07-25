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

class evaluate_product : public menu_item
{
  public:

    evaluate_product(Product_Stack* stack, const Feature_Queue* queue) 
        : stack(stack), queue(queue){}
    
    const char* option() const
    {
        return "Evaluate a Computer";

    }

    void action()
    {
        
        build_product();

        evaluate_features();

        if (product.matches() > 0)
        {
            std::cout << "\n\t'" << product.model() <<"' matched " 
                      << product.matches() << " features. \n\tWe saved it for later"
                      << " evaluation.\n";
            stack->push(product);
        }
        else
        {
            std::cout << "\n\t'" << product.model() << "' didn't match any "
                      << "features on your wishlist. It was not saved.";
        }

        // The product is reused from iteration to iteration and needs to be 
        // cleaned
        product.clear_matches();
        Interface::pause_console();
      
        return;
    }

  private:

    void build_product()
    {
        SString store;
        SString model;
        int price(-1);

        Interface::get_input(store, "\n\tEnter the name of the store: ");
        Interface::get_input(model, "\tEnter the computer's model name: ");
        while(price <= 0)
        {
            price = Interface::get_input<int>("\tEnter the price of the computer: ");
            if(price <= 0)
            {
                Interface::display_error("\nThat's not a valid price.");
            }
        }

        product.store(store).model(model).price(price);
        return;
    }

    void evaluate_features()
    {
        Feature_Queue::const_iterator it = queue->begin();
        do
        {
            std::cout << "\nDoes the computer have: '" << *it << "' (Y/N)";
            if (std::tolower(Interface::get_input<char>(": ")) == 'y')
            {
                std::cout << "\tGreat! '" << *it << "' was matched!\n";
                product.add_match(*it);
            }

            ++it;

        } while (it != queue->end());
        return;
    }

    Product_Stack* stack;
    const Feature_Queue* queue;

    Product product;
};

class view_saved_computers : public menu_item
{
  public:

    view_saved_computers(Product_Stack* stack) 
        : stack(stack) {}

    const char* option() const { return "View Saved Computers"; }

    void action()
    {
        stack->display();
        Interface::pause_console();
    }

  private:

    Product_Stack* stack;

};

class exit_shopping_menu : public exit_item
{
  public:

    exit_shopping_menu(Product_Stack* stack) 
        : exit_item(), stack(stack) {}

    bool operator()() { return exit; }

    const char* option() const { return "Finish Shopping"; }

    void action()
    {
        if (stack->empty())
        {
            std::cout << "\nYou haven't found any matching computers. Are you "
                         "sure you want to finish? (Y/N)";
        }
        else
        {
            std::cout << "\nAre you sure you're done shopping? (Y/N)";
        }

        if (std::tolower(Interface::get_input<char>(": "))== 'y')
        {
            exit = true;

            std::cout << "\n\tGreat! Heres all the computers that matched some "
                         "or all of the features on your wishlist!";

            stack->display();

            Interface::pause_console();

            std::cout << "\n\tHave a Great Day!" << std::endl;
        }
    }

  private:

    Product_Stack* stack;
};

class shopping_menu_model : public basic_model
{
  public:

    shopping_menu_model(const Feature_Queue* queue) 
        : basic_model(), stack(Product_Stack()), queue(queue) {}

    ~shopping_menu_model()
    {
        clear_menu();
    }

  private:

    unsigned size() const
    {
        return SIZE;
    }

    void build()
    {

        shopping_intro it;
        std::cout << it.option();
        it.action();

        if(_options)
        {
            clear_menu();
        }

        _options = new menu_item*[SIZE];
        _exit = new exit_shopping_menu(&stack);

        _options[0] = new evaluate_product(&stack, queue);
        _options[1] = new view_saved_computers(&stack);
        _options[2] = _exit;
    }

    static const int SIZE = 3;

    Product_Stack stack;
    const Feature_Queue* queue;
};


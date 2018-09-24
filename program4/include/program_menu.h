/*
File: program_menu.h

Brief: This file outlines the options and actions for each menu item as well as
       defines the model for the interface class

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 08/09/2018
*/

#include "csv.h"
#include "interface.h"
#include "item_table.h"

class add_item : public menu_item
{
  public:

    add_item(Item_Table* table)
        : table(table) {}

    const char* option() const
    {
        return "Add Item";
    }

    void action()
    {
        SString attributes[4];

        get_attributes(attributes);

        table->add(Item(attributes));

        std::cout << "\n\t'" << attributes[0] << "' was added!\n";

        Interface::pause_console();
        return;
    }

    void get_attributes(SString* attributes)
    {
        Interface::get_input(attributes[0], "\nEnter the item name:  ");
        Interface::get_input(attributes[1], "\nEnter item description:  ");
        Interface::get_input(attributes[2], "\nEnter the item's color:  ");
        Interface::get_input(attributes[3], "\nEnter the item's website:  ");
        return;
    }

  private:

    Item_Table* table;

};

class find_item : public menu_item
{
  public:

    find_item(Item_Table* table)
        : table(table) {}

    const char* option() const
    {
        return "Find Item";
    }

    void action() 
    {
        SString key = Interface::get_input<SString>("Enter items name:  ");

        Item item = table->retrieve(key);

        if(item.name() == key)
        {
            std::cout << "\n\tItem found!\n\n" << item;
        }
        else
        {
            std::cout << "\n\t'" << key << "' was not found\n";
        }

        Interface::pause_console();
    }

  private:

    Item_Table* table;
};

class remove_item : public menu_item
{
  public:

    remove_item(Item_Table* table)
        : table(table) {}

    const char* option() const
    {
        return "Remove Item";
    }

    void action()
    {
        SString key = Interface::get_input<SString>("Enter items name:  ");

        if(table->remove(key))
        {
            std::cout << "\n\t'" << key << "' was removed!";
        }
        else
        {
            std::cout << "\n\t'" << key << "' was not found";
        }
        Interface::pause_console();
    }

  private:

    Item_Table* table;
};

class clear_table : public menu_item
{
  public:

    clear_table(Item_Table* table)
        : table(table) {}

    const char* option() const
    {
        return "Clear Table";
    }
    
    void action()
    {
        table->clear();

        std::cout << "\n\tTable Cleared!";
        Interface::pause_console();
    }

  private:

    Item_Table* table;

};

class display_all : public menu_item
{
  public:

    display_all(Item_Table* table)
        : table(table) {}

    const char* option() const
    {
        return "Display All Items";
    }

    void action()
    {
        unsigned counter = 0;
        Item_Table::const_iterator it;
        for(it = table->begin(); it != table->end(); ++it)
        {
            std::cout << *it << std::endl;

            if (++counter % 5 == 0)
            {
                std::cout << '\n' << table->size() - counter << " Items remaining.";
                if(!Interface::repeat_loop(" Continue? Y/N:  "))
                {
                    return;
                }
            }
        }
        return;
    }

  private:

    Item_Table* table;
};

class display_items_by_website : public menu_item
{
  public:

    display_items_by_website(Item_Table* table)
        : table(table) {}

    const char* option() const
    {
        return "Display by Website";
    }

    void action()
    {
        SString website;
        Interface::get_input(website, "Enter Website's domain name:  ");

        std::cout << "\nDisplaying All Items related to '" << website << "'\n\n";

        Item_Table::const_iterator it;
        for(it = table->begin(); it != table->end(); ++it)
        {
            if(it->website() == website)
            {
                std::cout << *it << std::endl;
            }
        }

        Interface::pause_console();
        return;
    }

  private:

    Item_Table* table;

};

class display_diagnostics : public menu_item
{
  public:

    display_diagnostics(Item_Table* table)
        : table(table) {}

    const char* option() const
    {
        return "Diagnostics";
    }

    void action()
    {
        table->display_diagnostics();
        Interface::pause_console();
    }

  private:

    Item_Table* table;

};

class program_menu_model : public basic_model
{
  public:

    program_menu_model()
        : basic_model(), table() {}

    ~program_menu_model()
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
        if(_options)
        {
            clear_menu();
        }

        build_table();

        _options = new menu_item*[SIZE];
        _exit = new default_exit;

        _options[0] = new add_item(&table);
        _options[1] = new find_item(&table);
        _options[2] = new remove_item(&table);
        _options[3] = new display_all(&table);
        _options[4] = new display_items_by_website(&table);
        _options[5] = new clear_table(&table);
        _options[6] = new display_diagnostics(&table);
        _options[7] = _exit;
    }

    void build_table()
    {
        CSV::Reader reader("Shopping.txt", '|');

        SString attributes[reader.columns()];

        Item* items = new Item[reader.rows()];

        unsigned i = 0;
        while(i < reader.rows() && reader.readline(attributes))
        {
            items[i++] = Item(attributes);
        }

        std::sort(items, items + reader.rows());

        binary_insert(items, 0, i - 1);

        delete [] items;

        return;
    }

    void binary_insert(Item* items, int min, int max)
    {
        if(min >= max)
        {
            if(min == max)
            {
                table.add(items[min]);
            }
            return;
        }

        int mid = min + (max - min) / 2;

        table.add(items[mid]);

        binary_insert(items, min, mid - 1);
        binary_insert(items, mid + 1, max);
    }

    static const int SIZE = 8;

    Item_Table table;
};


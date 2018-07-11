/*
File: database_model.h

Description: database_model is the menu_item factory for the Interface class.
             The interface does not have knowledge of what menu options it will
             have or the implementation of those menu options. 

             The model is used to connect all defined menu_items together and
             construct them with the required dependencies. When the interface
             builds it passes in a menu_item pointer to the model and the model 
             proceeds to build the correct menu_items onto the array.

             The database_model is also the manager for the Database object 
             to be used in the application. The database_model connects each 
             menu option to this database for manipulation.

Author: Alexander DuPree

Date: 07/11/2018
*/

#ifndef DATABASE_MODEL
#define DATABASE_MODEL

#include "interface.h"
#include "menu_options.h"

class database_model : public menu_model
{
  public:

    // virtual method, required to build the interface
    void build(menu_item**& menu);
    
    // Builds the database with some predifined categories
    void build_database();

    // Returns the number of menu options the model builds
    unsigned size() const;

  private:

    static const unsigned SIZE = 6;

    Database database; // Primary database for the application

};

#endif // DATABASE_MODEL

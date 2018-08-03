/*
File: 

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/24/2018
*/

#include "csv.h"
#include "item.h"
#include "hash_table.h"

// String Specialization of the hash function
template <>
struct hash<SString>
{
    unsigned long operator()(const char* key) const
    {
        return djb2(key);
    }

    unsigned long djb2(const char* key) const
    {
        unsigned long hash = 5381;

        int val;

        while((val = *key++))
        {
            hash = ((hash << 5) + hash) + val;
        }
        return hash;
    }

    unsigned long danny_hash(const char* key) const
    {
        int index = 11;

        for (int i = 0; key[i] != '\0'; ++i)
        {
            if (i % 2 == 0)
            {
                index += key[i] * 3;
            }
            else
            {
                index *= key[i];
            }
            index *= 3;
        }

        index *= 199;

        return index;
    }
    
    unsigned long my_hash(const char * key) const
    {
        unsigned long hash = 7109;
        for(unsigned i = 0; i < std::strlen(key); ++i)
        {
            hash *= hash ^ (*(const unsigned long*)key + i) << 2;
        }
        return hash *= 7109;
    }
};

void build_hash_table(hash_table<SString, Item>& table);

int main()
{
    hash_table<SString, Item> table(1811);

    build_hash_table(table);

    std::cout << "Buckets: " << table.buckets() << '\n';
    std::cout << "Buckets in Use:" << table.buckets_in_use() << '\n';
    std::cout << "Load Factor: " << table.load_factor() << '\n';
    std::cout << "Spread: " << table.spread() << '\n';
    std::cout << "largest Buckets: " << table.largest_bucket() << '\n';

    std::cout << table.find("Vitara") << std::endl;
    return 0;
}

void build_hash_table(hash_table<SString, Item>& table)
{
    CSV::Reader reader("Shopping.csv", '|');

    SString attributes[reader.columns()];

    while(reader.readline(attributes))
    {
        table.insert(attributes[0], Item(attributes));
    }

    return;
}


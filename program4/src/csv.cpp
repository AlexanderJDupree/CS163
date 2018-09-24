/*
File: csv_reader.cpp

Brief: Implementation file for the CSV Reader object

Author: Alexander DuPree

Class: CS163

Assignment: program 4

Date: 08/03/2018
*/

#include "csv.h"

namespace CSV
{

Reader::Reader(const char* infile, char delimiter, char quotechar)
    : _fin(infile), _delim(delimiter), _quote(quotechar)
{
   throw_if_failed(); 

   _rows = determine_rows();
   _cols = determine_columns();
}

Reader::~Reader()
{
    close_file();
}

bool Reader::eof() const
{
    return _fin.eof();
}

Reader& Reader::close_file()
{
    if(_fin.is_open())
    {
        _fin.close();
        reset_columns_rows();
    }
    return *this;
}

Reader& Reader::open(const char* infile)
{
    close_file();

    _fin.open(infile);

    throw_if_failed();

    determine_rows();
    determine_columns();

    return *this;
}

Reader& Reader::set_columns(unsigned columns)
{
    _cols = columns;

    return *this;
}

unsigned Reader::determine_columns()
{
    char temp = '\0';
    while(_fin.get(temp) && temp != '\n' && temp != _delim);

    if (temp == _delim)
    {
        return 1 + determine_columns();
    }

    // Return file to beginning
    _fin.seekg(0, std::ios::beg);

    return 1;
}

Reader& Reader::set_rows(unsigned rows)
{
    if(rows <= 0)
    {
        _rows = determine_rows();
    }
    else
    {
        _rows = rows;
    }

    return *this;
}

unsigned Reader::determine_rows()
{
    // Skip line
    _fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if(_fin.eof())
    {
        // Return file to beginning
        _fin.seekg(0, std::ios::beg);
        return 0;
    }

    return 1 + determine_rows();
}

unsigned Reader::columns() const
{
    return _cols;
}

unsigned Reader::rows() const
{
    return _rows;
}

void Reader::seek(unsigned n)
{
    if (n >= _rows)
    {
        _fin.seekg(0, std::ios::end);
    }

    while (!_fin.eof() && n-- != 0)
    {
        _fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return;
}

void Reader::throw_if_failed()
{
    if(_fin.fail())
    {
        throw std::ios_base::failure("Error, csv reader failed to open file");
    }

    return;
}

void Reader::reset_columns_rows()
{
    _cols = 0;
    _rows = 0;
    return;
}

void Reader::read_next_attribute(char* buffer, unsigned n)
{
    unsigned i = 0;
    char temp = '\0';
    while(i < n-2 && _fin.get(temp) && temp != '\n' && temp != _delim)
    {
        buffer[i++] = temp;
    }

    buffer[i] = '\0';

    // Buffer is full but the delimiter was not reached
    if(temp != _delim && temp != '\n')
    {
        // Scan till the next delimiter
        while(_fin.get(temp) && temp != _delim && temp != '\n');
    }

    return;
}

}

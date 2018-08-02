/*
File: csv_reader.h

Brief:

Author: Alexander DuPree

Class: CS163

Assignment: program2

Date: 07/24/2018
*/

#ifndef CSV_H
#define CSV_H

#include <fstream>
#include <limits>

namespace CSV
{

class Reader
{
  public:

    typedef Reader self_type;

    Reader(const char* infile, char delimiter=',', char quotechar='"');

    ~Reader();

    // Returns true if reader reached the end of the file
    bool eof() const;

    // Closes the associated file
    self_type& close_file();

    // Closes the current file, opens the new file
    self_type& open(const char* infile);

    self_type& set_columns(unsigned columns);
    self_type& set_rows(unsigned rows);
    
    unsigned columns() const;
    unsigned rows() const;

    void seek(unsigned n);

    // Reads a lines attributes into a container
    template <class Container>
    bool readline(Container container, unsigned buffersize=100);

  private:

    std::ifstream _fin; // File in stream
    char _delim; // Delimiter character
    char _quote; // Quote character

    unsigned _cols; // Number of columns in the file
    unsigned _rows; // Number of rows in the file

    void throw_if_failed();
    void reset_columns_rows();
    void read_next_attribute(char* buffer, unsigned n);
    unsigned determine_columns();
    unsigned determine_rows();
};

template <class Container>
bool Reader::readline(Container container, unsigned buffersize)
{
    if (_fin.eof())
    {
        return false;
    }

    char* buffer = new char[buffersize];

    for(unsigned i = 0; i < _cols; ++i)
    {
        read_next_attribute(buffer, buffersize);
        container[i] = buffer;
    }

    delete [] buffer;

    return true;
}

}

#endif //CSV_H

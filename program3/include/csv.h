/*
File: csv_reader.h

Brief: CSV Reader is a rework of a side project I have been working on. The CSV 
       Reader's purpose is to parse and compose entries from a delimited file
       into an array. This current version of the CSV Reader is in it's early 
       stages of implementation and contains minimal functionality.

Author: Alexander DuPree

Class: CS163

Assignment: program 3

Date: 08/03/2018
*/

#ifndef CSV_H
#define CSV_H

#include <fstream> // ifstream
#include <limits> // streamsize limit

namespace CSV
{

class Reader
{
  public:

    typedef Reader self_type;

    // Open's the specified file and constructs the Reader object
    Reader(const char* infile, char delimiter=',', char quotechar='"');

    ~Reader();

    // Returns true if reader reached the end of the file
    bool eof() const;

    // Closes the associated file
    self_type& close_file();

    // Closes the current file, opens the new file
    self_type& open(const char* infile);

    // Set the number of columns to read. Columns should <= the actual number of
    // columns in the file
    self_type& set_columns(unsigned columns);

    // Set the number of rows to read. Rows should <= the actual number of rows
    // in the file
    self_type& set_rows(unsigned rows);
    
    // Returns the number of columns in the file
    unsigned columns() const;
    // Returns the number of rows in the file
    unsigned rows() const;

    // Moves the Reader to the specified row
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

    // Throws if file failed to open
    void throw_if_failed();

    // Resets the internal column and row count to 0
    void reset_columns_rows();

    // Reads the next attribute onto a buffer
    void read_next_attribute(char* buffer, unsigned n);

    // Scans the file header to determine the number of columns
    unsigned determine_columns();

    // Reads the whole file to determine the number of rows
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

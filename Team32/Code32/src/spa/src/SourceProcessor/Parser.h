#ifndef GUARD_PARSER_H
#define GUARD_PARSER_H


#include <string>

class Parser{
public:
    virtual int parse(std::string& source_program);
};

#endif
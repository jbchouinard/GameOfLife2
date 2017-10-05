#ifndef GAMEOFLIFE_RLEPARSER_H
#define GAMEOFLIFE_RLEPARSER_H

#include "CellAutomaton.h"
#include <fstream>

class parser_error: public std::runtime_error
{
public:
    explicit parser_error(const string& message) throw() : std::runtime_error(message)
    {}
};

class RLEParser
{
public:
    explicit RLEParser(istream*);
    virtual ~RLEParser();
    CellAutomaton parse();
protected:
    istream* is;
private:
    CellAutomaton* ca;
    int width;
    int height;
    int x;
    int y;
    char peek;
    void read();
    void read(char);
    int read_num();
    bool is_whitespace();
    void whitespace();
    void comments();
    void size_x();
    void size_y();
    string rule_def();
    void cell_run();
    void cell_row();
};

class RLEStringParser :public RLEParser
{
public:
    explicit RLEStringParser(const string&);
    ~RLEStringParser() override;
};

class RLEFileParser :public RLEParser
{
public:
    explicit RLEFileParser(const string&);
    ~RLEFileParser() override;
};

#endif //GAMEOFLIFE_RLEPARSER_H

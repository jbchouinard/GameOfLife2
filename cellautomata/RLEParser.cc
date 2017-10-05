#include "RLEParser.h"
#include <sstream>
#include <fstream>

RLEParser::RLEParser(istream* is)
    :width{0}, height{0}, x{0}, y{0}, ca{nullptr}, is{is}
{}

RLEParser::~RLEParser() {
    delete ca;
}

RLEStringParser::RLEStringParser(const string& in_str) :RLEParser((istream*) nullptr)
{
    auto strm = new stringstream;
    (*strm) << in_str;
    is = strm;
}

RLEStringParser::~RLEStringParser() { delete is; }

RLEFileParser::RLEFileParser(const string& in_fname) :RLEParser(new ifstream(in_fname))
{}

RLEFileParser::~RLEFileParser(){ delete is; }

CellAutomaton RLEParser::parse()
{
    read();
    whitespace();
    comments();
    whitespace();
    size_x();
    whitespace();
    read(',');
    whitespace();
    size_y();
    whitespace();
    if (peek == ',') {
        read();
        whitespace();
        string rule_str = rule_def();
        whitespace();
        ca = new CellAutomaton(width, height, rule_str);
    }
    else {
        ca = new CellAutomaton(width, height);
    }
    while (peek != '!') { cell_row(); }
    return *ca;
}

void RLEParser::read() {
    int c = is->get();
    if (c == EOF) { throw parser_error{"Unexpected end of file."}; }
    peek = (char) c;
}

void RLEParser::read(char c) {
    if (peek != c) {
        ostringstream msg;
        msg << "Expected character '" << c << "', got '" << peek << "'.";
        throw parser_error{msg.str()};
    }
    read();
}

int RLEParser::read_num()
{
    int n = 0;
    while (peek >= '0' && peek <= '9') {
        n *= 10;
        n += peek - '0';
        read();
    }
    return n;
}

bool RLEParser::is_whitespace() { return (peek == '\n' || peek == '\t' || peek == '\r' || peek == ' '); }

void RLEParser::whitespace() { while (is_whitespace()) { read(); } }

void RLEParser::comments()
{
    while (peek == '#') {
        while (peek != '\n') { read(); }
        whitespace();
    }
}

void RLEParser::size_x()
{
    read('x');
    whitespace();
    read('=');
    whitespace();
    width = read_num();
}

void RLEParser::size_y()
{
    read('y');
    whitespace();
    read('=');
    whitespace();
    height = read_num();
}

string RLEParser::rule_def()
{
    read('r'); read('u'); read('l'); read('e');
    whitespace();
    read('=');
    whitespace();

    ostringstream rulestrm;
    while(!is_whitespace()) {
        rulestrm << peek;
        read();
    }
    return rulestrm.str();
}

void RLEParser::cell_row()
{
    while (peek != '$' && peek != '!') {
        cell_run();
    }
    // Leave '!' (rle end of file symbol) to be handled by caller
    if (peek != '!') { read(); }
    // Jump to next row.
    y++; x = 0;
}

void RLEParser::cell_run()
{
    int n = read_num();
    // There is no number, so only one occurrence.
    if (n == 0) { n = 1; }
    if (peek != 'b') {
        while (n) {
            ca->cell(x, y, State::alive);
            x++; n--;
        }
    }
    else { x += n; }
    read();
}

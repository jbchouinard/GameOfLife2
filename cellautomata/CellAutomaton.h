#ifndef GAMEOFLIFE_CELLAUTOMATON_H
#define GAMEOFLIFE_CELLAUTOMATON_H
#include "Grid.h"
#include <string>
#include <functional>

using namespace std;

enum class State {dead, alive};

class CellAutomaton;

typedef function<State(const CellAutomaton&, int, int)> Rule;

class CellAutomaton
{
public:
    CellAutomaton(int, int);
    CellAutomaton(int, int, Rule);
    CellAutomaton(int, int, const string&);
    explicit CellAutomaton(const Grid<State>&);
    CellAutomaton(const Grid<State>&, Rule);
    CellAutomaton(const Grid<State>&, const string&);
    CellAutomaton(const CellAutomaton&);
    ~CellAutomaton();
    CellAutomaton& operator=(const CellAutomaton&);
    State cell(int, int) const;
    void cell(int, int, State);
    int height() const;
    int width() const;
    void tick();
private:
    Grid<State>* grid;
    Rule rule;
};

State get_random_state(int);
void initialize_random(CellAutomaton&, int);
void print(const CellAutomaton&);

#endif //GAMEOFLIFE_CELLAUTOMATON_H

#include "CellAutomaton.h"
#include "LifeLikeRule.h"
#include "WrappingGrid.tcc"
#include <iostream>

using namespace std;

CellAutomaton::CellAutomaton(int x, int y)
    :rule{LifeLikeRule()}, grid{new WrappingGrid<State>(y, x, State::dead)}
{}

CellAutomaton::CellAutomaton(int x, int y, Rule rule)
    :rule{move(rule)}, grid{new WrappingGrid<State>(y, x, State::dead)}
{}

CellAutomaton::CellAutomaton(int x, int y, const string& rule_str)
        :rule{LifeLikeRule(rule_str)}, grid{new WrappingGrid<State>(y, x, State::dead)}
{}

CellAutomaton::CellAutomaton(const Grid<State>& grid)
    :rule{LifeLikeRule()}, grid{grid.copy()}
{}

CellAutomaton::CellAutomaton(const Grid<State>& grid, Rule rule)
        :rule{move(rule)}, grid{grid.copy()}
{}

CellAutomaton::CellAutomaton(const Grid<State>& grid, const string& rule_str)
        :rule{LifeLikeRule(rule_str)}, grid{grid.copy()}
{}

CellAutomaton::CellAutomaton(const CellAutomaton& ca)
    :rule{ca.rule}, grid{ca.grid->copy()}
{}

CellAutomaton::~CellAutomaton() { delete grid; }

CellAutomaton& CellAutomaton::operator=(const CellAutomaton& ca)
{
    if (&ca != this) {
        this->rule = ca.rule;
        delete grid;
        this->grid = ca.grid->copy();
    }
    return *this;
}

int CellAutomaton::height() const { return grid->height(); }

int CellAutomaton::width() const { return grid->width(); }

State CellAutomaton::cell(int x, int y) const { return (*grid)[y][x]; }

void CellAutomaton::cell(int x, int y, State val) { (*grid)[y][x] = val; }

void CellAutomaton::tick()
{
    auto new_grid = grid->copy();
    for (auto i=0; i < width(); i++) {
        for (auto j=0; j < height(); j++) {
            (*new_grid)[j][i] = rule(*this, i, j);
        }
    }
    delete grid;
    grid = new_grid;
}

State get_random_state(int p_alive) { return rand() % 100 < p_alive ? State::alive: State::dead; }

void initialize_random(CellAutomaton& ca, int p_alive)
{
    for (auto i = 0; i < ca.width(); i++) {
        for (auto j = 0; j < ca.height(); j++)
            ca.cell(i, j, get_random_state(p_alive));
    }
}

void print(const CellAutomaton& ca)
{
    for (auto i = 0; i < (ca.width()*2+1); i++) { cout << '-'; }
    cout << '\n';
    for (auto j = 0; j < ca.height(); j++)
    {
        cout << '|';
        for (auto i = 0; i < ca.width(); i++)
        {
            cout << (ca.cell(i, j) == State::alive ? 'o' : ' ');
            if (i != ca.width()-1) { cout << ' '; }
        }
        cout << "|\n";
    }
    for (auto i = 0; i < (ca.width()*2+1); i++) { cout << '-'; }
    cout << '\n';
}

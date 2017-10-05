#include "WrappingGrid.tcc"
#include "CellAutomaton.h"
#include "RLEParser.h"
#include <iostream>
#include <sstream>

class test_failed : public std::runtime_error
{
public:
    explicit test_failed(const string& message) throw() : std::runtime_error(message)
    {}
};

int success = 0;
int failure = 0;

void run_test(void func(void), const string& name)
{
    std::cout << name << ": ";
    try {
        func();
        std::cout << "success" << "\n";
        success++;
    }
    catch (test_failed& ex)
    {
        std::cout << "failure - " << ex.what() << "\n";
        failure++;
    }
}

void assert(bool test, const string& message)
{
    if (! test)
        throw test_failed{message};
}

void assert(bool test) { assert(test, ""); }

State always_alive(const CellAutomaton& unv, int, int)
{
    return State::alive;
}

void test_WrappingGrid_grid()
{
    WrappingGrid<int> g(12, 12);
    assert(g[1][1] == 0, "Grid should be initialized to 0");

    g[3][7] = 20;
    assert(g[3][7] == 20, "Grid at 3, 7 should be set to 20");

    WrappingGrid<int> g2(10, 10, 1337);
    assert(g2[5][5] == 1337, "Grid should be initialized to 1337");
}

void test_WrappingGrid_copy()
{
    WrappingGrid<int> g(10, 10, 5);
    g[3][3] = 12;

    auto g2 = g.copy();
    assert((*g2)[1][1] == 5, "Copied grid at 1, 1 should be equal to 5");
    assert((*g2)[3][3] == 12, "Copied grid at 3, 3 should be equal to 12");
    delete g2;
}

void test_CellAutomaton_cells()
{
    CellAutomaton unv(12, 12, always_alive);
    unv.cell(1, 1, State::alive);
    assert(unv.cell(1, 1) == State::alive, "Cell 1, 1 should be alive");
    unv.cell(5, 11, State::dead);
    assert(unv.cell(5, 11) == State::dead, "Cell 5, 11 should be alive");
}

void test_CellAutomaton_tick()
{
    CellAutomaton unv(10, 10, always_alive);
    unv.tick();
    for (auto i = 0; i < 10; i++)
    {
        for (auto j = 0; j < 10; j++)
        {
            assert(unv.cell(i, j) == State::alive);
        }
    }
}

void test_RLEStringParser_parse()
{
    RLEStringParser parser("x=5,y=5,rule=b3/s23\nb$b$booob!");
    CellAutomaton ca = parser.parse();
    assert(ca.width() == 5, "Automaton should have width of 5");
    assert(ca.height() == 5, "Automaton should have height of 5");
    assert(ca.cell(0, 0) == State::dead, "Cell (0, 0) should be dead");
    assert(ca.cell(2, 2) == State::alive, "Cell (2, 2) should be alive");
}

void test_RLEFileParser_parse()
{
    RLEFileParser parser("../../patterns/glider_gun.rle");
    CellAutomaton ca = parser.parse();
    assert(ca.width() == 36, "Automaton should have width of 36");
    assert(ca.height() == 9, "Automaton should have height of 9");
}

void test_CellAutomaton_blinker()
{
    RLEStringParser parser("x=5,y=5,rule=b3/s23\nb$b$booob!");
    CellAutomaton ca = parser.parse();
    for (auto i = 0; i < 5; i++) {
        for (auto j = 0; j < 5; j++) {
            if (j == 2 && (i == 1 || i == 2 || i == 3)) { assert(ca.cell(i, j) == State::alive); }
            else { assert(ca.cell(i, j) == State::dead); }
        }
    }
    ca.tick();
    for (auto i = 0; i < 5; i++) {
        for (auto j = 0; j < 5; j++) {
            if (i == 2 && (j == 1 || j == 2 || j == 3)) { assert(ca.cell(i, j) == State::alive); }
            else { assert(ca.cell(i, j) == State::dead); }
        }
    }
}

int main ()
{
    std::cout << "Running tests...\n";
    run_test(test_WrappingGrid_grid, "test_WrappingGrid_grid");
    run_test(test_WrappingGrid_copy, "test_WrappingGrid_copy");
    run_test(test_RLEStringParser_parse, "test_RLEStringParser_parse");
    run_test(test_RLEFileParser_parse, "test_RLEFileParser_parse");
    run_test(test_CellAutomaton_cells, "test_CellAutomaton_cells");
    run_test(test_CellAutomaton_tick, "test_CellAutomaton_tick");
    run_test(test_CellAutomaton_blinker, "test_CellAutomaton_blinker");
    std::cout << success << " tests ok, " << failure << " tests failed.";
}

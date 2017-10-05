#include "LifeLikeRule.h"

LifeLikeRule::LifeLikeRule()  // Conway's Life Rule (B3/S23) by default
        :lookup_dead{State::dead, State::dead, State::dead, State::alive,
                     State::dead, State::dead, State::dead, State::dead, State::dead},
         lookup_alive{State::dead, State::dead, State::alive, State::alive,
                      State::dead, State::dead, State::dead, State::dead, State::dead}
{}

LifeLikeRule::LifeLikeRule(const string& rule_str)
        :lookup_dead{State::dead, State::dead, State::dead, State::dead,
                     State::dead, State::dead, State::dead, State::dead, State::dead},
         lookup_alive{State::dead, State::dead, State::dead, State::dead,
                      State::dead, State::dead, State::dead, State::dead, State::dead}
{
    if (! (rule_str[0] == 'B' || rule_str[0] == 'b')) { throw invalid_argument{"Invalid rule string."}; }
    bool parsing_alive = false;
    for (auto i = 1; i < rule_str.size(); i++)
    {
        char c = rule_str[i];
        if (c >= '0' && c <= '8')
        {
            if (parsing_alive) { lookup_alive[c - '0'] = State::alive; }
            else { lookup_dead[c - '0'] = State::alive; }
        }
        else if (c == '/')
        {
            if (! (rule_str[i+1] == 'S' || rule_str[i+1] == 's')) { throw invalid_argument{"Invalid rule string."}; }
            parsing_alive = true;
            i++;
        }
        else { throw invalid_argument{"Invalid rule string."};}
    }

}

State LifeLikeRule::operator() (const CellAutomaton& ca, int x, int y) const
{
    auto live_nbors = 0;

    for (auto i = x-1; i <= x+1; i++) {
        for (auto j = y-1; j <= y+1; j++) {
            // Don't count self
            if ((! (i == x && j == y)) && ca.cell(i, j) == State::alive) { live_nbors++; }
        }
    }
    return ca.cell(x, y) == State::alive ? lookup_alive[live_nbors] : lookup_dead[live_nbors];
}

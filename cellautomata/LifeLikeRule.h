#ifndef GAMEOFLIFE_LIFELIKERULE_H
#define GAMEOFLIFE_LIFELIKERULE_H

#include "CellAutomaton.h"

class LifeLikeRule
{
public:
    LifeLikeRule();
    explicit LifeLikeRule(const string&);
    State operator() (const CellAutomaton&, int, int) const;
protected:
    State lookup_dead[9];
    State lookup_alive[9];
};

#endif //GAMEOFLIFE_LIFELIKERULE_H

#include "CellAutomaton.h"
#include "RLEParser.h"
#include <iostream>
#include <unistd.h>

using namespace std;


int main()
{
//    int p_alive = -1;
//    int height = 0, width = 0;
//    cout << "Height: ";
//    cin >> height;
//    cout << "Width: ";
//    cin >> width;
//
//    while (! (p_alive >= 0 && p_alive <= 100))
//    {
//        cout << "Probability that a cell is alive (0-100): ";
//        cin >> p_alive;
//    }
//    cout << "Breathing life into " << p_alive << "% of cells...\n";
//    LifeLikeRule conway_life("B2/S23");
//    CellAutomaton game(width, height, conway_life);
//
//    srand((unsigned int) time(nullptr));
//    initialize_random(game, p_alive);

    ifstream ifs("../../patterns/glider_gun.rle");
    RLEParser parser(&ifs);
    CellAutomaton game = parser.parse();
    ifs.close();

    for (auto i = 0; i < 100; i++)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        print(game);
        game.tick();
        sleep(1);
    }
}

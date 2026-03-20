#include "basegame.hh"
#include "mostvowels.hh"
#include "rockpaperscissors.hh"
#include <iostream>

using namespace std;

int main()
{
    cout << "Enter two players: ";
    string player1 = "";
    string player2 = "";
    cin >> player1;
    cin >> player2;

    string command = "";
    while(true)
    {
        cout << "Available games:" << endl
             << "  1:             BaseGame (longest word wins)" << endl
             << "  2:             Most Vowels" << endl
             << "  3:             Rock-Paper-Scissors" << endl
             << "  anything else: Quit" << endl
             << "Pick one: ";
        cin >> command;

        if(command != "1" and command != "2" and command != "3")
        {
            return 0;
        }

        unsigned int rounds = 0;
        cout << "How many rounds you want to play? ";
        cin >> rounds;

        if(command == "1")
        {
            BaseGame base(rounds);
            base.setPlayers(player1, player2);
            base.play();
        }
        else if(command == "2")
        {
            MostVowels vowels(rounds);
            vowels.setPlayers(player1, player2);
            vowels.play();
        }
        else if(command == "3")
        {
            RockPaperScissors rps(rounds);
            rps.setPlayers(player1, player2);
            rps.play();
        }
        cout << endl;
    }

    return 0;
}

#include "Model/Deck.hpp"
#include "Controller/Game.hpp"
using namespace std;

bool LeaveOrContinue();
int VerifyArgument(string Argument);

int main(int argc, char *argv[]) //main du programme
{
    do
    {
        Game Game;
        if (argc > 1)
            Game.LaunchGame(VerifyArgument(argv[1]));
        else
            Game.LaunchGame(VerifyArgument("0"));
    } while (LeaveOrContinue());
    return 0;
}

bool LeaveOrContinue() //permet de vérifier si on veut quitter ou relancer une nouvelle partie
{
    do
    {
        string choice;
        View::ShowDoYouWantToLeave();
        cin >> choice;
        if (choice == "0")
            return false;
        else if (choice == "1")
            return true;
        cout << "Je n'ai pas compris" << endl;
    } while (true);
}
int VerifyArgument(string Argument) //Permet de parser le string récupéré en int
{
    cout << "Argument du programme : " << Argument << endl;
    int ParsedArgument = atoi(Argument.c_str());
    if (ParsedArgument <= 4)
        return ParsedArgument; //"atoi" permet de convertir un string en int, si le parsing échoue alors il prendra la valeur 0
    return 0;                  //ce qui est parfait dans notre cas car si l'argument est incorrect il faut avoir 0 joueur humain
}

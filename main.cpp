#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include "libs/txtdb.hpp"



enum enMenuOptions {
    ShowClientsList = 1,    AddNewClient    = 2,    DeleteClient    = 3,
    UpdateClient    = 4,    FindClient      = 5,    Exit            = 6,
};

const std::string filename = "ClientsData.txt";


/* funcation declarations */
void ShowMainMenuOptions();



void
MakeHeader(std::string title)
{
    for (short i = 1; i <= title.length()*3; ++i) { std::cout << "="; }

    std::cout << std::endl;

    for (short i = 1; i <= title.length(); ++i) { std::cout << " "; }

    std::cout << title << std::endl;

    for (short i = 1; i <= title.length()*3; ++i) { std::cout << "="; }

    std::cout << std::endl;
}

short
ReadShortNumber(std::string message)
{
    short option = 0;
    std::cout << message + ' '; std::cin >> option;
    return option;
}

void
ShowClientsData()
{

    std::cout << "test" << std::endl;

    
}


void
GoBackToMainMenuOptions()
{
    system("read -p \"\n\nPress any key to go back to main menu...\"");
    ShowMainMenuOptions();
}


void
PerfromMainMenueOption(enMenuOptions MenuOption)
{
    switch (MenuOption)
    {
    case enMenuOptions::ShowClientsList:
        system("clear");
        ShowClientsData();
        GoBackToMainMenuOptions();
        break;
    
    case enMenuOptions::AddNewClient:
        system("clear");
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::DeleteClient:
        system("clear");
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::UpdateClient:
        system("clear");
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::FindClient:
        system("clear");
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::Exit:
        system("clear");
        MakeHeader("GoodBye :(");
        break;

    }
}



void
ShowMainMenuOptions()
{
    std::string title = "Main Menu Screen";

    system("clear");

    MakeHeader(title);

    std::cout << "\t[1] Show Client List.\n";
    std::cout << "\t[2] Add New Client.\n";
    std::cout << "\t[3] Delete Client.\n";
    std::cout << "\t[4] Update Client Info.\n";
    std::cout << "\t[5] Find Client.\n";
    std::cout << "\t[6] Exit.\n";

    for (short i = 1; i <= title.length()*3; ++i) { std::cout << "="; }
    std::cout << std::endl;
    PerfromMainMenueOption((enMenuOptions)ReadShortNumber("Choose what do you want to do? [1 to 6]?"));


}




int main()
{
    ShowMainMenuOptions();

    return 0;
}
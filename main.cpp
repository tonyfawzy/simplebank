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
const char dividerChar = '-';

/* funcation declarations */
void ShowMainMenuOptions();



void
MakeHeader(std::string title, char _dividerChar = dividerChar)
{
    
    for (short i = 1; i <= title.length()*3; ++i) { std::cout << _dividerChar; }

    std::cout << std::endl;

    for (short i = 1; i <= title.length(); ++i) { std::cout << " "; }

    std::cout << title << std::endl;

    for (short i = 1; i <= title.length()*3; ++i) { std::cout << _dividerChar; }

    std::cout << std::endl;
}



void
ShowClientsData()
{
    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(filename);
    showInfo::AllClients(vClientsData);
}

void
AddClientData()
{
    MakeHeader("Add New Clients Screen");
    char addMore = 'n';
    do {
        std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(filename);
        vClientsData.push_back(getInfo::clientData(vClientsData,true));
        txtDB::SaveClientsDataToFile(vClientsData,filename);

        std::cout << "Client Added Successfully, Do you want to add more clients? Y/N? "; std::cin >> addMore;
    } while (tolower(addMore) == 'y');
}


void
DeleteClientData()
{
    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(filename);
    sClientData ClientData;

    MakeHeader("Delete Client Screen");
    std::string accountNumber = "";
    std::cout << "Please enter account number? "; std::getline(std::cin >> std::ws, accountNumber);
    if (isAccountNumberExist(accountNumber,ClientData,vClientsData))
    {
        char _delete = 'n';
        showInfo::ClientDataCard(ClientData);

        std::cout << "Are you sure you want to delete this client? Y/N? "; std::cin >> _delete;
        if (tolower(_delete) == 'y')
        {
            txtDB::MarkClientDataForDelete(accountNumber,vClientsData);
            txtDB::SaveClientsDataToFile(vClientsData,filename);
            std::cout << "The client has been deleted!\n";
        }
    } else {
        std::cout << accountNumber << " NOT exist!\n";
    }
    
}


void
UpdateClientInfo()
{

    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(filename);
    sClientData ClientData;

    MakeHeader("Update Client Info Screen");
    std::string AccountNumber = "";
    std::cout << "Please enter account number? "; std::getline(std::cin >> std::ws, AccountNumber);
    if (isAccountNumberExist(AccountNumber,ClientData,vClientsData))
    {
        char _update = 'n';
        showInfo::ClientDataCard(ClientData);

        std::cout << "Are you sure you want to update this client? Y/N? "; std::cin >> _update;
        if (tolower(_update) == 'y')
        {

            for (sClientData& C : vClientsData)
            {
                if (AccountNumber == C.AccountNumber)
                {
                    C = getInfo::clientData(vClientsData);
                    C.AccountNumber = AccountNumber;
                    ClientData = C;
                    break;
                }
            }

            txtDB::SaveClientsDataToFile(vClientsData,filename);
            std::cout << "The client has been updated!\n";


        }
    } else {
        std::cout << AccountNumber << " NOT exist!\n";
    }
    
}




void
FindClientData()
{
    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(filename);
    sClientData ClientData;

    MakeHeader("Find Client Screen");
    std::string AccountNumber = "";
    std::cout << "Please enter account number? "; std::getline(std::cin >> std::ws, AccountNumber);

    if (isAccountNumberExist(AccountNumber,ClientData,vClientsData))
    {
        showInfo::showClientData(ClientData);
    } else {
        std::cout << AccountNumber << " NOT exist!\n";
    }
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
        AddClientData();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::DeleteClient:
        system("clear");
        DeleteClientData();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::UpdateClient:
        system("clear");
        UpdateClientInfo();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::FindClient:
        system("clear");
        FindClientData();
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

    for (short i = 1; i <= title.length()*3; ++i) { std::cout << dividerChar; }
    std::cout << std::endl;
    PerfromMainMenueOption((enMenuOptions)getInfo::shortNum("Choose what do you want to do? [1 to 6]?"));


}




int main()
{
    ShowMainMenuOptions();

    return 0;
}
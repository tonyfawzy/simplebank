#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <cmath>
#include "libs/txtdb.hpp"

const std::string ClientsFilename = "ClientsData.txt";
const std::string UsersFilename = "Users.txt";


sUserData CurrentUser;

const char dividerChar = '-';

/* funcation declarations */
void ShowMainMenuOptions();
void ShowTransactionsMenuOptions();
void ShowManageUsersOptions();
void Login();
void GoBackToMainMenuOptions();


void 
clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void
AccessDeniedScreen()
{
    std::cout << "--------------------------------------------------\n";
    std::cout << "Access Denied,\nYou don't have \"Permission\" to do this,\nPlease Contact Your Admin.\n";
    std::cout << "--------------------------------------------------\n" << std::endl;

}

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


bool
CheckAccessPermission(enMenuPermissions Permission)
{
    if (CurrentUser.Permissions == enMenuPermissions::pAll)
        return true;
    
    if ((Permission & CurrentUser.Permissions) == Permission)
        return true;
    else
        return false;
}

void
ShowClientsData()
{
    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(ClientsFilename);
    showInfo::AllClients(vClientsData);
}

void
ShowUsersData()
{
    if (!CheckAccessPermission (enMenuPermissions::pShowClientsList))
    {
        AccessDeniedScreen();
        GoBackToMainMenuOptions();
        return;
    }

    std::vector<sUserData> vUsersData = txtDB::LoadUsersDataFromFile(UsersFilename);
    showInfo::AllUsers(vUsersData);
}


void
AddClientsData()
{

    if (!CheckAccessPermission (enMenuPermissions::pAddNewClient))
    {
        AccessDeniedScreen();
        GoBackToMainMenuOptions();
        return;
    }

    MakeHeader("Add New Clients Screen");
    char addMore = 'n';
    do {
        std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(ClientsFilename);
        vClientsData.push_back(getInfo::clientData(vClientsData,true));
        txtDB::SaveClientsDataToFile(vClientsData,ClientsFilename);
        std::cout << "Client Added Successfully, Do you want to add more clients? Y/N? "; std::cin >> addMore;
    } while (tolower(addMore) == 'y');
}

void
AddUsersData()
{
    MakeHeader("Add New Users Screen");
    char addMore = 'n';
    do {
        std::vector<sUserData> vUsersData = txtDB::LoadUsersDataFromFile(UsersFilename);
        vUsersData.push_back(getInfo::UserData(vUsersData));
        txtDB::SaveUsersDataToFile(vUsersData,UsersFilename);
        std::cout << "User Added Successfully, Do you want to add more users? Y/N? "; std::cin >> addMore;
    } while (tolower(addMore) == 'y');
}

void
DeleteClientData()
{
    if (!CheckAccessPermission (enMenuPermissions::pDeleteClient))
    {
        AccessDeniedScreen();
        GoBackToMainMenuOptions();
        return;
    }

    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(ClientsFilename);
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
            txtDB::SaveClientsDataToFile(vClientsData,ClientsFilename);
            std::cout << "The client has been deleted!\n";
        }
    } else {
        std::cout << accountNumber << " NOT exist!\n";
    }
  
}

void
DeleteUserData()
{
    std::vector<sUserData> vUsersData = txtDB::LoadUsersDataFromFile(UsersFilename);
    sUserData UserData;

    MakeHeader("Delete User Screen");
    std::string Username = "";
    std::cout << "Please enter username? "; std::getline(std::cin >> std::ws, Username);
    if (isUserExist(Username,UserData,vUsersData))
    {
        char _delete = 'n';
        showInfo::UserDataCard(UserData);

        std::cout << "Are you sure you want to delete this client? Y/N? "; std::cin >> _delete;
        if (tolower(_delete) == 'y')
        {
            txtDB::MarkUserDataForDelete(Username,vUsersData);
            txtDB::SaveUsersDataToFile(vUsersData,UsersFilename);
            std::cout << "The user has been deleted!\n";
        }
    } else {
        std::cout << Username << " NOT exist!\n";
    }
  
}
void
UpdateClientInfo()
{

    if (!CheckAccessPermission (enMenuPermissions::pUpdateClient))
    {
        AccessDeniedScreen();
        GoBackToMainMenuOptions();
        return;
    }
    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(ClientsFilename);
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

            txtDB::SaveClientsDataToFile(vClientsData,ClientsFilename);
            std::cout << "The client has been updated!\n";


        }
    } else {
        std::cout << AccountNumber << " NOT exist!\n";
    }
    
}


void
FindClientData()
{

    if (!CheckAccessPermission (enMenuPermissions::pFindClient))
    {
        AccessDeniedScreen();
        GoBackToMainMenuOptions();
        return;
    }

    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(ClientsFilename);
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
FindUserData()
{
    std::vector<sUserData> vUsersData = txtDB::LoadUsersDataFromFile(UsersFilename);
    sUserData UserData;

    MakeHeader("Find User Screen");
    std::string Username = "";
    std::cout << "Please enter username? "; std::getline(std::cin >> std::ws, Username);

    if (isUserExist(Username,UserData,vUsersData))
    {
        showInfo::UserDataCard(UserData);
    } else {
        std::cout << Username << " NOT exist!\n";
    }
}



void
GoBackToMainMenuOptions()
{
#ifdef _WIN32
    std::cout << "\n\nPress any key to go back to main menu...";
    system("pause>0");
    ShowMainMenuOptions();
#else
    system("read -p \"\n\nPress any key to go back to main menu...\"");
    ShowMainMenuOptions();
#endif
}


void
GoBackToTransactionsOptions()
{
#ifdef _WIN32
    std::cout << "\n\nPress any key to go back to main menu...";
    system("pause>0");
    ShowTransactionsMenuOptions();
#else
    system("read -p \"\n\nPress any key to go back to main menu...\"");
    ShowTransactionsMenuOptions();
#endif
}

void
GoBackToManageUsersOptions()
{
#ifdef _WIN32
    std::cout << "\n\nPress any key to go back to main menu...";
    system("pause>0");
    ShowManageUsersOptions();
#else
    system("read -p \"\n\nPress any key to go back to main menu...\"");
    ShowManageUsersOptions();
#endif
}

bool
PerformDepositByAccountNumber(std::string AccountNumber, double amount, std::vector<sClientData>& vClientsData)
{

    char confirm = 'n';

    std::cout << "Are you sure you want perform this transaction? y/n? "; std::cin >> confirm;

    if (tolower(confirm) == 'y')
    {
        for (sClientData& C : vClientsData)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += amount;
                txtDB::SaveClientsDataToFile(vClientsData, ClientsFilename);
                std::cout << "\nDone successfully. New balance is: " << C.AccountBalance;
                break;
            }
        }
        return true;
    }
    else {
        return false;
    }
}
   


void
PerformDeposit()
{
    MakeHeader("Deposit Screen");

    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(ClientsFilename);
    sClientData ClientData;

    std::string accountNumber = getInfo::s_string();

    while (!(isAccountNumberExist(accountNumber,ClientData,vClientsData)))
    {
        std::cout << "Invalid Account Number, Please try again!!\n";
        accountNumber = getInfo::s_string();
    }

    showInfo::ClientDataCard(ClientData);

    double amount = getInfo::doubleNum("Please enter deposit amount?");

    PerformDepositByAccountNumber(accountNumber, amount, vClientsData);
}


void
PerformWithdraw()
{
    MakeHeader("Withdraw Screen");

    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(ClientsFilename);
    std::string accountNumber = getInfo::s_string();
    sClientData ClientData;

    while (!(isAccountNumberExist(accountNumber, ClientData, vClientsData)))
    {
        std::cout << "Invalid Account Number, Please try again!!\n";
        accountNumber = getInfo::s_string();
    }
/*    PerformWithdrawByAccountNumber(accountNumber, vClientsData); */

    showInfo::ClientDataCard(ClientData);

    double amount = getInfo::doubleNum("Please enter withdraw amount?");
    while (amount > ClientData.AccountBalance)
    {
        std::cout << "Amount Exceeds the balance, you can withdraw up to: " + std::to_string(floor(ClientData.AccountBalance)) << std::endl;
        amount = getInfo::doubleNum("Please enter another amount?");
    }

    PerformDepositByAccountNumber(accountNumber, amount*-1, vClientsData);

}

void
ShowTotalBalances()
{
    std::vector<sClientData> vClientsData = txtDB::LoadClientsDataFromFile(ClientsFilename);
    showInfo::TotalBalances(vClientsData);
}


void
PerfromTransactionsOptions(enTransactionsOptions TransactionsOptions)
{
    switch (TransactionsOptions)
    {
    case enTransactionsOptions::Deposit:
        clearScreen();
        PerformDeposit();
        GoBackToTransactionsOptions();
        break;
    case enTransactionsOptions::Withdraw:
        clearScreen();
        PerformWithdraw();
        GoBackToTransactionsOptions();
        break;
    case enTransactionsOptions::Total_Balances:
        clearScreen();
        ShowTotalBalances();
        GoBackToTransactionsOptions();
        break;    
    case enTransactionsOptions::MainMenu_1:
        clearScreen();
        ShowMainMenuOptions();
        break;
    }
}

void
PerfromMainMenuOption(enMenuOptions MenuOption)
{
    switch (MenuOption)
    {
    case enMenuOptions::ShowClientsList:
        clearScreen();
        ShowClientsData();
        GoBackToMainMenuOptions();
        break;
    
    case enMenuOptions::AddNewClient:
        clearScreen();
        AddClientsData();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::DeleteClient:
        clearScreen();
        DeleteClientData();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::UpdateClient:
        clearScreen();
        UpdateClientInfo();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::FindClient:
        clearScreen();
        FindClientData();
        GoBackToMainMenuOptions();
        break;
    case enMenuOptions::Transactions:
        clearScreen();
        ShowTransactionsMenuOptions();
        break;
    case enMenuOptions::ManageUsers:
        clearScreen();
        ShowManageUsersOptions();
        break;
    case enMenuOptions::Logout:
        clearScreen();
        Login();
        break;

    }
}


void
PerfromManageUsersOption(enManageUsersOptions ManageUsersOptions)
{
    switch (ManageUsersOptions)
    {
    case enManageUsersOptions::ListUsers:
        clearScreen();
        ShowUsersData();
        GoBackToManageUsersOptions();
        break;
    case enManageUsersOptions::AddNewUser:
        clearScreen();
        AddUsersData();
        GoBackToManageUsersOptions();
        break;
    case enManageUsersOptions::DeleteUser:
        clearScreen();
        DeleteUserData();
        GoBackToManageUsersOptions();
        break;
    case enManageUsersOptions::UpdateUser:
        clearScreen();
        GoBackToManageUsersOptions();
        break;
    case enManageUsersOptions::FindUser:
        clearScreen();
        FindUserData();
        GoBackToManageUsersOptions();
        break;
    case enManageUsersOptions::MainMenu:
        clearScreen();
        ShowMainMenuOptions();
        break;
    }
}

void
ShowManageUsersOptions()
{
    if (!CheckAccessPermission (enMenuPermissions::pManageUsers))
    {
        AccessDeniedScreen();
        GoBackToMainMenuOptions();
        return;
    }

    std::string title = "Manage Users Menu Screen";

    clearScreen();

    MakeHeader(title);

    std::cout << "\t[1] List Users.\n";
    std::cout << "\t[2] Add New User.\n";
    std::cout << "\t[3] Delete User.\n";
    std::cout << "\t[4] Update User.\n";
    std::cout << "\t[5] Find User.\n";
    std::cout << "\t[6] Main Menu.\n";

    for (short i = 1; i <= title.length()*3; ++i) { std::cout << dividerChar; }
    std::cout << std::endl;
    PerfromManageUsersOption((enManageUsersOptions)getInfo::shortNum("Choose what do you want to do? [1 to 6]?"));


}


void
ShowMainMenuOptions()
{
    std::string title = "Main Menu Screen";

    clearScreen();

    MakeHeader(title);

    std::cout << "\t[1] Show Client List.\n";
    std::cout << "\t[2] Add New Client.\n";
    std::cout << "\t[3] Delete Client.\n";
    std::cout << "\t[4] Update Client Info.\n";
    std::cout << "\t[5] Find Client.\n";
    std::cout << "\t[6] Transactions.\n";
    std::cout << "\t[7] Manage Users.\n";
    std::cout << "\t[8] Logout.\n";

    for (short i = 1; i <= title.length()*3; ++i) { std::cout << dividerChar; }
    std::cout << std::endl;
    PerfromMainMenuOption((enMenuOptions)getInfo::shortNum("Choose what do you want to do? [1 to 8]?"));
}


void
ShowTransactionsMenuOptions()
{
    if (!CheckAccessPermission (enMenuPermissions::pTransactions))
    {
        AccessDeniedScreen();
        GoBackToMainMenuOptions();
        return;
    }

    std::string title = "Transactions Menu Screen";

    clearScreen();

    MakeHeader(title);

    std::cout << "\t[1] Deposit.\n";
    std::cout << "\t[2] Withdraw.\n";
    std::cout << "\t[3] Total Balances.\n";
    std::cout << "\t[4] Main Menu.\n";

    for (short i = 1; i <= title.length()*3; ++i) { std::cout << dividerChar; }
    std::cout << std::endl;
    PerfromTransactionsOptions((enTransactionsOptions)getInfo::shortNum("Choose what do you want to do? [1 to 4]?"));


}

bool 
FindUserByUsernameAndPassword(std::string Username, std::string Password, sUserData& UserData)
{
    std::vector<sUserData> vUsersData = txtDB::LoadUsersDataFromFile(UsersFilename);
    for (sUserData& U : vUsersData) {
        if (U.Username == Username && U.Password == Password) {
            UserData = U;
            return true;
        }
    }
    return false;
}

bool
LoadUserInfo(std::string Username, std::string Password)
{ return FindUserByUsernameAndPassword(Username, Password, CurrentUser); }

void
Login()
{
    std::string title = "Login Screen";

    clearScreen();

    MakeHeader(title);

    std::string Username = getInfo::s_string("Enter Username");
    std::string Password = getInfo::s_string("Enter Password");

    while (!LoadUserInfo(Username, Password))
    {
        clearScreen();
        MakeHeader(title);
        std::cout << "Invalid Username/Password!\n";
        Username = getInfo::s_string("Enter Username");
        Password = getInfo::s_string("Enter Password");

    }


    ShowMainMenuOptions();
}

int main()
{
    Login();

    return 0;
}
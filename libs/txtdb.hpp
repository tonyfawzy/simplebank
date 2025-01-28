#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>

#define DLIM " -> "

struct 
sClientData
{
    std::string AccountNumber = "";
    std::string PINCode = "";
    std::string Name = "";
    std::string PhoneNumber = "";
    double AccountBalance = 0;
    bool MarkForDelete = false;
};

struct 
sUserData
{
    std::string Username = "";
    std::string Password = "";
    short Permissions = 0;
    bool MarkForDelete = false;
};

/* funcation declarations */
bool isAccountNumberExist(std::string accountNumber, sClientData& ClientData, std::vector<sClientData>vClientsData);

const std::string delim = "#//#";


namespace getInfo {

    sClientData 
    clientData(std::vector<sClientData>vClientsData, bool enable_account_number = false)
    {
        sClientData ClientData;
        if (enable_account_number)
        {

            std::cout << "Please Enter Account Number? "; std::getline(std::cin >> std::ws, ClientData.AccountNumber);
            std::cout << "Please Enter PIN-Code? "; std::getline(std::cin, ClientData.PINCode);
            std::cout << "Please Enter The Name? "; std::getline(std::cin, ClientData.Name);
            std::cout << "Please Enter Phone Number? "; std::getline(std::cin, ClientData.PhoneNumber);
            std::cout << "Please Enter Balance? "; std::cin >> ClientData.AccountBalance;
            while (isAccountNumberExist(ClientData.AccountNumber, ClientData, vClientsData))
            {
                std::cout << "Client with [" + ClientData.AccountNumber + "] Already exists, "
                    << "Please Enter another Account Number? ";
                std::getline(std::cin >> std::ws, ClientData.AccountNumber);
            }

        }
        else {
            std::cout << "Please Enter PIN-Code? "; std::getline(std::cin >> std::ws, ClientData.PINCode);
            std::cout << "Please Enter The Name? "; std::getline(std::cin, ClientData.Name);
            std::cout << "Please Enter Phone Number? "; std::getline(std::cin, ClientData.PhoneNumber);
            std::cout << "Please Enter Balance? "; std::cin >> ClientData.AccountBalance;
        }

        return ClientData;
    }

    sUserData
    UserData (std::vector<sUserData> vUsersData)
    {
        
    }


    double 
    doubleNum(std::string message = "Please enter a double number")
    {
        double d_num = 0;
        std::cout << message + ": "; std::cin >> d_num; return d_num;
    }

    short 
    shortNum(std::string message = "Please enter a short number")
    {
        short s_num = 0;
        std::cout << message + ": "; std::cin >> s_num; return s_num;
    }

    std::string 
    s_string(std::string message = "Please enter the account number")
    {
        std::string txt = "";
        std::cout << message + ": "; std::getline(std::cin >> std::ws, txt);
        return txt;
    }

}

namespace showInfo {

    void 
    ClientDataCard(sClientData ClientData, std::string HeaderMessage = "The following are the client details:")
    {
        std::cout << HeaderMessage << '\n' << std::endl;
        char arrCol1[5][16] = {
            "Account Number",
            "PIN Code",
            "Name",
            "Phone Number",
            "Account Balance",
        };


        std::cout << std::left << std::setw(15) << arrCol1[0] << DLIM << ClientData.AccountNumber << std::endl;
        std::cout << std::left << std::setw(15) << arrCol1[1] << DLIM << ClientData.PINCode << std::endl;
        std::cout << std::left << std::setw(15) << arrCol1[2] << DLIM << ClientData.Name << std::endl;
        std::cout << std::left << std::setw(15) << arrCol1[3] << DLIM << ClientData.PhoneNumber << std::endl;
        std::cout << std::left << std::setw(15) << arrCol1[4] << DLIM << ClientData.AccountBalance << std::endl;

        std::cout << std::endl;
    }


    void 
    UserDataCard(sUserData UserData, std::string HeaderMessage = "The following are the user details:")
    {
        std::cout << HeaderMessage << '\n' << std::endl;
        char arrCol1[3][11] = {
            "Username",
            "Password",
            "Permission",
        };


        std::cout << std::left << std::setw(15) << arrCol1[0] << DLIM << UserData.Username << std::endl;
        std::cout << std::left << std::setw(15) << arrCol1[1] << DLIM << UserData.Password << std::endl;
        std::cout << std::left << std::setw(15) << arrCol1[2] << DLIM << UserData.Permissions << std::endl;

        std::cout << std::endl;
    }

    void 
    AllClients(std::vector<sClientData>vClientsData)
    {

        std::cout << "\t\t\t\t\tClients List(" << vClientsData.size() << ") Client(s).\n";
        std::cout << "---------------------------------------------------------------------------------------------\n";
        std::cout << "| " << std::left << std::setw(20) << "Account Number";
        std::cout << "| " << std::left << std::setw(10) << "PIN Code";
        std::cout << "| " << std::left << std::setw(30) << "Client Name";
        std::cout << "| " << std::left << std::setw(14) << "Phone";
        std::cout << "| " << std::left << std::setw(13) << "Balance";
        std::cout << "\n---------------------------------------------------------------------------------------------\n";
        for (sClientData& C : vClientsData)
        {
            std::cout << "| " << std::left << std::setw(20) << C.AccountNumber;
            std::cout << "| " << std::left << std::setw(10) << C.PINCode;
            std::cout << "| " << std::left << std::setw(30) << C.Name;
            std::cout << "| " << std::left << std::setw(14) << C.PhoneNumber;
            std::cout << "| " << std::left << std::setw(13) << C.AccountBalance;
            std::cout << std::endl;
        }
        std::cout << "---------------------------------------------------------------------------------------------\n";
    }

    void 
    AllUsers(std::vector<sUserData>vUsersData)
    {

        std::cout << "\t\t\t\t\tUsers List(" << vUsersData.size() << ") Users(s).\n";
        std::cout << "---------------------------------------------------------------------------------------------\n";
        std::cout << "| " << std::left << std::setw(20) << "Username";
        std::cout << "| " << std::left << std::setw(20) << "Password";
        std::cout << "| " << std::left << std::setw(20) << "Permission";
        std::cout << "\n---------------------------------------------------------------------------------------------\n";
        for (sUserData& U : vUsersData)
        {
            std::cout << "| " << std::left << std::setw(20) << U.Username;
            std::cout << "| " << std::left << std::setw(20) << U.Password;
            std::cout << "| " << std::left << std::setw(20) << U.Permissions;
            std::cout << std::endl;
        }
        std::cout << "---------------------------------------------------------------------------------------------\n";
    }

    void 
    TotalBalances(std::vector<sClientData>vClientsData)
    {
        double totalBalances = 0;

        std::cout << "\t\t\t\t\tBalances List(" << vClientsData.size() << ") Client(s).\n";
        std::cout << "---------------------------------------------------------------------------------------------\n";
        std::cout << "| " << std::left << std::setw(20) << "Account Number";
        std::cout << "| " << std::left << std::setw(30) << "Client Name";
        std::cout << "| " << std::left << std::setw(13) << "Balance";
        std::cout << "\n---------------------------------------------------------------------------------------------\n";
        for (sClientData& C : vClientsData)
        {
            std::cout << "| " << std::left << std::setw(20) << C.AccountNumber;
            std::cout << "| " << std::left << std::setw(30) << C.Name;
            std::cout << "| " << std::left << std::setw(13) << C.AccountBalance;
            std::cout << std::endl;

            totalBalances += C.AccountBalance;
        }
        std::cout << "---------------------------------------------------------------------------------------------\n";
        std::cout << "\t\t\t\t\tTotal Balances = " + std::to_string(totalBalances) + "\n";

    }


    void 
    showClientDataByAccountNumber(std::vector<sClientData>vClientsData)
    {
        std::string accountNumber = getInfo::s_string();
        sClientData ClientData;
        if (isAccountNumberExist(accountNumber, ClientData, vClientsData))
        {
            showInfo::ClientDataCard(ClientData);
        }
        else {
            std::cout << "Your account number (" + accountNumber + ") is not exist :(\n";
        }
    }

    void showClientData(sClientData ClientData)
    {
        showInfo::ClientDataCard(ClientData);
    }



}


std::vector<std::string> 
SplitString(std::string line, std::string _delim = delim)
{
    std::vector<std::string>vRecords;
    size_t pos = 0;
    std::string record = "";
    while ((pos = line.find(delim)) != std::string::npos)
    {
        record = line.substr(0, pos);
        if (record != "")
        {
            vRecords.push_back(record);
        }

        line.erase(0, pos + delim.length());
    }

    if (line != "")
    {
        vRecords.push_back(line);
    }

    return vRecords;
}

sClientData 
ConvertLineToRecord(std::string line)
{
    std::vector<std::string>vRecords = SplitString(line);
    sClientData ClientData;

    ClientData.AccountNumber = vRecords[0];
    ClientData.PINCode = vRecords[1];
    ClientData.Name = vRecords[2];
    ClientData.PhoneNumber = vRecords[3];
    ClientData.AccountBalance = std::stod(vRecords[4]);

    return ClientData;
}

sUserData 
ConvertUserLineToRecord(std::string line)
{
    std::vector<std::string>vRecords = SplitString(line);
    sUserData UserClient;

    UserClient.Username = vRecords[0];
    UserClient.Password = vRecords[1];
    UserClient.Permissions = std::stoi(vRecords[2]);

    return UserClient;
}


std::string 
ConvertRecordToLine(sClientData ClientData, std::string _delim = delim)
{
    std::string line = "";
    line += ClientData.AccountNumber + delim;
    line += ClientData.PINCode + delim;
    line += ClientData.Name + delim;
    line += ClientData.PhoneNumber + delim;
    line += std::to_string(ClientData.AccountBalance);
    return line;
}

std::string 
ConvertUsersRecordToLine(sUserData UserData, std::string _delim = delim)
{
    std::string line = "";
    line += UserData.Username + delim;
    line += UserData.Password + delim;
    line += std::to_string(UserData.Permissions);
    return line;
}

bool 
isAccountNumberExist(std::string accountNumber, sClientData& ClientData, std::vector<sClientData>vClientsData)
{
    for (sClientData& C : vClientsData)
    {
        if (accountNumber == C.AccountNumber)
        {
            ClientData = C;
            return true;
        }
    }
    return false;
}

bool 
isUsernameExist(std::string Username, sUserData& UserData, std::vector<sUserData>vUsersData)
{
    for (sUserData& U : vUsersData)
    {
        if (Username == U.Username)
        {
            UserData = U;
            return true;
        }
    }
    return false;
}


bool 
isUsernameAndPasswordExist(std::string Username, std::string Password, sUserData& UsersData, std::vector<sUserData>vUsersData)
{
    for (sUserData& U : vUsersData)
    {
        if (Username == U.Username && Password == U.Password) {
            UsersData = U;
            return true;
        }
    }
    return false;
}

namespace txtDB {

    std::vector<sClientData> 
    LoadClientsDataFromFile(std::string filename)
    {
        std::vector<sClientData> vClientsData;
        std::fstream file;
        file.open(filename, std::ios::in);
        if (file.is_open())
        {
            sClientData ClientData;
            std::string line = "";
            while (std::getline(file, line))
            {
                ClientData = ConvertLineToRecord(line);
                vClientsData.push_back(ClientData);
            }

            file.close();
        }
        return vClientsData;
    }

    std::vector<sUserData> 
    LoadUsersDataFromFile(std::string filename)
    {
        std::vector<sUserData> vUsersData;
        std::fstream file;
        file.open(filename, std::ios::in);
        if (file.is_open())
        {
            sUserData UserData;
            std::string line = "";
            while (std::getline(file, line))
            {
                UserData = ConvertUserLineToRecord(line);
                vUsersData.push_back(UserData);
            }

            file.close();
        }
        return vUsersData;
    }

    void 
    MarkClientDataForDelete(std::string accountNumber, std::vector<sClientData>& vClientsData)
    {
        for (sClientData& ClientData : vClientsData)
        {
            if (ClientData.AccountNumber == accountNumber)
            {
                ClientData.MarkForDelete = true;
            }
        }
    }

    void 
    MarkUserDataForDelete(std::string Username, std::vector<sUserData>& vUsersData)
    {
        for (sUserData& UserData : vUsersData)
        {
            if (UserData.Username == Username)
            {
                UserData.MarkForDelete = true;
            }
        }
    }



    void 
    SaveClientsDataToFile(std::vector<sClientData>vClientsData, std::string filename)
    {
        std::fstream file;
        file.open(filename, std::ios::out);
        if (file.is_open())
        {
            std::string line = "";
            for (sClientData& C : vClientsData)
            {
                if (C.MarkForDelete == false)
                {
                    line = ConvertRecordToLine(C);
                    file << line << std::endl;
                }
            }
            file.close();
        }

    }

    void 
    SaveUsersDataToFile(std::vector<sUserData>vUsersData, std::string filename)
    {
        std::fstream file;
        file.open(filename, std::ios::out);
        if (file.is_open())
        {
            std::string line = "";
            for (sUserData& U : vUsersData)
            {
                if (U.MarkForDelete == false)
                {
                    line = ConvertUsersRecordToLine(U);
                    file << line << std::endl;
                }
            }
            file.close();
        }

    }



}



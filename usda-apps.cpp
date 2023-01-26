#include <iostream>
#include <fstream>
#include <vector>
#include <csignal>
#include <string>
#include <cctype>
using namespace std;

#define arrLength(x) (sizeof(x) / sizeof(x[0]))

const string FILENAME = "users.csv";
const string SEPARATOR = ",";
const int userData = 3;

struct User
{
    string nama;
    string alamat;
    int umur;
};

void clearScreen()
{
#ifdef __linux__
    system("clear");
#else
    system("CLS");
#endif
}

bool isNumber(const string &s)
{
    return s.find_first_not_of("0123456789") == string::npos;
}

bool isAlphaSpace(const string &s)
{
    for (char c : s)
    {
        if (!(isalpha(c) || (c == ' ')))
        {
            return false;
        }
    }
    return true;
}

string toUpper(string str)
{
    for (int i = 0; i < str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

bool searchString(string str, string find) {
    return toUpper(str).find(toUpper(find)) != std::string::npos;
}

vector<string> split(string str, string separator = " ")
{
    vector<string> arr;
    int start, end = -1 * separator.size();
    do
    {
        start = end + separator.size();
        end = str.find(separator, start);
        arr.push_back(str.substr(start, end - start));
    } while (end != -1);
    return arr;
}

void signalHandler(int signum)
{
    cout << endl;
    cout << endl;
    cout << "  Interrupt signal (" << signum << ") by user." << endl;
    cout << endl;
    exit(signum);
}

int getDigit(int number)
{
    return to_string(number).length();
}

void writeFile(User *users, unsigned int count)
{
    fstream writeFile;
    writeFile.open(FILENAME, ios::out);
    if (writeFile.is_open())
    {
        for (int i = 0; i < count; i++)
        {
            User user = users[i];
            writeFile << user.nama << SEPARATOR << user.alamat << SEPARATOR << user.umur << "\n";
        }
        cout << count << " users have been recorded" << endl;
        writeFile.close();
    }
}

vector<User> readFile()
{
    fstream readFile;
    readFile.open(FILENAME, ios::in);
    if (!readFile.is_open())
    {
        vector<User> users;
        return users;
    }

    vector<User> users;
    string line, word;

    while (getline(readFile, line))
    {
        vector<string> row = split(line, SEPARATOR);
        if (row.size() == userData)
        {
            User user = User{
                row[0],
                row[1],
                stoi(row[2]),
            };
            users.push_back(user);
        }
    }

    readFile.close();
    return users;
}

void printApp()
{
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << "+ ---------------------------- UsDa Apps ----------------------------- +" << endl;
    cout << "+ ------------------------ User Database Apps ------------------------ +" << endl;
    cout << "+ -------------------------------------------------------------------- +" << endl;
}

void printUsers(vector<User> users)
{
    for (int i = 0; i < users.size(); i++)
    {
        User user = users[i];
        int idx = i + 1;

        cout << "+ -------------------------------------------------------------------- +" << endl;
        cout << "+ [" << idx << "] ";
        cout << "-> Name    : " << user.nama << endl;
        cout << "+  " << string(getDigit(idx), ' ') << "  ";
        cout << "-> Alamat  : " << user.alamat << endl;
        cout << "+  " << string(getDigit(idx), ' ') << "  ";
        cout << "-> Umur    : " << user.umur << endl;
        cout << "+ -------------------------------------------------------------------- +" << endl;
    }
    cout << endl;
}

void getAllUsers()
{
    printApp();
    cout << "+ -------------------------- Get all users --------------------------- +" << endl;
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << endl;

    vector<User> users = readFile();
    printUsers(users);
}

void searchUserByName()
{
    string search;
    printApp();
    cout << "+ ----------------------- Search users by name ----------------------- +" << endl;
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << endl;

    cin.ignore();
    while (true)
    {
        string tempSearch;
        cout << "  Search name: ";
        getline(cin, tempSearch);
        cout << endl;

        if (!isAlphaSpace(tempSearch))
        {
            cout << "  Please input an alpha space!" << endl;
            cout << endl;
            continue;
        }

        search = tempSearch;
        break;
    }

    vector<User> users = readFile();

    vector<User> filterUsers;
    for (int i = 0; i < users.size(); i++)
    {
        User user = users[i];
        bool found = searchString(user.nama, search);
        if (found)
        {
            filterUsers.push_back(user);
        }
    }

    if (filterUsers.size() == 0)
    {
        cout << "+ -------------------------------------------------------------------- +" << endl;
        cout << "+ -------------------------- Users not found ------------------------- +" << endl;
        cout << "+ -------------------------------------------------------------------- +" << endl;
    }

    printUsers(filterUsers);
}

void addUsers()
{
    cout << "  call addUsers()" << endl;
}

void deleteUser()
{
    cout << "  call deleteUser()" << endl;
}

bool buildMenu()
{
    int chooseMenu;
    int totalChoose = 5;
    printApp();
    cout << "\n  The menu: " << endl;
    cout << "  [1] Get all users" << endl;
    cout << "  [2] Search user by name" << endl;
    cout << "  [3] Add users" << endl;
    cout << "  [4] Delete user" << endl;
    cout << "  [5] Exit" << endl;
    cout << endl;

    while (true)
    {
        string strChooseMenu;
        cout << "  Choose the menu: ";
        cin >> strChooseMenu;
        cout << endl;

        if (!isNumber(strChooseMenu))
        {
            cout << "  Please input a number!" << endl;
            cout << endl;
            continue;
        }

        int tempChooseMenu = stoi(strChooseMenu);
        if (tempChooseMenu < 0)
        {
            cout << "  Please input a positive number!" << endl;
            cout << endl;
            break;
        }

        if (!(tempChooseMenu >= 0 && tempChooseMenu <= totalChoose))
        {
            cout << "  List menu not found, available in range 1-" << totalChoose << endl;
            cout << endl;
            continue;
        }

        chooseMenu = tempChooseMenu;
        break;
    }

    switch (chooseMenu)
    {
    case 1:
        clearScreen();
        getAllUsers();
        break;
    case 2:
        clearScreen();
        searchUserByName();
        break;
    case 3:
        addUsers();
        break;
    case 4:
        deleteUser();
        break;
    case 5:
        return true;
    }

    return false;
}

int main()
{
    signal(SIGINT, signalHandler);
    char confirm;
    do
    {
        clearScreen();
        bool quitSignal = buildMenu();
        if (quitSignal)
        {
            break;
        }

        cout << "  Press y or Y to continue: ";
        cin >> confirm;
    } while (confirm == 'y' || confirm == 'Y');
    cout << "  Thank you!" << endl;
}
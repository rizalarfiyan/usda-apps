#include <iostream>
#include <fstream>
#include <vector>
#include <csignal>
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
    cout << endl
         << endl;
    cout << "  Interrupt signal (" << signum << ") by user." << endl;
    cout << endl;
    exit(signum);
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

void getAllUsers()
{
    cout << "  call getAllUsers()" << endl;
}

void getUserByName()
{
    cout << "  call getUserByName()" << endl;
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
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << "+ ---------------------------- UsDa Apps ----------------------------- +" << endl;
    cout << "+ ------------------------ User Database Apps ------------------------ +" << endl;
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << "\n  The menu: " << endl;
    cout << "  [1] Get all users" << endl;
    cout << "  [2] Get user by name" << endl;
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
            cout << "  Please enter number!" << endl;
            cout << endl;
            continue;
        }

        int tempChooseMenu = stoi(strChooseMenu);
        if (tempChooseMenu < 0)
        {
            cout << "  Please enter positive number!" << endl;
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
        getAllUsers();
        break;
    case 2:
        getUserByName();
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
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
const int userData = 5;

struct User
{
    string name;
    string adress;
    string hoby;
    string phone;
    int age;
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

bool isAlphaNumericSpace(const string &s)
{
    for (char c : s)
    {
        if (!(isalpha(c) || isalnum(c) || (c == ' ')))
        {
            return false;
        }
    }
    return true;
}

string toUpper(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        str[i] = toupper(str[i]);
    }
    return str;
}

bool searchString(string str, string find)
{
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

void writeFile(vector<User> users)
{
    fstream writeFile;
    writeFile.open(FILENAME, ios::out);
    if (writeFile.is_open())
    {
        for (int i = 0; i < users.size(); i++)
        {
            User user = users[i];
            writeFile << user.name << SEPARATOR << user.adress << SEPARATOR << user.hoby << SEPARATOR << user.phone << SEPARATOR << user.age << "\n";
        }
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
                row[2],
                row[3],
                stoi(row[4]),
            };
            users.push_back(user);
        }
    }

    readFile.close();
    return users;
}

int inputInteger(string wording, int *maxRange = NULL, string rangeWording = "Data not found")
{
    int getInt;
    while (true)
    {
        string strGetInt;
        cout << wording;
        cin >> strGetInt;
        cout << endl;

        if (!isNumber(strGetInt))
        {
            cout << "  Please input a number!" << endl;
            cout << endl;
            continue;
        }

        int tempGetInt = stoi(strGetInt);
        if (tempGetInt < 0)
        {
            cout << "  Please input a positive number!" << endl;
            cout << endl;
            continue;
        }

        if (maxRange != NULL)
        {
            if (!(tempGetInt >= 0 && tempGetInt <= *maxRange))
            {
                cout << "  " << rangeWording << ", available in range 1-" << *maxRange << endl;
                cout << endl;
                continue;
            }
        }

        getInt = tempGetInt;
        break;
    }
    return getInt;
}

string inputString(string wording, string flag = "")
{
    string getString;
    while (true)
    {
        string tempGetString;
        cout << wording;
        getline(cin, tempGetString);
        cout << endl;

        if (!isAlphaSpace(tempGetString) && flag == "")
        {
            cout << "  Please input an alpha space!" << endl;
            cout << endl;
            continue;
        }

        if (!isNumber(tempGetString) && flag == "phone")
        {
            cout << "  Please input a number!" << endl;
            cout << endl;
            continue;
        }

        if (!isAlphaNumericSpace(tempGetString) && flag == "adress")
        {
            cout << "  Please input an alpha, numeric, and space!" << endl;
            cout << endl;
            continue;
        }

        getString = tempGetString;
        break;
    }
    return getString;
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

        string firsts = "+ [" + to_string(idx) + "] ";
        string spacer = "+  " + string(getDigit(idx), ' ') + "  ";
        cout << "+ -------------------------------------------------------------------- +" << endl;
        cout << firsts << "-> Name    : " << user.name << endl;
        cout << spacer << "-> Adress  : " << user.adress << endl;
        cout << spacer << "-> Hoby    : " << user.hoby << endl;
        cout << spacer << "-> Phone   : " << user.phone << endl;
        cout << spacer << "-> Age     : " << user.age << endl;
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

vector<User> findUserFilter(bool isDelete = false)
{
    cin.ignore();
    string search = inputString("  Search name: ");
    vector<User> users = readFile();

    vector<User> includeFilterUsers;
    vector<User> filterUsers;
    for (int i = 0; i < users.size(); i++)
    {
        User user = users[i];
        bool found = searchString(user.name, search);
        if (found)
        {
            filterUsers.push_back(user);
        }
        else if (isDelete)
        {
            includeFilterUsers.push_back(user);
        }
    }

    if (filterUsers.size() == 0)
    {
        cout << "+ -------------------------------------------------------------------- +" << endl;
        cout << "+ -------------------------- Users not found ------------------------- +" << endl;
        cout << "+ -------------------------------------------------------------------- +" << endl;
    }

    printUsers(filterUsers);

    return isDelete ? includeFilterUsers : filterUsers;
}

void searchUserByName()
{
    printApp();
    cout << "+ ----------------------- Search users by name ----------------------- +" << endl;
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << endl;

    findUserFilter();
}

void addUsers()
{
    printApp();
    cout << "+ ----------------------------- Add user ----------------------------- +" << endl;
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << endl;

    int countUser = inputInteger("  Many user: ");
    vector<User> users = readFile();
    int maxAge = 150;

    cin.ignore();
    for (int i = 0; i < countUser; i++)
    {
        string name = inputString("  Name    : ");
        string adress = inputString("  Adress  : ", "adress");
        string hoby = inputString("  Hoby    : ");
        string phone = inputString("  Phone   : ", "phone");
        int age = inputInteger("  Age     : ", &maxAge, "Age not valid");

        User user = User{
            name,
            adress,
            hoby,
            phone,
            age,
        };
        users.push_back(user);
    }

    writeFile(users);

    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << "+ ------------------------- Success add users ------------------------ +" << endl;
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << endl;
}

void deleteUser()
{
    printApp();
    cout << "+ ----------------------- Delete users by name ----------------------- +" << endl;
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << endl;

    vector<User> deleteUsers = findUserFilter(true);
    writeFile(deleteUsers);

    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << "+ ------------------- Success delete users by name ------------------- +" << endl;
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << endl;
}

bool buildMenu()
{
    int totalChoose = 5;
    printApp();
    cout << "\n  The menu: " << endl;
    cout << "  [1] Get all users" << endl;
    cout << "  [2] Search user by name" << endl;
    cout << "  [3] Add users" << endl;
    cout << "  [4] Delete user" << endl;
    cout << "  [5] Exit" << endl;
    cout << endl;

    int chooseMenu = inputInteger("  Choose the menu: ", &totalChoose, "List menu not found");
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
        clearScreen();
        addUsers();
        break;
    case 4:
        clearScreen();
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
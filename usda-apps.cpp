#include <iostream>
#include <fstream>
#include <vector>
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
    vector<string> row;
    string line, word;

    while (getline(readFile, line))
    {
        row.clear();

        int start, end = -1 * SEPARATOR.size();
        do
        {
            start = end + SEPARATOR.size();
            end = line.find(SEPARATOR, start);
            row.push_back(line.substr(start, end - start));
        } while (end != -1);

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

    cout << users.size() << " users have been read!" << endl;
    readFile.close();
    return users;
}

int main()
{
    cout << "+ -------------------------------------------------------------------- +" << endl;
    cout << "+ ---------------------------- UsDa Apps ----------------------------- +" << endl;
    cout << "+ ------------------------ User Database Apps ------------------------ +" << endl;
    cout << "+ -------------------------------------------------------------------- +" << endl;

    User users[] = {
        {"Rizal", "Kebumen", 19},
        {"Ami", "Kebumen", 19},
    };

    writeFile(users, arrLength(users));
    readFile();
}
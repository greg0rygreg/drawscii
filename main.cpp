/*
hey!
if you want to compile this, run this command:
g++ -o drawscii main.cpp
add .exe after drawscii if you're a windows user
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <cstdlib>
using namespace std;
namespace fs = filesystem;

void clear()
{
    cout << "\033[2J\033[1;1H";
}

void sep()
{
    cout << string(75, '-') << endl;
}

int main()
{
    clear();
    string VERSION = "1.0";
    char* dataLoc;
    bool windows;
    #ifdef _WIN32
        dataLoc = getenv("APPDATA");
        windows = true;
    #else
        dataLoc = getenv("HOME");
        windows = false;
    #endif
    if (!fs::exists(fs::path(dataLoc) / (windows ? "DRAWscii" : ".DRAWscii"))) { // somehow this works
        if (!fs::create_directories(fs::path(dataLoc) / (windows ? "DRAWscii" : ".DRAWscii"))) {
            std::cerr << "\x1b[1;31merror:\x1b[39m creating data folder for DRAWscii failed and app will exit (try running as " << (windows ? "administrator" : "superuser") << "?)\x1b[0m\n";
            exit(1);
        }
    }
    fs::path dciData = fs::path(dataLoc) / (windows ? "DRAWscii" : ".DRAWscii");
    cout << "welcome to\n";
    while (true)
    {
        if (fs::exists(dciData / "settings" / "logodisabled")) {
            cout << "DRAWscii\n";
        } else {
            cout << "\
┏━━━┳━━━┳━━━┳┓┏┓┏┓a greg project\n\
┗┓┏┓┃┏━┓┃┏━┓┃┃┃┃┃┃made in C++\n\
╋┃┃┃┃┗━┛┃┃╋┃┃┃┃┃┃┣━━┳━━┳┳┓\n\
╋┃┃┃┃┏┓┏┫┗━┛┃┗┛┗┛┃━━┫┏━╋╋┫\n\
┏┛┗┛┃┃┃┗┫┏━┓┣┓┏┓┏╋━━┃┗━┫┃┃\n\
┗━━━┻┛┗━┻┛╋┗┛┗┛┗┛┗━━┻━━┻┻┛\n\
blindpaint, refurbished.\n\
";
        }
    cout << "\
(1) new canvas\n\
(2) info\n\
(3) settings\n\
(0) exit\n\
>> ";
        int menu_in;
        cin >> menu_in;
        if (menu_in == 1)
        {
            clear();
            cout << "enter amount of rows (don\'t get greedy!)\n>> ";
            int canvasW;
            cin >> canvasW;
            clear();
            cout << "enter amount of columns (don\'t get greedy!)\n>> ";
            int canvasH;
            cin >> canvasH;
            clear();
            vector<vector<int>> canvas(canvasW, vector<int>(canvasH, 0));
            clear();
            while (true)
            {
                for (vector<int> row : canvas)
                {
                    for (int col : row)
                    {
                        cout << (col == 0 ? "  " : "# ");
                    }
                    cout << endl;
                }
                sep();
                cout << "actions:\n\
(1) paint pixel\n\
(2) fill region\n\
(0) save & exit\n\
>> ";
                int actions_in;
                cin >> actions_in;
                if (actions_in == 1)
                {
                    clear();
                    cout << "enter Y (starting from 0):\n>> ";
                    int posX;
                    cin >> posX;
                    posX = max(0, min(canvasW - 1, posX));
                    clear();
                    cout << "enter X (starting from 0):\n>> ";
                    int posY;
                    cin >> posY;
                    posY = max(0, min(canvasH - 1, posY));
                    clear();
                    cout << "enter paint value (0 or 1):\n>> ";
                    int paintVal;
                    cin >> paintVal;
                    paintVal = max(0, min(1, paintVal));
                    canvas[posX][posY] = paintVal;
                    clear();
                    cout << "successfully painted pixel " << posX << "," << posY << " with " << paintVal << endl;
                    sep();
                }
                else if (actions_in == 2)
                {
                    clear();
                    cout << "enter Y1 (starting from 0):\n>> ";
                    int x1;
                    cin >> x1;
                    clear();
                    cout << "enter X1 (starting from 0):\n>> ";
                    int y1;
                    cin >> y1;
                    clear();
                    clear();
                    cout << "enter Y2 (starting from 0):\n>> ";
                    int x2;
                    cin >> x2;
                    clear();
                    cout << "enter X2 (starting from 0):\n>> ";
                    int y2;
                    cin >> y2;
                    clear();
                    cout << "enter paint value (0 or 1):\n>> ";
                    int val;
                    cin >> val;
                    val = max(0, min(1, val));
                    clear();
                    // yeah i stole this code from MY dll what are you gonna do huh??
                    x1 = min(x1, x2);
                    x2 = max(x1, x2);
                    y1 = min(y1, y2);
                    y2 = max(y1, y2);

                    x1 = max(0, x1);
                    x2 = min(canvasW - 1, x2);
                    y1 = max(0, y1);
                    y2 = min(canvasH - 1, y2);

                    for (int i = x1; i <= x2; ++i)
                    {
                        for (int j = y1; j <= y2; ++j)
                        {
                            canvas[i][j] = val;
                        }
                    }
                    cout << "successfully filled region from pixel " << x1 << "," << y1 << " to " << x2 << "," << y2 << " with " << val << endl;
                    sep();
                }
                else if (actions_in == 0)
                {
                    clear();
                    cin.ignore();
                    string filename;
                    cout << "enter file name:\n>> ";
                    getline(cin, filename);
                    // i also stole this from MY dll
                    time_t currtime = time(0);
                    std::ofstream file(filename);
                    if (!file.is_open())
                    {
                        clear();
                        std::cerr << "\x1b[1;31merror:\x1b[39m exporting canvas to file " << filename << " failed\x1b[0m\n";
                        sep();
                        break;
                    }
                    file << "(tip: use a mono font for the best results!)\n";
                    for (auto row : canvas)
                    {
                        for (int pixel : row)
                        {
                            file << (pixel == 1 ? "# " : "  ");
                        }
                        file << "\n";
                    }
                    char *dt = ctime(&currtime);
                    file << "time created: " << dt << "made by: a very awesome person\n";
                    clear();
                    cout << "successfully exported canvas to " << filename << endl;
                    break;
                }
                else
                {
                    clear();
                    std::cerr << "\x1b[1;31merror:\x1b[39m no option made for input " << actions_in << "\x1b[0m\n";
                    sep();
                }
            }
        }
        else if (menu_in == 2)
        {
            clear();
            cout << "DRAWscii " << VERSION << " / blindpaint 2.0+\n\
blindpaint, refurbished.\n\
licensed under MIT license\n\
any changes YOU make are YOURS & YOURS ONLY\n\
this program was developed in C++; any other DRAWscii\n\
    version made in anything but C++ is either a fan-made,\n\
    or malicious.\n";
            sep();
        }
        else if (menu_in == 3)
        {
            if (!fs::exists(dciData / "settings")) {
                if (!fs::create_directories(dciData / "settings")) {
                    std::cerr << "\x1b[1;31merror:\x1b[39m creating settings folder for DRAWscii failed (try running as " << (windows ? "administrator" : "superuser") << "?)\x1b[0m\n";
                    break;
                }
            }
            clear();
            while (true) {
                cout << "options:\n\
(1) disable ASCII logo [" << (fs::exists(dciData / "settings" / "logodisabled") ? "✔️" : "✖️") << "]\n\
(0) exit\n\
>> ";
                int options_in;
                cin >> options_in;
                if (options_in == 1) {
                    clear();
                    if (fs::exists(dciData / "settings" / "logodisabled")) { // this, too, somehow works
                        if (!fs::remove(dciData / "settings" / "logodisabled")) {
                            std::cerr << "\x1b[1;31merror:\x1b[39m disabling setting failed (try running as " << (windows ? "administrator" : "superuser") << "?)\x1b[0m\n";
                        }
                    } else {
                        ofstream option(dciData / "settings" / "logodisabled");
                        if (!option.is_open()) {
                            std::cerr << "\x1b[1;31merror:\x1b[39m enabling setting failed (try running as " << (windows ? "administrator" : "superuser") << "?)\x1b[0m\n";
                        }  else { // i'm not sure if this else block does anything
                            option.close();
                        }
                    }
                }
                else if (options_in == 0) {
                    clear();
                    break;
                }
                else {
                    clear();
                    std::cerr << "\x1b[1;31merror:\x1b[39m no option made for input " << options_in << "\x1b[0m\n";
                    sep();
                }
            }
        }
        else if (menu_in == 0)
        {
            clear();
            cout << "bye!\n";
            exit(0);
        }
        else
        {
            clear();
            std::cerr << "\x1b[1;31merror:\x1b[39m no option made for input " << menu_in << "\x1b[0m\n";
            sep();
        }
    }
    return 0;
}
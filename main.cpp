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
using namespace std;

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
    string VERSION = "1.0";
    clear();
    cout << "welcome to\n";
    while (true)
    {
        cout << "\
┏━━━┳━━━┳━━━┳┓┏┓┏┓a greg project\n\
┗┓┏┓┃┏━┓┃┏━┓┃┃┃┃┃┃made in C++\n\
╋┃┃┃┃┗━┛┃┃╋┃┃┃┃┃┃┣━━┳━━┳┳┓\n\
╋┃┃┃┃┏┓┏┫┗━┛┃┗┛┗┛┃━━┫┏━╋╋┫\n\
┏┛┗┛┃┃┃┗┫┏━┓┣┓┏┓┏╋━━┃┗━┫┃┃\n\
┗━━━┻┛┗━┻┛╋┗┛┗┛┗┛┗━━┻━━┻┻┛\n\
blindpaint, refurbished.\n\
(1) new canvas\n\
(2) info\n\
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
                if (actions_in == 2)
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
                    clear();
                    // yeah i stole this code from MY dll what are you gonna do huh??
                    int startX = std::min(x1, x2);
                    int endX = std::max(x1, x2);
                    int startY = std::min(y1, y2);
                    int endY = std::max(y1, y2);

                    startX = std::max(0, startX);
                    endX = std::min(canvasW - 1, endX);
                    startY = std::max(0, startY);
                    endY = std::min(canvasH - 1, endY);

                    for (int i = startX; i <= endX; ++i)
                    {
                        for (int j = startY; j <= endY; ++j)
                        {
                            canvas[i][j] = val;
                        }
                    }
                    cout << "successfully filled region from pixel " << x1 << "," << y1 << " to " << x2 << "," << y2 << " with " << val << endl;
                    sep();
                }
                if (actions_in == 0)
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
                        std::cerr << "\x1b[1;31merror:\x1b[39m exporting canvas to file " << filename << " failed \x1b[0m\n";
                        break;
                        sep();
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
            }
        }
        if (menu_in == 2)
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
        if (menu_in == 0)
        {
            clear();
            cout << "bye!\n";
            exit(0);
        }
    }
    return 0;
}
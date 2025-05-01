// hey!
// if you want to compile this ON WINDOWS,
// run this command:
// g++ -o drawscii.exe main.cpp
// if you get make running on windows
// then cool, linux users can also
// use this method

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <chrono>
using namespace std;
namespace fs = filesystem;

void clear()
{
  cout << "\033[2J\033[H";
}

void sep()
{
  cout << string(75, '-') << endl;
}

int main(int argc, char** argv)
{
  clear();
  string VERSION = "1.2";
  string dataLoc;
  bool windows;
  bool danger = 0;
  if (argc > 1) {
    // hate it when you need to do random shit
    // so your app doesn't complain
    for (int i = 0; i < argc; i++) {
      if (strcmp(argv[i], "--danger") == 0) {
        danger = 1;
        break;
      }
    }
  }
#ifdef _WIN32
  dataLoc = getenv("APPDATA");
  windows = true;
#else
  dataLoc = getenv("HOME");
  windows = false;
#endif
  if (!fs::exists(fs::path(dataLoc) / (windows ? "DRAWscii" : ".DRAWscii")))
  { // somehow this works
    if (!fs::create_directories(fs::path(dataLoc) / (windows ? "DRAWscii" : ".DRAWscii")))
    {
      cout << "\x1b[1;31merror:\x1b[39m creating data folder for DRAWscii failed and app will exit (try running as " << (windows ? "administrator" : "superuser") << "?)\x1b[0m\n";
      exit(1);
    }
  }
  fs::path dciData = fs::path(dataLoc) / (windows ? "DRAWscii" : ".DRAWscii");
  cout << "welcome to\n";
  while (true)
  {
    if (fs::exists(dciData / "settings" / "logodisabled"))
    {
      cout << "DRAWscii\n";
    }
    else
    {
      cout << "┏━━━┳━━━┳━━━┳┓┏┓┏┓a greg project\n"
           << "┗┓┏┓┃┏━┓┃┏━┓┃┃┃┃┃┃made in C++\n"
           << " ┃┃┃┃┗━┛┃┃ ┃┃┃┃┃┃┣━━┳━━┳┳┓\n"
           << " ┃┃┃┃┏┓┏┫┗━┛┃┗┛┗┛┃━━┫┏━╋╋┫\n"
           << "┏┛┗┛┃┃┃┗┫┏━┓┣┓┏┓┏╋━━┃┗━┫┃┃\n"
           << "┗━━━┻┛┗━┻┛ ┗┛┗┛┗┛┗━━┻━━┻┻┛\n"
           << (danger ? "\x1b[1;31mDANGER MODE\x1b[0m\n" : "blindpaint, refurbished.\n");
    }
    cout << "(1) new canvas\n"
         << "(2) info\n"
         << "(3) settings\n"
         << "(0) exit\n"
         << ">> ";
    unsigned int menu_in;
    cin >> menu_in;
    if (menu_in == 1)
    {
      clear();
      cout << "enter amount of rows" << (!danger ? " (don\'t get greedy!)" : "") << "\n>> ";
      unsigned int canvasW;
      cin >> canvasW;
      clear();
      if (canvasW > (unsigned int)256 && danger == false) {
        cout << "\x1b[1;31merror:\x1b[39m canvas widths above 256 will not be accepted unless --danger argument is passed\x1b[0m\n";
        break;
      }
      cout << "enter amount of columns" << (!danger ? " (don\'t get greedy!)" : "") << "\n>> ";
      unsigned int canvasH;
      cin >> canvasH;
      clear();
      if (canvasH > 256 && danger == false) {
        cout << "\x1b[1;31merror:\x1b[39m canvas heights above 256 will not be accepted unless --danger argument is passed\x1b[0m\n";
        break;
      }
      // i still don't understand how this works,
      // and i think i need to make myself a visual
      // explanation of it (it's confusing for me)
      // UPDATE: i understand it now, kinda...
      vector<vector<unsigned int>> canvas(canvasW, vector<unsigned int>(canvasH, 0));
      clear();
      while (true)
      {
        for (vector<unsigned int> row : canvas)
        {
          for (unsigned int col : row)
          {
            cout << (col ? "# " : "  ");
          }
          cout << "\n";
        }
        sep();
        cout << "actions:\n"
             << "(1) paint pixel\n"
             << "(2) fill region\n"
             << "(0) save & exit\n"
             << ">> ";
        int actions_in;
        cin >> actions_in;
        if (actions_in == 1)
        {
          clear();
          cout << "enter row (starting from 0):\n>> ";
          int posX;
          cin >> posX;
          // horrid
          posX = max(0, min((int)canvasW - 1, posX));
          clear();
          cout << "enter column (starting from 0):\n>> ";
          int posY;
          cin >> posY;
          // horrid
          posY = max(0, min((int)canvasH - 1, posY));
          clear();
          cout << "enter value (0 or 1):\n>> ";
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
          // reminds me of nested if-statements
          clear();
          cout << "enter row 1 (starting from 0):\n>> ";
          int x1;
          cin >> x1;
          clear();
          cout << "enter column 1 (starting from 0):\n>> ";
          int y1;
          cin >> y1;
          clear();
          cout << "enter row 2 (starting from 0):\n>> ";
          int x2;
          cin >> x2;
          clear();
          cout << "enter column 2 (starting from 0):\n>> ";
          int y2;
          cin >> y2;
          clear();
          cout << "enter value (0 or 1):\n>> ";
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
          x2 = min((int)canvasW - 1, x2);
          y1 = max(0, y1);
          y2 = min((int)canvasH - 1, y2);

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
          cout << "saving...";
          time_t currtime = chrono::system_clock::to_time_t(chrono::system_clock::now());
          std::ofstream file(filename);
          if (!file.is_open())
          {
            clear();
            cout << "\x1b[1;31merror:\x1b[39m exporting canvas to file " << filename << " failed\x1b[0m\n";
            sep();
            break;
          }
          file << "(tip: use a mono font like Hack for the best results!)\n";
          for (vector<unsigned int> row : canvas)
          {
            for (unsigned int pixel : row)
            {
              file << (pixel ? "# " : "  ");
            }
            file << "\n";
          }
          
          file << "time created: " << ctime(&currtime) << "made by: a very awesome person\n";
          clear();
          cout << "successfully exported canvas to " << filename << endl;
          sep();
          break;
        }
        else
        {
          clear();
          cout << "\x1b[1;31merror:\x1b[39m no option made for input " << actions_in << "\x1b[0m\n";
          sep();
        }
      }
    }
    else if (menu_in == 2)
    {
      clear();
      cout << "DRAWscii " << VERSION << " / blindpaint 2.0+\n"
           << "blindpaint, refurbished.\n"
           << "licensed under MIT license\n"
           << (danger ? "running in danger mode, do not complain in issues if your PC bursts into flames\n" : "")
           << "any changes YOU make are YOURS & YOURS ONLY\n"
           << "this program was developed in C++; any other DRAWscii "
           << "version made in anything but C++ is either a fan-made, or malicious.\n";
      sep();
    }
    else if (menu_in == 3)
    {
      if (!fs::exists(dciData / "settings"))
      {
        if (!fs::create_directories(dciData / "settings"))
        {
          cout << "\x1b[1;31merror:\x1b[39m creating settings folder for DRAWscii failed (try running as " << (windows ? "administrator" : "superuser") << "?)\x1b[0m\n";
          break;
        }
      }
      clear();
      while (true)
      {
        cout << "options:\n"
        << "(1) disable ASCII logo ["
        << (fs::exists(dciData / "settings" / "logodisabled") ? "X" : " ") << "]\n"
        << "(0) exit\n"
        << ">> ";
        int options_in;
        cin >> options_in;
        if (options_in == 1)
        {
          clear();
          // this, too, somehow works
          if (fs::exists(dciData / "settings" / "logodisabled"))
          {
            if (!fs::remove(dciData / "settings" / "logodisabled"))
            {
              cout << "\x1b[1;31merror:\x1b[39m disabling setting failed (try running as " << (windows ? "administrator" : "superuser") << "?)\x1b[0m\n";
            }
          }
          else
          {
            ofstream option(dciData / "settings" / "logodisabled");
            if (!option.is_open())
            {
              cout << "\x1b[1;31merror:\x1b[39m enabling setting failed (try running as " << (windows ? "administrator" : "superuser") << "?)\x1b[0m\n";
            }
            option.close();
          }
        }
        else if (options_in == 0)
        {
          clear();
          break;
        }
        else
        {
          clear();
          cout << "\x1b[1;31merror:\x1b[39m no option made for input " << options_in << "\x1b[0m\n";
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
    else // I love comically large if-else-statements! :mhm:
    {
      clear();
      cout << "\x1b[1;31merror:\x1b[39m no option made for input " << menu_in << "\x1b[0m\n";
      sep();
    }
  }
  return 0;
}

// that's the end of the source code

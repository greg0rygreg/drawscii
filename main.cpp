#include <chrono>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "libmenu.hpp"
using namespace std;
using namespace libmenu;
namespace fs = filesystem;

int main(int argc, char** argv)
{
  util::clear();
  string VERSION = "1.4";
  string dataLoc;
  bool windows = true; // let's assume it's windows if for whatever reason the check at line 32 fails
  bool danger = false;
  if (argc > 1) {
    // this used to say that i hate
    // doing useless strcmp shit but
    // then i learned C and no longer
    // hate this
    for (int i = 0; i < argc; i++) {
      if (strcmp(argv[i], "--danger") == 0) {
        danger = true;
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
      error::error(string("creating data folder for DRAWscii failed and app will exit (try running as ") + (windows ? "administrator" : "root") + "?)");
      exit(1);
    }
  }
  fs::path dciData = fs::path(dataLoc) / (windows ? "DRAWscii" : ".DRAWscii");
  Menu dciMenu("DRAWscii", VERSION, {"new canvas", "info", "settings"});
  Menu actionsMenu("actions", "", {"paint pixel", "fill region"}, "save & exit");
  cout << "welcome to\n";
  while (true)
  {
    if (!(fs::exists(dciData / "settings" / "logodisabled")))
    {
      cout << "┏━━━┳━━━┳━━━┳┓┏┓┏┓a greg project\n"
           << "┗┓┏┓┃┏━┓┃┏━┓┃┃┃┃┃┃made in C++\n"
           << " ┃┃┃┃┗━┛┃┃ ┃┃┃┃┃┃┣━━┳━━┳┳┓\n"
           << " ┃┃┃┃┏┓┏┫┗━┛┃┗┛┗┛┃━━┫┏━╋╋┫\n"
           << "┏┛┗┛┃┃┃┗┫┏━┓┣┓┏┓┏╋━━┃┗━┫┃┃\n"
           << "┗━━━┻┛┗━┻┛ ┗┛┗┛┗┛┗━━┻━━┻┻┛\n"
           << (danger ? "\x1b[1;31mDANGER MODE\x1b[0m\n" : "blindpaint, refurbished.\n");
    }
    int menu_in;
    dciMenu.printAndGetInput(menu_in, (fs::exists(dciData / "settings" / "logodisabled") ? true : false));
    if (menu_in == 1)
    {
      util::clear();
      cout << "enter amount of rows" << (!danger ? " (don\'t get greedy!)" : "") << "\n>> ";
      unsigned int canvasW;
      cin >> canvasW;
      util::clear();
      if (canvasW > 256 && danger == false) {
        error::error("canvas widths above 256 will not be accepted unless --danger argument is passed");
        break;
      }
      cout << "enter amount of columns" << (!danger ? " (don\'t get greedy!)" : "") << "\n>> ";
      unsigned int canvasH;
      cin >> canvasH;
      util::clear();
      if (canvasH > 256 && danger == false) {
        error::error("canvas heights above 256 will not be accepted unless --danger argument is passed");
        break;
      }
      // i still don't understand how this works,
      // and i think i need to make myself a visual
      // explanation of it (it's confusing for me)
      // UPDATE: i understand it now, kinda...
      vector<vector<unsigned int>> canvas(canvasW, vector<unsigned int>(canvasH, 0));
      util::clear();
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
        util::sep();
        int actions_in;
        actionsMenu.printAndGetInput(actions_in, 1, 0);
        if (actions_in == 1)
        {
          util::clear();
          cout << "enter row (starting from 0):\n>> ";
          int posX;
          cin >> posX;
          // horrid
          posX = max(0, min((int)canvasW - 1, posX));
          util::clear();
          cout << "enter column (starting from 0):\n>> ";
          int posY;
          cin >> posY;
          // horrid
          posY = max(0, min((int)canvasH - 1, posY));
          util::clear();
          cout << "enter value (0 or 1):\n>> ";
          int paintVal;
          cin >> paintVal;
          paintVal = max(0, min(1, paintVal));
          canvas[posX][posY] = paintVal;
          util::clear();
          cout << "successfully painted pixel " << posX << "," << posY << " with " << paintVal << endl;
          util::sep();
        }
        else if (actions_in == 2)
        {
          // reminds me of nested if-statements
          util::clear();
          cout << "enter row 1 (starting from 0):\n>> ";
          int x1;
          cin >> x1;
          util::clear();
          cout << "enter column 1 (starting from 0):\n>> ";
          int y1;
          cin >> y1;
          util::clear();
          cout << "enter row 2 (starting from 0):\n>> ";
          int x2;
          cin >> x2;
          util::clear();
          cout << "enter column 2 (starting from 0):\n>> ";
          int y2;
          cin >> y2;
          util::clear();
          cout << "enter value (0 or 1):\n>> ";
          int val;
          cin >> val;
          val = max(0, min(1, val));
          util::clear();
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
          util::sep();
        }
        else if (actions_in == 0)
        {
          util::clear();
          cin.ignore();
          string filename;
          cout << "enter file name:\n>> ";
          getline(cin, filename);
          time_t currtime = chrono::high_resolution_clock::to_time_t(chrono::system_clock::now());
          std::ofstream file(filename);
          if (!file.is_open())
          {
            util::clear();
            cout << "\x1b[1;31merror:\x1b[39m exporting canvas to file " << filename << " failed\x1b[0m\n";
            util::sep();
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
          util::clear();
          cout << "successfully exported canvas to " << filename << endl;
          util::sep();
          file.close();
          break;
        }
        else
        {
          util::clear();
          error::inputErr(actions_in);
          util::sep();
        }
      }
    }
    else if (menu_in == 2)
    {
      util::clear();
      cout << dciMenu.getFormattedVersion() << " / blindpaint 2.0+\n"
           << "blindpaint, refurbished.\n"
           << "licensed under MIT license\n"
           << (danger ? "running in danger mode, do not complain in issues if your PC bursts into flames\n" : "")
           << "any changes YOU make are YOURS & YOURS ONLY\n"
           << "this program was developed in C++; any other DRAWscii "
           << "version made in anything but C++ is either a fan-made, or malicious.\n";
      util::sep();
    }
    else if (menu_in == 3)
    {
      if (!fs::exists(dciData / "settings"))
      {
        if (!fs::create_directories(dciData / "settings"))
        {
          error::error(string("creating settings folder for DRAWscii failed - try running as ") + (windows ? "administrator?" : "root?"));
          break;
        }
      }
      util::clear();
      while (true)
      {
        // will remake this once i have more time (it's 8:35 PM and i must rest at 9:00 PM)
        cout << "options:\n"
        << "(1) disable ASCII logo ["
        << (fs::exists(dciData / "settings" / "logodisabled") ? "X" : " ") << "]\n"
        << "(0) exit\n"
        << ">> ";
        int options_in;
        cin >> options_in;
        if (options_in == 1)
        {
          util::clear();
          // this, too, somehow works
          if (fs::exists(dciData / "settings" / "logodisabled"))
          {
            if (!fs::remove(dciData / "settings" / "logodisabled"))
            {
              error::error(string("disabling setting failed - try running as ") + (windows ? "administrator?" : "root?"));
            }
          }
          else
          {
            ofstream option(dciData / "settings" / "logodisabled");
            if (!option.is_open())
            {
              error::error(string("enabling setting failed - try running as ") + (windows ? "administrator?" : "root?"));
            }
            option.close();
          }
        }
        else if (options_in == 0)
        {
          util::clear();
          break;
        }
        else
        {
          util::clear();
          error::inputErr(options_in);
          util::sep();
        }
      }
    }
    else if (menu_in == 0)
    {
      util::clear();
      cout << "bye!\n";
      exit(0);
    }
    else // I love comically large if-else-statements! :mhm:
    {
      util::clear();
      error::inputErr(menu_in);
      util::sep();
    }
  }
  return 0;
}

// that's the end of the source code
// compilation:
// windows: g++ -o drawscii.exe main.cpp libmenu.cpp
// linux: g++ -o drawscii main.cpp libmenu.cpp
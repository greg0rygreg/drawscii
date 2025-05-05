#ifndef libmenu_HPP
#define libmenu_HPP
#include <string>
#include <vector>

namespace libmenu {
    //contains information about your menu
    class Menu {
        public:
        //name of the menu
        std::string name;
        //version of the menu
        std::string version;
        //options of the menu
        std::vector<std::string> options;
        //menu configurator/constructor
        Menu(std::string name, std::string version, std::vector<std::string> options, std::string exitText);
        //menu configurator/constructor
        Menu(std::string name, std::string version, std::vector<std::string> options);
        /*print the main menu and get user input and put it
        on `optionInt`
        `bool printName`: if 1, print the name of the app defined
        in your `libmenu::Menu.name` and version in `libmenu::Menu.version`
        
        else, don't print the name and version of the app

        `bool includeVersion`: defines if you want to include `libmenu::Menu.version`
        on the name "header", useful for submenus
        */
        void printAndGetInput(int &optionInt, bool printName, bool includeVersion);
        /*print the main menu and get user input and put it
        on `optionInt`
        `bool printName`: if 1, print the name of the app defined
        in your `libmenu::Menu.name` and version in `libmenu::Menu.version`
        
        else, don't print the name and version of the app*/
        void printAndGetInput(int &optionInt, bool printName);
        /*get a formatted string of the name and version of the menu

        `bool includeVersion`: defines if you want to include `libmenu::Menu.version`,
        useful for submenus
        */
        std::string getFormattedVersion(bool includeVersion);
        //get a formatted string of the name and version of the menu
        std::string getFormattedVersion();
        private:
        std::string exitText = "exit";
    };
    namespace util {
        //clear the screen for the next operation
        void clear();
        //seperate the screen by exactly 75 hyphens
        void sep();
    }
    namespace error {
        /*print an error incase of input invalidation or something
        else*/
        void error(std::string info);
        /*print a warning incase something goes wrong and an error
        doesn't fit*/
        void warning(std::string info);
        //print an input error
        void inputErr(int input);
    }
}

#endif // libmenu_HPP
// (no compile)
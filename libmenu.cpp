#include "libmenu.hpp"
#include <iostream>
#include <string>
#include <stdlib.h>

namespace libmenu {
    Menu::Menu(std::string name, std::string version, std::vector<std::string> options, std::string exitText) {
        this->name = name;
        this->version = version;
        this->options = options;
        this->exitText = exitText;
    }
    Menu::Menu(std::string name, std::string version, std::vector<std::string> options) {
        this->name = name;
        this->version = version;
        this->options = options;
    }
    SelMenu::SelMenu(std::string action, std::vector<std::string> options, std::string cancelText) {
        this->action = action;
        this->options = options;
        this->cancelText = cancelText;
    }
    SelMenu::SelMenu(std::string action, std::vector<std::string> options) {
        this->action = action;
        this->options = options;
    }
    void Menu::printAndGetInput(int &optionInt, bool printName, bool includeVersion) {
        if (printName) {
            std::cout << this->getFormattedVersion(includeVersion) << "\n";
        }
        for (long unsigned i = 0; i < this->options.size(); i++) {
            std::cout << "(" << i+1 << ") " << this->options[i] << "\n";
        }
        std::cout << "(0) " << this->exitText << "\n";
        std::cout << "\n(?) >> ";
        std::cin >> optionInt;
    }
    void SelMenu::printAndGetInput(int &optionInt, bool printAction) {
        if (printAction) {
            std::cout << this->action << "\n";
        }
        for (long unsigned i = 0; i < this->options.size(); i++) {
            std::cout << "(" << i+1 << ") " << this->options[i] << "\n";
        }
        std::cout << "(0) " << this->cancelText << "\n";
        std::cout << "\n(?) >> ";
        std::cin >> optionInt;
    }
    void Menu::printAndGetInput(int &optionInt, bool printName) {
        this->printAndGetInput(optionInt, printName, 1);
    }
    std::string Menu::getFormattedVersion(bool includeVersion) {
        return this->name + (includeVersion ? " v. " + this->version : ""); // python moment
    }
    std::string Menu::getFormattedVersion() {
        return this->getFormattedVersion(1);
    }
    namespace util {
        void clear() {
            std::cout << "\x1b[2J\x1b[H";
        }
        void sep() {
            std::cout << std::string(75, '=') << "\n";
        }
    }
    namespace error {
        void error(std::string info) {
            // i love unoptimizing things
            std::cout << "\x1b[1;31merror:\x1b[0m\x1b[1m " << info << "\x1b[0m\n";
        }
        void warning(std::string info) {
            std::cout << "\x1b[1;33mwarning:\x1b[0m\x1b[1m " << info << "\x1b[0m\n";
        }
        void inputErr(int input) {
            error("no option made for input " + std::to_string(input));
        }
    }
}

// use make
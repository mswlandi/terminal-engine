#include <SFML/Graphics.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include <ncurses.h>

#if !defined(TERMINAL_HPP)
#define TERMINAL_HPP

#define WINDOW_POS_DISPLACEMENT_X -10 // weird Xlib thing, might change at any moment or depending on the system
#define WINDOW_POS_DISPLACEMENT_Y -8
#define TERMINAL_WINDOW_TOP_BAR 24 // vertical size of the terminal window's title bar
#define TERMINAL_WINDOW_HELP_BAR 32 // vertical size of the terminal window's help bar
#define CHARACTER_SIZE_X 8 // might want to dinamically calculate this
#define CHARACTER_SIZE_Y 17 // might want to dinamically calculate this

class Terminal
{
    public:
        sf::Vector2i windowPosition;
        sf::Vector2i terminalSize;

        Terminal();
        ~Terminal();
        void RefreshTerminal();
        void ClearTerminal();
        void PutCharacter(char ch, sf::Vector2i pos);
        void DrawSquare(char ch, sf::Vector2i pos, int size);
        char GetChar(sf::Vector2i pos);
        sf::Vector2i getWindowPosition();
        sf::Vector2i getWindowSize();
        sf::Vector2i getMousePosition();
        sf::Vector2i getMouseCharacterPosition();

    private:
        Window XlibWindow;
        Window XlibParentOfFocusedWindow;
        Window XlibRootWindow;
        XWindowAttributes XlibAttrributes;
        Display* XlibDisplay;
};

#endif
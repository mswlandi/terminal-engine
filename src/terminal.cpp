#include <terminal.hpp>

Terminal::Terminal()
{
    // NCurses
    initscr();
    getmaxyx(stdscr, terminalSize.x, terminalSize.y);
    curs_set(0);

    // Xlib
    XlibDisplay = XOpenDisplay(NULL);
    int revert;

    XGetInputFocus(XlibDisplay, &XlibWindow, &revert);

    Window* childrenWindows;
    unsigned int numberOfChildren;

    bool stop = false;
    while (!stop)
    {
        if (XQueryTree(XlibDisplay, XlibWindow, &XlibRootWindow, &XlibParentOfFocusedWindow, &childrenWindows, &numberOfChildren) == 0)
        {
            throw "getToplevelParent XQueryTree Error";
        }
        if (childrenWindows)
        {
            XFree(childrenWindows);
        }
        if (XlibWindow == XlibRootWindow || XlibParentOfFocusedWindow == XlibRootWindow)
        {
            XlibParentOfFocusedWindow = XlibWindow;
            stop = true;
        }
        else
        {
            XlibWindow = XlibParentOfFocusedWindow;
        }
    }

    // Cursor cursor = XCreateFontCursor(XlibDisplay, 0);
    // XDefineCursor(XlibDisplay, finalChild, cursor);
    // XDefineCursor(XlibDisplay, *childrenWindows, cursor);
}

Terminal::~Terminal()
{
    std::cout << "fim" << std::endl;
    endwin();
}

// To be called before all draws
void Terminal::ClearTerminal()
{
    erase();
    getmaxyx(stdscr, terminalSize.y, terminalSize.x);
}

// To be called after all draws
void Terminal::RefreshTerminal()
{
    refresh();
}

void Terminal::PutCharacter(char ch, sf::Vector2i pos)
{
    if (pos.x >= 0 && pos.x <= terminalSize.x &&
        pos.y >= 0 && pos.y <= terminalSize.y)
    {
        mvaddch(pos.y, pos.x, ch);
    }
}

void Terminal::DrawRectangle(char ch, sf::Vector2i pos, sf::Vector2i size)
{
    for (int x = pos.x - size.x/2; x < pos.x + size.x/2 + size.x%2; x++)
    {
        for (int y = pos.y - size.y/2; y < pos.y + size.y/2 + size.y%2; y++)
        {
            PutCharacter(ch, { x, y });
        }
    }
}

// char Terminal::GetChar(sf::Vector2i pos)
// {
//     int ch = mvwinch(stdscr, pos.x, pos.y) & A_CHARTEXT;
// }

sf::Vector2i Terminal::getWindowPosition()
{
    int x, y;
    Window child;

    // XTranslateCoordinates(XlibDisplay, XlibWindow, XlibRootWindow, 0, 0, &x, &y, &child);
    XGetWindowAttributes(XlibDisplay, XlibWindow, &XlibAttrributes);
    // int absolute_pos_x = x - XlibAttrributes.x;
    // int absolute_pos_y = y - XlibAttrributes.y;

    return sf::Vector2i(XlibAttrributes.x - WINDOW_POS_DISPLACEMENT_X, XlibAttrributes.y - WINDOW_POS_DISPLACEMENT_Y);
}

sf::Vector2i Terminal::getWindowSize()
{
    XGetWindowAttributes(XlibDisplay, XlibParentOfFocusedWindow, &XlibAttrributes);
    int width = XlibAttrributes.width;
    int height = XlibAttrributes.height;

    return sf::Vector2i(width, height);
}

sf::Vector2i Terminal::getMousePosition()
{
    sf::Vector2i global = sf::Mouse::getPosition();
    sf::Vector2i windowPos = this->getWindowPosition();
    return sf::Vector2i(global.x - windowPos.x, global.y - windowPos.y - TERMINAL_WINDOW_TOP_BAR - TERMINAL_WINDOW_HELP_BAR);
}

sf::Vector2i Terminal::getMouseCharacterPosition()
{
    sf::Vector2i mousePos = this->getMousePosition();
    return sf::Vector2i(mousePos.x / CHARACTER_SIZE_X, mousePos.y / CHARACTER_SIZE_Y);
}
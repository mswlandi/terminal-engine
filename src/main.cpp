#include <iostream>

#include <terminal.hpp>

int main()
{
    Terminal terminal;

    while (true)
    {
        sf::Vector2i windowPosition = terminal.getWindowPosition();
        terminal.ClearTerminal();

        sf::Vector2i mouseRelative = terminal.getMousePosition();
        sf::Vector2i mouseCharacterPos = terminal.getMouseCharacterPosition();
        sf::Vector2i windowSize = terminal.getWindowSize();

        sf::Vector2i charPos;

        if (mouseCharacterPos.x < 0)
        {
            charPos.x = 0;
        }
        else if (mouseCharacterPos.x > terminal.terminalSize.x)
        {
            charPos.x = terminal.terminalSize.x;
        }
        else
        {
            charPos.x = mouseCharacterPos.x;
        }

        if (mouseCharacterPos.y < 0)
        {
            charPos.y = 0;
        }
        else if (mouseCharacterPos.y > terminal.terminalSize.y)
        {
            charPos.y = terminal.terminalSize.y;
        }
        else
        {
            charPos.y = mouseCharacterPos.y;
        }

        // terminal.PutCharacter('x', charPos);
        terminal.DrawSquare('X', charPos, 10);

        // mvprintw(terminal.terminalSize.x / 2, terminal.terminalSize.y / 2, "%d %d", windowSize.x, windowSize.y);
        mvprintw(terminal.terminalSize.x / 2, terminal.terminalSize.y / 2, "%d %d", mouseCharacterPos.x, mouseCharacterPos.y);
        // mvprintw(terminal.terminalSize.x / 2, terminal.terminalSize.y / 2, "%d %d", mouseRelative.x, mouseRelative.y);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
        {
            break;
        }

        terminal.RefreshTerminal();
    }

    return 0;
}
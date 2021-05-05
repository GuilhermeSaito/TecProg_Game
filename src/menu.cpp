#include "menu.h"

Menu::Menu(sf::RenderWindow *window)
{
    this->window = window;
}
Menu::~Menu()
{
    window = NULL;
}

void Menu::setWindow(sf::RenderWindow* w)
{
    this->window = w;
}
#pragma once

#include "../Game.hpp"
#include "../Interface.hpp"
#include "../Menu.hpp"

class MenuInterface : public Interface {
public:
    MenuInterface(Game* game)
    {
        MenuInterface::game = game;
        MenuInterface::menu = new Menu();
    }

    ~MenuInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

private:
    Game* game;

    Menu* menu;
};

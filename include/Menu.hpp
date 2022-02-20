#pragma once

class Menu {
public:
    Menu();

    ~Menu() = default;

    void update();

    void drawHome();

    void drawRules();

private:
    SDL_Texture* homeBackground, *rulesBackground;
};

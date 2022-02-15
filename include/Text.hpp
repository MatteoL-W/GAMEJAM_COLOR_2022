#pragma once

#include <SDL2/SDL_ttf.h>
#include <iostream>

class Text {
public:
    Text() {}

    ~Text() = default;

    void create(std::string text, SDL_Color color, std::string fontName);

    void draw();

    void changeText(std::string newText);

    void changeColor(SDL_Color newColor);

    void changeDestRect(int x, int y);

    void changeFont(std::string name, int size);

    int getSize() const { return size; };

    SDL_Rect getDestRect() { return destRect; };

    std::string getText() { return message; };

    int getX() const { return x; };

    void setX(const int newX) { x = newX; };

    int getY() const { return y; };

    void setY(const int newY) { y = newY; };

private:
    std::string message;

    TTF_Font* font;

    SDL_Surface* surface;

    SDL_Color color;

    SDL_Texture* texture;

    SDL_Rect destRect;

    int size = 24;

    int x = 0;

    int y = 0;
};

TTF_Font* createFont(Text* text, std::string fontName);

SDL_Rect createDestRect(TTF_Font* font, std::string text, int x, int y);

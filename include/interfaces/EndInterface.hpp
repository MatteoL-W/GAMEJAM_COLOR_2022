#pragma once

#include "../Game.hpp"
#include "../Interface.hpp"
#include "../End.hpp"

class EndInterface : public Interface {
public:
    explicit EndInterface(Game* game)
        : game(game), end(new End())
    {
    }

    ~EndInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

private:
    Game* game;

    End* end;
};

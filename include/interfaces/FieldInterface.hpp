#pragma once

#include "../Game.hpp"
#include "../Interface.hpp"
#include "../Field.hpp"

class FieldInterface : public Interface {
public:
    explicit FieldInterface(Game* game)
        : game(game), field(new Field())
    {
    }

    ~FieldInterface() = default;

    void handleEvents() override;

    void update() override;

    void render() override;

private:
    Game* game;

    Field* field;
};

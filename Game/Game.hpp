#pragma once

#include "Tree/Graphics.hpp"
#include "Tree/GameState.hpp"
#include "Tree/Timer.hpp"
#include "Tree/Shufflebag.hpp"

#include "World.hpp"
#include "Controller.hpp"

class Game : public Tree::GameState {
public:
    Game();

    bool HandleEvent( sf::Event &e );

    void Update( float dt );
    void Draw();
private:
    boost::shared_ptr<World> world;
    boost::shared_ptr<Controller> girl_controller;
};


#include "Tree/Game.hpp"#include "Tree/Settings.hpp"#include "Util.hpp"float Tree::GetFPS(){    return GAME->GetFPS();}const sf::Input &Tree::GetInput(){    return GAME->GetInput();}extern const int Tree::GetWindowWidth(){    return Tree::GetSettings()->GetValue<int>( "video_screen_width" );}extern const int Tree::GetWindowHeight(){    return Tree::GetSettings()->GetValue<int>( "video_screen_height" );}
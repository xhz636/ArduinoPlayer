#include "common.h"
#include "game_simulator.h"
#include "game.h"
void game_start()
{
  game_playing = true;
  game_start_time = millis();
  while(game_playing)
  {
    
  }
  game_end_time = millis();
  game_menu_point = 0;
  show_game_menu();
}


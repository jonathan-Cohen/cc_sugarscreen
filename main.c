#include <stdio.h>

#include "game.h"

int main()
{
    t_game *g = game_init();

    game_loop(g);
    return 0;
}

void game_loop(t_game *g)
{
  int p_hand = 0;

  for (; !is_game_finished(g);) {
    print_player_coins(g->player);
    broker_new_hand(g);
    player_new_hand(g);
    print_player_hand(g->player);
    p_hand = sum_player_hand(g->player);
    broker_place_bet(g);
    player_place_bet(g);
    print_turn_results(g, p_hand);
    p_hand += player_ask_cards(g);
    printf("p_hand:%d\n", p_hand);
    if (p_hand > 21) {
      player_breakthrough(g); // Le joueur dépasse 21
      player_lost(g); // Le joueur perd
    } else if (p_hand == 21) {
      player_jackpot(g); // Le joueur fait 21
      player_win(g); // Le joueur gagne
    }
    game_end(g);
  }
}
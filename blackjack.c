#include <stdlib.h>
#include "cards.h"

#define DEFAULT_CASH 1000

typedef struct Blackjack_Gamestate_t Blackjack_Gamestate_t;
struct Blackjack_Gamestate_t
{
    Deck_t *deck;
    Deck_t *dealer_hand;
    Deck_t *player_hand;
    int cash;
    int pot;
    int dealer_score;
    int player_score;
};

// 1. INITIALIZATION
    // init full deck
    // init empty dealer's hand
    // init empty player's hand
    // 2. BETTING
    // check for empty cash
    // print game over if no cash
    // print message asking the player to bet
    // 3. INITIAL DEAL
    // draw 2 cards for each player
    // 4. BLACKJACK CHECK
    // if blackjack end game
    // 5. HIT OR STAND
    // 6. DEALR"S DRAW
    // 7. RESET

Blackjack_Gamestate_t * init_blackjack_game(){
    Blackjack_Gamestate_t *gamestate = malloc(sizeof(Blackjack_Gamestate_t));
    //TODO: check for failure
    gamestate->deck = init_full_deck();
    gamestate->dealer_hand = init_empty_deck();
    gamestate->player_hand = init_empty_deck();
    gamestate->cash = DEFAULT_CASH;
    gamestate->pot = 0;
    gamestate->dealer_score = 0;
    gamestate->player_score = 0;

}

void end_game(Blackjack_Gamestate_t *gamestate){
    free_deck(gamestate->deck);
    free_deck(gamestate->dealer_hand);
    free_deck(gamestate->player_hand);
    free(gamestate);
}
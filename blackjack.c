#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "cards.h"

#define DEFAULT_CASH 1000
#define MIN_CASH 10
#define N_CARDS 52
#define ERR 0
#define OK 1
#define ERR_SIZE 256



typedef struct Blackjack_Gamestate_t Blackjack_Gamestate_t;
struct Blackjack_Gamestate_t
{
    int cash;
    int pot;
    int dealer_score;
    int player_score;
    Deck_t *deck;
    Deck_t *dealer_hand;
    Deck_t *player_hand;
    char err_msg[ERR_SIZE]; //contains a message describing the last error that occured
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
    //TODO: check for failure and return NULL
    gamestate->deck = init_full_deck();
    gamestate->dealer_hand = init_empty_deck();
    gamestate->player_hand = init_empty_deck();
    gamestate->cash = DEFAULT_CASH;
    gamestate->pot = 0;
    gamestate->dealer_score = 0;
    gamestate->player_score = 0;

    // init rand seed for random card draw
    srand(time(NULL));

    return gamestate;
}

int has_cash(Blackjack_Gamestate_t *gamestate){
    return (gamestate->cash >= MIN_CASH);
}

int player_bet(Blackjack_Gamestate_t *gamestate, int amount){
    if(amount == 0 && gamestate->pot > 0){
        return OK;
    }
    else if(amount > 0 && amount % 10 == 0 && amount <= gamestate->cash){
        gamestate->cash -= amount;
        gamestate->pot += amount;
        return OK;
    }
    strncpy(gamestate->err_msg, "[Betting] Amount to bet must be a non-negative integer divisible by 10", ERR_SIZE);
    return ERR;
}

void calculate_scores(Blackjack_Gamestate_t *gamestate){
    Card_t *p = gamestate->dealer_hand->head;
    bool has_ace = false;
    int score = 0;

    // Dealer
    while(p){
        uint8_t rank = p->data >> 4;
        if(rank > 10)
            rank = 10;
        if(rank == 1)
            has_ace = true;
        score += rank;
    }
    if(has_ace && score < 12){
        score += 10;
    }
    gamestate->dealer_score = score;

    // Player
    p = gamestate->player_hand->head;
    has_ace = false;
    score = 0;
    while(p){
        uint8_t rank = p->data >> 4;
        if(rank > 10)
            rank = 10;
        if(rank == 1)
            has_ace = true;
        score += rank;
    }
    if(has_ace && score < 12){
        score += 10;
    }
    gamestate->player_score = score;
}

void initial_deal(Blackjack_Gamestate_t *gamestate){
    // Draw 2 random cards for each player
    for (int i = 0; i < 2; i++)
    {
        Card_t *c = draw_at(gamestate->deck, rand() % gamestate->deck->len);
        addt_card(gamestate->dealer_hand, c);
        c = draw_at(gamestate->deck, rand() % gamestate->deck->len);
        addt_card(gamestate->player_hand, c);
    }
    calculate_scores(gamestate);
}

int is_blackjack(Blackjack_Gamestate_t *gamestate){
    return gamestate->player_score == 21;
}

void hit(Blackjack_Gamestate_t *gamestate){
    
}

void stand(Blackjack_Gamestate_t *gamestate){
    
}

void dealer_draw(Blackjack_Gamestate_t *gamestate){

}

void reset_cards(Blackjack_Gamestate_t *gamestate){

}

void end_game(Blackjack_Gamestate_t *gamestate){
    free_deck(gamestate->deck);
    free_deck(gamestate->dealer_hand);
    free_deck(gamestate->player_hand);
    free(gamestate);
}
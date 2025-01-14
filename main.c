#include <stdio.h>
#include <stdbool.h>
#include "cards.h"
#include "blackjack.h"


const char *welcome_msg = 
"\n\n\
+===============================================================+\n\
|          ░█▀▄░█░░░█▀█░█▀▀░█░█░▀▀█░█▀█░█▀▀░█░█░░░░█▀▀          |\n\
|          ░█▀▄░█░░░█▀█░█░░░█▀▄░░░█░█▀█░█░░░█▀▄░░░░█░░          |\n\
|          ░▀▀░░▀▀▀░▀░▀░▀▀▀░▀░▀░▀▀░░▀░▀░▀▀▀░▀░▀░▀░░▀▀▀          |\n\
+===============================================================+\n\
Welcome to Blackjack.c - a lightweight command-line game!\n\
Start game? [Y] for yes, any other key to quit...\n";

void print_stats(Blackjack_Gamestate_t *gamestate, bool hidden);

int main(void) {
    char user_choice;
    printf("%s", welcome_msg);
    scanf(" %c", &user_choice);
    if(user_choice == 'y' || user_choice == 'Y'){
        printf("\nOK - let's start!\n\n");
        Blackjack_Gamestate_t *game = init_blackjack_game();
        while(true){
            printf("You have %d in cash and a pot of %d from previous bets.\n\
                    How much are you willing to bet? ");
            
            break;
        }
    }

    printf("\nGoodbye!\n\n");
    return 0;
}

void print_stats(Blackjack_Gamestate_t *gamestate, bool hidden){
    printf("Player's hand: ");
    print_deck(gamestate->player_hand);
    printf("\nScore: %d \t Cash: %d \t Pot: %d\n\n",gamestate->player_score, gamestate->cash, gamestate->pot);

    printf("Dealer's hand: ");
    if(hidden){
        printf("?????");
        printf("\nScore: ??\n\n");
    }
    else{
        print_deck(gamestate->player_hand);
        printf("\nScore: %d\n\n", gamestate->dealer_score);
    }
}
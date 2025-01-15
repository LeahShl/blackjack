#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
        if(game == NULL){
            printf("ERROR: could not initiate game. Exiting...\n");
            exit(1);
        }
        while(true){
            if(game->state == STATE_GAME_OVER){
                printf("Out of cash! GAME OVER\n");
                break;
            }

            // Betting
            int bet;
            bool result;
            printf("You have %d in cash and a pot of %d from previous bets.\nHow much are you willing to bet? ", game->cash, game->pot);
            scanf("%d", &bet);
            result = player_bet(game, bet);
            while(!result){
                printf("\n%s\n\nBet again? ", game->err_msg);
                scanf("%d", &bet);
                result = player_bet(game, bet);
            }

            // Deal cards
            initial_deal(game);

            // Blackjack check
            print_stats(game, true);
            if(game->state == STATE_BLACKJACK){
                printf("\nBlackjack! Your win!\n");
                reset_cards(game);
            }
            // Hit or stand
            else{
                printf("\nHit or stand? [H]/[S]: ");
                scanf(" %c", &user_choice);
                while (user_choice != 'H' && user_choice != 'h' &&
                       user_choice != 'S' && user_choice != 's')
                {
                    printf("\nInvalid choice. Hit or stand? [H]/[S]: ");
                    scanf(" %c", &user_choice);
                }

                // Hit
                while(user_choice == 'H' || user_choice == 'h'){
                    hit(game);
                    print_stats(game, true);
                    if(game->state == STATE_PBUST){
                        printf("Busted! You lost your bet.\n");
                        reset_cards(game);
                        break;
                    }
                    else{
                        printf("\nHit or stand? [H]/[S]: ");
                        scanf(" %c", &user_choice);
                        while (user_choice != 'H' && user_choice != 'h' &&
                               user_choice != 'S' && user_choice != 's')
                        {
                            printf("\nInvalid choice. Hit or stand? [H]/[S]: ");
                            scanf(" %c", &user_choice);
                        }
                    }
                }

                // Stand
                if(user_choice == 'S' || user_choice == 's'){
                    dealer_draw(game);
                    print_stats(game, false);
                    if(game->state == STATE_DBUST){
                        printf("Dealer busted! You won!\n");
                        reset_cards(game);
                    }
                    else if(game->state == STATE_DWIN){
                        printf("Dealer won! You lost your bet.");
                        reset_cards(game);
                    }
                    else if(game->state == STATE_TIE){
                        printf("Tie!\n");
                        reset_cards(game);
                    }
                    else if (game->state == STATE_PWIN)
                    {
                        printf("You won!\n");
                        reset_cards(game);
                    }
                    
                    else{
                        printf("Gamestate error. Exiting...\n");
                        exit(1);
                    }
                }
            }

            break;
        }
        end_game(game);
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
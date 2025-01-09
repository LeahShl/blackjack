CFLAGS = -std=c99 -Wall -Wextra -pedantic

blackjack: main.o cards.o blackjack.o
	gcc $(CFLAGS) -g main.o cards.o blackjack.o -o blackjack

main.o: main.c
	gcc $(CFLAGS) -c -g main.c -o main.o

cards.o: cards.c
	gcc $(CFLAGS) -c -g cards.c -o cards.o

blackjack.o: blackjack.c
	gcc $(CFLAGS) -c -g blackjack.c -o blackjack.o

clean:
	rm -f main.o cards.o blackjack.o blackjack
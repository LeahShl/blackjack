blackjack: main.o cards.o
	gcc -g main.o cards.o -o blackjack

main.o: main.c
	gcc -c -g main.c -o main.o

cards.o: cards.c
	gcc -c -g cards.c -o cards.o

clean:
	rm -f main.o cards.o blackjack
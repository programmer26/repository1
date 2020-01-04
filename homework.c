#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct card_t
{
	int rank;
	int suit;
};

struct card_t draw(void) {
	struct card_t card;

	card.suit = rand() % 4;
	card.rank = rand() % 13;

	return card;
}

int hearts_count(struct card_t deck[], int size) {
	int cnt = 0;
	for(int i = 0; i < size; i++) {
		if(deck[i].suit == 2) cnt++;
	}
	return cnt;
}

void face_up(struct card_t* deck, int size) {
	int temp, temp2;
	//sorting the cards
	for(int i = 0; i < size; i++) {
		for(int j = i + 1; j < size; j++) {
			if(deck[i].rank > deck[j].rank) {
				//swap the rank
				temp = deck[i].rank;
				deck[i].rank = deck[j].rank;
				deck[j].rank = temp;
				//swap the suit
				temp2 = deck[i].suit;
				deck[i].suit = deck[j].suit;
				deck[j].suit = temp2;
			}
		}
	}
	//only unique cards
	for(int i = 0; i < size; i++) {
		int j;
		for(j = 0; j < i; j++) {
			if(deck[j].rank == deck[i].rank && deck[j].suit == deck[i].suit) break;
		}
		if(j == i)
		{
			switch(deck[i].rank)
			{
				case 0: printf("2 "); break;
				case 1: printf("3 "); break;
				case 2: printf("4 "); break;
				case 3: printf("5 "); break;
				case 4: printf("6 "); break;
				case 5: printf("7 "); break;
				case 6: printf("8 "); break;
				case 7: printf("9 "); break;
				case 8: printf("T "); break;
				case 9: printf("J "); break;
				case 10: printf("Q "); break;
				case 11: printf("K "); break;
				case 12: printf("A "); break;
			}
			switch(deck[i].suit)
			{
				case 0: printf("club\n"); break;
				case 1: printf("diamond\n"); break;
				case 2: printf("heart\n"); break;
				case 3: printf("spade\n"); break;
			}
		}
	}
}

int main(void) {
	struct card_t* deck = malloc(sizeof(struct card_t));
	srand(time(NULL));
	int cnt;

	for(cnt = 1, *deck = draw(); deck[cnt - 1].rank != 12 || deck[cnt - 1].suit != 3; cnt++) {
		deck = realloc(deck, sizeof(struct card_t) * (cnt + 1));
		deck[cnt] = draw();
	}

	face_up(deck, cnt);
	printf("Number of hearts: %d\n", hearts_count(deck, cnt));
	free(deck);

	return 0;
}

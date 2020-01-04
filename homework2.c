#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct movie
{
	char title[250];
	char director_name[30];
	int mins;
	int watch_time;
	float price_per_minute;
};

struct user_t
{
	char name[30];
	char email[50];
	int watched_movies;
	struct movie* p;
};

float get_bill(struct user_t user) {
	float bill = 0;
	for(int i = 0; i < user.watched_movies; i++) {
		bill += user.p[i].watch_time * user.p[i].price_per_minute;
	}
	return bill;
}

void user_details(struct user_t user) {
	if(user.watched_movies == 0)
	{
		printf("%s hasn't watched any movies, so his bill is 0$\n", user.name);
		return;
	}
	else
	{
		printf("%s has watched:\n", user.name);
		for(int i = 0; i < user.watched_movies; i++) {
			printf("\"%s\" - (%.2f$/min) %d minutes\n", user.p[i].title, user.p[i].price_per_minute, user.p[i].watch_time);
		}
		printf("Bill: %.2f$", get_bill(user));
	}
	printf("\n\n");
}

int main(void) {
	struct user_t user1 = {"John Newman", "example@example.com", 2};
	struct user_t user2 = {"Paul Walker", "example2@example.com", 2};
	user1.p = malloc(sizeof(struct movie) * user1.watched_movies);
	user2.p = malloc(sizeof(struct movie) * user2.watched_movies);

	strcpy(user1.p[0].title, "Fast and Furious 7");
	strcpy(user1.p[0].director_name, "James Wan");
	user1.p[0].mins = 140;
	user1.p[0].watch_time = 100;
	user1.p[0].price_per_minute = 1.33;

	strcpy(user1.p[1].title, "Bad Santa 2");
	strcpy(user1.p[1].director_name, "Mark Waters");
	user1.p[1].mins = 92;
	user1.p[1].watch_time = 10;
	user1.p[1].price_per_minute = 2.44;

	strcpy(user2.p[0].title, "The Expandables 3");
	strcpy(user2.p[0].director_name, "Patrick Hughes");
	user2.p[0].mins = 131;
	user2.p[0].watch_time = 110;
	user2.p[0].price_per_minute = 3;

	strcpy(user2.p[1].title, "Top Gun");
	strcpy(user2.p[1].director_name, "Tony Scott");
	user2.p[1].mins = 110;
	user2.p[1].watch_time = 110;
	user2.p[1].price_per_minute = 1.2;

	user_details(user1);
	user_details(user2);

	free(user1.p);
	free(user2.p);
	return 0;
}

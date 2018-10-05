#include "Global.h"

extern snake S1;

void Init()
{
	S1.food_x = 0;
	S1.food_y = 0;
	S1.bomb_x[100];
	S1.bomb_y[100];
	S1.length = 0;
	S1.speed = 0;
	S1.score = 0;
	S1.dir = 50;
	S1.key = 0;
	S1.status_on = 0;
	S1.num_of_bombs = 3;
	S1.food_crush_on = 0;
}

void food(void)
{
	int i;

	int food_crush_on = 0;
	int r = 0;
	gotoxy(MAP_ADJ_X, MAP_ADJ_Y + MAP_Y, " YOUR SCORE: ");
	printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", S1.score, S1.last_score, S1.best_score);

	while (1)
	{
		food_crush_on = 0;
		srand((unsigned)time(NULL) + r); // Creates random number table
		S1.food_x = (rand() % (MAP_X - 2)) + 1;
		S1.food_y = (rand() % (MAP_Y - 2)) + 1;

		for (i = 0; i<S1.length; i++)
		{
			if (S1.food_x == S1.x[i] && S1.food_y == S1.y[i]) // Check if the food is coordinated with the snake
			{
				food_crush_on = 1;
				r++;
				break;
			}

			else if (S1.food_x == S1.bomb_x[i] && S1.food_y == S1.bomb_y[i]) // Check if the bomb coordinates with the snake
			{
				food_crush_on = 1;
				r++;
				break;
			}
		}
		if (food_crush_on == 1) continue; // If coordinates, do the while statement again

		gotoxy(MAP_ADJ_X + S1.food_x, MAP_ADJ_Y + S1.food_y, "¡ß");
		S1.speed -= 3;
		break;
	}
}
 
// For Bomb
void bomb(void) // As new bombs are duplicated, others are fake bombs
{
	int i, j;
	int bomb_crush_on = 0;
	int r = 0;
	char* map; // Birngs the map by pointer of map array

	while (1)
	{
		bomb_crush_on = 0;
		srand((unsigned)time(NULL) + r); // Creates random number table

		for (j = 0; j < S1.num_of_bombs; j++)
		{
			S1.bomb_x[j] = (rand() % (MAP_X - 2)) + 1; // Random number between 1 ~ 28
			S1.bomb_y[j] = (rand() % (MAP_Y - 2)) + 1; // Random number between 1 ~ 18
		}
		for (j = 0; j < S1.num_of_bombs; j++)
		{
			for (i = 0; i < S1.length; i++)
			{
				if (S1.bomb_x[j] == S1.x[i] && S1.bomb_y[j] == S1.y[i]) // Check if the bomb coordinates with the snake
				{
					bomb_crush_on = 1;
					r++;
					break;
				}

				else if (S1.bomb_x[j] == S1.food_x && S1.bomb_y[j] == S1.food_y) // Check if the bomb coordinates with the snake
				{
					bomb_crush_on = 1;
					r++;
					break;
				}
			}
		}

		if (bomb_crush_on == 1) continue; // If coordinates, do the while statement again

		for (j = 0; j < S1.num_of_bombs; j++) // Creates bombs
			gotoxy(MAP_ADJ_X + S1.bomb_x[j], MAP_ADJ_Y + S1.bomb_y[j], "¡Þ");

		S1.speed -= 5;
		break;
	}
}


void status(void)
{
	int i;

	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y, "head= ");
	printf("%2d,%2d", S1.x[0], S1.y[0]);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 1, "food= ");
	printf("%2d,%2d", S1.food_x, S1.food_y);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 1, "bomb= "); // Shows the locations of real bombs
	for (i = 0; i < S1.num_of_bombs; i++) printf("(%2d,%2d) ", S1.bomb_x[i], S1.bomb_y[i]);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 2, "leng= ");
	printf("%2d", S1.length);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 3, "key= ");
	printf("%3d", S1.key);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 4, "stage= ");
	printf("%1d", S1.stage);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 5, "spd= ");
	printf("%3d", S1.speed);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 6, "score= ");
	printf("%3d", S1.score);
}
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

void food(struct _snake* snake)
{
	int i;

	int food_crush_on = 0;
	int r = 0;
	gotoxy(MAP_ADJ_X, MAP_ADJ_Y + MAP_Y, " YOUR SCORE: ");
	printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", snake->score, snake->last_score, snake->best_score);

	while (1)
	{
		food_crush_on = 0;
		srand((unsigned)time(NULL) + r); // Creates random number table
		snake->food_x = (rand() % (MAP_X - 2)) + 1;
		snake->food_y = (rand() % (MAP_Y - 2)) + 1;

		for (i = 0; i<snake->length; i++)
		{
			if (snake->food_x == snake->x[i] && snake->food_y == snake->y[i]) // Check if the food is coordinated with the snake
			{
				food_crush_on = 1;
				r++;
				break;
			}

			else if (snake->food_x == snake->bomb_x[i] && snake->food_y == snake->bomb_y[i]) // Check if the bomb coordinates with the snake
			{
				food_crush_on = 1;
				r++;
				break;
			}
		}
		if (food_crush_on == 1) continue; // If coordinates, do the while statement again

		gotoxy(MAP_ADJ_X + snake->food_x, MAP_ADJ_Y + snake->food_y, "¡ß");
		snake->speed -= 3;
		break;
	}
}
 
// For Bomb
void bomb(struct _snake* snake) // As new bombs are duplicated, others are fake bombs
{
	int i, j;
	int bomb_crush_on = 0;
	int r = 0;
	char* map; // Birngs the map by pointer of map array

	while (1)
	{
		bomb_crush_on = 0;
		srand((unsigned)time(NULL) + r); // Creates random number table

		for (j = 0; j < snake->num_of_bombs; j++)
		{
			snake->bomb_x[j] = (rand() % (MAP_X - 2)) + 1; // Random number between 1 ~ 28
			snake->bomb_y[j] = (rand() % (MAP_Y - 2)) + 1; // Random number between 1 ~ 18
		}
		for (j = 0; j < snake->num_of_bombs; j++)
		{
			for (i = 0; i < snake->length; i++)
			{
				if (snake->bomb_x[j] == snake->x[i] && snake->bomb_y[j] == snake->y[i]) // Check if the bomb coordinates with the snake
				{
					bomb_crush_on = 1;
					r++;
					break;
				}

				else if (snake->bomb_x[j] == snake->food_x && snake->bomb_y[j] == snake->food_y) // Check if the bomb coordinates with the snake
				{
					bomb_crush_on = 1;
					r++;
					break;
				}
			}
		}

		if (bomb_crush_on == 1) continue; // If coordinates, do the while statement again

		for (j = 0; j < snake->num_of_bombs; j++) // Creates bombs
			gotoxy(MAP_ADJ_X + snake->bomb_x[j], MAP_ADJ_Y + snake->bomb_y[j], "¡Þ");

		snake->speed -= 5;
		break;
	}
}


void status(struct _snake* snake)
{
	int i;

	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y, "head= ");
	printf("%2d,%2d", snake->x[0], snake->y[0]);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 1, "food= ");
	printf("%2d,%2d", snake->food_x, snake->food_y);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 1, "bomb= "); // Shows the locations of real bombs
	for (i = 0; i < snake->num_of_bombs; i++) printf("(%2d,%2d) ", snake->bomb_x[i], snake->bomb_y[i]);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 2, "leng= ");
	printf("%2d", snake->length);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 3, "key= ");
	printf("%3d", snake->key);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 4, "stage= ");
	printf("%1d", snake->stage);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 5, "spd= ");
	printf("%3d", snake->speed);
	gotoxy(MAP_ADJ_X + MAP_X + 1, MAP_ADJ_Y + 6, "score= ");
	printf("%3d", snake->score);
}
#include "Global.h"

void reset(struct _snake* snake)
{
	int i;
	system("cls");
	draw_map();
	while (kbhit())
		getch();

	snake->dir = LEFT; // Initialization of the values
	snake->length = 5;

	switch (snake->stage) // Changes the initial number of score, speed, and number of bombs
	{
	case 1:
		snake->score = 0;
		snake->speed = 100;
		snake->num_of_bombs = 3;
		break;

	case 2:
		snake->score = 150;
		snake->speed = 70;
		snake->num_of_bombs = 5;
		break;

	case 3:
		snake->score = 350;
		snake->speed = 50;
		snake->num_of_bombs = 7;
		break;
	}

	for (i = 0; i < snake->length; i++) // Draws the body of snake
	{
		snake->x[i] = MAP_X / 2 + i;
		snake->y[i] = MAP_Y / 2;
		gotoxy(MAP_ADJ_X + snake->x[i], MAP_ADJ_Y + snake->y[i], "¢Ã");
	}
	gotoxy(MAP_ADJ_X + snake->x[0], MAP_ADJ_Y + snake->y[0], "¢Ã"); // Actually, this part is for snakes' head. But it is unneccesery in this code
	food(snake); // Creates the food
	bomb(snake); // Creates the bomb
}

 
void game_over(struct _snake* snake)
{ 
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+5,"+----------------------+");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+6,"|      GAME OVER..     |");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+7,"+----------------------+");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+8," YOUR SCORE : ");
    printf("%d", snake->last_score=snake->score);
    
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+12," Press any keys to restart.. ");
    
    if(snake->score>snake->best_score) {
		snake->best_score= snake->score;
    gotoxy(MAP_ADJ_X+(MAP_X/2)-4,MAP_ADJ_Y+10,"¡Ù BEST SCORE ¡Ù");
    }
    Sleep(500);
        while (kbhit()) getch();
	snake->key=getch();
    title(snake);
}
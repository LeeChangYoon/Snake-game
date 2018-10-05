#include "Global.h"

extern snake S1;

void reset(void)
{
	int i;
	system("cls");
	draw_map();
	while (kbhit())
		getch();

	S1.dir = LEFT; // Initialization of the values
	S1.length = 5;

	switch (S1.stage) // Changes the initial number of score, speed, and number of bombs
	{
	case 1:
		S1.score = 0;
		S1.speed = 100;
		S1.num_of_bombs = 3;
		break;

	case 2:
		S1.score = 150;
		S1.speed = 70;
		S1.num_of_bombs = 5;
		break;

	case 3:
		S1.score = 350;
		S1.speed = 50;
		S1.num_of_bombs = 7;
		break;
	}

	for (i = 0; i<S1.length; i++) // Draws the body of snake
	{
		S1.x[i] = MAP_X / 2 + i;
		S1.y[i] = MAP_Y / 2;
		gotoxy(MAP_ADJ_X + S1.x[i], MAP_ADJ_Y + S1.y[i], "¢Ã");
	}
	gotoxy(MAP_ADJ_X + S1.x[0], MAP_ADJ_Y + S1.y[0], "¢Ã"); // Actually, this part is for snakes' head. But it is unneccesery in this code
	food(); // Creates the food
	bomb(); // Creates the bomb
}

 
void game_over(void)
{ 
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+5,"+----------------------+");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+6,"|      GAME OVER..     |");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+7,"+----------------------+");
    gotoxy(MAP_ADJ_X+(MAP_X/2)-6,MAP_ADJ_Y+8," YOUR SCORE : ");
    printf("%d", S1.last_score=S1.score);
    
    gotoxy(MAP_ADJ_X+(MAP_X/2)-7,MAP_ADJ_Y+12," Press any keys to restart.. ");
    
    if(S1.score>S1.best_score) {
        S1.best_score=S1.score;
    gotoxy(MAP_ADJ_X+(MAP_X/2)-4,MAP_ADJ_Y+10,"¡Ù BEST SCORE ¡Ù");
    }
    Sleep(500);
        while (kbhit()) getch();
    S1.key=getch();
    title();
}
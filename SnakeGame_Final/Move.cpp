#include "Global.h"

void move(int dir, struct _snake* snake)
{
	int i, j;

	if (snake->x[0] == snake->food_x && snake->y[0] == snake->food_y) // Case when it hits with food
	{
		snake->score += 10;
		food(snake);
		snake->length++;
		snake->x[snake->length - 1] = snake->x[snake->length - 2];
		snake->y[snake->length - 1] = snake->y[snake->length - 2];
	}
	for (j = 0; j < snake->num_of_bombs; j++)
	{
		if (snake->x[0] == snake->bomb_x[j] && snake->y[0] == snake->bomb_y[j]) // Case when it hits with bomb
		{
			snake->score -= 10;

			for (j = 0; j <snake->num_of_bombs; j++)
				gotoxy(MAP_ADJ_X + snake->bomb_x[j], MAP_ADJ_Y + snake->bomb_y[j], " "); // Delets the lastest bombs

			bomb(snake);
			gotoxy(MAP_ADJ_X + snake->x[snake->length - 1], MAP_ADJ_Y + snake->y[snake->length - 1], " "); // Delets the last body of the snake
			snake->length--;
		}
	}
	if (snake->x[0] == 0 || snake->x[0] == MAP_X - 1 || snake->y[0] == 0 || snake->y[0] == MAP_Y - 1) // Case when it hits the wall
	{
		game_over(snake);
		return;
	}
	for (i = 1; i < snake->length; i++) // Case when it hits itself
	{
		if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i])
		{
			game_over(snake);
			return;
		}
	}

	gotoxy(MAP_ADJ_X + snake->x[snake->length - 1], MAP_ADJ_Y + snake->y[snake->length - 1], "  "); // Delets it's last one
	for (i = snake->length - 1; i>0; i--) // Move the coordinates one by one
	{
		snake->x[i] = snake->x[i - 1];
		snake->y[i] = snake->y[i - 1];
	}
	gotoxy(MAP_ADJ_X + snake->x[0], MAP_ADJ_Y + snake->y[0], "▣"); // Part that changes head to body. But in this code, it is unnecessery
	if (dir == LEFT) --snake->x[0];
	if (dir == RIGHT) ++snake->x[0];
	if (dir == UP) --snake->y[0];
	if (dir == DOWN) ++snake->y[0];
	gotoxy(MAP_ADJ_X + snake->x[i], MAP_ADJ_Y + snake->y[i], "▣"); // Part that puts new head. But unnecessery in this code

	if (snake->length < 2) // If length goes down below 2, gmae is over
		game_over(snake);

	// Beccause it was too hard to change stages by recent score, I gave additional points for it
	if (snake->score == 100) // 50 additional points
	{
		snake->score = 150;
		stage2(snake);
	}

	if (snake->score == 250) // 100 additional points
	{
		snake->score = 350;
		stage3(snake);
	}
}

//일시중지 함수(key:P)
void pause(struct _snake* snake)
{ 
    while(1){
        if(snake->key==PAUSE){
            gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y,"< PAUSE : PRESS ANY KEY TO RESUME > ");
            Sleep(400);
            gotoxy(MAP_ADJ_X+(MAP_X/2)-9,MAP_ADJ_Y,"                                    ");
            Sleep(400);
        }
        else{
            draw_map();
            return;
        } 
        if(kbhit()){
                do{
					snake->key=getch();
                }
                while(snake->key==224);
        }
    }
}
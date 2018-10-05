#include "Global.h"

extern snake S1;

void move(int dir)
{
	int i, j;

	if (S1.x[0] == S1.food_x && S1.y[0] == S1.food_y) // Case when it hits with food
	{
		S1.score += 10;
		food();
		S1.length++;
		S1.x[S1.length - 1] = S1.x[S1.length - 2];
		S1.y[S1.length - 1] = S1.y[S1.length - 2];
	}
	for (j = 0; j < S1.num_of_bombs; j++)
	{
		if (S1.x[0] == S1.bomb_x[j] && S1.y[0] == S1.bomb_y[j]) // Case when it hits with bomb
		{
			S1.score -= 10;

			for (j = 0; j < S1.num_of_bombs; j++)
				gotoxy(MAP_ADJ_X + S1.bomb_x[j], MAP_ADJ_Y + S1.bomb_y[j], " "); // Delets the lastest bombs

			bomb();
			gotoxy(MAP_ADJ_X + S1.x[S1.length - 1], MAP_ADJ_Y + S1.y[S1.length - 1], " "); // Delets the last body of the snake
			S1.length--;
		}
	}
	if (S1.x[0] == 0 || S1.x[0] == MAP_X - 1 || S1.y[0] == 0 || S1.y[0] == MAP_Y - 1) // Case when it hits the wall
	{
		game_over();
		return;
	}
	for (i = 1; i<S1.length; i++) // Case when it hits itself
	{
		if (S1.x[0] == S1.x[i] && S1.y[0] == S1.y[i])
		{
			game_over();
			return;
		}
	}

	gotoxy(MAP_ADJ_X + S1.x[S1.length - 1], MAP_ADJ_Y + S1.y[S1.length - 1], "  "); // Delets it's last one
	for (i = S1.length - 1; i>0; i--) // Move the coordinates one by one
	{
		S1.x[i] = S1.x[i - 1];
		S1.y[i] = S1.y[i - 1];
	}
	gotoxy(MAP_ADJ_X + S1.x[0], MAP_ADJ_Y + S1.y[0], "▣"); // Part that changes head to body. But in this code, it is unnecessery
	if (dir == LEFT) --S1.x[0];
	if (dir == RIGHT) ++S1.x[0];
	if (dir == UP) --S1.y[0];
	if (dir == DOWN) ++S1.y[0];
	gotoxy(MAP_ADJ_X + S1.x[i], MAP_ADJ_Y + S1.y[i], "▣"); // Part that puts new head. But unnecessery in this code

	if (S1.length < 2) // If length goes down below 2, gmae is over
		game_over();

	// Beccause it was too hard to change stages by recent score, I gave additional points for it
	if (S1.score == 100) // 50 additional points
	{
		S1.score = 150;
		stage2();
	}

	if (S1.score == 250) // 100 additional points
	{
		S1.score = 350;
		stage3();
	}
}

//일시중지 함수(key:P)
void pause(void)
{ 
    while(1){
        if(S1.key==PAUSE){
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
                    S1.key=getch();
                }
                while(S1.key==224);
        }
    }
}
#include "Global.h"

extern snake S1;

void gotoxy(int x, int y, const char* s) { 
    COORD pos={2*x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    printf("%s",s);
}

void cursor_delete(void)
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
 
void draw_map(void)
{ 
    int i,j;
    for(i=0;i<MAP_X;i++){
        gotoxy(MAP_ADJ_X+i,MAP_ADJ_Y,"¡á");
    }
    for(i=MAP_ADJ_Y+1;i<MAP_ADJ_Y+MAP_Y-1;i++){
        gotoxy(MAP_ADJ_X,i,"¡á");
        gotoxy(MAP_ADJ_X+MAP_X-1,i,"¡á");
    }
    for(i=0;i<MAP_X;i++){
        gotoxy(MAP_ADJ_X+i,MAP_ADJ_Y+MAP_Y-1,"¡á");
    }
}


void title(void)
{
	int i, j;

	while (kbhit()) // Takes off the value in buffer 
		getch(); // Gets the value in buffer

	draw_map();
	cursor_delete();
	for (i = MAP_ADJ_Y + 1; i<MAP_ADJ_Y + MAP_Y - 1; i++) // Fills the inside of frame with blanks
	{
		for (j = MAP_ADJ_X + 1; j<MAP_ADJ_X + MAP_X - 1; j++)
			gotoxy(j, i, "  ");
	}

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+--------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|         S N A K E        |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "+--------------------------+");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, " < PRESS ANY KEY TO START > ");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 11, "   ¡Þ ¡ç,¡æ,¡è,¡é : Move    ");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 12, "   ¡Þ P : Pause             ");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 13, "   ¡Þ ESC : Quit            ");

	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 17, "      < iThings Lab >       ");

	while (1)
	{
		if (kbhit()) // If keyboard is hit
		{
			S1.key = getch(); // Gets the value of the buffer
			if (S1.key == ESC) // If ESC, program exits
			{
				system("cls"); // Clear the current console
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
			else break; // If not ESC, then continues
		}

		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "                            ");
		Sleep(400);

	}
	stage1();
}
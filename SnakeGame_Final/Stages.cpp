#include "Global.h"

void stage1(struct _snake* snake)
{
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+--------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|        S T A G E 1       |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "+--------------------------+");

	while (1)
	{
		if (kbhit())
		{
			snake->key = getch();
			if (snake->key == ESC) // If ESC, program exits
			{
				system("cls");
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
			else break; // If not ESC, then continues
		}

		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 10, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 10, "                            ");
		Sleep(400);

	}
	snake->stage = 1;
	reset(snake); // Resets the game
}

void stage2(struct _snake* snake)
{
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+-----------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|          S T A G E 2        |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "+-----------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9,"        BONUS 50 Points!!!      ");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 11,"       BOMB Increase To 5      ");
	while (1)
	{
		if (kbhit())
		{
			snake->key = getch();
			if (snake->key == ESC) // If ESC, program exits
			{
				system("cls");
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
			else break; // If not ESC, then continues
		}

		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 13, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 12, "                            ");
		Sleep(400);
	}
	snake->stage = 2;
	reset(snake); // Resets the game

}

void stage3(struct _snake* snake)
{
	system("cls");
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+-----------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|          S T A G E 3        |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "+-----------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9,"       BONUS 100 Points!!!!     ");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 11,"       BOMB Increase To 7      ");
	while (1)
	{
		if (kbhit())
		{
			snake->key = getch();
			if (snake->key == ESC) // If ESC, program exits
			{
				system("cls");
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
			else break; // If not ESC, then continues
		}

		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 13, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 12, "                            ");
		Sleep(400);
	}
	snake->stage = 3;
	reset(snake); // Resets the game
}

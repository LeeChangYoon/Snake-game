#include "Global.h"

extern snake S1;

void stage1(void)
{
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+--------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|        S T A G E 1       |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "+--------------------------+");

	while (1)
	{
		if (kbhit())
		{
			S1.key = getch();
			if (S1.key == ESC) // If ESC, program exits
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
	S1.stage = 1;
	reset(); // Resets the game
}

void stage2(void)
{
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+-----------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|          S T A G E 2        |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "|        B O N U S + 5 0      |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 8, "+-----------------------------+");
	while (1)
	{
		if (kbhit())
		{
			S1.key = getch();
			if (S1.key == ESC) // If ESC, program exits
			{
				system("cls");
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
			else break; // If not ESC, then continues
		}

		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 12, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 12, "                            ");
		Sleep(400);
	}
	S1.stage = 2;
	reset(); // Resets the game

}

void stage3(void)
{
	system("cls");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 5, "+-----------------------------+");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 6, "|          S T A G E 3        |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 7, "|        B O N U S + 100      |");
	gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 8, "+-----------------------------+");
	while (1)
	{
		if (kbhit())
		{
			S1.key = getch();
			if (S1.key == ESC) // If ESC, program exits
			{
				system("cls");
				gotoxy(MAP_ADJ_X + (MAP_X / 2) - 7, MAP_ADJ_Y + 9, "");
				exit(0);
			}
			else break; // If not ESC, then continues
		}

		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 12, " < PRESS ANY KEY TO START > ");
		Sleep(400);
		gotoxy(MAP_ADJ_X + (MAP_X / 2) - 6, MAP_ADJ_Y + 12, "                            ");
		Sleep(400);
	}
	S1.stage = 3;
	reset(); // Resets the game
}

//Tetris project
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>				// for the randomizer in srand

#include "Header.h"

void main(void)
{
	// Initialise graphic window
	int gd = DETECT, gm = 0, i;						//default is gd = DETECT, gm = 0

	initgraph(&gd, &gm, "");						//640x480
	int *current_piece = NULL;						//Have to set it to NULL otherwise I get an error
	int c = 0;

	printf("Please have this window active\n\nThe controls are left arrow, right arrow, down arrow and F1 to flip the piece.\n\nPress F1 to start");
	while (c != 59)
	{
		if (_kbhit())
		{
			c = _getch();
		}
	}

	while(loss_condition == 0)
	{
		backgroundcolor();
		if (new_piece == 1)
		{
			current_piece = pick_a_new_piece();
			new_piece_orientation(current_piece);
			new_piece = 0;
		}
		move_down(current_piece, &map);
		draw_current_piece (current_piece, &map);
		check_for_input(current_piece, &map);
		draw_landed_blocks(&map);
		delay(30);
		clearviewport();
	}

	// wait for key pressed
	readkey();

	// close graphic
	closegraph();
}
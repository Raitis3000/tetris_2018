//Tetris project
#include <graphics.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void backgroundcolor();

int new_piece = 1;										//is a new piece required? 1 = yes, 0 = no.
int loss_condition = 0;									//1 = loss, 0 = not lost yet
int move_down_timer = 0; 
int speed_increase_timer = 0;
float increment = 100.0;

typedef struct piece
{
	int block[4][4][4];							//4 arrangements of 4rows by 4columns
	int top_left_x;								//top left point of current piece pixel wise from the left side of the screen
	int top_left_y;								//top left point of current piece pixel wise from the top side of the screen
	int color;
	int row;									//row of the top left grid value of the piece matrix
	int column;									//column of the top left value of the piece matrix
	int orientation;							//value between 0-3
	int next_movement;							/*5 for neutral
												  2 for down
												  6 for right
												  4 for left
												  10 for rotation
												*/
}PIECE;

typedef struct x
{
	int aray[20][10];
}MAP;

MAP map =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

PIECE i_piece =
{
	1, 1, 1, 1,			//piece matrices
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,

	1, 1, 1, 1,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,			// until here

	0,					//top_left_x

	0,					//top_left_y

	14,					//color

	0,					//row

	4,					//column

	0,					//orientation

	5		//next movement
};

PIECE o_piece =
{
	1, 1, 0, 0,			//piece matrices
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,			// until here

	0,					//top_left_x

	0,					//top_left_y

	14,					//color

	0,					//row

	4,					//column

	0,					//orientation

	5					//next movement
};

PIECE j_piece =
{
	0, 1, 0, 0,			//piece matrices
	0, 1, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,

	1, 0, 0, 0,
	1, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,
	1, 0, 0, 0,
	1, 0, 0, 0,
	0, 0, 0, 0,

	1, 1, 1, 0,
	0, 0, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,			// until here

	0,					//top_left_x

	0,					//top_left_y

	14,					//color

	0,					//row

	4,					//column

	1,					//orientation

	5		//next movement
};

PIECE l_piece =
{
	1, 0, 0, 0,			//piece matrices
	1, 0, 0, 0,
	1, 1, 0, 0,
	0, 0, 0, 0,

	0, 0, 1, 0,
	1, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,
	0, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

	1, 1, 1, 0,
	1, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,			// until here

	0,					//top_left_x

	0,					//top_left_y

	14,					//color

	0,					//row

	4,					//column

	0,					//orientation

	5		//next movement
};

PIECE z_piece =
{
	1, 1, 0, 0,			//piece matrices
	0, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 0, 1, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

	1, 1, 0, 0,			
	0, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 0, 1, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,			// until here

	0,					//top_left_x

	0,					//top_left_y

	14,					//color

	0,					//row

	4,					//column

	0,					//orientation

	5		//next movement
};

PIECE s_piece =
{
	0, 1, 1, 0,			//piece matrices
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 0, 0, 0,
	1, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

	0, 1, 1, 0,		
	1, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	1, 0, 0, 0,
	1, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,			// until here

	0,					//top_left_x

	0,					//top_left_y

	14,					//color

	0,					//row

	4,					//column

	0,					//orientation

	5		//next movement
};

PIECE t_piece =
{
	0, 1, 0, 0,			//piece matrices
	1, 1, 1, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	1, 1, 0, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,

	1, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,

	0, 1, 0, 0,
	0, 1, 1, 0,
	0, 1, 0, 0,
	0, 0, 0, 0,			// until here

	0,					//top_left_x

	0,					//top_left_y

	14,					//color

	0,					//row

	4,					//column

	0,					//orientation

	5		//next movement
};

void drawblock(int x, int y)
{
	setfillstyle(SOLID_FILL, YELLOW);
	bar(200 + x, y, 224 + x, y + 24);
}

int check_for_collision(PIECE *piece, MAP *map)								//Returns 4 for wall collision that limits movement TO THE LEFT, 6 for wall collision that limits movement TO THE RIGHT
																			//2 for piece collision that would lock the current piece in place, 0 for no collision
																			//8 for game over
{
	if (piece->row == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			int column_check = piece->column;
			for (int j = 0; j < 4; j++)
			{
				if (piece->block[piece->orientation][i][column_check] == 1)
				{
					if (map->aray[i][column_check] == 1)
					{
						loss_condition = 1;
						printf("LOST\n");
						return 8;
					}

				}
			}
		}
	}
	//---------------------------------------------------CHECKS FOR EDGE OF MAP COLLISIONS--------------------------------------------------------------------------------
	if (piece->next_movement == 4 || piece->next_movement == 10)													//Checks for a wall to the left
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (piece->block[piece->orientation][i][j] == 1)
				{
					if ((piece->column - 1) == -1 - j)
					{
						piece->next_movement = 5;								//Removes movement from piece if wall is detected
						return 4;
					}
				}
			}
		}																			
	}

	if (piece->next_movement == 6 || piece->next_movement == 10) {											//checks for a wall to the right
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (piece->block[piece->orientation][i][j] == 1)
				{
					if ((piece->column + j) == 9)							
					{
						piece->next_movement = 5;
						return 6;
					}
				}
			}
		}
	}

	if (piece->next_movement == 2 /*|| piece->next_movement == 10*/)													//Checks for a wall below
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (piece->block[piece->orientation][i][j] == 1)
				{
					if ((piece->row) == 19 - i)
					{
						piece->next_movement = 5;								//Removes movement from piece if wall is detected
						return 2;
					}
				}
			}
		}
	}
	//------------------------------------------END OF EDGE OF MAP COLLISION CHECKS------------------------------------------------------------------------------


	//------------------------------------------BEGINNING OF PIECE COLLISION CHECKS------------------------------------------------------------------------------
	if (piece->next_movement == 2 /*|| piece->next_movement == 10*/) {
		int	next_draw_row = (piece->row + 1);											// this function checks the next 4 rows for colisions
		for (int j = 0; j < 4; j++) {

			int column_check = piece->column;											//sets an independent variable according to the current column position, this viariable resets every for 4 checks

			for (int i = 0; i < 4; i++)
			{
				if (piece->block[piece->orientation][j][i] == 1)						//checks if there's a block to be drawn from the piece matrix
				{
					if (map->aray[next_draw_row][column_check] == 1)					//checks  if there's a block on the next row
					{
						return 2;														//found a collision and will lock piece in place
					}
				}
				column_check++;														// moves over 1 to the right.
			}
			next_draw_row++;															//moves down 1 to check the next row
		}
	}

	if (piece->next_movement == 4 || piece->next_movement == 10)														//checks for collision if movement to the left
	{
		int row_check = piece->row;
		for (int j = 0; j < 4; j++)
		{
			int next_draw_column = (piece->column - 1);
			for (int i = 0; i < 4; i++)
			{
				if (piece->block[piece->orientation][j][i] == 1)
				{
					if (map->aray[piece->row + j][next_draw_column] == 1)
					{
						piece->next_movement = 5;
						return 4;														//returns 4 if there is a wall to the left						
					}
				}
				next_draw_column++;
			}
			row_check++;
		}
	}

	if (piece->next_movement == 6 || piece->next_movement == 10)														//checks for collision if movement to the right
	{
		int row_check = piece->row;
		for (int j = 0; j < 4; j++)
		{
			int next_draw_column = (piece->column + 1);
			for (int i = 0; i < 4; i++)
			{
				if (piece->block[piece->orientation][j][i] == 1)
				{
					if (map->aray[piece->row + j][next_draw_column] == 1)
					{
						piece->next_movement = 5;
						return 6;														//returns 6 if there is a wall to the right	
					}
				}
				next_draw_column++;
			}
			row_check++;
		}
	}

	return 0;
}

void draw_landed_blocks(MAP *map)																					
{
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++)
		{
			if (map->aray[i][j] != 0){
				drawblock(																//draws the piece
					j*24,
					i*24);
			}
		}
	}
}

void new_piece_orientation(PIECE *piece)
{
	int piece_orientation;
	srand(time(NULL));
	piece_orientation = rand() % (4);

	piece->orientation = piece_orientation;
}

int *pick_a_new_piece()										//7 pieces, each has 4 orientations
{
	int piece_num;
	srand(time(NULL));										//Generates a different seed every time the program is booted up
	piece_num = rand() % (7) + 1;									//number between 1 and 7 including

	if (piece_num == 1)
	{
		return &j_piece;
	}
	if (piece_num == 2)
	{
		return &o_piece;
	}
	if (piece_num == 3)
	{
		return &i_piece;
	}
	if (piece_num == 4)
	{
		return &l_piece;
	}
	if (piece_num == 5)
	{
		return &z_piece;
	}
	if (piece_num == 6)
	{
		return &s_piece;
	}
	if (piece_num == 7)
	{
		return &t_piece;
	}
}

void delete_lines(MAP *map)
{
	for (int i = 0; i < 20; i++)
	{
		int piece_count = 0;
		for (int j = 0; j < 10; j++)
		{
			if (map->aray[i][j] == 1)				// counts how many blocks are in a row
			{
				piece_count++;
			}
		}
		if (piece_count == 10)						// if a row is full
		{
			int new_i = i;							// creating a throwaway variable
			speed_increase_timer++;
			if (speed_increase_timer == 4)			// if 8 lines have been cleared
			{
				increment *= 1.5;						// increase the speed
				speed_increase_timer = 0;				 // reset timer
			}
		
			for (int x = 0; x < i; x++)
			{
				for (int z = 0; z < 10; z++)
				{
					map->aray[new_i][z] = map->aray[new_i - 1][z];	//shifting all of the above rows down one
				}
				new_i--;
			}			
		}
	}
}

void lock_piece_on_map(PIECE *piece, MAP *map)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (piece->block[piece->orientation][i][j] == 1)
				map->aray[piece->row + i][piece->column + j] = 1;
		}
	}

	delete_lines(map);

	new_piece = 1;													// draw a new piece (The variable is stored in source)
}

void draw_current_piece(PIECE *piece, MAP *map) {
	
	int	check_col = check_for_collision(piece, map);

	if (check_col == 4 || check_col == 6)
		return 0;
	else if (check_col == 2)
	{
		lock_piece_on_map(piece, map);
		piece->column = 4;
		piece->row = 0;
		piece->top_left_x = 0;
		piece->top_left_y = 0;
		piece->next_movement = 5;
		return 0;
	}
	else if (check_col == 8)
		return 0;

	if (piece->next_movement == 6)
		piece->column++;
	if (piece->next_movement == 4)
		piece->column--;
	if (piece->next_movement == 2)
		piece->row++;


	int current_draw_row = piece->row;

	for (int j = 0; j < 4; ++j) {		

		int current_draw_column = piece->column;						//sets an independent variable according to the current column position, this viariable resets every for 4 checks

		for (int i = 0; i < 4; ++i)
		{
			if (piece->block[piece->orientation][j][i] == 1) {			//checks the piece matrix if a block needs to be drawn
				piece->top_left_x = 24 * current_draw_column;
				piece->top_left_y = 24 * current_draw_row;

				drawblock(	piece->top_left_x,
							piece->top_left_y);	
			}
			current_draw_column += 1;											//proceeds to the next column
		}
		current_draw_row += 1;													//proceeds to the next row
	}
	
	piece->next_movement = 5;	//reset the movement back to neutral
}

void rotate(PIECE *piece, MAP *map)
{
	piece->next_movement = 10;

	int	old_orientation	 = piece->orientation,
		old_column		 = piece->column,
		old_row			 = piece->row;

	if (piece->orientation != 3)
		piece->orientation++;
	else
		piece->orientation = 0;

	for (int i = 0; i < 4; i++) {														// edge of the map to the left
		for (int j = 0; j < 4; j++)
		{
			if (piece->block[piece->orientation][i][j] == 1)
			{
				while ((piece->column) < 0)											// check collision with left side wall and correct it
					piece->column++;
				while ((piece->column + j) > 9)										// check collision with right side wall and correct it
					piece->column--;
				while ((piece->row + i) > 19)										//check collision with floor and correct it
					piece->row--;

			}
				if (map->aray[piece->row + i][piece->column + j] == 1)					// checks if there are pieces obstructing the turn
				{	
					piece->orientation	= old_orientation;								// resets the orientation back to the previous one
					piece->column		= old_column;
					piece->row			= old_row;
					return 0;

				}
			}
		}
	}

void move_piece(int input, PIECE *piece, MAP *map)			//32 is space, 075 is left, 077 is right, 080 is down
{
	if (input == 59)									/*rotate*/
	{
		rotate(piece, map);
	}

	if (input == 75)
	{
		piece->next_movement = 4;						//move left
	}

	if (input == 77)
	{
		piece->next_movement = 6;						//move right
	}

	if (input == 80)
	{
		piece->next_movement = 2;						//move down
	}
}

int check_for_input(PIECE *piece, MAP *map)
{
	int k;
	int press_or_not = _kbhit();
	if (press_or_not)
	{
		k = _getch();
		move_piece(k, piece, map);
	}
}

void move_down(PIECE *piece, MAP *map)
{
	move_down_timer++;
	if (move_down_timer > 1000 / increment)
	{
		move_down_timer = 0;
		move_piece(80, piece, map);
	}
}

void backgroundcolor()
{
	int maxx, maxy;
	maxx = getmaxx();
	maxy = getmaxy();

	setfillstyle(SOLID_FILL, LIGHTGRAY);
	bar(maxx - 195, 0, maxx, maxy);		//Right Bar
	bar(0, 0, 195, maxy);				//Left Bar      Width of the Grid + A Rectangle 2px away from the edge of grid to indicate the edges of the playing field.

	setfillstyle(SOLID_FILL, WHITE);
	bar(195, 0, 200, maxy);
	bar(maxx - 200, 0, maxx - 195, maxy);

	setcolor(DARKGRAY);
	for (int i = 224; i < (maxx - 200); i += 24)
	{
		line(i, 0, i, maxy);
	}
	for (int i = 0; i < maxy; i += 24)
	{
		line(200, i, maxx - 200, i);
	}
}
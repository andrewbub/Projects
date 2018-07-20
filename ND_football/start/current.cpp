// Andrew Bub	CSE 20311	Final Project
// current.cpp

#include "gfxnew.h"

void background();

int main()
{
	int wd = 900;
	int ht = 800;

	// Open a new window for drawing
	gfx_open(wd, ht, "Final");

	gfx_clear_color(7, 13, 23); // set background color
	gfx_clear();

	background();
	
	while(true)
	{
		if(gfx_wait() == 'q')
			break;
	}
	
}

void background()
{
	gfx_color(13, 121, 24); // set grass - TENTH
	gfx_fill_rectangle(0, 451, 900, 349);

	gfx_color(200, 202, 146); // set stands - NINTH
	gfx_fill_rectangle(0, 203, 900, 248);

	gfx_color(210, 187, 73); // set library building -SECOND
	gfx_fill_rectangle(337.5, 47.5, 225, 157.5);
	gfx_color(201, 159, 199);
	gfx_fill_rectangle(387, 47.5, 126, 157.5);

	gfx_color(210, 187, 73); // set top of library -FIRST
	gfx_fill_rectangle(360, 25, 180, 22.5);

	gfx_color(249, 249, 131); // set halo - THIRD
	gfx_circle(450, 68, 18);

	gfx_color(255, 255, 255); // set Jesus' head - FOURTH
	gfx_fill_circle(450, 72, 9);

	gfx_fill_rectangle(445.5, 81.5, 9, 4.5); // set Jesus' neck - FIFTH

	gfx_fill_rectangle(418.5, 85.5, 63, 14); // set Jesus' shoulders -SIXTH

	for(int i = 85.5; i <= 98; i++) // set Jesus' arms - SEVENTH
	{
		gfx_line(405, 63, 418.5, i);
		gfx_line(495, 63, 481.5, i);
	}

	gfx_fill_rectangle(432, 99, 36, 105); // set Jesus' body - EIGTH

	gfx_color(58, 94, 178); // set scoreboard - SEVENTEENTH
	gfx_fill_rectangle(382.5, 128, 135, 67.5); // legs first for y

	gfx_color(180, 180, 180); // set scoreboard legs - SIXTEENTH
	gfx_fill_rectangle(414, 195, 9, 9);
	gfx_fill_rectangle(477, 195, 9, 9);

	int c = 212;  // ELEVENTH
	while(c < 406) // set green fans
	{
		gfx_color(31, 146, 58);
		gfx_line(0, c, 900, c);

		c = c + 3;
	}

	c = 213;
	while(c < 406) // set blue fans
	{
		gfx_color(26, 39, 223);
		gfx_line(0, c, 900, c);

		c = c + 3;
	}

	gfx_color(255, 255, 255); // set back of endzone - TWELVTH
	gfx_fill_rectangle(0, 451, 900, 22.5);

	int j = 0;
	for(int i = 0; i < 9; i++) // set dashes - FOURTEENTH
	{
			gfx_line(j, 490, j + 90, 597);
		j = j + 99;
	}

	gfx_fill_rectangle(0, 617, 900, 9); // set goal line - THIRTHEENTH
	
	gfx_fill_rectangle(0, 770, 900, 10); // set 10 yard line

	int h = 1; // set hash marks
	int m = 643;
	while(h < 5) 
	{
		gfx_fill_rectangle(220, m, 10, 2);
		gfx_fill_rectangle(670, m, 10, 2);
		m = m + 35;
		h++;
	}

	// set field goal - FIFTEENTH

	gfx_color(255, 255, 0); // set base
	gfx_fill_rectangle(441, 383.5, 18, 90);

	gfx_fill_rectangle(360, 370, 180, 13); // set crossbar

	gfx_fill_rectangle(342, 248, 18, 135); // set posts
	gfx_fill_rectangle(540, 248, 18, 135);
}

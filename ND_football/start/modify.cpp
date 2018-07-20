// Andrew Bub	CSE 20311	Final Project
// modify.cpp

#include "gfxnew.h"

void background();

int main()
{
	int wd = 900;
	int ht = 800;

	// Open a new window for drawing
	gfx_open(wd, ht, "Final");

	gfx_clear_color(2, 8, 40); // set background color
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
	gfx_color(13, 121, 24); // set grass
	gfx_fill_rectangle(0, 405, 900, 395);

	gfx_color(200, 202, 146); // set stands
	gfx_fill_rectangle(0, 182, 900, 223);

	gfx_color(210, 187, 73); // set library building
	gfx_fill_rectangle(348, 42, 202, 140);
	gfx_color(201, 159, 199);
	gfx_fill_rectangle(393, 42, 113, 140);
	gfx_color(0, 0, 0);
	gfx_fill_rectangle(366, 45, 3, 137);
	gfx_fill_rectangle(531, 45, 3, 137);

	gfx_color(210, 187, 73); // set top of library
	gfx_fill_rectangle(369, 25, 162, 20);

	gfx_color(249, 249, 131); // set halo
	gfx_circle(450, 61, 15);

	gfx_color(255, 255, 255); // set Jesus' head
	gfx_fill_circle(450, 64, 8);

	gfx_fill_rectangle(446, 72, 8, 4); // set Jesus' neck

	gfx_fill_rectangle(421, 76, 56, 12); // set Jesus' shoulders

	for(int i = 76; i <= 87; i++) // set Jesus' arms
	{
		gfx_line(408, 56, 421, i);
		gfx_line(493, 56, 477, i);
	}

	gfx_fill_rectangle(434, 88, 32, 94); // set Jesus' body

	gfx_color(58, 94, 178); // set scoreboard
	gfx_fill_rectangle(389, 113, 121, 61); // legs first for y

	gfx_color(180, 180, 180); // set scoreboard legs
	gfx_fill_rectangle(415, 174, 8, 8);
	gfx_fill_rectangle(477, 174, 8, 8);

	int c = 190;
	while(c < 366) // set green fans
	{
		gfx_color(31, 146, 58);
		gfx_line(0, c, 900, c);

		c = c + 3;
	}

	c = 191;
	while(c < 366) // set blue fans
	{
		gfx_color(26, 39, 223);
		gfx_line(0, c, 900, c);

		c = c + 3;
	}

	gfx_color(255, 255, 255); // set back of endzone
	gfx_fill_rectangle(0, 405, 900, 20);

	int j = 0;
	for(int i = 0; i < 9; i++) // set dashes
	{
			gfx_line(j, 440, j + 81, 502);
		j = j + 99;
	} 

	gfx_fill_rectangle(0, 517, 900, 7); // set goal line

	gfx_fill_rectangle(0, 633, 900, 9); // set 10 yard line
	
	gfx_fill_rectangle(0, 770, 900, 10); // set 20 yard line

	int h = 1; // set hash marks between 10 and 20
	int m = 658;
	while(h < 5) 
	{
		gfx_fill_rectangle(220, m, 10, 2);
		gfx_fill_rectangle(670, m, 10, 2);
		m = m + 32;
		h++;
	}

	h = 1; // set hash marks betwen goal line and 10
	m = 540;
	while(h < 5)
	{
		gfx_fill_rectangle(221, m, 8, 1);
		gfx_fill_rectangle(671, m, 8, 1);
		m = m + 27;
		h++; 
	}

	// set field goal

	gfx_color(255, 255, 0); // set base
	gfx_fill_rectangle(442, 344, 16, 81);

	gfx_fill_rectangle(369, 332, 162, 12); // set crossbar

	gfx_fill_rectangle(353, 223, 16, 121); // set posts
	gfx_fill_rectangle(531, 223, 16, 121);
}

// Andrew Bub	CSE 20311	Final Project
// original.cpp

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
	gfx_color(13, 121, 24); // set grass
	gfx_fill_rectangle(0, 500, 900, 500);

	gfx_color(200, 202, 146); // set stands
	gfx_fill_rectangle(0, 225, 900, 275);

	gfx_color(255, 255, 255); // set stars
	for(int i = 0; i < 255; i = i+20)
	{
		for(int j = 0; j < 325; j+=10)
		{
			gfx_point(j, i);
		}
		for(int j = 575; j < 900; j+=10)
		{
			gfx_point(j, i);
		}
	}

	gfx_color(210, 187, 73); // set library building
	gfx_fill_rectangle(325, 50, 250, 175);
	gfx_color(201, 159, 199);
	gfx_fill_rectangle(380, 50, 140, 175);

	gfx_color(210, 187, 73); // set top of library
	gfx_fill_rectangle(350, 25, 200, 25);

	gfx_color(249, 249, 131); // set halo
	gfx_circle(450, 75, 20);

	gfx_color(255, 255, 255); // set Jesus' head
	gfx_fill_circle(450, 80, 10);

	gfx_fill_rectangle(445, 90, 10, 5); // set Jesus' neck

	gfx_fill_rectangle(415, 95, 70, 15); // set Jesus' shoulders

	for(int i = 95; i <= 110; i++) // set Jesus' arms
	{
		gfx_line(400, 70, 415, i);
		gfx_line(500, 70, 485, i);
	}

	gfx_fill_rectangle(430, 110, 40, 115); // set Jesus' body

	gfx_color(58, 94, 178); // set scoreboard
	gfx_fill_rectangle(400, 165, 100, 50);

	gfx_color(180, 180, 180); // set scoreboard legs
	gfx_fill_rectangle(410, 215, 10, 10);
	gfx_fill_rectangle(480, 215, 10, 10);

	// fill scoreboard numbers
	gfx_color(245, 204, 92);
	gfx_line(405, 175, 415, 175); // 3 (ND)
	gfx_line(405, 180, 415, 180);
	gfx_line(405, 185, 415, 185);
	gfx_line(415, 175, 415, 185);

	gfx_line(420, 175, 420, 185); // 1 (ND)

	gfx_line(485, 175, 495, 175); // 0 (Michigan)
	gfx_line(485, 185, 495, 185);
	gfx_line(485, 175, 485, 185);
	gfx_line(495, 175, 495, 185);

	gfx_line(440, 171, 445, 171); // 0 (time)
	gfx_line(440, 179, 445, 179);
	gfx_line(440, 171, 440, 179);
	gfx_line(445, 171, 445, 179);

	gfx_point(450, 173); // : (time)
	gfx_point(450, 177);

	gfx_line(455, 171, 460, 171); // 0 (time)
	gfx_line(455, 179, 460, 179);
	gfx_line(455, 171, 455, 179);
	gfx_line(460, 171, 460, 179);

	gfx_line(465, 171, 470, 171); // 0 (time)
	gfx_line(465, 179, 470, 179);
	gfx_line(465, 171, 465, 179);
	gfx_line(470, 171, 470, 179);

	int c = 235;  
	while(c < 450) // set green fans
	{
		gfx_color(31, 146, 58);
		gfx_line(0, c, 900, c);

		c = c + 3;
	}

	c = 236;
	while(c < 450) // set blue fans
	{
		gfx_color(26, 39, 223);
		gfx_line(0, c, 900, c);

		c = c + 3;
	}

	gfx_color(255, 255, 255); // set back of endzone
	gfx_fill_rectangle(0, 500, 900, 25);

	int j = 0;
	for(int i = 0; i < 9; i++) // set dashes
	{
			gfx_line(j, 550, j + 100, 685);
		j = j + 99;
	}

	gfx_fill_rectangle(0, 710, 900, 10); // set goal line

	// set field goal
	// probaly take this out of background function

	gfx_color(255, 255, 0); // set base
	gfx_fill_rectangle(440, 425, 20, 100);

	gfx_fill_rectangle(350, 410, 200, 15); // set crossbar

	gfx_fill_rectangle(330, 275, 20, 150); // set posts
	gfx_fill_rectangle(550, 275, 20, 150);
}

// Andrew Bub and Harry Gebremedhin
// CSE 20311	Final Project
// background.cpp
// implementation for the Background class

#include "background.h"
#include "gfxnew.h"

Background::Background()
{}

Background::Background(int lv)
{
	level = lv;
}

Background::~Background() 
{}

void Background::setBackground(int lv)
{
	level = lv;
	switch(level)
	{
		case 1: // Level 1
			set10();
			break;
		case 2: // Level 2
			set20();
			break;
		case 3: // Level 3
			set30();
			break;
		case 4: // Game Over
			over();
			break;
	}
}

void Background::set10()
{
	gfx_color(13, 121, 24); // set grass
        gfx_fill_rectangle(0, 500, 900, 500);

        gfx_color(200, 202, 146); // set stands
        gfx_fill_rectangle(0, 225, 900, 275);

        gfx_color(210, 187, 73); // set library building
        gfx_fill_rectangle(325, 50, 250, 175);
        gfx_color(201, 159, 199);
        gfx_fill_rectangle(380, 50, 140, 175);
	gfx_color(0, 0, 0);
	gfx_fill_rectangle(345, 55, 5, 170);
	gfx_fill_rectangle(550, 55, 5, 170);

        gfx_color(210, 187, 73); // set top of library
        gfx_fill_rectangle(350, 25, 200, 25);

        gfx_color(249, 249, 131); // set halo
        gfx_circle(450, 75, 20);

        gfx_color(255, 255, 255); // set Jesus' head
        gfx_fill_circle(450, 80, 10);

        gfx_fill_rectangle(445, 90, 10, 5); // set Jesus' neck

        gfx_fill_rectangle(415, 95, 70, 15); // set Jesus' shoulders

        for(int i = 95; i <= 109; i++) // set Jesus' arms
        {
                gfx_line(400, 70, 415, i);
                gfx_line(500, 70, 485, i);
        }

        gfx_fill_rectangle(430, 110, 40, 115); // set Jesus' body

        gfx_color(58, 94, 178); // set scoreboard
        gfx_fill_rectangle(375, 140, 150, 75);

        gfx_color(180, 180, 180); // set scoreboard legs
        gfx_fill_rectangle(410, 215, 10, 10);
        gfx_fill_rectangle(480, 215, 10, 10);

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
	gfx_color(255, 255, 0); // set base
        gfx_fill_rectangle(440, 425, 20, 100);

        gfx_fill_rectangle(350, 410, 200, 15); // set crossbar

        gfx_fill_rectangle(330, 275, 20, 150); // set posts
        gfx_fill_rectangle(550, 275, 20, 150);
}

void Background::set20()
{
	gfx_color(13, 121, 24); // set grass
        gfx_fill_rectangle(0, 451, 900, 349);

        gfx_color(200, 202, 146); // set stands
        gfx_fill_rectangle(0, 203, 900, 248);

        gfx_color(210, 187, 73); // set library building
        gfx_fill_rectangle(337, 47, 225, 157);
        gfx_color(201, 159, 199);
        gfx_fill_rectangle(387, 47, 126, 157);
	gfx_color(0, 0, 0);
	gfx_fill_rectangle(356, 51, 4, 153);
	gfx_fill_rectangle(540, 51, 4, 153);

        gfx_color(210, 187, 73); // set top of library
        gfx_fill_rectangle(360, 25, 180, 22);

        gfx_color(249, 249, 131); // set halo
        gfx_circle(450, 68, 18);

        gfx_color(255, 255, 255); // set Jesus' head
        gfx_fill_circle(450, 72, 9);

        gfx_fill_rectangle(445, 81, 9, 4); // set Jesus' neck

        gfx_fill_rectangle(418, 85, 63, 14); // set Jesus' shoulders

        for(int i = 85.5; i <= 98; i++) // set Jesus' arms
        {       
                gfx_line(405, 63, 418, i);
                gfx_line(495, 63, 481, i);
        }

        gfx_fill_rectangle(432, 99, 36, 105); // set Jesus' body

        gfx_color(58, 94, 178); // set scoreboard
        gfx_fill_rectangle(382, 128, 135, 67);

        gfx_color(180, 180, 180); // set scoreboard legs
        gfx_fill_rectangle(414, 195, 9, 9);
        gfx_fill_rectangle(477, 195, 9, 9);

        int c = 212;
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

        gfx_color(255, 255, 255); // set back of endzone
        gfx_fill_rectangle(0, 451, 900, 22);

        int j = 0;
        for(int i = 0; i < 9; i++) // set dashes
        {
                gfx_line(j, 490, j + 90, 597);
                j = j + 99;
        }

        gfx_fill_rectangle(0, 617, 900, 9); // set goal line

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

        // set field goal
	gfx_color(255, 255, 0); // set base
        gfx_fill_rectangle(441, 383, 18, 90);

        gfx_fill_rectangle(360, 370, 180, 13); // set crossbar

        gfx_fill_rectangle(342, 248, 18, 135); // set posts
        gfx_fill_rectangle(540, 248, 18, 135);
}

void Background::set30()
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
        gfx_fill_rectangle(389, 113, 121, 61);

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

void Background::over()
{
	gfx_clear();
}

// Andrew Bub CSE 20311 Lab 10 Part 3
// animate.cpp

#include <unistd.h>
#include <math.h>
#include "gfxnew.h"

int main()
{
	int wd = 500;
	int ht = 500;

	char r;

	float Txi = 250; // top of the arrow initial x position
	float Tyi = 400; // top of the arrow initial y position
	
	float Lx = 230; // left point x position
	float Ly = 475; // left point y position
	float Rx = 270; // right point x position
	float Ry = 475; // right point y position
	float Tx = Txi; // top of arrow x position
	float Ty = Tyi; // top of arrow y position

	float Cx = 250;
	float Cy = 475;
	float wrad = 10;
	float hrad = 20;
	int dc = 0;
	int dr = 0;

	float angle = (3*M_PI)/2;
	int d = 1;

	gfx_open(wd, ht, "Arrow");
	
	while(r != 113)
	{
//		gfx_clear_color(31, 113, 185);
		gfx_clear();

//		gfx_color(210, 239, 23); // field goal
		gfx_fill_rectangle(244, 200, 12, 75); // base
		gfx_fill_rectangle(204, 195, 92, 10); // cross
		gfx_fill_rectangle(194, 120, 10, 85); // left
		gfx_fill_rectangle(296, 120, 10, 85); // right

//		gfx_color(247, 99, 36); // arrow
		gfx_line(Tx, Ty, Lx, Ly);
		gfx_line(Tx, Ty, Rx, Ry);
		gfx_line(Lx, Ly, Rx, Ry);

//		gfx_color(121, 78, 28); // football
		gfx_ellipse(Cx, Cy, wrad, hrad);

		gfx_flush();

		Tx = Txi + 60*cos(angle); // rotate x of arrow
		Ty = Tyi + 60*sin(angle); // rotate y of arrow

		Cx = Cx + dc*cos(angle); // move x of ball
		Cy = Cy + dc*sin(angle); // move y of ball
		wrad = wrad - wrad*dr*.001; // make ball smaller
		hrad = hrad - hrad*dr*.001;

		angle = angle + d*(M_PI/128);

		if(angle >= 2*M_PI || angle <= M_PI)
			d = -d;

		usleep(10000);

		if(gfx_event_waiting())
		{
			r = gfx_wait();
	
			if(r == 32)
			{
				d = 0;
				dc = 1;
				dr = 1;
			}

			if(r == 114)
			{
				d = 1;
				dc = 0;
				dr = 0;
				Cx = 250;
				Cy = 475;
				wrad = 10;
				hrad = 20;
				
			}
		}

		if(Cy <= 165)
		{
			dc = 0;
			dr = 0;
		}
		
	}

	return 0;
}

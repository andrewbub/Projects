// Andrew Bub , Harry Gebremedhin 
// CSE20311 Final Project  
// final.cpp

#include <unistd.h>
#include <math.h>
#include "gfxnew.h"
#include <cstring>
#include <string>
#include "background.h"

using namespace std;
int main()
{
	int wd = 900;
	int ht = 800;
        int score=0, life=3;
	int level = 1, a_part = 1, b_part = 2;
	Background b;
        char r;
	
	float Txi = 450; // initial top of arrow x position
	float Tyi = 745; // initial top of arrow y position
	float Cxi = 450; // initial center of ball x position
	float Cyi = 745; // initial center of ball y position

	float Lx = 430; // left point x position
	float Ly = 780; // left point y position
	float Rx = 470; // right point x position
	float Ry = 780; // right point y position
	float Tx = Txi; // top of arrow x position
	float Ty = Tyi; // top of arrow y position

	float Cx = Cxi; // center of ball x position
	float Cy = Cyi;// center of ball y position
	float wrad = 10; // radius of width of ball
	float hrad = 20; // radius of height of ball
	int dc = 0; // change ball center
	int dr = 0; // change ball radius

	float angle = (3*M_PI)/2;
	int d = 5; // scalar factor on angle

	float Fgl = 350; // field goal left (x)
	float Fgr = 550; // field goal right (x)
	float Fgt = 310; // field goal top (y)
	float Stx = 385; // score text x position
	float Sty = 155; // score text y position
	float Snx = 395; // score number x position
	float Sny = 170; // score number y position
	float Ltx = 488; // life text x position
	float Lty = 155; // life text y position
	float Lnx = 500; // life number x position
	float Lny = 170; // life number y position

	gfx_open(wd, ht, "Field Goal!!!");
             
	string scorestring;
	string lifestring;
	while(r != 'q') // while 'q' not pressed
	{
              	scorestring = to_string(score);
              	lifestring = to_string(life); 	
		
		gfx_clear();
		b.setBackground(level);

		if(a_part == 1)
		{	
			Txi = 450;
			Tyi = 745;
			Lx = 430;
			Ly = 780;
			Rx = 470;
			Ry = 780;
		}
		if(b_part == 1)
		{
			Cxi = 450;
			Cyi = 745;
		}

		if(a_part == 2)
		{
			Txi = 225;
			Tyi = 745;
			Lx = 205;
			Ly = 780;
			Rx = 245;
			Ry = 780;
		}
		if(b_part == 2)
		{
			Cxi = 225;
			Cyi = 745;
		}

		if(a_part == 3)
		{
			Txi = 675;
			Tyi = 745;
			Lx = 655;
			Ly = 780;
			Rx = 695;
			Ry = 780;
		}
		if(b_part == 3)
		{
			Cxi = 675;
			Cyi = 745;
		}

		if(level == 1)
		{
			Fgl = 350;
			Fgr = 550;
			Fgt = 310;
			Stx = 385;
			Sty = 155;
			Snx = 395;
			Sny = 170;
			Ltx = 488;
			Lty = 155;
			Lnx = 500;
			Lny = 170;
		}

		if(level == 2)
		{
			Fgl = 360;
			Fgr = 540;
			Fgt = 280;
			Stx = 390;
			Sty = 145;
			Snx = 400;
			Sny = 160;
			Ltx = 483;
			Lty = 145;
			Lnx = 495;
			Lny = 160;
		}

		if(level == 3)
		{
			Fgl = 369;
			Fgr = 531;
			Fgt = 252;
			Stx = 395;
			Sty = 130;
			Snx = 405;
			Sny = 145;
			Ltx = 478;
			Lty = 130;
			Lnx = 490;
			Lny = 145;
		}

		gfx_color(255, 102, 0);
		gfx_line(Tx, Ty, Lx, Ly);// Arrow pointer
		gfx_line(Tx, Ty, Rx, Ry);
		gfx_line(Lx, Ly, Rx, Ry);

		gfx_color(75, 44, 7);
		gfx_ellipse(Cx, Cy, wrad, hrad);// Ellipse

		gfx_color(255, 255, 0);
                gfx_text(Stx,Sty,"Score");// Score text
                gfx_text(Ltx,Lty,"Lives");// Lives text                
                gfx_text(Snx,Sny,scorestring.c_str());// number for score
                gfx_text(Lnx,Lny,lifestring.c_str());// number for Life
		gfx_flush();

		Tx = Txi + 60*cos(angle); // rotate x of arrow
		Ty = Tyi + 60*sin(angle); // rotate y of arrow

		Cx = Cx + dc*cos(angle); // move x of ball
		Cy = Cy + dc*sin(angle); // move y of ball
		wrad = wrad - wrad*dr*.001; // make ball smaller
		hrad = hrad - hrad*dr*.001;

		angle = angle + d*(M_PI/128);
                 
		if(Cy < Fgt)
		{
                	if (Cx>Fgl and Cx<Fgr) // condition for scoring  
  			{	
				score+=3;
 				d = 5;
				dc = 0;
				dr = 0;
				Cx = Cxi;
				Cy = Cyi; 
				wrad = 10;
				hrad = 20;
				a_part++;
				b_part++;
			}

                	else if(Cx<Fgl or Cx>Fgr)// condition for missing    
                        {
				life=life-1;
				d = 5;
				dc = 0;
				dr = 0;
				Cx = Cxi;
				Cy = Cyi; 
				wrad = 10;
				hrad = 20;
				a_part++;
				b_part++;
                 	}
		}

		if(Cx <= 0 or Cx >= wd) // out of screen
		{
				life=life-1;
				d = 5;
				dc = 0;
				dr = 0;
				Cx = Cxi;
				Cy = Cyi; 
				wrad = 10;
				hrad = 20;
				a_part++;
				b_part++;	
		} 

                if(life<=0){ // Game over condition
		  gfx_text(310,250,"Game Over! Press 'R' to restart and 'Q' to quit");
	          gfx_flush();
		  level = 4;                 
		  d = 0;
		  dr = 0; 
		  Cx = Txi;
		  Cy = Tyi;
                  gfx_clear();
                 }   

                if (score>0 and life>0){ // Reporting score and life
                 gfx_text(Snx,Sny,scorestring.c_str()); // display new score
                 gfx_text(Lnx,Lny,lifestring.c_str()); // display new life
                 gfx_flush();	
           		
		}
 
                if (score>100){// player gets an extra life for every 100 points 
                     score=0;
                     life+=life;}
 
		if(angle >= 2*M_PI || angle <= M_PI)
			d = -d;

		usleep(100000);

		if(a_part > 3)
		{
			level++;
			a_part = 1;
		}
		if(b_part > 3)
			b_part = 1;

		if(level > 3)
		{
			level = 1;
		}


		if(gfx_event_waiting())// button inputs from user
		{
			r = gfx_wait();
	
			if(r == 32)// spacebar
			{
				d = 0;
				dc = 6;
				dr = 3;
			}

			if(r == 'r')//restart condition
			{
				level = 1;
				a_part = 1;
				b_part = 2;     
                                life=3;
		      		d = 5;
				dc = 0;
				dr = 0;
				Cx = 450;
				Cy = 745;
				Txi = 450;
				Tyi = 745;
				wrad = 10;
				hrad = 20;
                                score=0;
				
			}
		}

		
	}
	return 0;
}

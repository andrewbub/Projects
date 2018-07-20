// Andrew Bub	CSE 20311	Final Project
// final.cpp
// driver to test the Background Class

#include "background.h"
#include "gfxnew.h"

int main()
{
	int wd = 900;
	int ht = 800;

	int level = 3;
	int part = 1;

	Background b;

	// Open a new window for drawing
	gfx_open(wd, ht, "Final");

	gfx_clear_color(2, 8, 35); // set background color
	gfx_clear();

	b.setBackground(level);

	while(gfx_wait() != 'q')
	{}
/**	while(true)
	{
		gfx_clear_color(2, 8, 35); // set background color
		gfx_clear();
		b.setBackground(level);
		if(gfx_wait() == 'q')
			break;
		if(gfx_wait() == '1')
			level = 1;
		if(gfx_wait() == '2')
			level = 2;
	} **/
}

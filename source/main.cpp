#include "commun.h"
#include "Ball.hpp"

sftd_font *mainFont;

int Do_All()
{
	bool pause = false;

	unsigned score = 0;

	touchPosition touch;

	Ball *ball = new Ball;

	while(true)
	{
		if(ball->newBall()){	
			delete ball;	//trying to learn pointers
			ball = 0;
			ball = new Ball;
		}

		hidScanInput();
		hidTouchRead(&touch);
		if(hidKeysDown() & KEY_START)
			pause = !pause;

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sftd_draw_text(mainFont, TOP_WIDTH/3-20, TOP_HEIGHT/4, RGBA8(0, 0, 0, 255), 25, "bubblepop BETA");
			sftd_draw_textf(mainFont, TOP_WIDTH/2-10, TOP_HEIGHT/2+20, RGBA8(0, 0, 255, 220), 40, "%03d", score);
			sftd_draw_text(mainFont, TOP_WIDTH/5, TOP_HEIGHT-20, RGBA8(0, 0, 0, 255), 15, "Touch the bubbles!");
		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			ball->UpdateAndDraw(touch);

			if(ball->hasLost()){
				sftd_draw_text(mainFont, BOT_WIDTH/3, BOT_HEIGHT/2, RGBA8(0, 0, 0, 255), 15, "Lost!");
				sf2d_end_frame();	//crappy
				sf2d_swapbuffers();	//crappy
				delete ball;
				ball = 0;
				break;
			}

		sf2d_end_frame();

		if(ball->hasBeenTouch())
			score++;

		sf2d_swapbuffers();
	}

	return 0;
}

void InitTextures()
{
	mainFont = sftd_load_font_mem(main_font_ttf, main_font_ttf_size);
}

int main()
{
	srand(time(NULL));

	sf2d_init();
	sftd_init();

	InitTextures();

	sf2d_set_clear_color(RGBA8(255, 255, 255, 255));

	while(aptMainLoop()){
		hidScanInput();

		if(hidKeysHeld() & KEY_A)
			Do_All();
		if(hidKeysHeld() & KEY_SELECT)
			break;

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			sftd_draw_text(mainFont, TOP_WIDTH/3-20, TOP_HEIGHT/4, RGBA8(0, 0, 0, 255), 25, "bubblepop BETA");
			sftd_draw_text(mainFont, TOP_WIDTH/5, TOP_HEIGHT/2, RGBA8(0, 0, 0, 255), 15, "Press A to start, SELECT to return to HBL :)");
		sf2d_end_frame();

		sf2d_swapbuffers();
	}

	sftd_free_font(mainFont);
	sftd_fini();
	sf2d_fini();
	return 0;
}
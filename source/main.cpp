#include "commun.h"
#include "Ball.hpp"

sftd_font *mainFont, *titleFont;

void Do_All()
{
	bool pause = false, lost = false;

	unsigned score = 0;

	touchPosition touch;

	Ball ball;

	while(true)
	{
		hidScanInput();
		hidTouchRead(&touch);
		if(hidKeysDown() & KEY_START)
			pause = !pause;

		sf2d_start_frame(GFX_TOP, GFX_LEFT);

			sftd_draw_text(titleFont, TOP_WIDTH/3-20, TOP_HEIGHT/4, RGBA8(0, 0, 0, 255), 25, "BUBBLEPOP");
			sftd_draw_textf(mainFont, TOP_WIDTH/2-10, TOP_HEIGHT/2+20, RGBA8(0, 0, 255, 220), 40, "%03d", score);
			sftd_draw_text(mainFont, TOP_WIDTH/5, TOP_HEIGHT-20, RGBA8(0, 0, 0, 255), 15, "Touch the bubbles!");

		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

			ball.UpdateAndDraw(&touch, score, pause);

			if(ball.hasLost()){
				sftd_draw_text(mainFont, BOT_WIDTH/3, BOT_HEIGHT/2, RGBA8(0, 0, 0, 255), 15, "Lost!");
				lost = true;
			}

		sf2d_end_frame();

		sf2d_swapbuffers();

		if(lost)
			break;
	}
}

void InitTextures()
{
	mainFont = sftd_load_font_mem(main_font_ttf, main_font_ttf_size);
	titleFont = sftd_load_font_mem(title_font_ttf, title_font_ttf_size);
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
			sftd_draw_text(titleFont, TOP_WIDTH/3-20, TOP_HEIGHT/4, RGBA8(0, 0, 0, 255), 25, "BUBBLEPOP");
			sftd_draw_text(mainFont, 10, TOP_HEIGHT/2, RGBA8(0, 0, 0, 255), 15, "Press A to start, SELECT to return to HBL :)");
		sf2d_end_frame();

		sf2d_swapbuffers();
	}

	sftd_free_font(mainFont);
	sftd_fini();
	sf2d_fini();
	return 0;
}
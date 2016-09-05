#include "commun.h"
#include "Ball.hpp"

sftd_font *mainFont, *titleFont, *scoreFont;

u32 SetBgColor(int score)
{
	if(score >= 0 && score < 10){
		return RGBA8(255 , 255, 255, 255);
	}else if(score >= 10 && score < 20){
		return RGBA8(200 ,200 ,255, 255);
	}else if(score >= 20 && score < 25){
		return RGBA8(255 ,200 ,200, 255);
	}else if(score >= 25 && score < 30){
		return RGBA8(255 ,180 ,180, 255);
	}else if(score >= 35 && score < 40){
		return RGBA8(255 ,160 ,160, 255);
	}else if(score >= 40 && score < 45){
		return RGBA8(255 ,120 ,120, 255);
	}else if(score >= 50 && score < 70)
		return RGBA8(0 ,0, 0, 255);
	
	return RGBA8(255,0,255, 255);
}

void DrawTextCentered(sftd_font *font, float h, u32 color, int size, const char* str)
{
	sftd_draw_text(font, TOP_WIDTH/2-sftd_get_text_width(font, size, str)/2, h, color, size, str);
}
void DrawTextCenteredBot(sftd_font *font, float h, u32 color, int size, const char* str)
{
	sftd_draw_text(font, BOT_WIDTH/2-sftd_get_text_width(font, size, str)/2, h, color, size, str);
}

void Do_All()
{
	Ball ball;
	touchPosition touch;
	bool pause = false, lost = false;
	unsigned score = 0;

//-----------------------TIMER-----------------------------------------------------------------------------------------
	for (int i = 3; i >= 0; --i)
	{
		std::stringstream timeStr;
		timeStr << (i);
		std::string timeStrFinal = timeStr.str();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			DrawTextCenteredBot(mainFont, 20, RGBA8(100, 100, 100, 255), 13, "Game start in...");
			DrawTextCenteredBot(scoreFont, BOT_HEIGHT/2-10, RGBA8(255, 0, 0, 255), 20, timeStrFinal.c_str());
		sf2d_end_frame();
		sf2d_swapbuffers();

		svcSleepThread(1000000000);
	}
//---------------------------------------------------------------------------------------------------------------------

	while(aptMainLoop())
	{
//-----------------------INPUTS----------------------------------------------------------------------------------------
		hidScanInput();
		hidTouchRead(&touch);

		if(hidKeysDown() & KEY_START)
			pause = !pause;

		if(hidKeysDown() & KEY_B || lost){
			ball.Reset();
			break;
		}
//-----------------------DRAWING---------------------------------------------------------------------------------------
		sf2d_set_clear_color(SetBgColor(score));

		sf2d_start_frame(GFX_TOP, GFX_LEFT);

			DrawTextCentered(titleFont, TOP_HEIGHT/4, RGBA8(0, 0, 0, 255), 25, "BubblePop");
			sftd_draw_textf(scoreFont, TOP_WIDTH/2-20, TOP_HEIGHT/2+20, RGBA8(0, 0, 255, 220), 40, "%d", score);
			DrawTextCentered(mainFont, TOP_HEIGHT-20, RGBA8(0, 0, 0, 255), 15, "START=pause|B=Exit|Touch the bubbles!");

		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

			ball.UpdateAndDraw(&touch, score, pause);

			if(ball.hasLost()){
				DrawTextCenteredBot(mainFont, BOT_HEIGHT/2, RGBA8(255, 0, 0, 255), 15, "Lost!");				
				lost = true; 	//used to properly exit Do_All() instead of using break;
			}

		sf2d_end_frame();
//---------------------------------------------------------------------------------------------------------------------
		sf2d_swapbuffers();
	}
}

void InitFonts()
{
	mainFont = sftd_load_font_mem(main_font_ttf, main_font_ttf_size);
	titleFont = sftd_load_font_mem(title_font_ttf, title_font_ttf_size);
	scoreFont = sftd_load_font_mem(score_font_ttf, score_font_ttf_size);
}

int main()
{
	srand(time(NULL));

	sf2d_init();
	sftd_init();
	InitFonts();

	const char* str = "Press A to start, SELECT to return to HBL :)";
	const char* str2 = "BubblePop by cynosura - 2016 | version 2.1";

	while(aptMainLoop()){
		sf2d_set_clear_color(RGBA8(255, 255, 255, 255));

		hidScanInput();

		if(hidKeysHeld() & KEY_A)
			Do_All();
		if(hidKeysHeld() & KEY_SELECT)
			break;

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			DrawTextCentered(titleFont, TOP_HEIGHT/4, RGBA8(0, 0, 0, 255), 25, "BubblePop");
			DrawTextCentered(mainFont, TOP_HEIGHT/2, RGBA8(0, 0, 0, 255), 15, str);
			DrawTextCentered(mainFont, TOP_HEIGHT-20, RGBA8(0, 0, 0, 200), 12, str2);
		sf2d_end_frame();
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			//To do
		sf2d_end_frame();

		sf2d_swapbuffers();
	}

	sftd_free_font(mainFont);
	sftd_fini();
	sf2d_fini();
	return 0;
}
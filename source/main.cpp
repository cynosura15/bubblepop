#include "commun.h"
#include "Ball.hpp"

//music: TODO
/*u8* buffer;
u32 size;
#define SAMPLERATE 32000*/

sftd_font *mainFont, *titleFont, *scoreFont;
bool easy_mode = false;

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
			if(easy_mode)
				DrawTextCenteredBot(mainFont, BOT_HEIGHT-20, RGBA8(0, 100, 0, 255), 13, "Easy Mode");
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
			if(lost)
				svcSleepThread(3000000000);

			ball.Reset();
			sf2d_set_clear_color(RGBA8(205, 225, 245, 255));

			break;
		}
//-----------------------DRAWING---------------------------------------------------------------------------------------
		sf2d_set_clear_color(SetBgColor(score));

		//Convert score from int to string in order to be drawed at the center
		std::stringstream scoreStrTemp;
		scoreStrTemp << (score);
		std::string scoreStr = scoreStrTemp.str();

		sf2d_start_frame(GFX_TOP, GFX_LEFT);

			DrawTextCentered(titleFont, TOP_HEIGHT/4, RGBA8(0, 0, 0, 255), 25, "BubblePop");
			DrawTextCentered(scoreFont, TOP_HEIGHT/2+20, RGBA8(0, 0, 255, 220), 40, scoreStr.c_str());
			DrawTextCentered(mainFont, TOP_HEIGHT-20, RGBA8(0, 0, 0, 255), 15, "START to Pause | B to Exit | Touch the bubbles!");

		sf2d_end_frame();

		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

			if(easy_mode){
				DrawTextCenteredBot(mainFont, BOT_HEIGHT-20, RGBA8(0, 255, 0, 50), 13, "Easy Mode");
				sf2d_draw_line(40, 0, 40, BOT_HEIGHT, 3, RGBA8(0, 0, 255, 255));
				sf2d_draw_line(BOT_WIDTH-40, 0, BOT_WIDTH-40, BOT_HEIGHT, 3, RGBA8(0, 0, 255, 255));
			}

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
	srand(svcGetSystemTick());

	sf2d_init();
	sftd_init();
	//csndInit();
	InitFonts();
	sf2d_set_clear_color(RGBA8(205, 225, 245, 255));

	//play_audio("/3ds/data/bubblepop/audio/sample.bin");

	while(aptMainLoop()){

		hidScanInput();
		if(hidKeysHeld() & KEY_A && hidKeysHeld() & KEY_DOWN){
			easy_mode = true;
			Do_All();
			easy_mode = false;
		}
		else if(hidKeysDown() & KEY_A)
			Do_All();
		if(hidKeysDown() & KEY_SELECT)
			break;

		sf2d_start_frame(GFX_TOP, GFX_LEFT);
			DrawTextCentered(titleFont, TOP_HEIGHT/4, RGBA8(0, 0, 0, 255), 30, "BubblePop");
			DrawTextCentered(mainFont, TOP_HEIGHT/2, RGBA8(0, 0, 0, 255), 15, "Press A to start, SELECT to exit :)");
			DrawTextCentered(mainFont, TOP_HEIGHT-20, RGBA8(0, 0, 0, 200), 12, "BubblePop by cynosura - 2016 | version 2.2");
		sf2d_end_frame();
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			//To do
		sf2d_end_frame();

		sf2d_swapbuffers();
	}

	//stop_audio();
	//stop_audio();
	//csndExit();
	sftd_free_font(mainFont);
	sftd_fini();
	sf2d_fini();
	return 0;
}

/*void play_audio(const char *audio){

	FILE *file = fopen(audio, "rb");

	// seek to end of file
	fseek(file, 0, SEEK_END);

	// file pointer tells us the size
	size_t size = ftell(file);

	// seek back to start
	fseek(file, 0, SEEK_SET);

	//allocate a buffer
	buffer =(u8*) linearAlloc(size);

	//read contents !
	size_t bytesRead = fread(buffer, 1, size, file);
	//u8 test = &buffer;

	//close the file because we like being nice and tidy
	fclose(file);

	csndPlaySound(8, SOUND_FORMAT_16BIT | SOUND_REPEAT, SAMPLERATE, 1, 0, buffer, buffer, size);
	linearFree(buffer);
}

void stop_audio(){
	csndExecCmds(true);
	CSND_SetPlayState(0x8, 0);
	memset(buffer, 0, size);
	GSPGPU_FlushDataCache(buffer, size);
	linearFree(buffer);
}*/
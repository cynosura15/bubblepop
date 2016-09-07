#ifndef _COMMUN_H_
#define _COMMUN_H_

#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <sstream>

#define BOT_WIDTH 320
#define BOT_HEIGHT 240
#define TOP_WIDTH 400
#define TOP_HEIGHT 240

#include "main_font_ttf.h"
#include "title_font_ttf.h"
#include "score_font_ttf.h"

//void play_audio(const char *audio);
//void stop_audio();

extern sftd_font *mainFont;
extern bool easy_mode;

#endif
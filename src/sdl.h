#ifndef _SDL_H_
#define _SDL_H_

enum sound { EHIT, ESPLODE, PSHOOT, PHIT, PSPLODE };
enum gamestates { GS_NORMAL_PLAY, GS_QUIT_MENU, GS_SHUTDOWN, GS_PAUSED,
	GS_LOST };

extern enum gamestates gamestate;

extern int screen_width;
extern int screen_height;
extern int half_screen_width;
extern int half_screen_height;
extern char zsort;
extern char mute;
extern char monochrome;


void start_video(int w, int h, int bpp, int fs);
void start_audio();
void sdl_game_loop();
void play_sound(enum sound s);
void display_loud_text(char *s, int duration);

#endif

#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <string.h>
#include <time.h>

#include "ai.h"
#include "letters.h"
#include "world.h"
#include "geometry.h"
#include "sdl.h"

#define MOVE_THRESHOLD 0.001

enum gamestates gamestate;

int screen_width;
int screen_height;

int half_screen_width;
int half_screen_height;

char monochrome;
char mute;
char zsort;

SDL_Surface *screen = NULL;
SDL_Surface *buffer = NULL;

Mix_Chunk *enemy_hit;
Mix_Chunk *enemy_explode;
Mix_Chunk *player_shoot;
Mix_Chunk *player_hit;
Mix_Chunk *player_explode;

int loud_text_time;
char *loud_text;


void start_video(int w, int h, int bpp, int fs) {
	/* SDL nonsense... */
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
		printf("Unable to start up SDL.\n");
		exit(1);
	} 
	screen_width = w;
	screen_height = h;

	half_screen_width = w / 2;
	half_screen_height = h / 2;

	SDL_WM_SetIcon( SDL_LoadBMP("ps.ico"), NULL );

	if ( fs )
		screen = SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE | SDL_FULLSCREEN );
	else
		screen = SDL_SetVideoMode(w, h, bpp, SDL_SWSURFACE );

	if ( screen == NULL ) {
		fprintf(stderr, "Unable to use requested screen resolution: %s\n", 
			SDL_GetError());
		exit(1);
	}

	buffer = SDL_CreateRGBSurface(SDL_SWSURFACE, screen_width, screen_height, 
		16, 0, 0, 0, 0);

	SDL_WM_SetCaption("Pocket Starfighter", NULL);
}

void start_audio() {
	if(Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) != 0) {
		mute = 1;
	}
	enemy_hit = Mix_LoadWAV("sounds/enemyhit.wav");
	enemy_explode = Mix_LoadWAV("sounds/enemysplode.wav");
	player_shoot = Mix_LoadWAV("sounds/playershoot.wav");
	player_hit = Mix_LoadWAV("sounds/playerhit.wav");
	player_explode = Mix_LoadWAV("sounds/playerslode.wav");
}

void play_sound(enum sound s) {
	if ( mute ) return;
	if ( s == PSHOOT ) Mix_PlayChannel( -1, player_shoot, 0 );
	if ( s == PHIT ) Mix_PlayChannel( -1, player_hit, 0 );
	if ( s == PSPLODE ) Mix_PlayChannel( -1, player_explode, 0 );
	if ( s == EHIT ) Mix_PlayChannel( -1, enemy_hit, 0 );
	if ( s == ESPLODE ) Mix_PlayChannel( -1, enemy_explode, 0 );
}
int resolve_color(unsigned short qbcolor) {
	int r, g, b;
	Uint32 color;
	unsigned short q = qbcolor;

	if ( monochrome ) return SDL_MapRGB( buffer->format, 255, 255, 255);

	if ( q > 8 ) q -= 8;
	r = 0; g = 0; b = 0;

	if ( q == 4 || q == 5 || q == 6 || q == 7 || q == 7 || q == 8) r = 127;
	else r = 0;

	if ( q == 2 || q == 3 || q == 6 || q == 7 || q == 8 ) g = 127;
	else g = 0;

	if ( q == 1 || q == 3 || q == 5 || q == 7 || q == 8 ) b = 127;
	else b = 0;

	if ( qbcolor > 8 ) {
		r *= 2;
		g *= 2;
		b *= 2;
	} else {
		r += 20;
		g += 20;
		b += 20;
	}

	color = SDL_MapRGB( buffer->format, r, g, b);
	return color;
}

void draw_line(double x1, double y1, double x2, double y2, Uint32 color) {
	double dist = sqrt( pow(x2 - x1, 2) + pow( y2 - y1, 2) );
	SDL_Rect rect;
	double x, y, p;
	int j = 0;
	int i = 0;
	rect.x = x1;
	rect.y = y1;
	rect.w = 2;
	rect.h = 2;

	if ( x1 == x2 && y1 == y2 ) return;

	if ( dist > screen_width ) return;
	for ( i = 0; i <= dist; i+= 2 ) {
		p = (double)i / dist;
		x = x1 + p*(x2 - x1);
		y = y1 + p*(y2 - y1);
		rect.x = (int)x;
		rect.y = (int)y;
		/* Unlike QBasic, SDL gets whiney if you go off the edge. */
		if ( rect.x >= 0 && rect.y >= 0 && 
				(rect.x + rect.w) <= screen_width && 
				(rect.y + rect.h <= screen_height) ) {
			SDL_FillRect( buffer, &rect, color);
		}
		j++;
		if ( j > dist ) { return; }
	}
	SDL_UpdateRect(buffer, 0,0,0,0);
}

void print(char *s, int x, int y, unsigned short _color, float scale ) {
	int i, j;
	struct letter l;
	Uint32 color = resolve_color(_color);
	for ( i = 0; i < strlen(s); i++ ) {
		l = make_letter( s[i] );
		for ( j = 0; j < 2*LINES_PER_LETTER; j+=2 ) {
			if ( l.lines[j] == -1 ) break;
			draw_line( 
				(x+((i+1)*scale))+scale*l.xs[ l.lines[j] ],
				y+scale*l.ys[ l.lines[j] ],
				(x+((i+1)*scale))+scale*l.xs[ l.lines[j+1] ],
				y+scale*l.ys[ l.lines[j+1] ],
				color );
		}
	}
}

void sort_ships() {
	struct ship swap;
	int i, j;

	/* TODO: Optimize away from bubblesort?! */
	for ( i = 0; i < ships_in_world; i++ ) {
		for ( j = 0; j < ships_in_world; j++ ) {
			if ( world[i].location.z > world[j].location.z ) {
				swap = world[i];
				world[i] = world[j];
				world[j] = swap;
			}
		}
	}
}

void flush_screen() {
	SDL_Rect area;
	Uint32 black = SDL_MapRGB( buffer->format, 0, 0, 0);
	area.x = 0;
	area.y = 0;
	area.w = screen_width;
	area.h = screen_height;
	if ( SDL_BlitSurface( buffer, &area, screen, &area ) < 0 ) {
		fprintf(stderr, "Blit error?!");
	}
	SDL_FillRect(buffer, &area, black);
}


void draw_map() {
	/* TODO: Calls to draw_line shouldn't have to resolve_color.
	draw_line should just _do_ that. */

	int map_width = screen_width / 6;
	int map_height = screen_height / 6;
	int map_padding = 3; 

	int map_mid_x = screen_width - map_padding - (map_width/2);
	int map_mid_y = screen_height - map_padding - (map_height/2);
	int i;
	double scan_distance = 200;


	/* Horizontal map line */
	draw_line( map_mid_x - map_width/2, map_mid_y, 
		map_mid_x + map_width/2, map_mid_y, resolve_color(2) );
	/* Vertical map line */
	draw_line( map_mid_x, map_mid_y - map_height/2, 
		map_mid_x, map_mid_y + map_height/2, resolve_color(2) );

	for ( i = 0; i < ships_in_world; i++ ) {
		/* Remember Y in world[] is up-down... so reading here gets
		   confusing. */
		if ( distance( origin, world[i].location ) <= scan_distance ) {
			double x = (world[i].location.x / scan_distance) *
				(map_width/2) + map_mid_x;
			double y = -(world[i].location.z / scan_distance) *
				(map_height/2) + map_mid_y;
			double zoff = -((map_height/2)*(world[i].location.y / scan_distance));
			draw_line(x, y, x, y + zoff, resolve_color(15) );
			draw_line(x, y + zoff, x, y + zoff + 1, resolve_color(4) );
		}
	}

}


void render() {
	int i, j;
	int x[MAX_SHIPS * MAX_SHIP_POINTS];
	int y[MAX_SHIPS * MAX_SHIP_POINTS];
	char str[20];
	double zoom = half_screen_height;


	for ( i = 0; i < MAX_DEBRIS; i++ ) {
		draw_line( debrisfield[i].x, debrisfield[i].y, 
			debrisfield[i].x + 1, debrisfield[i].y, resolve_color(8) );
	}

	if ( zsort ) sort_ships();

	for ( i = 0; i < ships_in_world; i++ ) {
		for ( j = 0; j < world[i].type.ship_model.num_points; j++ ) {
			x[ i*MAX_SHIP_POINTS + j ] = (int) (( 
				(double)zoom * (world[i].location.x + 
					world[i].type.ship_model.points[j].x )) / 
				(world[i].location.z + 
					world[i].type.ship_model.points[j].z + 1) ) 
				+ half_screen_width;
			y[ i*MAX_SHIP_POINTS + j ] = -(int) (( 
				(double)zoom * (world[i].location.y + 
					world[i].type.ship_model.points[j].y )) / 
				(world[i].location.z + 
					world[i].type.ship_model.points[j].z + 1) ) 
				+ half_screen_height;
		}
		for ( j = 0; j < world[i].type.ship_model.num_lines; j++ ) {
			if ( world[i].location.z > 0 )
				draw_line(
				x[ i*MAX_SHIP_POINTS + world[i].type.ship_model.line_start[j] ],
				y[ i*MAX_SHIP_POINTS + world[i].type.ship_model.line_start[j] ],
				x[ i*MAX_SHIP_POINTS + world[i].type.ship_model.line_end[j] ],
				y[ i*MAX_SHIP_POINTS + world[i].type.ship_model.line_end[j] ],
				resolve_color(world[i].color)
				);
		}
	}
	

	/* TODO: You know the drill...  */
	/*
	for ( i = 0; i < ships_in_world; i++ ) {
		x[0] = (int)(( (double)zoom * world[i].location.x ) / 
				(world[i].location.z + 1)) 
				+ half_screen_width;
		y[0] = -(int)(( (double)zoom * world[i].location.y ) / 
				(world[i].location.z + 1)) 
				+ half_screen_height;
		if ( world[i].location.z > 0 )
			draw_line( x[0], y[0], x[0]+1, y[0] + 1, resolve_color(10) );
			
	}

	for ( i = 0; i < ships_in_world; i++ ) {
		int j;
		for ( j = 0; j < 8; j++ ) {
			x[0] = (int)(( (double)zoom * 
				(world[i].location.x + 
					world[i].type.ship_model.hitbox.p[j].x ) ) / 
				( (world[i].location.z + 
					world[i].type.ship_model.hitbox.p[j].z ) + 1)) 
				+ half_screen_width;
			y[0] = -(int)(( (double)zoom * 
				(world[i].location.y + 
					world[i].type.ship_model.hitbox.p[j].y ) ) / 
				( (world[i].location.z + 
					world[i].type.ship_model.hitbox.p[j].z ) + 1)) 
				+ half_screen_height;
			if ( world[i].location.z > 0 )
				draw_line( x[0], y[0], x[0]+1, y[0] + 1, resolve_color(10) );
		}
	}
	*/
	/* ... END OF DRILL ... */


	/* TODO: Fix up crosshair: */
	draw_line( half_screen_width, half_screen_height - 3, 
		half_screen_width, half_screen_height + 3, resolve_color(10));
	draw_line( half_screen_width - 3, half_screen_height, 
		half_screen_width + 3, half_screen_height, resolve_color(10));

	draw_map();

	/* "LOUD" text */
	if ( loud_text_time > 0 ) {
		double scale = screen_width / (strlen(loud_text) + 3);
		print(loud_text, scale, half_screen_height - (scale/2), 15, scale);
	}

	/* HUD! */
	sprintf(str, "Speed: %i / %i", (int)(player.speed*100), 
		(int)(player.type.max_speed*100) );
	
	print(str, 5, screen_height - (half_screen_height / 15), 10, 
		(half_screen_height / 20));

	sprintf(str, "Hull: %i", (int)(player.current_hull_strength));
	print(str, 5, screen_height - 2*(half_screen_height / 15), 10, 
		(half_screen_height / 20));

	sprintf(str, "Armor: %i", (int)(player.current_armor));
	print(str, 5, screen_height - 3*(half_screen_height / 15), 10, 
		(half_screen_height / 20));

	if ( player.fire_again_counter > 0 ) 
		print("cooling", 5, screen_height - 4*(half_screen_height / 15), 10, 
			(half_screen_height / 20));
	/* END HUD */

}

void display_loud_text(char *s, int duration) {
	loud_text_time = duration;
	loud_text = s;	
}

void sdl_game_loop() {
	SDL_Event event;
	Uint8 *keystates = SDL_GetKeyState( NULL );
	double pdp, pdr, pdy, damping, delta;

	pdp = 0;
	pdr = 0;
	pdy = 0;
	
	SDL_ShowCursor( SDL_DISABLE );
	gamestate = GS_NORMAL_PLAY;

	delta = player.type.turn_speed / 5;
	damping = player.type.turn_speed / 50;
	
	display_loud_text("Welcome to Pocket Starfighter", 60);
	while ( gamestate != GS_SHUTDOWN ) {
		SDL_Delay( 50 ); /* 20 FPS */
		SDL_UpdateRect( screen, 0, 0, 0, 0);
		while ( SDL_PollEvent(&event) ) {
			if ( event.type == SDL_QUIT ) {	gamestate = GS_SHUTDOWN; }
			if ( keystates[SDLK_ESCAPE] ) { 
				gamestate = GS_QUIT_MENU; 
			}

			if ( keystates[SDLK_x] && gamestate == GS_NORMAL_PLAY ) {
				player.speed += player.type.max_speed / 10;
				if ( player.speed > player.type.max_speed )
					player.speed = player.type.max_speed;
			}
			if ( keystates[SDLK_z] && gamestate == GS_NORMAL_PLAY ) {
				player.speed -= player.type.max_speed / 10;
				if ( player.speed < 0 )
					player.speed = 0;
			}

			if ( keystates[SDLK_BACKSPACE] && gamestate == GS_NORMAL_PLAY )
				player.speed = 0;

			if ( keystates[SDLK_TAB] && gamestate == GS_NORMAL_PLAY )
				player.speed = player.type.max_speed;

			if ( keystates[SDLK_w] ) pdp += delta;
			if ( keystates[SDLK_s] ) pdp -= delta;
			if ( keystates[SDLK_d] ) pdy += delta;
			if ( keystates[SDLK_a] ) pdy -= delta;
			if ( keystates[SDLK_e] ) pdr += delta;
			if ( keystates[SDLK_q] ) pdr -= delta;

			if ( keystates[SDLK_RETURN] && gamestate == GS_PAUSED )
				gamestate = GS_NORMAL_PLAY;

			if ( keystates[SDLK_p] && gamestate != GS_PAUSED )
				gamestate = GS_PAUSED;

			if ( keystates[SDLK_y] && gamestate == GS_QUIT_MENU ) {
				gamestate = GS_SHUTDOWN;
			} else if ( keystates[SDLK_n] && gamestate == GS_QUIT_MENU ) {
				gamestate = GS_NORMAL_PLAY;
			}

			if ( keystates[SDLK_SPACE] && gamestate == GS_NORMAL_PLAY ) {
				player_attack();
			}

			/* F11 is the Angie-Key */
			if ( keystates[SDLK_F11] && gamestate == GS_NORMAL_PLAY ) {
				display_loud_text("puppies", 30);
			}

			if ( keystates[SDLK_F12] ) {
				char filename[25];
				sprintf(filename, "%ld.bmp", time(NULL));
				SDL_SaveBMP( screen, filename );
			}

		}

		if ( gamestate == GS_NORMAL_PLAY ) {
			int i;
			if ( pdp > player.type.turn_speed )
				pdp = player.type.turn_speed;
			else if ( pdp < -player.type.turn_speed )
				pdp = -player.type.turn_speed;
			if ( pdr > player.type.turn_speed )
				pdr = player.type.turn_speed;
			else if ( pdr < -player.type.turn_speed )
				pdr = -player.type.turn_speed;
			if ( pdy > player.type.turn_speed )
				pdy = player.type.turn_speed;
			else if ( pdy < -player.type.turn_speed )
				pdy = -player.type.turn_speed;

			if ( pdp > 0 ) pdp -= damping;
			else if ( pdp < 0 ) pdp += damping;
			if ( pdy > 0 ) pdy -= damping;
			else if ( pdy < 0 ) pdy += damping;
			if ( pdr > 0 ) pdr -= damping;
			else if ( pdr < 0 ) pdr += damping;
		
			
			if ( pdy != 0 || pdr != 0 || pdp != 0 )
				rotate_world(pdp,pdr,pdy);

			move_debris(player.speed, pdp, pdr, pdy);
			
			if ( fabs(pdp) < MOVE_THRESHOLD ) pdp = 0;
			if ( fabs(pdr) < MOVE_THRESHOLD ) pdr = 0;
			if ( fabs(pdy) < MOVE_THRESHOLD ) pdy = 0;


			if ( player.speed > 0 ) {
				move_world(0,0,-player.speed);
			}

			for ( i = 0; i < ships_in_world; i++ ) {
				do_ship_action(i);
				if ( world[i].current_armor < world[i].type.max_armor ) {
					world[i].current_armor++;
				}
			}
			
			if ( player.fire_again_counter > 0 ) player.fire_again_counter--;
			if ( loud_text_time > 0 ) loud_text_time--;

			if ( player.current_armor < player.type.max_armor ) {
				player.current_armor++;
			}


			fix_overflow();
			render();
		} else if ( gamestate == GS_QUIT_MENU ) {
			print("Are you sure: y/n", 10, 10, 15, screen_width / 20);
		} else if ( gamestate == GS_PAUSED ) {
			print("Game Paused", screen_width / 15, screen_height/3, 15,
				 screen_height/15);
			print("press enter to continue", screen_width / 25, 
				2*screen_height/3, 15,
				 screen_height/25);
		} else if ( gamestate == GS_LOST ) {
			print("You have lost", screen_width / 15, 
				half_screen_height - screen_width / 15, 15,
				screen_width / 15);
		}


		flush_screen();


	}
}


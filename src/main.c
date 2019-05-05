/*
    Pocket Starfighter -- A Wireframe 3D Space Dogfight Simulator
    Copyright (C) 2012  Mark Burger

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. (licenses/LICENSE.TXT) If not, 
	see <http://www.gnu.org/licenses/>.

 */


#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ai.h"
#include "world.h"
#include "ships.h"
#include "sdl.h"

#define NUM_SHIP_CLASSES 6

/*
Command line (so far): 
			-tp (target practice)
			-bw
			-vidmode [width] [height] [bpp]
            -p [alpha | beta | gamma | delta | epsilon]
			-fs
			-ne [number] (def: 3)
			-et [string containing 'a', 'b', 'g', 'd', 'e'] (def: "abgde")
			-nzo (disables z-order)
			-god (like TP, but ships move)
			-mute
			-nopd (disables proportional damage)

Adding ships: Add model points, add model lines, add hitbox,
	add parameters, add 
	one to NUM_SHIP_CLASSES, add the representing letter to the char 
	ship_classes[], add the name to the -p option for parsing, 
	add the appropriate model to the loop for the add_ship_to_world
	call, and add appropriate references in ships.h ... it's a lot
	of stuff. :-(

*/

int main(int argc, char *argv[]) {
	int i;
	char j;
	short int classet = 0;
	int width = 640;
	int height = 480;
	int bpp = 8;
	int fs = 0;
	int num_enemies = 3;

	/* TODO: Tinker with this when you've got more classes */
	char ship_classes[NUM_SHIP_CLASSES] = "abgdez";

	srand( time(NULL) );
	monochrome = 0;
	zsort = 1;
	mute = 0;
	target_practice = 0;
	god_mode = 0;
	proportional_damage = 1;
	
	build_ships();

	for ( i = 0; i < argc; i++ ) {
		if ( !strcmp( argv[i], "-vidmode" ) && i + 3 < argc ) {
			width = atoi(argv[i+1]);
			height = atoi(argv[i+2]);
			bpp = atoi(argv[i+3]);
			printf("Using width %i, height %i, %i bpp...\n",
				width, height, bpp);
			i += 3;
		} else if ( !strcmp( argv[i], "-vidmode" ) ) {
			printf("-vidmode expects three arguments.\n");
		} else if ( !strcmp( argv[i], "-nzo" ) ) {
			zsort = 0;
		} else if ( !strcmp( argv[i], "-fs") ) {
			fs = 1;
			printf("Using fullscreen.\n");
		} else if ( !strcmp( argv[i], "-p" ) && i + 1  < argc ) {
			i++;
			classet = 1;
			if ( !strcmp(argv[i], "alpha") ) {
				player.type = alpha_class;
			} else if ( !strcmp(argv[i], "beta") ) {
				player.type = beta_class;
			} else if ( !strcmp(argv[i], "gamma") ) {
				player.type = gamma_class;
			} else if ( !strcmp(argv[i], "delta") ) {
				player.type = delta_class;
			} else if ( !strcmp(argv[i], "epsilon") ) {
				player.type = epsilon_class;
			} else if ( !strcmp(argv[i], "zeta") ) {
				player.type = zeta_class;
			} else {
				fprintf(stderr, "Couldn't find ship class %s. Using default.\n",
					argv[i] );
				classet = 0;
			}
		} else if ( !strcmp( argv[i], "-ne") && i + 1 < argc ) {
			i++;
			num_enemies = atoi(argv[i]);
			if ( num_enemies > MAX_SHIPS )
				num_enemies = MAX_SHIPS;
			if ( num_enemies < 0 )
				num_enemies = 0;
		} else if ( !strcmp( argv[i], "-et") && i + 1 < argc ) {
			i++;
			if ( strlen(argv[i]) > NUM_SHIP_CLASSES ) continue;
			memset(ship_classes, '\0', NUM_SHIP_CLASSES);
			strcpy(ship_classes, argv[i]);
		} else if ( !strcmp( argv[i], "-bw") ) {
			monochrome = 1;
		} else if ( !strcmp( argv[i], "-mute") ) {
			mute = 1;
		} else if ( !strcmp( argv[i], "-tp") ) {
			target_practice = 1;
		} else if ( !strcmp( argv[i], "-god") ) {
			god_mode = 1;
		} else if ( !strcmp( argv[i], "-nopd") ) {
			proportional_damage = 0;
		}
		
	}

	start_video(width, height, bpp, fs);
	if ( !mute ) start_audio();	

	if ( !classet ) {
		player.type = alpha_class;
	}

	start_world();
	ships_in_world = 0;

	for ( i = 0; i < num_enemies; i++ ) {
		j = ship_classes[ rand() % NUM_SHIP_CLASSES ];
		while ( j == '\0' ) {
			j = ship_classes[ rand() % NUM_SHIP_CLASSES ];
		}
		if ( j == 'a' )
			add_ship_to_world( alpha_class );
		if ( j == 'b' )
			add_ship_to_world( beta_class );
		if ( j == 'g' )
			add_ship_to_world( gamma_class );
		if ( j == 'd' )
			add_ship_to_world( delta_class );
		if ( j == 'e' )
			add_ship_to_world( epsilon_class );
		if ( j == 'z' )
			add_ship_to_world( zeta_class );
	}


	sdl_game_loop();

	return 0;
}


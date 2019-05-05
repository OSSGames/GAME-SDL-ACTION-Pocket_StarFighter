#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "sdl.h"
#include "geometry.h"
#include "ships.h"
#include "world.h"

struct ship world[MAX_SHIPS];
struct debris debrisfield[MAX_DEBRIS];

int world_point_index;
int ships_in_world;
struct ship player;

void start_world() {
	int i;

	origin = make_point(0,0,0);

	player.location = make_point(0,0,1);
	player.pitch = 0;
	player.yaw = 0;
	player.roll = 0;
	player.speed = 0;
	world_point_index = 0;

	player.current_hull_strength = player.type.hull_strength;
	player.current_armor = player.type.max_armor;

	for ( i = 0; i < MAX_DEBRIS; i++ ) {
		debrisfield[i].x = rand() % screen_width;
		debrisfield[i].y = rand() % screen_height;
	}
}

void warp_ship(int whichone) {
	double dx, dy, dz;

	struct point newloc = make_point(
		rand() % 30, rand() % 30, rand() % 30	
	);

	dx = world[whichone].location.x - newloc.x;
	dy = world[whichone].location.y - newloc.y;
	dz = world[whichone].location.z - newloc.z;

	world[whichone].location = newloc;

}

void fix_overflow() {
	int i;
	for ( i = 0; i < ships_in_world; i++ ) {
		if ( 
			fabs( world[i].location.x ) - 20 >= ( FLT_MAX - 20 )  ||
			fabs( world[i].location.y ) - 20 >= ( FLT_MAX - 20 )  ||
			fabs( world[i].location.z ) - 20 >= ( FLT_MAX - 20 ) 
			) {
			warp_ship(i);
		}
	}
}

void move_debris(double speed, double pdp, double pdr, double pdy) {
	int i;
	double f, d, dx, dy;
	speed *= 5;
	for ( i = 0; i < MAX_DEBRIS; i++ ) {
		debrisfield[i].x -= 500*pdy;
		debrisfield[i].y -= 500*pdp;
		

		if ( pdr != 0 ) {
			d = sqrt( pow( debrisfield[i].y - half_screen_height, 2) +
				pow(debrisfield[i].x - half_screen_width, 2) );
			f = atan2( debrisfield[i].y - half_screen_height, 
				debrisfield[i].x - half_screen_width);
			debrisfield[i].x = half_screen_width + d * cos( f - pdr );
			debrisfield[i].y = half_screen_height + d * sin( f - pdr );
		}

		if ( speed > 0 ) {
			dx = 3* fabs( half_screen_width - debrisfield[i].x ) / 
				half_screen_width;

			dy = 3* fabs( half_screen_height - debrisfield[i].y ) / 
				half_screen_height;

			if ( debrisfield[i].x < half_screen_width )
				debrisfield[i].x -= speed * dx;
			else debrisfield[i].x += speed * dx; 

			if ( debrisfield[i].y < half_screen_height ) 
				debrisfield[i].y -= speed * dy;
			else debrisfield[i].y += speed * dy; 
		}
	
		if ( debrisfield[i].x < 1 || debrisfield[i].x > screen_width ) 
			debrisfield[i].x = rand() % screen_width; 
		if ( debrisfield[i].y < 1 || debrisfield[i].y > screen_height )
			debrisfield[i].y = rand() % screen_height; 

	}	
}

void move_world(double dx, double dy, double dz) {
	int i;
	for ( i = 0; i < ships_in_world; i++ ) {
		world[i].location = move_point(
				world[i].location, make_point(dx, dy, dz) );
	}
}

void rotate_world(double dp, double dr, double dy) {
	int i, j;
	
	player.location = rotate_point( player.location, dp, dr, dy );
	for ( i = 0; i < ships_in_world; i++ ) {
		world[i].controller = rotate_point(world[i].controller,
			dp, dr, dy);
		for ( j = 0; j < world[i].type.ship_model.num_points; j++ ) {
			world[i].type.ship_model.points[j] = rotate_point(
				world[i].type.ship_model.points[j], dp, dr, dy );
		}
		for ( j = 0; j < 8; j++ ) {
			world[i].type.ship_model.hitbox.p[j] = rotate_point(
				world[i].type.ship_model.hitbox.p[j], dp, dr, dy );
		}
		world[i].location = rotate_point( world[i].location, dp, dr, dy);
		world[i].pitch += dp;
		world[i].roll += dr;
		world[i].yaw += dy;
	}

}

struct point rotate_point(struct point p, double dp, double dr, double dy) {
	double temprot, dist;

	/* Roll */
	temprot = atan2( p.y, p.x );
	dist = sqrt( pow( p.x, 2) + pow(p.y, 2) );
	p.x = dist*cos(temprot + dr);
	p.y = dist*sin(temprot + dr);

	/* Yaw */
	temprot = atan2( p.z, p.x );
	dist = sqrt( pow( p.x, 2) + pow(p.z, 2) );
	p.z = dist*sin(temprot + dy);
	p.x = dist*cos(temprot + dy);

	/* Pitch */
	temprot = atan2( p.y, p.z );
	dist = sqrt( pow( p.z, 2) + pow(p.y, 2) );
	p.z = dist*cos(temprot + dp);
	p.y = dist*sin(temprot + dp);
	return p;
}

void remove_ship_from_world(int whichone) {
	world[whichone] = world[ships_in_world - 1];
	ships_in_world--;	
}

void add_ship_to_world(struct ship_template t) {
	struct ship s;

	s.speed = t.max_speed;
	s.type = t;
	s.action = GOTO_JOUST_POINT;
	s.action_ticks = -(100 + rand() % 300);
	s.fire_again_counter = 0;

	s.current_hull_strength = s.type.hull_strength;
	s.current_armor = s.type.max_armor;

	s.color = ( ships_in_world % 15 ) + 1;

	s.controller = make_point(0,0,1);

	s.location = make_point( 
		rand() % 300 - 150, 
		rand() % 300 - 150, 
		rand() % 300 - 150 );

	s.pitch = 0;
	s.yaw = 0;
	s.roll = 0;

	world[ships_in_world] = s;

	rotate_ship(ships_in_world, 
		(double)(rand() % 100) / 100 * 6.283,
		(double)(rand() % 100) / 100 * 6.283,
		(double)(rand() % 100) / 100 * 6.283
	);


	ships_in_world++;

}

#include <stdlib.h>
#include "sdl.h"
#include "geometry.h"
#include "world.h"

char target_practice;
char god_mode;
char proportional_damage;

void rotate_ship_toward_point(int whichone, struct point p) {
	struct ship *ship = &world[whichone];
	double theta = ship->type.turn_speed / 2;
	double dist2;
	double dist;
	double dp, dr, dy;


	dist = distance(p, 
		move_point( 
			rotate_point(ship->controller, theta, 0, 0), ship->location ) );

	dist2 = distance(p, 
		move_point( 
			rotate_point(ship->controller, -theta, 0, 0), ship->location ) );

	if ( dist2 < dist ) dp = -theta;
	else dp = theta;

	dist = distance(p, 
		move_point( 
			rotate_point(ship->controller, 0, theta, 0), ship->location ) );

	dist2 = distance(p, 
		move_point( 
			rotate_point(ship->controller, 0, -theta, 0), ship->location ) );

	if ( dist2 < dist ) dr = -theta;
	else dr = theta;

	dist = distance(p, 
		move_point( 
			rotate_point(ship->controller, 0, 0, theta), ship->location ) );

	dist2 = distance(p, 
		move_point( 
			rotate_point(ship->controller, 0, 0, -theta), ship->location ) );

	if ( dist2 < dist ) dy = -theta;
	else dy = theta;

	rotate_ship(whichone, dp, dr, dy);

}

void hurt_ship(int attacker, int victim) {
	struct ship *a;
	struct ship *v;
	float partial;
	double dmg;

	/* It's alright. I know. I'm the bomb. */
	if ( attacker >= 0 ) a = &world[attacker];
	else a = &player;

	if ( victim >= 0 ) v = &world[victim];
	else v = &player;

	if ( victim < 0 && god_mode ) return;

	partial = ( (float)(rand() % 100) / 100) * 
		a->type.dmg_per_shot_additional;
	dmg = ( partial +
		a->type.dmg_per_shot_base) * player.type.num_laser_cannons;

	if ( proportional_damage && victim < 0 )
		dmg = dmg / ships_in_world;

	v->current_armor -= dmg;
	if ( v->current_armor < 0 ) {
		v->current_hull_strength += v->current_armor;
		v->current_armor = 0;
	}
	if ( v->current_hull_strength < 0 ) {
		if ( victim >= 0 ) {
			remove_ship_from_world( victim );
			play_sound(ESPLODE);
			display_loud_text("enemy explodes", 40);
		} else {
			play_sound(PSPLODE);
			gamestate = GS_LOST;
		}
	}

}

void player_attack() {
	int i;
	struct point p = make_point(0,0,player.type.laser_range);

	if ( ships_in_world == 0 ) {
		display_loud_text("no enemies left", 40);
	}

	if ( player.fire_again_counter > 0 ) return;
	else player.fire_again_counter = player.type.laser_fire_rate;

	play_sound(PSHOOT);

	for ( i = 0; i < ships_in_world; i++ ) {
		if ( strikes(origin, p, i) ) {
			play_sound(EHIT);
			display_loud_text("hit", 10);
			hurt_ship( -1, i );
		}
	}
}

void do_ship_action(int whichone) {
	struct ship *ship = &world[whichone];

	if ( target_practice ) return;

	if ( ship->fire_again_counter > 0 ) ship->fire_again_counter--;

	if ( ship->action == GOTO_JOUST_POINT || ship->action == TRACK_ATTACK ) {
		move_ship(whichone);
	} 
	if ( ship->action == ROTATE_TO_JOUST_POINT ) {
		rotate_ship_toward_point(whichone, move_point(ship->location,
			ship->joust_vector) );
		move_ship(whichone);
	} 
	if ( ship->action == ROTATE_TO_PLAYER || ship->action == TRACK_ATTACK ) {
		rotate_ship_toward_point(whichone, origin );
		move_ship(whichone);
	}
	ship->action_ticks++;
	
	if ( ship->action == TRACK_ATTACK ) {
		struct point tack = move_point(
			scale_point(ship->controller, ship->type.laser_range),
			ship->location);
		if ( strikes(tack, origin, -1) && ship->fire_again_counter == 0 ) {
			ship->fire_again_counter = ship->type.laser_fire_rate;
			hurt_ship(whichone, -1);
			if ( !god_mode ) {
				display_loud_text("ouch", 10);
				play_sound(PHIT);
			}
		} 

		if ( distance(ship->location, origin ) > 10 ) {
			ship->speed = ship->type.max_speed;
		} else {
			ship->action = ROTATE_TO_JOUST_POINT;
			ship->action_ticks = 0;
		}
	}

	if ( ship->action_ticks > 120 ) {
		ship->action_ticks = 0;
		if ( ship->action == GOTO_JOUST_POINT ) {
			ship->action = ROTATE_TO_PLAYER;
			ship->speed = ship->type.max_speed / 5;
		} else if ( ship->action == ROTATE_TO_PLAYER ) {
			ship->action = TRACK_ATTACK;
			ship->action_ticks = 70;
		} else if ( ship->action == TRACK_ATTACK ) {
			ship->action = ROTATE_TO_JOUST_POINT;
			ship->speed = ship->type.max_speed / 10;
			ship->action_ticks -= rand() % 500;
		} else if ( ship->action == ROTATE_TO_JOUST_POINT ) {
			ship->action = GOTO_JOUST_POINT;
			ship->action_ticks -= rand() % 500;
			ship->speed = ship->type.max_speed;
		}
	}



}

/* TODO: reduce this to one line */
void move_ship(int whichone) {
	struct ship *ship = &world[whichone];
	struct point nl = move_point(ship->location, 
		scale_point(ship->controller, ship->speed) );
	ship->location = nl;

}

void rotate_ship(int whichone, double dp, double dr, double dy ) {
	struct ship *ship = &world[whichone];
	int i;

	for (i = 0; i < ship->type.ship_model.num_points; i++ ) {
		ship->type.ship_model.points[i] = 
			rotate_point(ship->type.ship_model.points[i], dp, dr, dy);
	}
	ship->controller = rotate_point(ship->controller, dp, dr, dy);

	ship->pitch += dp;
	ship->yaw += dy;
	ship->roll += dr;

	prevent_rotational_overflow( &ship->pitch );
	prevent_rotational_overflow( &ship->roll );
	prevent_rotational_overflow( &ship->yaw );

}



#ifndef _SHIPS_H_
#define _SHIPS_H_

#include "geometry.h"
	
enum ai_action { GOTO_JOUST_POINT, ROTATE_TO_JOUST_POINT, ROTATE_TO_PLAYER,
	 TRACK_ATTACK }; 


/* 
	Attacks are (num_laser_cannons)*(dmg_per_shot_base + 
		(rand()*dmg_per_shot_additional))
	Attacks damage armor first, which regenerates at some rate (to be determined
		during play testing) before damaging the hull itself, which doesn't
		regenerate.
	Once the hull integrity is zero, the ship is destroyed.
	Color is QBColor, without black (1 = blue, 2 = green, 3 = cyan, 4 = red,
		5 = magenta, 6 = yellow, 7 = white, 8 = gray, 9 = bright blue,
		10 = bright green, 11 = bright cyan, 12 = bright red, 
		13 = bright magenta, 14 = bright yellow, 15 = bright white ).
*/
struct ship_template {
	struct model ship_model;
	double max_speed;
	double turn_speed;
	double num_laser_cannons;
	double laser_fire_rate;
	double laser_range;
	double dmg_per_shot_base;
	double dmg_per_shot_additional;
	double max_armor;
	double hull_strength;
};

/* TODO: Maybe make armor/strength stuff into ints? */

struct ship {
	struct ship_template type;

	enum ai_action action;
	struct point joust_vector;
	int action_ticks;

	double speed;
	double pitch;
	double yaw;
	double roll;
	double current_armor;
	double current_hull_strength;
	int color;
	int fire_again_counter;
	struct point controller;
	struct point location;
};

void build_ships();


extern struct ship_template alpha_class;
extern struct ship_template beta_class;
extern struct ship_template gamma_class;
extern struct ship_template delta_class;
extern struct ship_template epsilon_class;
extern struct ship_template zeta_class;

#endif

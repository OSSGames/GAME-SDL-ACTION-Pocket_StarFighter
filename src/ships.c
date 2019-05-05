#include <stdlib.h>
#include <limits.h>
#include "world.h"
#include "geometry.h"
#include "ships.h"

struct ship_template alpha_class;
struct ship_template beta_class;
struct ship_template gamma_class;
struct ship_template delta_class;
struct ship_template epsilon_class;
struct ship_template zeta_class;


void build_ships() {
	/* This is all here because I don't want to bundle data files. */
	struct point term = make_point(-INT_MAX, -INT_MAX, -INT_MAX);

	struct model alpha_model;
	struct model beta_model;
	struct model gamma_model;
	struct model delta_model;
	struct model epsilon_model;
	struct model zeta_model;

	insert_model_points( gamma_model.points,
		make_point(-5, 1.2, 1), make_point(-5, 1.2, -1), make_point(5, 1.2, 1),
		make_point(5, 1.2, -1), make_point(4, -1, 0), make_point(4, -1, -2),
		make_point(-4, -1, 0), make_point(-4, -1, -2), make_point(-1, 1, 2), 
		make_point(1, 1, 2), make_point(0, -1, -6), make_point(0, -1, 2), 
		make_point(0, -.5, -4), make_point(0, 1, -6), term
	);
	insert_model_lines( gamma_model.line_start, gamma_model.line_end,
		0, 1, 1, 3, 2, 3, 0, 2, 4, 5, 4, 6, 7, 5, 6, 7, 8, 10, 9, 10, 11, 
		10, 8, 9, 9, 11, 8, 11, 10, 13, 12, 13, -1);
	insert_hitbox_points(gamma_model.hitbox.p, 
		make_point(-5,-1,2), make_point(5,2,-6), make_point(-5,2,2), 
		make_point(5,-1,-6), make_point(5,-1,2), make_point(-5,2,-6),
		make_point(5,2,2), make_point(-5,-1,-6) );

	gamma_model.num_points = 14;
	gamma_model.num_lines = 16;
	gamma_class.turn_speed = 0.25;
	gamma_class.max_speed = 1.0;
	gamma_class.ship_model = gamma_model;

	gamma_class.num_laser_cannons = 2;
	gamma_class.laser_range = 100;
	gamma_class.max_armor = 200;
	gamma_class.hull_strength = 200;
	gamma_class.dmg_per_shot_base = 40;
	gamma_class.dmg_per_shot_additional = 30;
	gamma_class.laser_fire_rate = 10;



	insert_model_lines(alpha_model.line_start, alpha_model.line_end, 
		0, 1, 0, 3, 1, 2, 2, 3, 2, 9, 2, 11, 3, 8, 3, 10, 4, 7, 4, 5, 5, 6, 
		6, 7, 6, 9, 6, 11, 7, 8, 7, 10, 8, 10, 8, 12, 9, 11, 10, 11, 10, 12, 
		13, 14, 13, 15, 13, 16, 14, 15, 14, 16, 15, 16, 17, 18, 17, 19, 17, 
		20, 18, 19, 18, 20, 19, 20, -1);
	
	insert_model_points(alpha_model.points,
		make_point(-6,0,-3), make_point(-5,0,0), make_point(-1,0,1), 
		make_point(-1,0,-3), make_point(6,0,-3), make_point(5,0,0), 
		make_point(1,0,1), make_point(1,0,-3), make_point(0,0,-4), 
		make_point(0,0,3), make_point(0,1,-3), make_point(0,1,2), 
		make_point(0,2,-4), make_point(-2,-.5,0), make_point(-3,-.5,0), 
		make_point(-2.5,0,0), make_point(-2.5,0,2), make_point(3,-.5,0), 
		make_point(2,-.5,0), make_point(2.5,0,0), make_point(2.5,0,2),
		term
		);

	insert_hitbox_points(alpha_model.hitbox.p,
		make_point(-6,-1,-5), make_point(-6,2,-5), make_point(-6,-1,3),
		make_point(-6,2,3), make_point(6,-1,3), make_point(6,2,3),
		make_point(6,-1,-5), make_point(6,2,-5) );


	alpha_model.num_points = 21;
	alpha_model.num_lines = 33;
	alpha_class.ship_model = alpha_model;
	alpha_class.turn_speed = 0.065;	
	alpha_class.max_speed = 0.8;

	alpha_class.num_laser_cannons = 4;
	alpha_class.laser_range = 150;
	alpha_class.max_armor = 500;
	alpha_class.hull_strength = 200;
	alpha_class.dmg_per_shot_base = 20;
	alpha_class.dmg_per_shot_additional = 15;
	alpha_class.laser_fire_rate = 5;


	insert_model_points( beta_model.points, 
		make_point(-3,0,-3),  make_point(-3,0,-2), make_point(0,0,3), 
		make_point(3,0,-2), make_point(3,0,-3), make_point(-1, 1.5,-3), 
		make_point(0,2,-3), make_point(1,1.5,-3), make_point(0,0,-3),
		term);
	insert_model_lines( beta_model.line_start, beta_model.line_end,
		0, 1, 1, 2, 1, 2, 2, 3, 2, 6, 2, 8, 2, 5, 2, 7, 3, 4, 0, 4, 7, 8, 5, 
		8, 6, 8, -1);

	insert_hitbox_points(beta_model.hitbox.p,
		make_point(-3,0,-3), make_point(-3,2,3), 
		make_point(-3,0,3),
		make_point(-3,2,-3), make_point(3,0,3), make_point(3,2,3),
		make_point(3,0,-3), make_point(3,2,-3) );


	beta_model.num_points = 9;
	beta_model.num_lines = 13;
	beta_class.ship_model = beta_model;

	beta_class.turn_speed = 0.1;
	beta_class.max_speed = 1.5;
	beta_class.num_laser_cannons = 1;
	beta_class.laser_range = 100;
	beta_class.max_armor = 500;
	beta_class.hull_strength = 150;
	beta_class.dmg_per_shot_base = 75;
	beta_class.dmg_per_shot_additional = 75;
	beta_class.laser_fire_rate = 5;

	insert_model_points( delta_model.points,
		make_point(0,0,2), make_point(-1,0,0), make_point(0,1,0), 
		make_point(1,0,0), make_point(0,-1,0), make_point(0,0,-4), 
		make_point(0,3,-5), make_point(0,1,-6), make_point(0,2,-5), 
		make_point(0,-2,-5), make_point(0,-1,-6), make_point(0,-3,-5), 
		make_point(-3,0,-5), make_point(-1,0,-6), make_point(-2,0,-5), 
		make_point(2,0,-5), make_point(1,0,-6), make_point(3,0,-5),
		term );
	insert_hitbox_points(delta_model.hitbox.p,
		make_point(-3,3,2), make_point(3,3,2), make_point(-3,-3,2),
		make_point(3,-3,2), make_point(-3,-3,-6), make_point(-3,3,-6),
		make_point(3,3,-6), make_point(3,-3,-6) );
	insert_model_lines( delta_model.line_start, delta_model.line_end,
		0, 1, 0, 2, 0, 3, 0, 4, 1, 2, 2, 3, 3, 4, 1, 4, 5, 1, 5, 2, 
		5, 3, 5, 4, 5, 12, 5, 14, 13, 12, 13, 14, 5, 15, 5, 17, 16, 15, 
		16, 17, 5, 6, 5, 8, 7, 6, 7, 8, 5, 11, 5, 9, 10, 11, 10, 9, -1);

	delta_model.num_points = 18;
	delta_model.num_lines = 29;
	delta_class.ship_model = delta_model;
	delta_class.turn_speed = 0.03;
	delta_class.max_speed = 2.0;

	delta_class.num_laser_cannons = 1;
	delta_class.laser_range = 150;
	delta_class.max_armor = 200;
	delta_class.hull_strength = 200;
	delta_class.dmg_per_shot_base = 60;
	delta_class.dmg_per_shot_additional = 80;
	delta_class.laser_fire_rate = 5;



	insert_model_points( epsilon_model.points,
		make_point(-3,3,1), make_point(-3,3,-3), make_point(-1,1,-1), 
		make_point(-1,1,1), make_point(-3,-3,1), make_point(-3,-3,-3), 
		make_point(-1,-1,-1), make_point(-1,-1,1), make_point(3,3,1), 
		make_point(3,3,-3), make_point(1,1,-1), make_point(1,1,1), 
		make_point(3,-3,1), make_point(3,-3,-3), make_point(1,-1,-1), 
		make_point(1,-1,1), make_point(0,0,-5), term );
	insert_hitbox_points( epsilon_model.hitbox.p,
		make_point(-3, -3, 1), make_point(-3, -3, -5), make_point(-3, 3, 1),
		make_point(-3, 3, -5), make_point(3, -3, 1), make_point(3, -3, -5),
		make_point(3, 3, 1), make_point(3, 3, -5) );
	insert_model_lines( epsilon_model.line_start, epsilon_model.line_end,
		0, 1, 0, 3, 1, 2, 2, 3, 4, 5, 4, 7, 5, 6, 6, 7, 8, 9, 8, 11, 9, 10, 
		10, 11, 12, 13, 12, 15, 13, 14, 14, 15, 2, 10, 3, 11, 6, 14, 7, 15, 
		2, 6, 3, 7, 10, 14, 11, 15, 16, 2, 16, 6, 16, 10, 16, 14, -1 );

	epsilon_model.num_lines = 28;
	epsilon_model.num_points = 17;
	epsilon_class.ship_model = epsilon_model;
	epsilon_class.turn_speed = 0.7;
	epsilon_class.max_speed = 2.0;

	epsilon_class.num_laser_cannons = 4;
	epsilon_class.laser_range = 75;
	epsilon_class.max_armor = 200;
	epsilon_class.hull_strength = 100;
	epsilon_class.dmg_per_shot_base = 40;
	epsilon_class.dmg_per_shot_additional = 20;
	epsilon_class.laser_fire_rate = 20;


	insert_model_points( zeta_model.points, 
		make_point(-6, 1, 0), make_point(-6, 1, -2), make_point(-3, 0, -2), 
		make_point(-3, 0, 0), make_point(3, 0, 0), make_point(3, 0, -2), 
		make_point(6, 1, -2), make_point(6, 1, 0), make_point(-1, 0, 1), 
		make_point(0, -1.5, 1), make_point(1, 0, 1), make_point(0,0, -7), 
		make_point(2.5, -1, -3), make_point(3, 0, -3), 
		make_point(3.5, -1, -3), make_point(3, 0, 1), make_point(-3, 0, 1), 
		make_point(-2.5, -1, -3), make_point(-3, 0, -3), 
		make_point(-3.5, -1, -3), make_point(0, 1, -7), make_point(0, 0, -5),
		term);

	insert_hitbox_points( zeta_model.hitbox.p, 
		make_point(-6, 1, 1), make_point(-6, 1, -7), make_point(6, 1, -7),
		make_point(6, 1, 1), make_point(-6, -1.5, 1), make_point(-6, -1.5, -7), 
		make_point(6, -1.5, -7), make_point(6, -1.5,1) );    

	insert_model_lines( zeta_model.line_start, zeta_model.line_end,
		0, 1, 1, 2, 2, 3, 0, 3, 2, 5, 3, 4, 4, 5, 5, 6, 6, 7, 4, 7, 8, 9, 
		9, 10, 8, 10, 9, 11, 8, 11, 10, 11, 12, 15, 13, 15, 14, 15, 12, 13, 
		13, 14, 12, 14, 17, 16, 18, 16, 19, 16, 17, 18, 18, 19, 17, 19, 11, 
		20, 20, 21, -1);


	zeta_model.num_lines = 30;
	zeta_model.num_points = 22;
	zeta_class.ship_model = zeta_model;

	zeta_class.turn_speed = 0.065;
	zeta_class.max_speed = 1.0;

	zeta_class.num_laser_cannons = 4;
	zeta_class.laser_range = 75;
	zeta_class.max_armor = 300;
	zeta_class.hull_strength = 200;
	zeta_class.dmg_per_shot_base = 45;
	zeta_class.dmg_per_shot_additional = 20;
	zeta_class.laser_fire_rate = 10;


}



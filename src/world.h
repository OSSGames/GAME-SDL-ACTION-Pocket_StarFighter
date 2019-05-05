#define MAX_SHIPS 84
#define MAX_DEBRIS 50

#ifndef _WORLD_H_
#define _WORLD_H_

#include "ships.h"

struct debris {
	float x; 
	float y;
};

void warp_ship(int whichone);
void fix_overflow();
void add_ship_to_world(struct ship_template t);
void remove_ship_from_world(int whichone);

void move_ship(int whichone);
void move_world(double dx, double dy, double dz);
void rotate_world(double dp, double dr, double dy);
void rotate_ship(int whichone, double dp, double dr, double dy );
void rotate_ship_toward_point(int whichone, struct point p);
void start_world();
void move_debris(double speed, double pdp, double pdr, double pdy);
void rotate_ship_toward_player(int whichone);
struct point rotate_point(struct point p, double dp, double dr, double dy);

extern struct ship player;
extern struct ship world[MAX_SHIPS];
extern struct debris debrisfield[MAX_DEBRIS];

extern int world_point_index;
extern int ships_in_world;


#endif

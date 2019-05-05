#define MAX_SHIP_POINTS 25
#define MAX_SHIP_LINES 35
#include "letters.h"

#ifndef _geometry_h_
#define _geometry_h_

struct point {
	double x;
	double y;
	double z;
};

struct box {
	struct point p[8];
};

struct model {
	int num_points;
	int num_lines;
	struct box hitbox;
	struct point points[MAX_SHIP_POINTS];
	int line_start[MAX_SHIP_LINES];
	int line_end[MAX_SHIP_LINES]; 
};

void prevent_rotational_overflow( double *n );

/* I think I've made my point here.*/
struct point make_point(double x, double y, double z);
struct point move_point(struct point p, struct point d);
struct point scale_point(struct point p, double scalar);

void insert_letter_ints(int l[2*LINES_PER_LETTER], int x, ...);
void insert_letter_floats(float l[LINES_PER_LETTER], double x, ...);
void insert_model_points(struct point list[MAX_SHIP_POINTS], 
	struct point p, ...);
void insert_hitbox_points(struct point list[8], struct point p, ...);
void insert_model_lines(int list_start[MAX_SHIP_LINES], 
		int list_end[MAX_SHIP_LINES], int a, ...);

double distance(struct point a, struct point b);
int strikes(struct point a, struct point b, int whichone );

extern struct point origin;

#endif

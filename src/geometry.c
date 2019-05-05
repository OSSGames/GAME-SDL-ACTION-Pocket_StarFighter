#include <stdarg.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include "letters.h"
#include "world.h"
#include "ships.h"
#include "geometry.h"

struct point origin;

struct point make_point(double x, double y, double z) {
	struct point r;
	r.x = x;
	r.y = y;
	r.z = z;
	return r;
}

struct point move_point(struct point p, struct point d) {
	struct point rp;
	rp.x = p.x + d.x;
	rp.y = p.y + d.y;
	rp.z = p.z + d.z;
	return rp;
}

struct point scale_point(struct point p, double scalar) {
	struct point rp;
	rp.x = p.x * scalar;
	rp.y = p.y * scalar;
	rp.z = p.z * scalar;
	return rp;
}

void prevent_rotational_overflow( double *n ) {
	if ( *n > 6.283 ) *n -= 6.283;
	if ( *n < 6.283 ) *n += 6.283;
}


double distance(struct point a, struct point b) {
	return sqrt( pow( a.x - b.x, 2 ) + pow( a.y - b.y, 2) + pow( a.z - b.z, 2));
}

/* The order of a is start, end, start, end, 
   NOT start, start, start, end, end, end */
void insert_model_lines(int list_start[MAX_SHIP_LINES], 
		int list_end[MAX_SHIP_LINES], int a, ...) {
	va_list arglist;
	int i, j;


	va_start(arglist, a);
	for ( i = 0; i < MAX_SHIP_LINES; i++ ) {
		list_start[i] = a;
		a = va_arg(arglist, int);

		list_end[i] = a;
		a = va_arg(arglist, int);
		if ( a < 0 ) { break; }
	}
	
	for ( j = i+1; j < MAX_SHIP_LINES; j++ ) {
		list_start[j] = 0;
		list_end[j] = 0;
	}

	va_end(arglist);
}

void insert_letter_ints(int l[2*LINES_PER_LETTER], int x, ...) {
	va_list arglist;
	int i;
	va_start(arglist, x);

	for ( i = 0; i < 2*LINES_PER_LETTER; i++ ) {
		l[i] = x;
		if ( x < 0 ) break;
		x = va_arg(arglist, int);
	}
	va_end(arglist);
}

void insert_letter_floats(float l[POINTS_PER_LETTER], double x, ...) {
	va_list arglist;
	int i;
	va_start(arglist, x);

	for ( i = 0; i < POINTS_PER_LETTER; i++ ) {
		l[i] = x;
		x = va_arg(arglist, double);
		if ( x < 0 ) break;
	}
	va_end(arglist);
}


void insert_hitbox_points(struct point list[8], struct point p, ...) {
	va_list arglist;
	int i = 0;

	va_start(arglist, p);
	while ( i < 8 ) {
		list[i] = p;
		p = va_arg(arglist, struct point);
		i++;
	}
	va_end(arglist);
}

void insert_model_points(struct point list[MAX_SHIP_POINTS], 
		struct point p, ...) {
	va_list arglist;
	int i = 0;

	va_start(arglist, p);
	while ( i < MAX_SHIP_POINTS ) {
		list[i] = p;
		p = va_arg(arglist, struct point);
		if ( p.x == -INT_MAX && p.y == -INT_MAX && p.z == -INT_MAX ) break;
		i++;
	}
	i++;
	while ( i < MAX_SHIP_POINTS ) {
		list[i] = make_point(0,0,0);
		i++;
	}
	va_end(arglist);
}


int strikes(struct point a, struct point b, int whichone ) {
	int qYtestA = 0;
	int qPtestA = 0;
	int qYtestB = 0;
	int qPtestB = 0;

	int i;

	double thQyawA[8];
	double thQpitchA[8];
	double thQyawB[8];
	double thQpitchB[8];

	double thPyawA = atan2( (b.z - a.z), (b.x - a.x) );
	double thPpitchA = atan2( (b.y - a.y), (b.x - a.x) );

	double thPyawB = atan2( (a.z - b.z), (a.x - b.x) );
	double thPpitchB = atan2( (a.y - b.y), (a.x - b.x) );

	struct box q;

	for ( i = 0; i < 8; i++ ) {
		if ( whichone >= 0 )
	   		q.p[i] = move_point( world[whichone].type.ship_model.hitbox.p[i],
				world[whichone].location );
		else q.p[i] = player.type.ship_model.hitbox.p[i];
	}

	for ( i = 0; i < 8; i++ ) {
		thQyawA[i] = atan2(q.p[i].z - a.z, q.p[i].x - a.x);
		thQpitchA[i] = atan2(q.p[i].y - a.y, q.p[i].x - a.x);

		thQyawB[i] = atan2(q.p[i].z - b.z, q.p[i].x - b.x);
		thQpitchB[i] = atan2(q.p[i].y - b.y, q.p[i].x - b.x);
	}


	for ( i = 0; i < 8; i++ ) {
		if ( thQyawA[i] > thPyawA ) qYtestA++;
		else qYtestA--;
		if ( thQpitchA[i] > thPpitchA ) qPtestA++;
		else qPtestA--;

		if ( thQyawB[i] > thPyawB ) qYtestB++;
		else qYtestB--;
		if ( thQpitchB[i] > thPpitchB ) qPtestB++;
		else qPtestB--;
	}
	

	if ( abs(qPtestA) < 8 && abs(qPtestB) < 8 && 
		 abs(qYtestA) < 8  && abs(qYtestB) < 8 ) return 1;

	return 0;
}

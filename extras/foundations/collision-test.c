#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct point3D {
	double x;
	double y;
	double z;
};

struct line3D {
	struct point3D a;
	struct point3D b;
};

struct shape3D {
	struct point3D p[8];
};

struct point3D buildPoint(double x, double y, double z) {
	struct point3D p;
	p.x = x;
	p.y = y;
	p.z = z;
	return p;
}
struct line3D buildLine(struct point3D a, struct point3D b) {
	struct line3D l;	
	l.a = a;
	l.b = b;
	return l;
}

double distance(struct point3D a, struct point3D b) {
	return sqrt( pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2) );
}

int collides(struct line3D l, struct shape3D q) {
	int qYtestA = 0;
	int qPtestA = 0;
	int qYtestB = 0;
	int qPtestB = 0;

	int i;

	double thQyawA[8];
	double thQpitchA[8];
	double thQyawB[8];
	double thQpitchB[8];

	double thPyawA = atan2( (l.b.z - l.a.z), (l.b.x - l.a.x) );
	double thPpitchA = atan2( (l.b.y - l.a.y), (l.b.x - l.a.x) );

	double thPyawB = atan2( (l.a.z - l.b.z), (l.a.x - l.b.x) );
	double thPpitchB = atan2( (l.a.y - l.b.y), (l.a.x - l.b.x) );

	for ( i = 0; i < 8; i++ ) {
		thQyawA[i] = atan2(q.p[i].z - l.a.z, q.p[i].x - l.a.x);
		thQpitchA[i] = atan2(q.p[i].y - l.a.y, q.p[i].x - l.a.x);

		thQyawB[i] = atan2(q.p[i].z - l.b.z, q.p[i].x - l.b.x);
		thQpitchB[i] = atan2(q.p[i].y - l.b.y, q.p[i].x - l.b.x);
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

int main(int argc, char *argv[]) {
	struct line3D line_collides;
	struct line3D line_collides2;
	struct line3D line_collides3;
	struct line3D line_doesnt_collide1;
	struct line3D line_doesnt_collide2;
	struct line3D line_might_collide;
	struct shape3D shape;

	/* Not in proper order. (;-) */
	shape.p[0] = buildPoint(2,2,2);
	shape.p[1] = buildPoint(2,2,3);
	shape.p[2] = buildPoint(2,3,2);
	shape.p[3] = buildPoint(2,3,3);
	shape.p[4] = buildPoint(3,2,2);
	shape.p[5] = buildPoint(3,2,3);
	shape.p[6] = buildPoint(3,3,2);
	shape.p[7] = buildPoint(3,3,3);

	line_collides = buildLine( buildPoint(0,0,0), buildPoint(24,24,24));
	line_collides2 = buildLine( buildPoint(4,4,5), buildPoint(0,0,0));
	line_collides3 = buildLine( buildPoint(2.5,2.5,8), 
		buildPoint(2.5,2.5,-2.5));

	line_might_collide = buildLine( buildPoint(0,0,0), buildPoint(2.5,2.5,2.5));


	/* passes beside */
	line_doesnt_collide1 = buildLine(buildPoint(0,0,0), buildPoint(0,5,0) );

	/* Doesn't reach... */
	line_doesnt_collide2 = buildLine(buildPoint(0,0,0), buildPoint(1,1,1) );


	printf( "Test one: %i\n", collides(line_collides, shape));
	printf( "Test two: %i\n", collides(line_collides2, shape));
	printf( "Test three: %i\n", collides(line_collides3, shape));
	printf( "Test four: %i\n", collides(line_doesnt_collide1, shape));
	printf( "Test five: %i\n", collides(line_doesnt_collide2, shape));
	printf( "Test six: %i\n", collides(line_might_collide, shape));




	return 0;
}

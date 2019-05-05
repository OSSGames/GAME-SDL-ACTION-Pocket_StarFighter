
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#define MAX_POINTS 100
#define MAX_LINES 200


struct point3d {
	double x;
	double y;
	double z;
};

struct line3d {
	int a;
	int b;
};


/* FUNCTIONS --- */
void setup();
int add_point_p( struct point3d p );
int add_point(double x, double y, double z);
void add_line(double x1, double y1, double z1, double x2, 
	double y2, double z2);
void add_line_p(struct point3d a, struct point3d b);
void draw_line(SDL_Surface *surface, double x1, double y1, 
		double x2, double y2);
void render();
void rotate(double p, double y, double r);
void move(double x, double y, double z);
void rotate2(double p, double y, double r);
void add_platform(double x1, double y1, double x2, double y2, double z);
void wiggle_mouse(Uint16 x, Uint16 y);

/* Globals n' stuff... */
int point_index = 0;
int line_index = 0;
int box_index = 0;

int sensitivity = 1;
double pitch = 0;

struct point3d pointlist[MAX_POINTS];
struct line3d linelist[MAX_LINES];
struct box3d boxlist[MAX_BOXES];

SDL_Surface *screen = NULL;


/* Kilroy was here. */
int add_point_p( struct point3d p ) {
	return add_point( p.x, p.y, p.z );
}

int add_point(double x, double y, double z) {
	struct point3d addpoint;
	int i = 0;
	for ( i = 0 ; i < point_index; i++ ) {
		if ( pointlist[i].x == x && pointlist[i].y == y && 
			pointlist[i].z == z ) {
			return i;
		}
	}
	if ( point_index >= MAX_LINES ) {
		fprintf( stderr, "Too many points defined. Point %i ignored!\n", 
			point_index);
		return 0;
	}
	addpoint.x = x;
	addpoint.y = y;
	addpoint.z = z;
	pointlist[point_index] = addpoint;
	point_index++;
	return point_index - 1;
}

void add_line(double x1, double y1, double z1, double x2, 
	double y2, double z2) {
	struct point3d a;
	struct point3d b;
	a.x = x1;
	a.y = y1;
	a.z = z1;
	b.x = x2;
	b.y = y2;
	b.z = z2;
	add_line_p(a, b);
	
}

void add_line_p(struct point3d a, struct point3d b) {
	int ia = add_point_p( a );
	int ib = add_point_p( b );
	struct line3d addline;
	addline.a = ia;
	addline.b = ib;
	if ( line_index >= MAX_LINES ) {
		fprintf(stderr, "Too many lines defined! Point %i ignored!\n",
			line_index);
		return;
	}
	linelist[line_index] = addline;
	line_index++;
	return;
}

void add_box(double x1, double y1, double z1, double x2, double y2, 
		double z2 ) {
	struct box3d p;
	double s;
	int a, b;
	if ( box_index >= MAX_BOXES ) {
		fprintf(stderr, "Too many lines defined! Box %i ignored!\n",
			box_index);
		return;
	}
	if ( x1 > x2 ) {
		s = x1;
		x1 = x2;	
		x2 = s;
	}
	if ( y1 > y2 ) {
		s = y1;
		y1 = y2;
		y2 = s;
	}
	if ( z1 > z2 ) {
		s = z1;
		z1 = z2;
		z2 = s;
	}
	a = add_point( x1, y1, z1 );
	b = add_point( x2, y2, z2 );
	p.a = a;
	p.b = b;
	boxlist[box_index] = p;	
	box_index++;
	return;
}

void draw_line(SDL_Surface *surface, double x1, double y1, 
		double x2, double y2) {
	double dist = sqrt( pow(x2 - x1, 2) + 
		pow( y2 - y1, 2) );
	SDL_Rect rect;
	double x, y, p;
	int j = 0;
	Uint32 white = SDL_MapRGB( surface->format, 255, 255, 255);
	int i = 0;
	rect.x = x1;
	rect.y = y1;
	rect.w = 2;
	rect.h = 2;

	for ( i = 0; i <= dist; i+= 2 ) {
		p = (double)i / dist;
		x = x1 + p*(x2 - x1);
		y = y1 + p*(y2 - y1);
		rect.x = (int)x;
		rect.y = (int)y;
		/* Unlike QBasic, SDL gets whiney if you go off the edge. */
		if ( rect.x >= 0 && rect.y >= 0 && 
				(rect.x + rect.w) <= 640 && (rect.y + rect.h <= 480) ) {
			SDL_FillRect( surface, &rect, white);
		}
		j++;
		if ( j > 640 ) { return; }
	}
	SDL_UpdateRect(surface, 0,0,0,0);
}


void render() {
	SDL_Rect area;
	SDL_Surface *buffer = SDL_CreateRGBSurface(SDL_SWSURFACE, 640, 480, 8, 
		255, 255, 255, 0);
	int i;
	double x1, y1, z1, x2, y2, z2;
	double zoom;
	zoom = 220;

	for ( i = 0; i < line_index; i++ ) {
		x1 = pointlist[ linelist[i].a ].x;
		y1 = pointlist[ linelist[i].a ].y;
		z1 = pointlist[ linelist[i].a ].z;

		x2 = pointlist[ linelist[i].b ].x;
		y2 = pointlist[ linelist[i].b ].y;
		z2 = pointlist[ linelist[i].b ].z;

		if ( z1 < 0 && z2 < 0 ) continue;

		if (z1 <= 0) { z1 = 0; }
		if (z2 <= 0) { z2 = 0; }

		x1 = zoom * x1 * ( 1 / (z1 + 1)) + 320;
		y1 = zoom * y1 * ( 1 / (z1 + 1)) + 240;

		x2 = zoom * x2 * ( 1 / (z2 + 1)) + 320;
		y2 = zoom * y2 * ( 1 / (z2 + 1)) + 240;

		draw_line( buffer, x1, y1, x2, y2 );
	}
	
	
	/* Perform blit! */
	area.x = 0;
	area.y = 0;
	area.w = 640;
	area.h = 480;
	if ( SDL_BlitSurface( buffer, &area, screen, &area ) < 0 ) {
		fprintf(stderr, "Blit error?!");
	}
	
}

int main(int argc, char *argv[]) {
	char run = 1;
	SDL_Event event;
	int delay = 20;
	Uint8 *keystates = SDL_GetKeyState( NULL );
	setup();
	while ( run == 1 ) {
		SDL_Delay(delay);
		while ( SDL_PollEvent(&event) ) {
			if ( event.type == SDL_QUIT ) {	run = 0; }
		}
		if ( keystates[SDLK_ESCAPE] ) { run = 0; }
		else if ( keystates[SDLK_UP] ) { rotate(.03,0,0); }
		else if ( keystates[SDLK_DOWN] ) { rotate(-.03,0,0);  }
		else if ( keystates[SDLK_LEFT] ) { rotate(0,-.03,0); }
		else if ( keystates[SDLK_RIGHT] ) { rotate(0,.03,0);  }
		else if ( keystates[SDLK_w] ) { move(0,0,-.03); }
		else if ( keystates[SDLK_s] ) { move(0,0,.03); }
		else if ( keystates[SDLK_a] ) { move(.03,0,0); }
		else if ( keystates[SDLK_d] ) { move(-.03,0,0); }
		
		render();
		SDL_UpdateRect( screen, 0, 0, 0, 0);
	}
	return 0;
}

void rotate2(double p, double y, double r) {
	double sx, sy, sz;
	int i;
	sx = 0;
	sy = 0;
	sz = 0;
	for ( i = 0; i < point_index; i++ ) {
		sx += pointlist[i].x;
		sy += pointlist[i].y;
		sz += pointlist[i].z;
	}
	sx /= point_index;
	sy /= point_index;
	sz /= point_index;
	move(-sx, -sy, -sz);
	rotate(p, y, r);
	move(sx, sy, sz);
}

void rotate(double p, double y, double r) {
	double oroll, opitch, oyaw, dist;
	int i;
	pitch += p;

	/* 1.57075 is an approximation of pi/2 */
	if ( pitch >= 1.57075 || pitch <=  -1.57075 ) { 
		pitch -= p;  
		return; 
	}

	/* Fix pitch-rotation around a fixed point trouble */
	if ( p != 0 ) {
		move(0, p*0.6366,0);
	}

	for ( i = 0; i < point_index; i++ ) {
		/* atan2 saves some of the fun and games that 
		   we had with the QB version */
		oroll = atan2( pointlist[i].y, pointlist[i].x );
		dist = sqrt( pow( pointlist[i].x, 2) + pow(pointlist[i].y, 2) );
		pointlist[i].x = dist*cos(oroll + r);
		pointlist[i].y = dist*sin(oroll + r);

		opitch = atan2( pointlist[i].y, pointlist[i].z );
		dist = sqrt( pow( pointlist[i].y, 2) + pow(pointlist[i].z, 2) );
		pointlist[i].z = dist*cos(opitch + p);
		pointlist[i].y = dist*sin(opitch + p);

		oyaw = atan2( pointlist[i].z, pointlist[i].x );
		dist = sqrt( pow( pointlist[i].x, 2) + pow(pointlist[i].z, 2) );
		pointlist[i].x = dist*cos(oyaw + y);
		pointlist[i].z = dist*sin(oyaw + y);

	}
}

void move(double x, double y, double z) {
	int i;
	for ( i = 0; i < point_index; i++ ) {
		pointlist[i].x += x;
		pointlist[i].y += y;
		pointlist[i].z += z;
	}
}

void setup() {
	/* SDL nonsense... */
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) {
		printf("Unable to start up SDL.\n");
		exit(1);
	} 
	screen = SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
	if ( screen == NULL ) {
		printf("Unable to set 640x480 video: %s\n", 
			SDL_GetError());
		exit(1);
	}
	SDL_WM_SetCaption("Pocket Starfighter", NULL);
}




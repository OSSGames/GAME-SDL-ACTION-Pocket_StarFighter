#define LINES_PER_LETTER 8
#define POINTS_PER_LETTER 8

#ifndef _LETTERS_H_
#define _LETTERS_H_

struct letter {
	float xs[POINTS_PER_LETTER];
	float ys[POINTS_PER_LETTER];
	int lines[2*LINES_PER_LETTER];
};


struct letter make_letter(char c);

#endif

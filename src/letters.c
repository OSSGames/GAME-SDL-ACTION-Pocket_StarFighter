#include <stdlib.h>
#include "geometry.h"
#include "letters.h"


/* Make some arrays, stuff 'em in a struct, and call it a day. 
	Glyphs have in-built kerning.
*/

struct letter make_letter(char c) {
	struct letter l;

	switch ( c ) {
	case '0': case 'o': case 'O':
		insert_letter_floats(l.xs, 0.3, 0.7, 0.3, 0.7, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 3, 3, 2, 2, 0, -1);
		break;
	case '1':
		insert_letter_floats(l.xs, 0.3, 0.5, 0.5, 0.2, 0.8, -1);
		insert_letter_floats(l.ys, 0.4, 0.2, 0.8, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 3, 4, -1);
		break;
	case '2':
		insert_letter_floats(l.xs, 0.2, 0.5, 0.8, 0.2, 0.8, -1);
		insert_letter_floats(l.ys, 0.4, 0.2, 0.4, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, -1);
		break;
	case '3':
		insert_letter_floats(l.xs, 0.2, 0.5, 0.8, 0.5, 0.8, 0.5, 0.2, -1); 
		insert_letter_floats(l.ys, 0.2, 0.2, 0.4, 0.5, 0.6, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4,4, 5, 5, 6, -1);
		break;
	case '4':
		insert_letter_floats(l.xs, 0.3, 0.3, 0.8, 0.8, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.5, 0.5, 0.2, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1,2, 3, 4, -1);
		break;
	case '5':
		insert_letter_floats(l.xs, 0.2, 0.8, 0.2, 0.5, 0.8, 0.5, 0.2, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.4, 0.4, 0.6, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 0, 2, 2, 3, 3,4, 4, 5, 5, 6, -1);
		break;
	case '6':
		insert_letter_floats(l.xs, 0.2, 0.8, 0.2, 0.8, 0.2, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.5, 0.5, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 0, 4, 2, 3, 3, 5, 4, 5, -1);
		break;
	case '7':
		insert_letter_floats(l.xs, 0.2, 0.8, 0.2, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, -1);
		break;
	case '8':
		insert_letter_floats(l.xs, 0.3, 0.5, 0.7, 0.3, 0.5, 0.7, -1);
		insert_letter_floats(l.ys, 0.3, 0.2, 0.3, 0.7, 0.8, 0.7, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 0, -1);
		break;
	case '9':
		insert_letter_floats(l.xs, 0.2, 0.8, 0.2, 0.8, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.5, 0.5, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 4, 0, 2, 2, 3, -1);
		break;
	case 'a': case 'A':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.5, 0.8, 0.8, -1);
		insert_letter_floats(l.ys, 0.8, 0.5, 0.2, 0.5, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 1, 3, 4, -1);
		break;
	case 'b': case 'B':
		insert_letter_floats(l.xs, 0.2, 0.6, 0.8, 0.6, 0.8, 0.6, 0.2, 0.2, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.3, 0.5, 0.7, 0.8, 0.8, 
			0.5, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 0, 
			3, 7, -1);
		break;
	case 'c': case 'C':
		insert_letter_floats(l.xs, 0.8, 0.3, 0.2, 0.2, 0.3, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.4, 0.6, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, -1);
		break;
	case 'd': case 'D':
		insert_letter_floats(l.xs, 0.2, 0.6, 0.8, 0.6, 0.2, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.5, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, 4, 0, -1);
		break;
	case 'e': case 'E':
		insert_letter_floats(l.xs, 0.2, 0.6, 0.2, 0.6, 0.2, 0.6, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.5, 0.5, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 2, 3, 4, 5, 0, 4, -1);
		break;
	case 'f': case 'F':
		insert_letter_floats(l.xs, 0.2, 0.6, 0.2, 0.6, 0.2, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.5, 0.5, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 2, 3, 0, 4, -1);
		break;
	case 'g': case 'G':
		insert_letter_floats(l.xs, 0.8, 0.4, 0.2, 0.2, 0.8, 0.8, 0.5, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.4, 0.8, 0.8, 0.5, 0.5, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, -1);
		break;
	case 'h': case 'H':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.2, 0.8, 0.8, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.8, 0.5, 0.5, 0.2, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 2, 3, 4, 5, -1);
		break;
	case 'i': case 'I': 
		insert_letter_floats(l.xs, 0.2, 0.8, 0.2, 0.8, 0.5, 0.5, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.8, 0.8, 0.2, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 2, 3, 4, 5, -1);
		break;
	case 'j': case 'J':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.4, 0.6, 0.6, 0.4, 0.8, -1);
		insert_letter_floats(l.ys, 0.6, 0.8, 0.8, 0.6, 0.2, 0.2, 0.2, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, 5, 6, -1);
		break;
	case 'k': case 'K':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.2, 0.6, 0.6, -1);
		insert_letter_floats(l.ys, 0.2, 0.8, 0.5, 0.2, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 2, 3, 2, 4, -1);
		break;
	case 'l': case 'L':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, -1);
		break;
	case 'm': case 'M':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.5, 0.8, 0.8, -1);
		insert_letter_floats(l.ys, 0.8, 0.2, 0.5, 0.2, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, -1);
		break;
	case 'n': case 'N':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.8, 0.8, -1);
		insert_letter_floats(l.ys, 0.8, 0.2, 0.8, 0.2, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, -1);
		break;
	case 'p': case 'P':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.8, 0.8, 0.2, -1);
		insert_letter_floats(l.ys, 0.8, 0.2, 0.2, 0.5, 0.5, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, -1);
		break;
	case 'q': case 'Q':
		insert_letter_floats(l.xs, 0.2, 0.8, 0.8, 0.6, 0.2, 0.5, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.5, 0.8, 0.8, 0.5, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, 4, 0, 5, 6, -1);
		break;
	case 'r': case 'R':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.8, 0.8, 0.2, 0.6, 0.8, -1);
		insert_letter_floats(l.ys, 0.8, 0.2, 0.2, 0.5, 0.5, 0.5, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3 ,4, 5, 6, -1);
		break;
	case 's': case 'S':
		insert_letter_floats(l.xs, 0.8, 0.4, 0.25, 0.4, 0.6, 0.8, 0.6, 0.2, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.4, 0.5, 0.5, 0.6, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 
			-1);
		break;
	case 't': case 'T':
		insert_letter_floats(l.xs, 0.2, 0.8, 0.5, 0.5, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.2, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 2, 3, -1);
		break;
	case 'u': case 'U':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.8, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.8, 0.8, 0.2, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, -1);
		break;
	case 'v': case 'V':
		insert_letter_floats(l.xs, 0.2, 0.5, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.8, 0.2, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, -1);
		break;
	case 'w': case 'W':
		insert_letter_floats(l.xs, 0.2, 0.2, 0.5, 0.8, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.8, 0.5, 0.8, 0.2, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, 3, 4, -1);
		break;
	case 'x': case 'X':
		insert_letter_floats(l.xs, 0.2, 0.8, 0.2, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.8, 0.8, 0.2, -1);
		insert_letter_ints(l.lines, 0, 1, 2, 3, -1);
		break;
	case 'y': case 'Y':
		insert_letter_floats(l.xs, 0.2, 0.5, 0.8, 0.5, -1);
		insert_letter_floats(l.ys, 0.2, 0.5, 0.2, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 1, 3, -1);
		break;
	case 'z': case 'Z':
		insert_letter_floats(l.xs, 0.2, 0.8, 0.2, 0.8, -1);
		insert_letter_floats(l.ys, 0.2, 0.2, 0.8, 0.8, -1);
		insert_letter_ints(l.lines, 0, 1, 1, 2, 2, 3, -1);
		break;
	case '/':
		insert_letter_floats(l.xs, 0.2, 0.8, -1);
		insert_letter_floats(l.ys, 0.8, 0.2, -1);
		insert_letter_ints(l.lines, 0, 1, -1);
		break;
	case ':': case '=':
		insert_letter_floats(l.xs, 0.2, 0.8, 0.2, 0.8, -1);
		insert_letter_floats(l.ys, 0.3, 0.3, 0.5, 0.5, -1);
		insert_letter_ints(l.lines, 0, 1, 2, 3, -1);
		break;
	default: case ' ':
		insert_letter_floats(l.xs, -1);
		insert_letter_floats(l.ys, -1);
		insert_letter_ints(l.lines, -1);
		break;
	}

	return l;
}


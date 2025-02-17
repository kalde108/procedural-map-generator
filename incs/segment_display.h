#ifndef SEGMENT_DISPLAY_H
# define SEGMENT_DISPLAY_H

# include "ft_math.h"

# define SEGMENT_DISPLAY_SIZE 7
# define POINTS_PER_SEGMENT 6
# define TRIANGLES_PER_SEGMENT 4
# define TOTAL_POINTS 26

extern t_v2d_d all_points[TOTAL_POINTS];

/*
 . . 0 . . . . . 1 . .
 . 2 . . . . . . . 3 .
 4 . 5 . . . . . 6 . 7
 . . . . . . . . . . .
 . . . . . . . . . . .
 . . . . . . . . . . .
 . . . . . . . . . . .
 . . . . . . . . . . .
 . . . . . . . . . . .
 8 . 9 . . . . .10 .11
 .12 . . . . . . .13 .
14 .15 . . . . .16 .17
 . . . . . . . . . . .
 . . . . . . . . . . .
 . . . . . . . . . . .
 . . . . . . . . . . .
 . . . . . . . . . . .
 . . . . . . . . . . .
18 .19 . . . . .20 .21
 .22 . . . . . . .23 .
 . .24 . . . . .25 . .
*/

/*
  __a__
||     ||
f|     |b
||__g__||
||     ||
e|     |c
||__d__||

*/

extern int seg_a[TRIANGLES_PER_SEGMENT][3];

extern int seg_b[TRIANGLES_PER_SEGMENT][3];

extern int seg_c[TRIANGLES_PER_SEGMENT][3];

extern int seg_d[TRIANGLES_PER_SEGMENT][3];

extern int seg_e[TRIANGLES_PER_SEGMENT][3];

extern int seg_f[TRIANGLES_PER_SEGMENT][3];

extern int seg_g[TRIANGLES_PER_SEGMENT][3];

// segments variable contains all segments from a to g
extern int *segments[SEGMENT_DISPLAY_SIZE];

enum e_segments
{
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	END
};

extern int zero[7];
extern int one[3];
extern int two[6];
extern int three[6];
extern int four[5];
extern int five[6];
extern int six[7];
extern int seven[4];
extern int eight[8];
extern int nine[7];

int *get_num_arr(int num);

#endif

/*


t_v2d_d all_points[TOTAL_POINTS] = {
	{-0.3, 1.0},
	{0.3, 1.0},
	{-0.4, 0.9},
	{0.4, 0.9},
	{-0.5, 0.8},
	{-0.3, 0.8},
	{0.3, 0.8},
	{0.5, 0.8},
	{-0.5, 0.1},
	{-0.3, 0.1},
	{0.3, 0.1},
	{0.5, 0.1},
	{-0.4, 0},
	{0.4, 0},
	{-0.5, -0.1},
	{-0.3, -0.1},
	{0.3, -0.1},
	{0.5, -0.1},
	{-0.5, -0.8},
	{-0.3, -0.8},
	{0.3, -0.8},
	{0.5, -0.8},
	{-0.4, -0.9},
	{0.4, -0.9},
	{-0.3, -1.0},
	{0.3, -1.0}
};


int seg_a[TRIANGLES_PER_SEGMENT][3] = {
	{0, 2, 5},
	{1, 3, 6},
	{0, 1, 5},
	{1, 6, 5}
};

int seg_b[TRIANGLES_PER_SEGMENT][3] = {
	{3, 7, 6},
	{6, 7, 11},
	{6, 11, 10},
	{10, 11, 13}
};

int seg_c[TRIANGLES_PER_SEGMENT][3] = {
	{13, 17, 16},
	{16, 17, 21},
	{16, 21, 20},
	{20, 21, 23}
};

int seg_d[TRIANGLES_PER_SEGMENT][3] = {
	{23, 25, 20},
	{20, 25, 24},
	{19, 20, 24},
	{19, 24, 22}
};

int seg_e[TRIANGLES_PER_SEGMENT][3] = {
	{12, 15, 14},
	{14, 15, 19},
	{14, 19, 18},
	{18, 19, 22}
};

int seg_f[TRIANGLES_PER_SEGMENT][3] = {
	{2, 4, 5},
	{5, 4, 8},
	{5, 8, 9},
	{9, 8, 12}
};

int seg_g[TRIANGLES_PER_SEGMENT][3] = {
	{9, 15, 12},
	{9, 10, 15},
	{10, 16, 15},
	{10, 13, 16}
};

// segments variable contains all segments from a to g
int *segments[SEGMENT_DISPLAY_SIZE] = {
	seg_a[0],
	seg_b[0],
	seg_c[0],
	seg_d[0],
	seg_e[0],
	seg_f[0],
	seg_g[0]
};

enum e_segments
{
	A = 0,
	B,
	C,
	D,
	E,
	F,
	G,
	END
};

int zero[7] = {A, B, C, D, E, F, END};
int one[3] = {B, C, END};
int two[6] = {A, B, D, E, G, END};
int three[6] = {A, B, C, D, G, END};
int four[5] = {B, C, F, G, END};
int five[6] = {A, C, D, F, G, END};
int six[7] = {A, C, D, E, F, G, END};
int seven[4] = {A, B, C, END};
int eight[8] = {A, B, C, D, E, F, G, END};
int nine[7] = {A, B, C, D, F, G, END};


*/

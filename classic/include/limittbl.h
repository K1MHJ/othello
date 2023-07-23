unsigned limit[64][8] = 
{
	{ 0, 0, 7, 7, 7, 0, 0, 0 },
	{ 0, 0, 6, 6, 7, 1, 1, 0 },
	{ 0, 0, 5, 5, 7, 2, 2, 0 },
	{ 0, 0, 4, 4, 7, 3, 3, 0 },
	{ 0, 0, 3, 3, 7, 4, 4, 0 },
	{ 0, 0, 2, 2, 7, 5, 5, 0 },
	{ 0, 0, 1, 1, 7, 6, 6, 0 },
	{ 0, 0, 0, 0, 7, 7, 7, 0 },
	{ 1, 1, 7, 6, 6, 0, 0, 0 },
	{ 1, 1, 6, 6, 6, 1, 1, 1 },
	{ 1, 1, 5, 5, 6, 2, 2, 1 },
	{ 1, 1, 4, 4, 6, 3, 3, 1 },
	{ 1, 1, 3, 3, 6, 4, 4, 1 },
	{ 1, 1, 2, 2, 6, 5, 5, 1 },
	{ 1, 1, 1, 1, 6, 6, 6, 1 },
	{ 1, 0, 0, 0, 6, 6, 7, 1 },
	{ 2, 2, 7, 5, 5, 0, 0, 0 },
	{ 2, 2, 6, 5, 5, 1, 1, 1 },
	{ 2, 2, 5, 5, 5, 2, 2, 2 },
	{ 2, 2, 4, 4, 5, 3, 3, 2 },
	{ 2, 2, 3, 3, 5, 4, 4, 2 },
	{ 2, 2, 2, 2, 5, 5, 5, 2 },
	{ 2, 1, 1, 1, 5, 5, 6, 2 },
	{ 2, 0, 0, 0, 5, 5, 7, 2 },
	{ 3, 3, 7, 4, 4, 0, 0, 0 },
	{ 3, 3, 6, 4, 4, 1, 1, 1 },
	{ 3, 3, 5, 4, 4, 2, 2, 2 },
	{ 3, 3, 4, 4, 4, 3, 3, 3 },
	{ 3, 3, 3, 3, 4, 4, 4, 3 },
	{ 3, 2, 2, 2, 4, 4, 5, 3 },
	{ 3, 1, 1, 1, 4, 4, 6, 3 },
	{ 3, 0, 0, 0, 4, 4, 7, 3 },
	{ 4, 4, 7, 3, 3, 0, 0, 0 },
	{ 4, 4, 6, 3, 3, 1, 1, 1 },
	{ 4, 4, 5, 3, 3, 2, 2, 2 },
	{ 4, 4, 4, 3, 3, 3, 3, 3 },
	{ 4, 3, 3, 3, 3, 3, 4, 4 },
	{ 4, 2, 2, 2, 3, 3, 5, 4 },
	{ 4, 1, 1, 1, 3, 3, 6, 4 },
	{ 4, 0, 0, 0, 3, 3, 7, 4 },
	{ 5, 5, 7, 2, 2, 0, 0, 0 },
	{ 5, 5, 6, 2, 2, 1, 1, 1 },
	{ 5, 5, 5, 2, 2, 2, 2, 2 },
	{ 5, 4, 4, 2, 2, 2, 3, 3 },
	{ 5, 3, 3, 2, 2, 2, 4, 4 },
	{ 5, 2, 2, 2, 2, 2, 5, 5 },
	{ 5, 1, 1, 1, 2, 2, 6, 5 },
	{ 5, 0, 0, 0, 2, 2, 7, 5 },
	{ 6, 6, 7, 1, 1, 0, 0, 0 },
	{ 6, 6, 6, 1, 1, 1, 1, 1 },
	{ 6, 5, 5, 1, 1, 1, 2, 2 },
	{ 6, 4, 4, 1, 1, 1, 3, 3 },
	{ 6, 3, 3, 1, 1, 1, 4, 4 },
	{ 6, 2, 2, 1, 1, 1, 5, 5 },
	{ 6, 1, 1, 1, 1, 1, 6, 6 },
	{ 6, 0, 0, 0, 1, 1, 7, 6 },
	{ 7, 7, 7, 0, 0, 0, 0, 0 },
	{ 7, 6, 6, 0, 0, 0, 1, 1 },
	{ 7, 5, 5, 0, 0, 0, 2, 2 },
	{ 7, 4, 4, 0, 0, 0, 3, 3 },
	{ 7, 3, 3, 0, 0, 0, 4, 4 },
	{ 7, 2, 2, 0, 0, 0, 5, 5 },
	{ 7, 1, 1, 0, 0, 0, 6, 6 },
	{ 7, 0, 0, 0, 0, 0, 7, 7 }};
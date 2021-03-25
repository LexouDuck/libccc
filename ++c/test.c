
#include <stdlib.h>
#include <stdio.h>

typedef struct s_point_
{
	int x;
	int y;
	struct s_point_* (*incr)(struct s_point_* p);
}		s_point;

s_point* increment(s_point* p)
{
	p->x += 1;
	p->y += 1;
	return (p);
}

s_point newpoint(int x, int y)
{
	s_point result;
	result.x = x;
	result.y = y;
	result.incr = increment;
	return (result);
}

int main()
{
	s_point* b = &(s_point){ 3, 5, increment };//newpoint(3, 5);
	int a = b->incr(b)->incr(b)->incr(b)->incr(b)->incr(b)->x;
	printf("a = %d, b = (%d,%d)\n", a, b->x, b->y);
	return (a);
}

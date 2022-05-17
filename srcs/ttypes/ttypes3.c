#include "ttypes.h"
#include <stdlib.h>

t_vector3_f	*pv3_f(float x, float y, float z)
{
	t_vector3_f	*p;

	p = malloc(sizeof(t_vector3_f));
	p->x = x;
	p->y = y;
	p->z = z;
	return (p);
}

t_vector4	*pv4(int x, int y, int z, int w)
{
	t_vector4	*p;

	p = malloc(sizeof(t_vector4));
	p->x = x;
	p->y = y;
	p->z = z;
    p->w = w;
	return (p);
}

t_vector4_f	*pv4_f(float x, float y, float z, float w)
{
	t_vector4_f	*p;

	p = malloc(sizeof(t_vector4_f));
	p->x = x;
	p->y = y;
	p->z = z;
    p->w = w;
	return (p);
}

#include "libccc_algebra.h"



s_vector3d	Vector3D_Cross(s_vector3d const* v1, s_vector3d const* v2)
{
	s_vector3d result;

	result.x = (v1->y * v2->z) - (v1->z * v2->y);
	result.y = (v1->z * v2->x) - (v1->x * v2->z);
	result.z = (v1->x * v2->y) - (v1->y * v2->x);
	return (result);
}

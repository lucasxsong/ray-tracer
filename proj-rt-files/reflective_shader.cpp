#include "reflective_shader.h"
#include "ray.h"
#include "render_world.h"

vec3 Reflective_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;

    color = (1 - reflectivity) * shader->Shade_Surface(ray, intersection_point, normal, recursion_depth);
    vec3 r = ray.direction - 2 * dot(ray.direction, normal) * normal;
    Ray R(intersection_point, r);

    if(recursion_depth < world.recursion_depth_limit && recursion_depth > 0) {
        return world.Cast_Ray(R, recursion_depth + 1) * reflectivity + color;
    }

    return color;
}

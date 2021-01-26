#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color = color_ambient * world.ambient_color * world.ambient_intensity;

    // I = I_a + I_d + I_s
    // I_a = R_a + L_a
    // I_d = R_d * L_d max(dot(n, l), 0)
    // I_s = R_s * L_s * max(dot(v, r), 0)^alpha
    return color;
}

#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
    Shade_Surface(const Ray &ray, const vec3 &intersection_point,
                  const vec3 &normal, int recursion_depth) const
{
    vec3 color = {0, 0, 0};
    // I_a = R_a * L_a
    vec3 I_a = color_ambient * world.ambient_color * world.ambient_intensity;
    Hit hit;
    color += I_a;

    for (auto a: world.lights)
    {
        vec3 l = a->position - intersection_point; // vec for surface -> light
        vec3 curr_light_color = a->Emitted_Light(l);
        if (world.enable_shadows)
        {
            Ray shadow_ray(intersection_point, l.normalized());
            hit = world.Closest_Intersection(shadow_ray);
            if (hit.object != NULL && hit.dist < l.magnitude())
            {
                // shadow is cast on object -- only return ambient
                continue;
            }
        }

        // I_d = R_d * L_d max(dot(n, l), 0)
        double d = std::max(dot(normal, l.normalized()), 0.0);
        vec3 I_d = color_diffuse * curr_light_color * d;
        color += I_d;

        // I_s = R_s * L_s * max(dot(v, r), 0)^alpha
        // r = 2 * (dot(l, n) * n - 1)
        vec3 r = (2 * dot(l, normal) * normal - l).normalized();
        d = std::max(dot(-(ray.direction.normalized()), r), 0.0);
        vec3 I_s = curr_light_color * color_specular * pow(d, specular_power);
        color += I_s;
    }

    return color;
}

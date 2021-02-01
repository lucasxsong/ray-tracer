#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    // I_a = R_a + L_a
    vec3 I_a = color_ambient * world.ambient_color * world.ambient_intensity;
    color += I_a;
    
    Hit h;

    for (unsigned i = 0; i <world.lights.size(); ++i) {
        Light* curr_light = world.lights.at(i); 
        vec3 light_vec = curr_light -> position - intersection_point;
        if (world.enable_shadows) {
            Ray r(intersection_point, light_vec.normalized());
            h = world.Closest_Intersection(r);
            if(h.dist < light_vec.magnitude() && h.object != NULL ) return color;
        }
        vec3 curr_light_color = curr_light-> Emitted_Light(ray.direction) / light_vec.magnitude_squared();
        
        // I_d = R_d * L_d max(dot(n, l), 0)
        vec3 I_d = color_diffuse * curr_light_color * std::max(dot(normal, light_vec.normalized()), 0.0);
        color += I_d;

        // I_s = R_s * L_s * max(dot(v, r), 0)^alpha
    }


    // I = I_a + I_d + I_s
    // I_a = R_a + L_a
    // I_d = R_d * L_d max(dot(n, l), 0)
    // I_s = R_s * L_s * max(dot(v, r), 0)^alpha
    return color;
}

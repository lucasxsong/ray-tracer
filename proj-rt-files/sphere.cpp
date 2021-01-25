#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray& ray, int part) const
{
    double a, b, c;
    a = ray.direction.magnitude_squared(); 
    b = 2 * dot(ray.direction, (ray.endpoint - center));
    c = (ray.endpoint - center).magnitude_squared() - (radius * radius);

    // our discriminant, from b^2 - 4ac
    double dt= (b * b) - (4 * a * c);

    if (dt < 0) {
        // case where no intersection
        return {NULL, 0, part};
    }

    // need to find t from t_1 and t_2
    double t1 = (-b + sqrt(dt))/(2 * a);
    if (t1 > 0) {
        return {this, t1, part};
    }
    double t2 = (-b - sqrt(dt))/(2 * a);
    if (t2 > 0)  {
        return {this, t1, part};
    }

    return {NULL, 0, part};

    // , t2;



    return {0,0,0};
}

vec3 Sphere::Normal(const vec3& point, int part) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}

#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
Hit Sphere::Intersection(const Ray &ray, int part) const
{
    double a, b, c;
    a = ray.direction.magnitude_squared();
    b = 2 * dot(ray.direction, (ray.endpoint - center));
    c = (ray.endpoint - center).magnitude_squared() - (radius * radius);

    // our discriminant, from b^2 - 4ac
    double dt = (b * b) - (4 * a * c);

    if (dt < 0)
    {
        // case where no intersection
        return {NULL, 0, -1};
    }

    // need to find t from t_1 and t_2
    double t1 = (-b + sqrt(dt)) / (2 * a);
    double t2 = (-b - sqrt(dt)) / (2 * a);
    if (t1 < t2 && t1 >= small_t)
    {
        return {this, t1, part};
    }
    else if (t2 <= t1 && t2 >= small_t)
    {
        return {this, t2, part};
    }
    return {NULL, 0, -1};
}

vec3 Sphere::Normal(const vec3 &point, int part) const
{
    return (point - center).normalized();
}

Box Sphere::Bounding_Box(int part) const
{
    Box box;
    TODO; // calculate bounding box
    return box;
}

#include <iostream>
#include <limits.h>
#include "camera.h"
#include "vectors.h"

//OrthographicCamera(const OrthographicCamera& c){
//    center = c.center;
//    direction = c.direction, up = c.up, horizontal = c.horizontal;
//    size = c.size;
//}

OrthographicCamera& OrthographicCamera:: operator=(const OrthographicCamera c){
    center = c.center;
    direction = c.direction, up = c.up, horizontal = c.horizontal;
    size = c.size;
    return (*this);
}

OrthographicCamera::OrthographicCamera(Vec3f c, Vec3f d, Vec3f u, float s){
    center = c;
    direction = d;
    direction.Normalize();
    up = u;
    up.Normalize();
    if(up.Dot3(direction) != 0){
        up -= (up.Dot3(direction) * up);
        up.Normalize();
    }
    Vec3f::Cross3(horizontal,direction,up);
    horizontal.Normalize();
    size = s;
std::cout<<center<<" "<<direction<<" "<<up<<" "<<horizontal<<" "<<size<<std::endl;
} 

Ray OrthographicCamera::generateRay(Vec2f point){
    float x = point.x(), y = point.y();
    //std::cout<<"x1: "<<x<<" y1: "<<y<<std::endl;
    //x = center.x() + (x-0.5)*size*horizontal.x();
    //y = center.y() + (y-0.5)*size*up.y();
    Vec3f origin = center + (x-0.5)*horizontal*size + (y-0.5)*up*size;
    return Ray(origin, direction);
}

float OrthographicCamera::getTMin() const{
    return INT_MIN;
}

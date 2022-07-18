#include <iostream>
#include <cmath>
#include "ray.h"
#include "hit.h"
#include "sphere.h"

bool Sphere:: intersect(const Ray &r, Hit &h, float tmin){
    //Vec3f ro = r.getOrigin();
    Vec3f ro = r.getOrigin()-center;
    Vec3f rd = r.getDirection();
    double a = 1.0, b= 2.0 * (rd).Dot3(ro), c = (ro).Dot3(ro) - radium*radium; 
    double delta = b*b-4*a*c;
    if(delta<0)    
        return false;
    double d = sqrt(delta);
    double t1 = (-b+d)/(2*a);
    double t2 = (-b-d)/(2*a);
    double t;
    // if(t1>0 && t2>0){
    //     t = (t1-t2)>epsilon?t2:t1;
    // }
    // else if(t1>=epsilon)
    //     t = t1;
    // else if(t2>=epsilon)
    //     t = t2;
    // else
    //     return false;
    // if(t>tmin && t<h.getT()){
    //     // update t and material and ray
    //     h.set(t,material,r);
    //     return true;
    // }
    //std::cout<<"t1: "<<t1<<" t2: "<<t2<<std::endl;
    if(t1 > tmin && t1 < h.getT()){
        if(t2 > tmin && t2 <h.getT()){
            t = (t1-t2)>epsilon?t2:t1;
            h.set(t,material,r);
            return true;
        }
        else{
            h.set(t1,material,r);
            return true;
        }
    }
    else if(t2 > tmin && t2 <h.getT()){
        h.set(t2,material,r);
        return true;
    }
    else
        return false;
}

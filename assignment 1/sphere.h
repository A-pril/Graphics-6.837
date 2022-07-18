#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Object3D.h"

class Sphere: public Object3D {

public:
    Sphere(){
        center = Vec3f();
        radium = 0;
        material = NULL;
    }
    Sphere(Vec3f c, float r, Material *m){
        center = c;
        radium = r;
        material = m;
    }
    ~Sphere(){}
    virtual bool intersect(const Ray &r, Hit &h, float tmin);

private:
    Vec3f center;
    float radium;
};

#endif // _SPHERE_H_

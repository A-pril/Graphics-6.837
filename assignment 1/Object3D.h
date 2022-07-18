#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include "vectors.h"
#include "material.h"
#include "hit.h"

class Object3D{

public:
    double epsilon = 1e-3;
    Object3D(){
        material = NULL;
    }
    Object3D(Material *m){
        material = m;
    }
    ~Object3D(){}
    virtual bool intersect(const Ray &r, Hit &h, float tmin) = 0;

    Vec3f color;
    Material *material;
};

#endif

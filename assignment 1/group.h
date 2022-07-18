#ifndef _GROUP_H_
#define _GROUP_H_

#include "Object3D.h"
#include "ray.h"
#include "hit.h"
#include <iostream>
#include <vector>

class Group: public Object3D{
public:
    Group(){}
    Group(int num){
        number = num;
    }
    ~Group(){}
    void addObject(int index, Object3D *obj); 
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    int Get_Number();
private:
    Object3D* objects[100]; 
    int number;

};

#endif // _GROUP_H_

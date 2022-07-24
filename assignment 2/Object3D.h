#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include <iostream>
#include "vectors.h"
#include "material.h"
#include "matrix.h"
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

class Group: public Object3D{
public:
    Group(){}
    Group(const int num){
        number = num;
        objects = new Object3D*[num];
    }
    ~Group(){}
    void addObject(int index, Object3D *obj); 
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    int Get_Number();
private:
    Object3D** objects; 
    int number;

};

class Plane: public Object3D{
public:
    Plane(){};
    ~Plane(){};
    Plane(Vec3f &n, float d, Material *m){
        normal = n;
        this->d = -d;
        material = m;
    }
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
private:
    Vec3f normal;
    float d;
};

class Triangle: public Object3D{
public:
    Triangle(){};
    ~Triangle(){};
    Triangle(Vec3f &a, Vec3f &b, Vec3f &c, Material *m){
        this->a = a;
        this->b = b;
        this->c = c;
        material = m;
    }
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
private:
    Vec3f a,b,c;
};

class Transform: public Object3D{
public:
    Transform(){};
    ~Transform(){};
    Transform(Matrix &m, Object3D *o){
        this->m = m;
        this->obj = o;
    }
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
private:
    Matrix m;
    Object3D *obj;
};

#endif

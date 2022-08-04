#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

#include <iostream>
#include <GL/freeglut.h>
#include "vectors.h"
#include "material.h"
#include "matrix.h"
#include "hit.h"
#define PI 3.1415926

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
    virtual void paint() = 0;
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
    virtual void paint();
    Vec3f Get_point(float phi, float theta);
    static void Set_theta_phi(int phi, int theta) {
        step_phi = phi;
        step_theta = theta;
        delta_phi = PI / phi;
        delta_theta =  2 * PI / theta;
    }
    static void Set_gouraud(){
	    gouraud = true;
    }
    static bool gouraud;

private:
    Vec3f center;
    float radium;
public:
    //const static int step_phi = 10, step_theta = 5;
    static int step_phi, step_theta;
    //float delta_phi = 2 * PI / step_phi, delta_theta = PI / step_theta;
    static float delta_phi, delta_theta;
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
    virtual void paint();

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
        this->d = d;
        material = m;
    }
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    virtual void paint();

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
        Vec3f ab = b - a, bc = c - b;
        Vec3f::Cross3(normal, ab, bc);
        normal.Normalize();
    }
    virtual bool intersect(const Ray &r, Hit &h, float tmin);
    virtual void paint();

private:
    Vec3f a,b,c;
    Vec3f normal;
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
    virtual void paint();

private:
    Matrix m;
    Object3D *obj;
};

#endif

#ifndef _CAMERA_H_
#define _CAMERA_H_


// ====================================================================
// Here are the prototypes for five pure virtual functions for
// initializing, placing, dollying, trucking, and rotating an
// OpenGL camera.  These should be added to the Camera class and
// each of its subclasses
// ====================================================================

#include <GL/freeglut.h>

#include <iostream>
#include "ray.h"
#include "vectors.h"
#include "matrix.h"

class Camera{
public:
   Camera(){}
   ~Camera(){}
   virtual Ray generateRay(Vec2f point) = 0;
   virtual float getTMin() const = 0;
   virtual void glInit(int w, int h) = 0;
   virtual void glPlaceCamera(void) = 0;
   virtual void dollyCamera(float dist) = 0;
   virtual void truckCamera(float dx, float dy) = 0;
   virtual void rotateCamera(float rx, float ry) = 0;
};

class OrthographicCamera: public Camera{
public:
   OrthographicCamera(){}
   //OrthographicCamera(const OrthographicCamera& c);
   OrthographicCamera(Vec3f c, Vec3f d, Vec3f u, float s);
   ~OrthographicCamera(){}
   OrthographicCamera& operator=(const OrthographicCamera c);
   virtual Ray generateRay(Vec2f point);
   virtual float getTMin() const;
   virtual void glInit(int w, int h);
   virtual void glPlaceCamera(void);
   virtual void dollyCamera(float dist);
   virtual void truckCamera(float dx, float dy);
   virtual void rotateCamera(float rx, float ry);

private:
    Vec3f center;
    Vec3f direction, up, horizontal;
    float size;
};

class PerspectiveCamera: public Camera{
public:
   PerspectiveCamera(){};
   ~PerspectiveCamera(){};
   PerspectiveCamera(Vec3f &c, Vec3f &direction, Vec3f &up, float angle);
   virtual Ray generateRay(Vec2f point);
   virtual float getTMin() const;
   virtual void glInit(int w, int h);
   virtual void glPlaceCamera(void);
   virtual void dollyCamera(float dist);
   virtual void truckCamera(float dx, float dy);
   virtual void rotateCamera(float rx, float ry);

private:
   Vec3f center;
   Vec3f direction, up, horizontal;
   float angle;
};


#endif // _CAMERA_H_

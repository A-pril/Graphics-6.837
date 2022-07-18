#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <iostream>
#include "ray.h"
#include "vectors.h"

class Camera{
public:
   Camera(){}
   ~Camera(){}
   virtual Ray generateRay(Vec2f point) = 0;
   virtual float getTMin() const = 0;
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

private:
    Vec3f center;
    Vec3f direction, up, horizontal;
    float size;
};

#endif // _CAMERA_H_

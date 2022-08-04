// ====================================================================
// OPTIONAL: 3 pass rendering to fix the specular highlight 
// artifact for small specular exponents (wide specular lobe)
// ====================================================================

#define GLUT_DISABLE_ATEXIT_HACK
// Included files for OpenGL Rendering
#include <GL/freeglut.h>
// include glCanvas.h to access the preprocessor variable SPECULAR_FIX
#include "glCanvas.h"  
#include <cmath>
#include <algorithm>
#include <iostream>

#ifdef SPECULAR_FIX
// OPTIONAL:  global variable allows (hacky) communication 
// with glCanvas::display
extern int SPECULAR_FIX_WHICH_PASS;
#endif


#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "vectors.h"
#include "ray.h"
#include "hit.h"

// ====================================================================
// ====================================================================

// You will extend this class in later assignments

class Material {

public:

  // CONSTRUCTORS & DESTRUCTOR
  Material(const Vec3f &d_color) { diffuseColor = d_color; }
  virtual ~Material() {}

  // ACCESSORS
  virtual Vec3f getDiffuseColor() const { return diffuseColor; }
  virtual Vec3f Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, 
     const Vec3f &lightColor) const = 0;
  // ====================================================================
  // Add this function prototype to the Material class and each of
  // its subclasses.
  // ====================================================================
  virtual void glSetMaterial(void) const = 0;

protected:
  // REPRESENTATION
  Vec3f diffuseColor;
  
};


class PhongMaterial: public Material{
public:
  PhongMaterial(const Vec3f &diffuseColor): Material(diffuseColor){}
  ~PhongMaterial(){}
  PhongMaterial::PhongMaterial(const Vec3f &diffuseColor, 
     const Vec3f &specularColor, float exponent): Material(diffuseColor){
      // this->diffuseColor = diffuseColor;
      this->specularColor = specularColor;
      this->exponent = exponent;
     }

  virtual Vec3f Shade(const Ray &ray, const Hit &hit, const Vec3f &dirToLight, 
     const Vec3f &lightColor) const{
        Vec3f normal = hit.getNormal();
        //kd
        Vec3f color = diffuseColor * lightColor * std::max(normal.Dot3(dirToLight),0.0f);

        Vec3f dirToCamera = ray.getDirection() * (-1.0f);
        dirToCamera.Normalize();
        Vec3f halfway = dirToCamera + dirToLight;
        halfway.Normalize();
        color += specularColor * lightColor * pow(std::max(normal.Dot3(halfway),0.0f), exponent);
        return color;
  }
  const Vec3f& getSpecularColor() const;
  virtual void glSetMaterial(void) const;

private:
  Vec3f specularColor;
  float exponent;
};

// ====================================================================
// ====================================================================

#endif

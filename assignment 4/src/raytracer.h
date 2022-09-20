#include <iostream>
#include <climits>
#include "scene_parser.h"
#include "matrix.h"
#include "camera.h" 
#include "material.h"
#include "object3d.h"
#include "image.h"
#include "light.h"
#include "rayTree.h"
const float epsilon = 1e-3;

class RayTracer{
    public:
        RayTracer(){}
        RayTracer(SceneParser *s, int max_bounces, float cutoff_weight, bool shadows,
               int w, int h, float d_min, float d_max,
                    char *dif, char * n, char * dep, bool back);
        ~RayTracer(){}
        Vec3f traceRay(Ray &ray, float tmin, int jumps, float weight, float indexOfRefraction, Hit &hit) const;
        Vec3f mirrorDirection(const Vec3f &normal, const Vec3f &incoming) const;
        bool RayTracer::transmittedDirection(const Vec3f& normal, const Vec3f& incoming, 
               float index_i, float index_t, Vec3f& transmitted) const;
        Vec3f Get_Depth(float d_min,float d_max, float d);
        Vec3f Get_Normal(Vec3f normal);
        Vec3f Get_Diffuse(Light * l, Vec3f pos, Vec3f n);
        //void run();
    
    private:
        SceneParser *sp = NULL;

        int width, height;
        float depth_max,depth_min;

        int max_bounces;
        float cutoff_weight;
        
        char *output_raytrace;
        char *output_normal;
        char *output_depth;
        bool raytrace = false;
        bool normal = false;
        bool depth = false;
        bool shade_back = false, shadows = false;
};

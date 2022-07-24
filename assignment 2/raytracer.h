#include <iostream>
#include <climits>
#include "scene_parser.h"
#include "matrix.h"
#include "camera.h" 
#include "material.h"
#include "Object3D.h"
#include "image.h"
#include "light.h"

class RayTracer{
    public:
        RayTracer(){}
        RayTracer(const char *filename, int w, int h, float d_min, float d_max,
        char *dif, char * normal, char * dep, bool shade_back);
        ~RayTracer(){}
        Vec3f Get_Depth(float d_min,float d_max, float d);
        Vec3f Get_Normal(Vec3f normal);
        Vec3f Get_Diffuse(Light * l, Vec3f pos, Vec3f n);
        //void run();
    
    private:
        double epsilon = 1e-3;
        Camera *camera = NULL;
        Vec3f background_color;
        Vec3f ambient_light;
        int num_lights;
        int num_materials;
        Light **lights = NULL;
        Material **materials = NULL;
        Material *current_material = NULL;
        Group *group = NULL;

        int width, height;
        float depth_max,depth_min;

        char *output_diffuse;
        char *output_normal;
        char *output_depth;
        bool diffuse = false;
        bool normal = false;
        bool depth = false;
        bool shade_back = false;
};

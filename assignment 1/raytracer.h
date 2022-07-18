#include <iostream>
#include "scene_parser.h"
#include "matrix.h"
#include "camera.h" 
#include "material.h"
#include "Object3D.h"
#include "group.h" 
#include "sphere.h"
#include "image.h"

class RayTracer{
    public:
        RayTracer(){}
        RayTracer(const char *filename, int w, int h, char * out, 
                    float d_min, float d_max, char * dep);
        ~RayTracer(){}
	Vec3f Get_Depth(float d_min,float d_max, float d);
        //void run();
    private:
        double epsilon = 1e-3;
        Vec3f background_color;
        int num_materials;
        Material *current_material;

        int width, height;
        char *output_file;
        float depth_min;
        float depth_max;
        char *depth_file;

        Image img_color;
        Image img_depth;
};

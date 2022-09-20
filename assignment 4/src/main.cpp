// OpenGL 渲染的包含文件
#include <GL/freeglut.h>
#include "glCanvas.h"
#include "raytracer.h"
#include <cstring>
#include <iostream>
#include <assert.h>


SceneParser* sp = NULL;
RayTracer *rt = NULL;
int width = 100;
int height = 100;

void render(){
}

void traceRay(float x,float y){
    //std::cout << "x:" << x << " y:" << y << std::endl;
    Vec2f pos(x, y);
    Ray ray = sp->getCamera()->generateRay(pos);            
    Hit hit(INT_MAX, NULL, Vec3f());
    rt->traceRay(ray, sp->getCamera()->getTMin()+epsilon, 0, 1.0f, 1.0f, hit);
    RayTree::SetMainSegment(ray, 0, hit.getT());
}

int main(int argc, char** argv){
    char *input_file = NULL;
    char *output_file = NULL;
    float depth_min = 0;
    float depth_max = 1;
    char *depth_file = NULL;
    char *normal_file = NULL;
    bool shade_back = false;
    bool gui = false;
    int num_theta = 1, num_pi = 0;
    bool gouraud = false;
    int bounces = 0;
    float weight = 1;
    bool shadows = false;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i],"-input")) {
            i++; assert (i < argc); 
            input_file = argv[i];
        } else if (!strcmp(argv[i],"-size")) {
            i++; assert (i < argc); 
            width = atoi(argv[i]);
            i++; assert (i < argc); 
            height = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-output")) {
            i++; assert (i < argc); 
            output_file = argv[i];
        } else if (!strcmp(argv[i],"-depth")) {
            i++; assert (i < argc); 
            depth_min = atof(argv[i]);
            i++; assert (i < argc); 
            depth_max = atof(argv[i]);
            i++; assert (i < argc); 
            depth_file = argv[i];
        } else if(!strcmp(argv[i],"-normals")){
            i++; assert(i <argc);
            normal_file = argv[i];
        }else if(!strcmp(argv[i],"-shade_back")){
            shade_back = true;
        }else if(!strcmp(argv[i],"-gui")){
            gui = true;
        }else if(!strcmp(argv[i],"-tessellation")){
            i++; assert(i <argc);
            num_theta = atof(argv[i]);
            i++; assert(i <argc);
            num_pi = atof(argv[i]);
            Sphere::Set_theta_phi(num_pi, num_theta);
        }else if(!strcmp(argv[i],"-gouraud")){
            gouraud = true;
            Sphere::gouraud = true;
        }else if(!strcmp(argv[i],"-shadows")){
            shadows = true;
        }else if(!strcmp(argv[i],"-bounces")){
            i++; assert(i <argc);
            bounces = atof(argv[i]);
        }else if(!strcmp(argv[i],"-weight")){
            i++; assert(i <argc);
            weight = atof(argv[i]);
        }else{
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }

   sp = new SceneParser(input_file);

    rt = new RayTracer(sp, bounces, weight, shadows, 
                    width, height, depth_min, depth_max, 
                        output_file, normal_file, depth_file, shade_back);

    if (gui) {
        glutInit(&argc, argv);
        GLCanvas glc;
        SceneParser sp = SceneParser(input_file);
        glc.initialize(&sp, render, traceRay);
    }

    return 0;
}
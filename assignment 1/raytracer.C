#include "raytracer.h"

Vec3f RayTracer::Get_Depth(float d_min,float d_max, float d){

    if(d-d_max>epsilon) d=d_max;
    else if(d-d_min<epsilon) d=d_min; 
    float t = (d_max-d)/(d_max-d_min);

    return Vec3f(t,t,t);
}

RayTracer::RayTracer(const char *filename, int w, int h, char * out, 
            float d_min, float d_max, char * dep){
    SceneParser sp(filename);

    Camera* camera = sp.getCamera();
    background_color = sp.getBackgroundColor();
    num_materials = sp.getNumMaterials();
    Group* group = sp.getGroup();
    width = w, height = h;
    output_file = out, depth_file = dep;
    depth_min = d_min, depth_max = d_max;

    Image img_color(width, height);
    Image img_depth(width, height);
    img_color.SetAllPixels(background_color);
    img_depth.SetAllPixels(background_color);
    
    for(int i=0; i<height;i++){
        for(int j=0;j<width;j++){
            Vec2f pos = Vec2f((float)j/width,(float)i/height);
            Ray r = camera->generateRay(pos);
	    //std::cout<<r<<std::endl;
            Hit h;
            if(group->intersect(r,h,camera->getTMin())){
		//std::cout<<h<<std::endl;
                float t = h.getT();
            	img_depth.SetPixel(j,i,Get_Depth(depth_min,depth_max, h.getT()));
		assert(h.getMaterial() !=NULL);
                img_color.SetPixel(j,i,h.getMaterial()->getDiffuseColor());

            }
        }
    }
    img_color.SaveTGA(output_file);
    img_depth.SaveTGA(depth_file);
}

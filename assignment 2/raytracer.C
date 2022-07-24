#include "raytracer.h"

//clamp the depth and get the right color in depth_img
Vec3f RayTracer::Get_Depth(float d_min,float d_max, float d){

    if(d-d_max>epsilon) d=d_max;
    else if(d-d_min<epsilon) d=d_min; 
    float t = (d_max-d)/(d_max-d_min);

    return Vec3f(t,t,t);
}

//get the right color in the normal_img
Vec3f RayTracer::Get_Normal(Vec3f normal){
    //normal.Normalize();
    //normal *= 255;
    return Vec3f(abs(normal.x()),abs(normal.y()),abs(normal.z()));
}

//get the right color in the diffuse_img
Vec3f RayTracer::Get_Diffuse(Light * l, Vec3f pos, Vec3f n){
    Vec3f dir,col;
    l->getIllumination(pos,dir,col);
    dir.Normalize();
    float d = dir.Dot3(n);
    if(d<0) d=0;
    return d*col;
}

RayTracer::RayTracer(const char *filename, int w, int h, float d_min, float d_max,
        char *dif, char * n, char * dep, bool back){
    SceneParser sp(filename);

    //pointer 
    camera = sp.getCamera();
    group = sp.getGroup();
    background_color = sp.getBackgroundColor();
    ambient_light = sp.getAmbientLight();
    num_materials = sp.getNumMaterials();
    num_lights = sp.getNumLights();
    width = w, height = h;
    shade_back = back;
    
    Image img_diffuse(width, height);
    Image img_normal(width,height);
    Image img_depth(width, height);

    if(dif!=NULL){
        output_diffuse = dif;
        diffuse = true;
        img_diffuse.SetAllPixels(background_color);
    }
    if(n!=NULL){
        output_normal = n;
        normal = true;
        img_normal.SetAllPixels(Vec3f(0,0,0));
    }
    if(dep!=NULL){
        output_depth = dep;
        depth = true;
        img_depth.SetAllPixels(background_color);
    }
    
    depth_min = d_min, depth_max = d_max;
    Vec3f color; // ambient color
    
    for(int i=0; i<height;i++){
        for(int j=0;j<width;j++){
            Vec2f pos = Vec2f((float)j/width,(float)i/height);
            Ray r = camera->generateRay(pos);
	    //std::cout<<r<<std::endl;
            Hit h(INT_MAX,NULL,Vec3f());

            if(group->intersect(r,h,camera->getTMin())){
		    //std::cout<<h<<std::endl;
                bool hit_back = r.getDirection().Dot3(h.getNormal()) > 0;
                if(hit_back && !shade_back){
                    color.Set(0,0,0);
                }
                else{
                    if(diffuse){
                        color = h.getMaterial()->getDiffuseColor() * ambient_light;
                        for(int li=0;li<num_lights;li++){
                            Vec3f normal = h.getNormal();
                            if(hit_back){
                                // reverse the normal vector on the back side 
                                normal *= -1.0f;
                            }
                            color += h.getMaterial()->getDiffuseColor()*Get_Diffuse(sp.getLight(li),h.getIntersectionPoint(),normal);
                        }
                    }
                }
                if(depth)
            	    img_depth.SetPixel(j,i,Get_Depth(depth_min,depth_max, h.getT()));
                if(diffuse)
                    img_diffuse.SetPixel(j,i,color);
                if(normal)
         img_normal.SetPixel(j,i,Get_Normal(h.getNormal()));
            }
        }
    }
    if(depth)
        img_depth.SaveTGA(output_depth);
    if(diffuse)
        img_diffuse.SaveTGA(output_diffuse);
    if(normal)
        img_normal.SaveTGA(output_normal);

}

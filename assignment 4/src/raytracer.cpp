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
    return Vec3f(abs(normal.x()),abs(normal.y()),abs(normal.z()));
}

RayTracer::RayTracer(SceneParser *s, int max_bounces, float cutoff_weight, bool shadows,
               int w, int h, float d_min, float d_max,
                    char *dif, char * n, char * dep, bool back){
    sp = s;
    this->max_bounces = max_bounces;
    this->cutoff_weight = cutoff_weight;
    this->shadows = shadows;

    //pointer 
    Camera *camera = sp->getCamera();
    Group *group = sp->getGroup();  
    Vec3f background_color = sp->getBackgroundColor();
    Vec3f ambient_light = sp->getAmbientLight();
    int num_lights = sp->getNumLights();
    int num_materials = sp->getNumMaterials();

    width = w, height = h;
    shade_back = back;
    
    Image img_raytrace(width, height);
    Image img_normal(width,height);
    Image img_depth(width, height);

    if(dif!=NULL){
        output_raytrace = dif;
        raytrace = true;
        //img_raytrace.SetAllPixels(background_color);
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
            Hit h(INT_MAX,NULL,Vec3f());
            Vec3f color = traceRay(r, camera->getTMin()+epsilon, 0, 1.0, 1.0, h);
            if (depth)
                img_depth.SetPixel(j, i, Get_Depth(depth_min, depth_max, h.getT()));
            if (raytrace)
                img_raytrace.SetPixel(j, i, color);
            if (normal)
                img_normal.SetPixel(j, i, Get_Normal(h.getNormal()));
        }
    }
    if(depth)
        img_depth.SaveTGA(output_depth);
    if(raytrace)
        img_raytrace.SaveTGA(output_raytrace);
    if(normal)
        img_normal.SaveTGA(output_normal);
}

Vec3f RayTracer::traceRay(Ray &ray, float tmin, int jumps, float weight, float indexOfRefraction, Hit &hit) const{
    Vec3f color = Vec3f(0, 0, 0);
    Group *group = sp->getGroup();  
    Vec3f ambient_light = sp->getAmbientLight();
    int num_lights = sp->getNumLights();

     if(group->intersect(ray,hit,tmin)){
         Vec3f normal = hit.getNormal();
         Vec3f pos = hit.getIntersectionPoint();
        //std::cout<<h<<std::endl;
        bool hit_back = ray.getDirection().Dot3(hit.getNormal()) > 0;
        if(hit_back && !shade_back){
            color.Set(0,0,0);
        }
        else{
            if (hit_back) // reverse the normal vector on the back side 
                normal *= -1.0f;
            color += hit.getMaterial()->getDiffuseColor() * ambient_light;
            for(int li=0;li<num_lights;li++){
                Vec3f dir2light,colr_light;
                float dis2light;
                sp->getLight(li)->getIllumination(pos,dir2light,colr_light,dis2light);

                //shadows
                Ray ray2light(pos, dir2light);
                Hit shadowHit(dis2light, NULL, Vec3f());
                if(shadows){                        
                    //no shadow
                    //Note: the epsilon is important
                    if(!group->intersect(ray2light,shadowHit,epsilon)){
                        //specularColor
                        color += hit.getMaterial()->Shade(ray,hit,dir2light,colr_light);
                    }
                }
                else 
                    color += hit.getMaterial()->Shade(ray, hit, dir2light, colr_light);
                RayTree::AddShadowSegment(ray2light, tmin, shadowHit.getT());
            }//end lights

            const Vec3f& reflectColor = hit.getMaterial()->getReflectiveColor();
            const Vec3f& transColor = hit.getMaterial()->getTransparentColor();

            //reflectiveColor
            if (jumps < max_bounces && weight >= cutoff_weight && reflectColor.Length() > epsilon) {
                Vec3f Refdir = mirrorDirection(normal, ray.getDirection());
                Ray refRay(pos, Refdir);
                Hit refHit(INT_MAX, NULL, Vec3f());
                color += reflectColor * traceRay(refRay, tmin, jumps + 1, weight * reflectColor.Length(), 
                                                    indexOfRefraction, refHit);
                RayTree::AddReflectedSegment(refRay, tmin, refHit.getT());
            }
        
            //transparentColor
            if (jumps < max_bounces && weight >= cutoff_weight && transColor.Length() > epsilon) {
                Vec3f Transdir;
                float index_i , index_t ;
                if (!hit_back) {
                    index_i = indexOfRefraction;
                    index_t = hit.getMaterial()->getIndexOfRefraction();
                }
                else {
                    index_i = hit.getMaterial()->getIndexOfRefraction();
                    index_t = indexOfRefraction;
                }
                if (transmittedDirection(normal, ray.getDirection(), index_i, index_t, Transdir)) {
                    Ray transRay(hit.getIntersectionPoint(), Transdir);
                    Hit transHit(INT_MAX, NULL, Vec3f());
                    color += transColor * traceRay(transRay, tmin, jumps + 1, weight * transColor.Length(), index_i, transHit);
                    RayTree::AddTransmittedSegment(transRay, tmin, transHit.getT());
                }
            }
        }
        return color;
     }//have intersection
     return sp->getBackgroundColor();
}

Vec3f RayTracer::mirrorDirection(const Vec3f &normal, const Vec3f &incoming) const{
    Vec3f mirrorDirection = incoming - 2 * incoming.Dot3(normal) * normal;
    mirrorDirection.Normalize();
    return mirrorDirection;
}

bool RayTracer::transmittedDirection(const Vec3f &normal, const Vec3f &incoming, float index_i, float index_t, Vec3f& transmitted) const{
    // Note: the incoming ray's direction
    Vec3f in = -1.0f * incoming;
    float cos_i = normal.Dot3(in);
    float eta = index_i / index_t;
    float t = 1.0f - eta*eta * (1.0f - cos_i * cos_i);
    if (t > epsilon) {
        transmitted =  (eta * cos_i - sqrt(t))*normal - in * eta;
        transmitted.Normalize();
        return true;
    }
    else  return false;
}
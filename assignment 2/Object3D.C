#include "Object3D.h"

bool Sphere::intersect(const Ray &r, Hit &h, float tmin){
    //Vec3f ro = r.getOrigin();
    Vec3f ro = r.getOrigin()-center;
    Vec3f rd = r.getDirection();
    double a = 1.0, b= 2.0 * (rd).Dot3(ro), c = (ro).Dot3(ro) - radium*radium; 
    double delta = b*b-4*a*c;
    if(delta<0)    
        return false;
    double d = sqrt(delta);
    double t1 = (-b+d)/(2*a);
    double t2 = (-b-d)/(2*a);
    double t;

    if(t1 > tmin && t1 < h.getT()){
        if(t2 > tmin && t2 <h.getT()){
            t = (t1-t2)>epsilon?t2:t1;
        }
        else{
            t= t1;
        }
    }
    else if(t2 > tmin && t2 <h.getT()){
        t = t2;
    }
    else
        return false;
        
    Vec3f n = r.pointAtParameter(t) - center;
    n.Normalize();
    h.set(t,material,n,r);
    return true;
}

void Group::addObject(int index, Object3D *obj){
    objects[index] = obj;
}

bool Group::intersect(const Ray &r, Hit &h, float tmin){\
    bool flag = false;
    for(int i=0;i<number;i++){
        if(objects[i]->intersect(r,h,tmin)){
	    flag = true;

	}
    }
    return flag;
}

int Group::Get_Number(){
    return number;
}

bool Plane:: intersect(const Ray &r, Hit &h, float tmin){
    Vec3f ro = r.getOrigin();
    Vec3f rd = r.getDirection();
    float t = -(d+normal.Dot3(ro))/(normal.Dot3(rd));
    if(t>tmin && t<h.getT()){
        h.set(t,material,normal,r);
        return true;
    }
    return false;
}

bool Triangle:: intersect(const Ray &r, Hit &h, float tmin){
    Vec3f ro = r.getOrigin();
    Vec3f rd = r.getDirection();
    Vec3f ab = b-a, bc = c-b, normal;
    Vec3f::Cross3(normal,ab,bc);
    normal.Normalize();
    float detA = det3x3(a.x()-b.x(),a.x()-c.x(),rd.x(),
                        a.y()-b.y(),a.y()-c.y(),rd.y(),
                        a.z()-b.z(),a.z()-c.z(),rd.z());
    float beta = det3x3(a.x()-ro.x(),a.x()-c.x(),rd.x(),
                        a.y()-ro.y(),a.y()-c.y(),rd.y(),
                        a.z()-ro.z(),a.z()-c.z(),rd.z())/detA;
    float gamma = det3x3(a.x()-b.x(),a.x()-ro.x(),rd.x(),
                         a.y()-b.y(),a.y()-ro.y(),rd.y(),
                         a.z()-b.z(),a.z()-ro.z(),rd.z())/detA;
    float t = det3x3(a.x()-b.x(),a.x()-c.x(),a.x()-ro.x(),
                     a.y()-b.y(),a.y()-c.y(),a.y()-ro.y(),
                     a.z()-b.z(),a.z()-c.z(),a.z()-ro.z())/detA;
    if(beta+gamma<1 && beta>0 && gamma>0 && t>tmin && t<h.getT()){
        h.set(t,material,normal,r);
        return true;
    }
    return false;
}

bool Transform::intersect(const Ray &r, Hit &h, float tmin){
    Matrix mI = m;
    mI.Inverse();
    Vec3f ro = r.getOrigin();
    Vec4f rd(r.getDirection(),0);
    mI.Transform(ro);
    mI.Transform(rd);
    Vec3f rdir(rd.x(),rd.y(),rd.z());
    float tScale = rdir.Length();
    rdir.Normalize();
    Ray rw(ro, rdir);
    Hit hw(h.getT() * tScale, nullptr, Vec3f(0, 0, -1.0f));
    if (obj->intersect(rw, hw, tmin * tScale)) {
        Vec3f normal = hw.getNormal();
        Matrix mIT = mI;
        mIT.Transpose(mIT);
        mIT.Transform(normal);
        normal.Normalize();
        h.set(hw.getT() / tScale, hw.getMaterial(), normal, r);
        return true;
    }
    return false;
}

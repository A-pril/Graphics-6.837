#include "object3d.h"
#include <vector>

//static variable should be assigned in .cpp
int Sphere::step_phi = 20, Sphere::step_theta = 10;
float Sphere::delta_phi = PI / step_phi, Sphere::delta_theta = 2*PI / step_theta;
bool Sphere::gouraud = false;

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

Vec3f Sphere::Get_point(float phi, float theta){
   //phi = -pi/2:pi/2, the angle between axis z and the line
    float x = cos(phi) * cos(theta);
    float y = sin(phi);
    float z = cos(phi) * sin(theta);
    return Vec3f(x,y,z) * radium;
}

void Sphere::paint(){
    material->glSetMaterial();
    glBegin(GL_QUADS); 
    float phi = PI*(-0.5), phi1 = phi+delta_phi;
        if(gouraud){
            for (int iPhi=0; iPhi<step_phi; iPhi+=1){
                float theta = 0, theta1 = theta + delta_theta;
                for (int iTheta=0; iTheta<step_theta; iTheta+=1) { 
                    // 计算适当的坐标和法线
                    Vec3f a = Get_point(phi,theta);
                    Vec3f b = Get_point(phi1,theta);
                    Vec3f c = Get_point(phi1,theta1);
                    Vec3f d = Get_point(phi,theta1);
                    a.Normalize(), b.Normalize(), c.Normalize(), d.Normalize();
                    // 发送 gl 顶点命令
                    glNormal3f(a.x(),a.y(),a.z()); 
                    //std::cout << "a:" << a << " b:" << b << " c:" << c << " d:" << d << std::endl;
                    a+=center;
                    glVertex3f(a.x(),a.y(),a.z()); 

                    glNormal3f(b.x(),b.y(),b.z()); 
                    b+=center;
                    glVertex3f(b.x(),b.y(),b.z());

                    glNormal3f(c.x(),c.y(),c.z()); 
                    c+=center;
                    glVertex3f(c.x(),c.y(),c.z()); 

                    glNormal3f(d.x(),d.y(),d.z());  
                    d+=center;
                    glVertex3f(d.x(),d.y(),d.z()); 
                    
                    theta = theta1; theta1 += delta_theta;
                } 
                phi = phi1; phi1 += delta_phi;
            } 
        }
        else{
            for (int iPhi=0; iPhi<step_phi; iPhi+=1){
                float mid_phi = phi + 0.5*delta_phi;
                float theta = 0, theta1 = theta + delta_theta;
                for (int iTheta=0; iTheta<step_theta; iTheta+=1) { 
                    // 计算适当的坐标和法线
                    float mid_theta = theta + 0.5*delta_theta;
                    Vec3f normal = Get_point(mid_phi, mid_theta);
                    normal.Normalize();
                    glNormal3f(normal.x(),normal.y(),normal.z());
                    Vec3f a = Get_point(phi,theta);
                    Vec3f b = Get_point(phi1,theta);
                    Vec3f c = Get_point(phi1,theta1);
                    Vec3f d = Get_point(phi,theta1);                
                    a += center, b += center, c += center, d += center;
                    // 发送 gl 顶点命令
                    //std::cout << "a:" << a << " b:" << b << " c:" << c << " d:" << d << std::endl;
                    glVertex3f(a.x(),a.y(),a.z()); 
                    glVertex3f(b.x(),b.y(),b.z()); 
                    glVertex3f(c.x(),c.y(),c.z()); 
                    glVertex3f(d.x(),d.y(),d.z()); 

                    theta = theta1; theta1 += delta_theta;
                } 
                phi = phi1; phi1 += delta_phi;
            } 
        }
        
   glEnd();
}

void Group::addObject(int index, Object3D *obj){
    objects[index] = obj;
}

bool Group::intersect(const Ray &r, Hit &h, float tmin){
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

void Group::paint(){
    for(int i=0;i<number;i++){
        objects[i]->paint();
	}
}

bool Plane:: intersect(const Ray &r, Hit &h, float tmin){
    Vec3f ro = r.getOrigin();
    Vec3f rd = r.getDirection();
    float t = -(-d+normal.Dot3(ro))/(normal.Dot3(rd));
    if(t>tmin && t<h.getT()){
        h.set(t,material,normal,r);
        return true;
    }
    return false;
}

void Plane::paint(){
    Vec3f ori = d*normal;
    float big = 1e3;
    Vec3f v = Vec3f(1,0,0);
    Vec3f n = normal;
    n.Normalize();
    if(abs(n.Dot3(v)-1)<=1e-3){
        v = Vec3f(0,1,0);
    }
    Vec3f b1,b2;
    Vec3f::Cross3(b1,normal,v);
    Vec3f::Cross3(b2,normal,b1);
    b1 *= big, b2*= big;
    Vec3f a = ori - b1 ;
    Vec3f b = ori - b2;
    Vec3f c = ori + b1;
    Vec3f d = ori + b2;

    //set the material parameters first
    material->glSetMaterial();
    glBegin(GL_QUADS); 
    glNormal3f(n.x(), n.y(), n.z()); 
    glVertex3f(a.x(), a.y(), a.z()); 
    glVertex3f(b.x(), b.y(), b.z()); 
    glVertex3f(c.x(), c.y(), c.z()); 
    glVertex3f(d.x(), d.y(), d.z()); 
    glEnd();
}

bool Triangle:: intersect(const Ray &r, Hit &h, float tmin){
    Vec3f ro = r.getOrigin();
    Vec3f rd = r.getDirection();
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

void Triangle::paint(){
    material->glSetMaterial();
    glBegin(GL_TRIANGLES);
    glNormal3f(normal.x(), normal.y(), normal.z());
    glVertex3f(a.x(), a.y(), a.z());
    glVertex3f(b.x(), b.y(), b.z());
    glVertex3f(c.x(), c.y(), c.z());
    glEnd();
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

void Transform::paint(){
    glPushMatrix(); 
    GLfloat *glMatrix = m.glGet(); 
    glMultMatrixf(glMatrix); 
    delete[] glMatrix;
    obj->paint();
    glPopMatrix();
}
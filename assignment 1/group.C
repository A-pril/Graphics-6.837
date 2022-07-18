#include "group.h"

void Group::addObject(int index, Object3D *obj){
    objects[index] = obj;
}

bool Group::intersect(const Ray &r, Hit &h, float tmin){\
    bool flag = false;
    //std::cout<<number<<std::endl;
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

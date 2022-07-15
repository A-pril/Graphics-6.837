#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "ifs.h"

// ====================================================================
// ====================================================================
// some helper functions for iterted function system
//添加转换矩阵
void IFS::Add_Transform(Matrix m){
    this->transforms.push_back(m);
}
//添加某转换矩阵对应的可能性
void IFS::Add_Porb(float p){
    this->probalities.push_back(p);
}
//设置image实例的背景颜色
void IFS::Set_BackColor(const Vec3f &color){
    this->Background_color = color;
}
//设置image实例当前画笔颜色
void IFS::Set_PointColor(const Vec3f &color){
    this->Front_color = color;
}
//set random points
void IFS::Get_RandPoints(int w, int h){
    for(int i=0; i<num_points; i++){
        Vec2f point = Vec2f(rand()%w,rand()%h);
        this->points.push_back(point);
    }
}
//show each transform and probility
void IFS::Show_Transforms(){
    for(int i=0;i<num_trans;i++){
        std::cout<<probalities[i]<<std::endl;
        std::cout<<transforms[i].glGet()<<std::endl;
    }
}
//set the bound-box
void IFS::Set_BoundBox(){
    int x_min, x_max = this->points[0].x();
    int y_min, y_max = this->points[0].y(); 

    for(int i=1; i<num_points; i++){
        int x = this->points[i].x();
        int y = this->points[i].y();
        if(x<x_min) x_min = x;
        else if(x>x_max) x_max = x;
        if(y<y_min) y_min =  y;
        else if(y>y_max) y_max = y;
    }

    if(x_min<0) {
        x_max -= x_min;
        for(int i=0; i<num_points; i++){
            int x = this->points[i].x(), y = this->points[i].y();
		    this->points[i].Set(x-x_min,y);
        }
    }
    if(y_min<0) {
        y_max -= y_min;
        for(int i=0; i<num_points; i++){
            int x = this->points[i].x(), y = this->points[i].y();
		    this->points[i].Set(x,y-y_min);
        }
    }

    if(x_max >= this->img.Width()){
        float x_ratio = img.Width()/x_max - 0.1;
        for(int i=0; i<num_points; i++){
            int x = this->points[i].x(), y = this->points[i].y();
            this->points[i].Set((floor)(x*x_ratio),y);
        }
    }

    if(y_max >=this->img.Height()){
        float y_ratio = this->img.Height()/y_max - 0.1;
        for(int i=0; i<num_points; i++){
            int x = this->points[i].x(), y = this->points[i].y();;
	    //int y = (floor)(this->points[i].y()*y_ratio);

	    //if(y>=img.Height()) y=img.Height()-1;
            this->points[i].Set(x,(floor)(y*y_ratio));
        }
    }

}
//运行IFS
void IFS::run(const char *f){
    //Set imags's background color
    this->img.SetAllPixels(Background_color);
    //Get random Points

    this->Get_RandPoints(this->img.Width(), this->img.Height());

    for(int i=0; i<num_iters; i++){
        for(int j=0; j<num_points; j++){
            x_now = this->points[j].x();
            y_now = this->points[j].y();
            float p = rand()/(RAND_MAX+1.0);
            float p_now = 0;
            int way = 0;
            while(p_now<=p){
                p_now += probalities[way++];
            }
            way -= 1;
            //use Matrix::Transform is alright

	    Vec2f pos(x_now/(float)this->img.Width(), y_now/(float)this->img.Height());
	    transforms[way].Transform(pos);

            this->points[j].Set(pos.x()*this->img.Width(), pos.y()*this->img.Height());
        }
    }

    //this->Set_BoundBox();

    for(int i=0; i<num_points; i++){
        this->img.SetPixel(points[i].x(), points[i].y(), Front_color);
    }
    
    std::cout<<"data success!"<<std::endl;
    img.SaveTGA(f);
    std::cout<<"save success!"<<std::endl;
}

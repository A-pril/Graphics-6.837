#ifndef _IFS_H_
#define _IFS_H_

#include <cstdio>
#include <assert.h>
#include <vector>
#include "vector.h"
#include "image.h"
#include "matrix.h"

class IFS{

public:
    IFS(int iter, int point, int trans, Image &img){
        this->num_iters = iter;
        this->num_points = point;
        this->num_trans = trans;
        this->img = img;
    }
    ~IFS(){
        //transforms.clear();
        probalities.clear();
    }
    void Add_Transform(Matrix m);
    void Add_Porb(float p);
    void Set_BackColor(const Vec3f &color);
    void Set_PointColor(const Vec3f &color);
    void Get_RandPoints(int w, int h);
    void Set_BoundBox();
    void Show_Transforms();
    void run(const char *f);

private:
    //迭代次数
    int num_iters = 1;
    //点数
    int num_points = 1;
    //转换类型数
    int num_trans = 0;
    //转换矩阵
    std::vector<Matrix> transforms;
    //概率矩阵
    std::vector<float> probalities;
    //points pos
    std::vector<Vec2f> points;
    //图像实例
    Image img;
    //背景颜色
    Vec3f Background_color = Vec3f(0.0f,0.0f,0.0f);
    //当前渲染画笔颜色
    Vec3f Front_color = Vec3f(255.0f,255.0f,255.0f);
    //当前位置坐标
    float x_now = 0;
    float y_now = 0;

};


// ====================================================================
// ====================================================================

#endif

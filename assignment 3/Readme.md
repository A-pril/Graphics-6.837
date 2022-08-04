## OpenGL & Phong Shading

### Lecture

漫反射项
![image](https://user-images.githubusercontent.com/76250553/182794859-48b1bdd0-9a2d-494d-afde-ed0ccefa5de7.png)
![image](https://user-images.githubusercontent.com/76250553/182794950-1260fcbf-946a-48a3-ab1c-a67b7cc80516.png)

高光项

![image](https://user-images.githubusercontent.com/76250553/182794996-3fd75e59-dd2b-4dc0-b4c4-ab26143f0ce9.png)

![image](https://user-images.githubusercontent.com/76250553/182795065-cf630d5f-16f6-43ea-a001-378f5475b6d5.png)

Phong Model

![image](https://user-images.githubusercontent.com/76250553/182795121-25bdd319-67e7-44ec-a9b6-83147a1239b3.png)
![image](https://user-images.githubusercontent.com/76250553/182795780-16cd9029-02b2-403c-8345-d864315e29b8.png)

球体细分：

https://zhuanlan.zhihu.com/p/32564705

注意点1：在代码中，指明pi是-pi/2—pi/2，故是当前点所在射线与Z轴的夹角，而theta则是投影下x-z平面的射线与x轴的夹角

注意点2：所有以四边形渲染的图形，如plane或者sphere中的每个细分的四边形面，都需要注意点的连接顺序

### file

由于在linux上调用opengl的API不太方便，尤其是glut很难下载安装，所以在这个作业我选择了使用windows10+opengl

其中lib和include以及out/Debug中的freeglutd.dll需要提前拷贝下来，并将调用opengl头文件的代码语句改为

```
#include <GL/freeglut.h>
```

代码通过cmake进行链接，注意CMakeLists.txt中规定了cmake最低版本要求为3.15，链接生成03_Phong_Shading.sln

```
cmake .
```

用vs打开项目，右键选择项目点击生成，即可生成raytracer.exe并保存到/out/Debug中

![image](https://user-images.githubusercontent.com/76250553/182795837-2f40242d-587b-427f-8fbe-711a7e9c00fd.png)

在raytracer.exe所在的文件夹通过命令行即可运行该应用

参照：

https://blog.csdn.net/qq_43327771/article/details/121595241?spm=1001.2014.3001.5501

https://github.com/fuzhanzhan/MIT-CG6.837-2004/tree/master/03_Phong_Shading

### Result
![image](https://user-images.githubusercontent.com/76250553/182795902-ab8ac1ac-2eed-42dd-8228-f8bd100d5446.png)


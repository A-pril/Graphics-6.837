## OpenGL & Phong Shading

### Lecture

漫反射项

![image-20220804150048319](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220804150048319.png)

<img src="C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220804150128289.png" alt="image-20220804150128289" style="zoom:80%;" />

高光项

<img src="C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220804150201537.png" alt="image-20220804150201537" style="zoom:80%;" />

<img src="C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220804150238143.png" alt="image-20220804150238143" style="zoom:80%;" />

Phong Model

<img src="C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220804150314069.png" alt="image-20220804150314069" style="zoom:80%;" />

<img src="C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220804150352689.png" alt="image-20220804150352689" style="zoom:80%;" />

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

![image-20220804152220336](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220804152220336.png)

在raytracer.exe所在的文件夹通过命令行即可运行该应用

参照：

https://blog.csdn.net/qq_43327771/article/details/121595241?spm=1001.2014.3001.5501

https://github.com/fuzhanzhan/MIT-CG6.837-2004/tree/master/03_Phong_Shading

### Result

![image-20220804152656759](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220804152656759.png)

![image-20220804152712806](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220804152712806.png)

![image-20220804152730339](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20220804152730339.png)
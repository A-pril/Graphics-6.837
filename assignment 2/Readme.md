# Ray Tracing

## Lecture
![image](https://user-images.githubusercontent.com/76250553/180650309-37fdb7a8-b5e0-4eff-bf79-b350132f0b8e.png)
screen_center = direction * (0.5/tan(0.5*angle))
ray = screen_center + (x-0.5)*horizontal + (y-0.5)*up

![image](https://user-images.githubusercontent.com/76250553/180650649-34601112-9944-4fd0-a765-27f7236ab53a.png)

![image](https://user-images.githubusercontent.com/76250553/180650689-2a8db4b8-fa34-4e11-b6d7-3993681c9e65.png)
![image](https://user-images.githubusercontent.com/76250553/180650703-7364844c-27c6-466a-9944-b6a842feabc5.png)

![image](https://user-images.githubusercontent.com/76250553/180650744-e120edff-4250-46eb-8f18-aee5b2ec1370.png)
![image](https://user-images.githubusercontent.com/76250553/180650755-a4c16115-9b88-441d-a298-978b215cf724.png)
![image](https://user-images.githubusercontent.com/76250553/180650767-c7f3b967-05e5-4a3a-8367-e895e991e282.png)
![image](https://user-images.githubusercontent.com/76250553/180650781-ce2e6b8e-3a0d-4392-ba23-8706cbc0a7e7.png)
![image](https://user-images.githubusercontent.com/76250553/180650801-f67efdbf-8ebc-494a-8d46-df2fe05ad63a.png)

![image](https://user-images.githubusercontent.com/76250553/180650948-7d46c7ed-704a-495d-a185-854bfc9a3324.png)
![image](https://user-images.githubusercontent.com/76250553/180651104-3fcaed53-e76a-4832-90c2-7b400a817b74.png)

![image](https://user-images.githubusercontent.com/76250553/180651153-d89575e6-8d84-43e5-ad2e-30eff3e518f7.png)
![image](https://user-images.githubusercontent.com/76250553/180651163-4473addf-eb94-455c-86e0-89b516a7d856.png)
![image](https://user-images.githubusercontent.com/76250553/180651167-37a1a651-5aa0-4148-a99b-fa50359d0842.png)
![image](https://user-images.githubusercontent.com/76250553/180651189-86c5a3d5-a043-489e-89d5-85270588c742.png)

## Result
./raytracer -input scene2_01_diffuse.txt -size 200 200 -output output2_01.tga
![image](https://user-images.githubusercontent.com/76250553/180651244-d5db08d0-dd08-4d2c-bc56-553650b25be8.png)

./raytracer -input scene2_02_ambient.txt -size 200 200 -output output2_02.tga
![image](https://user-images.githubusercontent.com/76250553/180651272-e16c53d5-29ff-41a1-8b76-058eee14afdf.png)

./raytracer -input scene2_07_sphere_triangles.txt -size 200 200 -output output2_07.tga -depth 9 11 depth2_07.tga -normals normals2_07.tga -shade_back
![image](https://user-images.githubusercontent.com/76250553/180651345-376e2cb7-3cdc-4318-9980-1656629d8f96.png)
![image](https://user-images.githubusercontent.com/76250553/180651376-da0b83ba-e94e-4503-a0a7-ef1de85f1ca2.png)
![image](https://user-images.githubusercontent.com/76250553/180651541-7a6621aa-9bc3-42ac-91a1-ff47a127d011.png)

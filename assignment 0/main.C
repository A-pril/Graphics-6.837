#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <cstring>
#include "matrix.h"
#include "image.h"
#include "ifs.h"

int main(int argc, char ** argv){
    // ========================================================
    // ========================================================
    // Some sample code you might like to use for parsing 
    // command line arguments and the input IFS files

    // sample command line:
    // ./ifs -input fern.txt -points 50000 -iters 30 -size 400 -output fern.tga
    // ./ifs -input sierpinski_triangle.txt -points 10000 -iters 1 -size 200 -output sierpinski_triangle_1.tga

    char *input_file = NULL;
    int num_points = 10000;
    int num_iters = 10;
    int size = 100;

    char *output_file = NULL;    

    //command line 
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i],"-input")) {
            i++; assert (i < argc); 
            input_file = argv[i];
        } else if (!strcmp(argv[i],"-points")) {
            i++; assert (i < argc); 
            num_points = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-iters")) {
            i++; assert (i < argc); 
            num_iters = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-size")) {
            i++; assert (i < argc); 
            size = atoi(argv[i]);
        } else if (!strcmp(argv[i],"-output")) {
            i++; assert (i < argc); 
            output_file = argv[i];
        } else {
            printf ("whoops error with command line argument %d: '%s'\n",i,argv[i]);
            assert(0);
        }
    }

    // ========================================================
    // ========================================================
    // Some sample code you might like to use for
    // parsing the IFS transformation files

    // open the file
    FILE *input = fopen(input_file,"r");
    assert(input != NULL);

    // read the number of transforms
    int num_transforms; 
    fscanf(input,"%d",&num_transforms);

    // < DO SOMETHING WITH num_transforms >
    //create an image instance
    Image image(size,size);
    //create an ifs instance
    IFS ifs(num_iters, num_points, num_transforms, image);

    // read in the transforms
    for (int i = 0; i < num_transforms; i++) {
        float probability; 
        fscanf (input,"%f",&probability);
        Matrix m; 
        m.Read3x3(input);
        // < DO SOMETHING WITH probability and m >
        ifs.Add_Porb(probability);
        ifs.Add_Transform(m);
    }
    //std::cout<<"before run success!"<<std::endl;
    // close the file
    fclose(input);
    ifs.run(output_file);
    std::cout<<"success!"<<std::endl;

// ========================================================
// ========================================================

    return 0;
}

#pragma once

#include <cmath>
float vertices[]{
    // posx, posy, texposs, texpost
        -0.5f, -0.5f, 0.0f, 0.0f, // 0 
         0.5f, -0.5f, 1.0f, 0.0f, // 1
         0.5f,  0.5f, 1.0f, 1.0f, // 2
        -0.5f,  0.5f, 0.0f, 1.0f  // 3
};
unsigned int indices[]{
    0, 1, 2,
    2, 3, 0
};
float cubeVertices[]{
    //posx, posy, posz, texposs, texpost

    //behind
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,

	//front
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    
    //left
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    //right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

     //down
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    //up
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,

};
unsigned int cubeIndices[]{
    0, 1, 2, 2, 3, 0, //behind
    4, 5, 6, 6, 7, 4, //front
    8, 9,10,10,11, 8, //left
   12,13,14,14,15,12, //right
   16,17,18,18,19,16, //down
   20,21,22,22,23,20  //up
};

float regularSolidVertices[]{
    //posx, posy, posz, texposs, texpost

     1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // 0
    -1.0f, -1.0f,  1.0f, 1.0f, 0.0f, // 1
    -1.0f,  1.0f, -1.0f, 0.5f, 1.0f, // 2
     1.0f, -1.0f, -1.0f, 0.5f, 0.5f  // 3



};

unsigned int regularSolidIndices[]{
    0, 1, 2, // plane 0
    0, 2, 3, // plane 1
    0, 3, 1, // plane 2
    1, 3, 2  // plane 3
};
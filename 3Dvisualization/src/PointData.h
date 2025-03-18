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
float cubevertices[]{
    //posx, posy, posz, texposs, texpost
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f

};
unsigned int cubeindices[]{
    4, 5, 7, 7, 6, 4, //front
    1, 0, 2, 2, 3, 1, //behind
    0, 4, 6, 6, 2, 0, //left
    5, 1, 3, 3, 7, 5, //right
    6, 7, 3, 3, 2, 6, //up
    1, 0, 4, 4, 5, 1  //down
};
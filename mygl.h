#ifndef _MYGL_H_
#define _MYGL_H_
#include"Arquivos/pixel.cpp"
#include "definitions.h"
#include "objLoader.h"
#include"Arquivos/bresenham.cpp"
#include"Arquivos/triangle.cpp"
#include <Eigen/Dense>
#include <math.h>   

using namespace Eigen;
//*****************************************************************************
// Defina aqui as suas funções gráficas
//*****************************************************************************
double angle = 0; //como variável global

void PutPixel(int x, int y, int rgba[]){
//*************************************************************************
// Chame aqui as funções do mygl.h
//*************************************************************************
    Pixel p;
    p.setX(x);
    p.setY(y);
    p.setCores(rgba[0], rgba[1], rgba[2], rgba[3]);
    p.getPixel();
}

void DrawLine(int x0, int y0, int x1, int y1, int rgba[], int rgba1[]) {
    Bresenham line;
    line.calcBresenham(x0,y0,x1,y1,rgba, rgba1);
}

void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int rgba[], int rgba1[], int rgba2[]){
    Triangle triangle;
    triangle.getTriangle(x0,y0,x1,y1,x2,y2,rgba,rgba1,rgba2);
}

void Pipeline(objLoader *objData){

    //declaração de vértices
  /*  Vector4d v1(-1,-1,-1,1);
    Vector4d v2(-1,-1,1,1);
    Vector4d v3(1,-1,-1,1);
    Vector4d v4(1,-1,1,1);
    Vector4d v5(-1,1,-1,1);
    Vector4d v6(-1,1,1,1);
    Vector4d v7(1,1,-1,1);
    Vector4d v8(1,1,1,1);*/
   // std::cout << v << std::endl;

//Model Matrix
    int rgba[4];
    rgba[0] = 255, rgba[1] = 255, rgba[2]=255, rgba[3]=255;
    int rgba2[4];
    rgba2[0] = 255, rgba2[1] = 255, rgba2[2]=255, rgba2[3]=255;
    int rgba3[4];
    rgba3[0] = 255, rgba3[1] = 255, rgba3[2]=255, rgba3[3]=255;

    Matrix4d model1 = Matrix4d::Identity();
    Matrix4d rotation = Matrix4d::Identity();
   // angle+=0.005;
    rotation(0,0) = cos(0);
    rotation(0,2) = sin(0);
    rotation(2,0) = (-1) * sin(0);
    rotation(2,2) = cos(0);
//     std::cout << rotation << std::endl;*/

    Matrix4d model = Matrix4d::Identity();
    model = model1*rotation;
// Camera Parameters
    Vector3d cam_pos(0,0,4);
    Vector3d cam_lookat(0,0,0);
    Vector3d cam_up(0,1,0);

    Vector3d cam_dir = cam_lookat - cam_pos;
    
    Vector3d z_cam = (-1)*(cam_dir.normalized());
    Vector3d x_cam = (cam_up.cross(z_cam)).normalized();
    Vector3d y_cam = (z_cam.cross(x_cam)).normalized();

    Matrix4d B;

    B << x_cam.row(0), y_cam.row(0), z_cam.row(0),0,
         x_cam.row(1), y_cam.row(1), z_cam.row(1),0,
         x_cam.row(2), y_cam.row(2), z_cam.row(2),0,
         0,0,0,1;
    

  //  std::cout << B << std::endl;

    Vector3d t = (-1)*cam_pos;
    Matrix4d trans;
    trans << 1,0,0,t.row(0),
             0,1,0,t.row(1),
             0,0,1,t.row(2),
             0,0,0,1;

    Matrix4d B_transp = B.transpose();
//    std::cout << B_transp << std::endl;

    Matrix4d view = trans*B_transp;
  //  std::cout << view << std::endl;

    Matrix4d modelView = view*model;    
  //  std::cout << modelView << std::endl;
    
    // Espaço da Camera - Espaço Projetivo (Recorte)
    float d =2;
    Matrix4d projection;
    projection << 1,0,0,0,
                  0,1,0,0,
                  0,0, 1,d,
                  0,0,-1/d,0;
//    std::cout << projection << std::endl;
    Matrix4d modelViewProjection = projection*modelView;
    //std::cout << modelViewProjection << std::endl;

    // Espaço de Recorte -> Espaço Canonico
   /* v1 = modelViewProjection*v1;
    v2 = modelViewProjection*v2;
    v3 = modelViewProjection*v3;
    v4 = modelViewProjection*v4;
    v5 = modelViewProjection*v5;
    v6 = modelViewProjection*v6;
    v7 = modelViewProjection*v7;
    v8 = modelViewProjection*v8;
  
    v1 = v1*((v1.row(3)).inverse());
    v2 = v2*((v2.row(3)).inverse());
    v3 = v3*((v3.row(3)).inverse());
    v4 = v4*((v4.row(3)).inverse());
    v5 = v5*((v5.row(3)).inverse());
    v6 = v6*((v6.row(3)).inverse());
    v7 = v7*((v7.row(3)).inverse());
    v8 = v8*((v8.row(3)).inverse());
*/
    // Espaço Canonico -> Espaço da Tela

    Matrix4d S1 = ::Matrix4d::Identity();
    S1(1,1)=-1;
  //  std::cout << invert_y << std::endl;

    Matrix4d S2 = ::Matrix4d::Identity();
    S2(0,0) = 511/2;
    S2(1,1) = 511/2;
  //  std::cout << scale<< std::endl;

      Matrix4d translate = ::Matrix4d::Identity();
      translate(0,3) = 512/2;    
      translate(1,3) = 512/2;
  //    std::cout << translate << std::endl; 

      Matrix4d viewport1 = S1*S2;
      Matrix4d viewport = translate*viewport1;
      
    //Matrix4d invScale = invert_y*scale;
    //Matrix4d transInvScale = translate*invScale;
  //  std::cout << transInvScale << std::endl; 

  for(int i=0; i < objData->faceCount; i++){
     obj_face *o = objData->faceList[i];
    //primeira coordenada do espaço do objeto
     Vector4d v0(objData->vertexList[o->vertex_index[0]]->e[0],
                 objData->vertexList[o->vertex_index[0]]->e[1],
                 objData->vertexList[o->vertex_index[0]]->e[2],
                 1);
     //segunda coordenada do espaço do objeto
     Vector4d v1(objData->vertexList[o->vertex_index[1]]->e[0],
                 objData->vertexList[o->vertex_index[1]]->e[1],
                 objData->vertexList[o->vertex_index[1]]->e[2],
                 1);
     //terceira coordenada do espaço do objeto
     Vector4d v2(objData->vertexList[o->vertex_index[2]]->e[0],
                 objData->vertexList[o->vertex_index[2]]->e[1],
                 objData->vertexList[o->vertex_index[2]]->e[2],
                 1);

    v0 = modelViewProjection*v0;
    v1 = modelViewProjection*v1;
    v2 = modelViewProjection*v2;
    
    v0 = v0*((v0.row(3)).inverse());
    v1 = v1*((v1.row(3)).inverse());
    v2 = v2*((v2.row(3)).inverse()); 

    v0 = viewport*v0;
    v1 = viewport*v1;
    v2 = viewport*v2;

    DrawTriangle(v0(0),v0(1),v1(0),v1(1),v2(0),v2(1),rgba,rgba2,rgba3);
    }
       //angle = angle + 0.005;

    /*v1 =viewport*v1;
    v2 = viewport*v2;
    v3 = viewport*v3;
    v4 = viewport*v4;
    v5 = viewport*v5;
    v6 = viewport*v6;
    v7 = viewport*v7;
    v8 = viewport*v8;

    //Rasterizaçao
    int rgba[4];
    rgba[0] = 255, rgba[1] = 0, rgba[2]=0, rgba[3]=0;
    int rgba2[4];
    rgba2[0] = 255, rgba2[1] = 0, rgba2[2]=0, rgba2[3]=0;
    DrawLine(v1(0),v1(1), v2(0),v2(1),rgba,rgba2);
    DrawLine(v1(0),v1(1), v3(0),v3(1),rgba,rgba2);
    DrawLine(v1(0),v1(1), v5(0),v5(1),rgba,rgba2);

    DrawLine(v4(0),v4(1), v2(0),v2(1),rgba,rgba2);
    DrawLine(v4(0),v4(1), v3(0),v3(1),rgba,rgba2);
    DrawLine(v4(0),v4(1), v8(0),v8(1),rgba,rgba2);

    DrawLine(v6(0),v6(1), v2(0),v2(1),rgba,rgba2);
    DrawLine(v6(0),v6(1), v5(0),v5(1),rgba,rgba2);
    DrawLine(v6(0),v6(1), v8(0),v8(1),rgba,rgba2);

    DrawLine(v7(0),v7(1), v3(0),v3(1),rgba,rgba2);
    DrawLine(v7(0),v7(1), v5(0),v5(1),rgba,rgba2);
    DrawLine(v7(0),v7(1), v8(0),v8(1),rgba,rgba2);*/
}
#endif // _MYGL_H_
      

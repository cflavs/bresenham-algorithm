#include<iostream>
#include "mygl.h"

class Bresenham{
    public: void calcBresenham(int x0, int y0, int x1, int y1, int rgba[], int rgba1[]);
            void PutPixel(int x, int y, int rgba[]);
            void decliveD();
            void inverteVertice();
            void simpleBresenham(bool declive, bool simetrico, int rgba[], int rgba1[]);
            void inverteCoordenadas(int x, int y, int rgba[]);

    private: Pixel p0,p1,pixelFinal;
             int dx, dy;
};

void Bresenham::PutPixel(int x, int y, int rgba[]){
    pixelFinal.setX(x);
    pixelFinal.setY(y);
    pixelFinal.setCores(rgba[0], rgba[1], rgba[2], rgba[3]);
    pixelFinal.getPixel();
}

void Bresenham::decliveD(){
    //inverte x com -y
     int temp = p0.getX();
     p0.setX(-p0.getY());
     p0.setY(temp);
   
     temp = p1.getX();
     p1.setX(-p1.getY());
     p1.setY(temp);
    
    //recalcula deltas
     dx = p1.getX() - p0.getX();
     dy = p1.getY() - p0.getY();
}

void Bresenham::inverteVertice(){
    //inverte os vertices
     int temp = p0.getX();
     p0.setX(p1.getX());
     p1.setX(temp);
 
     temp = p0.getY();
     p0.setY(p1.getY());
     p1.setY(temp);
 
     //recalcula deltas
     dx = p1.getX() - p0.getX();
     dy = p1.getY() - p0.getY();
}

void Bresenham::inverteCoordenadas(int x, int y, int rgba[]){
    PutPixel(y,-x,rgba);
}

void Bresenham::simpleBresenham(bool declive, bool simetrico, int rgba[],int rgba1[]){
    int d = 2 * dy - dx;
    int incr_e = 2 * dy;
    int incr_ne = 2 * (dy - dx);
    int x = p0.getX();
    int y = p0.getY();

    int rgbaFinal[4];
    float rInicial = rgba[0], gInicial = rgba[1], bInicial = rgba[2];
    float varR = (float)(rgba1[0] - rgba[0])/dx;
    float varG = (float)(rgba1[1] - rgba[1])/dx;
    float varB = (float)(rgba1[2] - rgba[2])/dx;
    rInicial += varR;
    gInicial += varG;
    bInicial += varB;
     
    rgbaFinal[0] = rInicial;
    rgbaFinal[1] = gInicial;
    rgbaFinal[2] = bInicial;

    if(declive)
    inverteCoordenadas(x,y, rgbaFinal);
    else PutPixel(x,y,rgbaFinal);
   
     while (x < p1.getX()) {
           if (d <= 0) {
               d += incr_e;
               x++;
           } else {
               d += incr_ne;
               x++;
               if(simetrico)
               y--;
               else y++;
           }
           if(declive){
                rInicial = rInicial + varR;
                gInicial = gInicial + varG;
                bInicial = bInicial + varB;
                 
                rgbaFinal[0] = rInicial;
                rgbaFinal[1] = gInicial;
                rgbaFinal[2] = bInicial;
                inverteCoordenadas(x,y, rgbaFinal);
            }
           else {
                rInicial = rInicial + varR;
                gInicial = gInicial + varG;
                bInicial = bInicial + varB;
                 
                rgbaFinal[0] = rInicial;
                rgbaFinal[1] = gInicial;
                rgbaFinal[2] = bInicial;
                PutPixel(x,y,rgbaFinal);
            }
    }   
}
void Bresenham::calcBresenham(int x0, int y0, int x1, int y1, int rgba[],int rgba1[]) {
  //  Pixel p0,p1, pixelFinal;
    p0.setX(x0), p0.setY(y0);
    p1.setX(x1), p1.setY(y1);
    bool declive=false, simetrico=false;
    dx = p1.getX() - p0.getX();
    dy = p1.getY() - p0.getY();
    
    if (abs(dy) > abs(dx)) {
        declive=true;
        decliveD();}
    if (dx<0) {
        inverteVertice();
        int *tempCor;
        tempCor = rgba;
        rgba = rgba1;
        rgba1 = tempCor;
    }
    if (dy<0){
            dy = dy*(-1);
            simetrico = true;
            simpleBresenham(declive,simetrico,rgba,rgba1);
    }else
        simpleBresenham(declive,simetrico, rgba,rgba1);
}

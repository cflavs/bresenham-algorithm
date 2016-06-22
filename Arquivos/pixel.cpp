#include<iostream>
#include "mygl.h"

using namespace std;
class Pixel{
    public: void setX(int x);
            void setY(int y);
            int getX();
            int getY();
            void setCores(int red, int green, int blue, int alpha);
            void getPixel();
    private: int x,y, red, green, blue, alpha;
};

void Pixel::setX(int x){
    this->x = x;
}
void Pixel::setY(int y){
    this->y = y;
}
void Pixel::setCores(int red, int green, int blue, int alpha){
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}
int Pixel::getX(){
    return x;
}
int Pixel::getY(){
    return y;
}

void Pixel::getPixel(){
    FBptr[(x*4)+(y*4*IMAGE_WIDTH)+0] = red; // componente R
    FBptr[(x*4)+(y*4*IMAGE_WIDTH)+1] = green; // componente G
    FBptr[(x*4)+(y*4*IMAGE_WIDTH)+2] = blue; // componente B
    FBptr[(x*4)+(y*4*IMAGE_WIDTH)+3] = alpha; // componente A*/
}



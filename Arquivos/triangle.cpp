class Triangle{
    public: void getTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int rgba[], int rgba1[], int rgba2[]);
};

void Triangle::getTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int rgba[], int rgba1[], int rgba2[]){
    Bresenham line1, line2, line3;
    line1.calcBresenham(x0,y0,x1,y1,rgba, rgba1);
    line2.calcBresenham(x1,y1,x2,y2,rgba1,rgba2);
    line3.calcBresenham(x0,y0,x2,y2,rgba,rgba2);
}


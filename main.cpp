#include "main.h"
#include "objLoader.h"
#include <iostream>
#include <stdio.h>


// Ponteiro para o objeto que carregará o modelo 3D (formato OBJ).
objLoader *objData;
//-----------------------------------------------------------------------------
void MyGlDraw(void)
{
	//*************************************************************************
	// Chame aqui as funções do mygl.h
	//*************************************************************************
	int x1, y1, x2,y2,x3,y3,x4,y4,rgba[4], rgba1[4], rgba2[4];
    int red = 255, green=0, blue = 0, alpha=255;
	x1 = 100, y1 = 100, x2 = 100, y2 =400, x3 = 400, y3 = 100, x4=400, y4=400;
	rgba[0] = 255, rgba[1] = 0, rgba[2]=0, rgba[3]=0;
	rgba1[0] = 255, rgba1[1] = 0, rgba1[2]=0, rgba1[3]=0;
	rgba2[0] = 255, rgba2[1] = 0, rgba2[2]=255, rgba2[3]=0;

	//DrawLine(x1,y1,x2,y2,rgba,rgba1);
	//DrawLine(x1,y1,x3,y3,rgba,rgba1);
	//DrawLine(x3,y3,x4,y4,rgba,rgba1);
	//DrawLine(x4,y4,x2,y2,rgba,rgba1);
	
//	DrawLine(x1,y1,x2,y2,rgba,rgba1);
	//DrawTriangle(x1,y1,x2,y2,x3,y3,rgba,rgba1,rgba2);
	Pipeline(objData);
/*	int rgba[3], rgba1[3];
	rgba[0] = 255, rgba[1] = 0, rgba[2]=0, rgba[3]=255;
	int x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,x7,y7,x8,y8, x9, y9, x10, y10, x11, y11;
	int x12, y12, x13,y13, x14, y14, x15,y15, x16, y16, x17, y17;	
	x1 = 256, y1=256, x2 = 256, y2 =0;
	x3 = 0, y3 = 256;
	x4 = 0, y4 = 512;
	x5 = 512, y5 = 0;
	x6 = 512, y6 = 512;
	x7 = 0, y7 = 0;
	x8 = 256, y8= 512;
	x9 = 512, y9 = 256;
	x10 = 0, y10 = 384;
	x11 = 128, y11 = 512;
	x12 = 384, y12 = 512;
	x13 = 512, y13 = 384;
	x14 = 512, y14 = 128;
	x15 = 384, y15 = 0;
	x16 = 128, y16 = 0;
	x17 = 0, y17 = 128;
	DrawLine(x1,y1,x2,y2,rgba,rgba1);
	DrawLine(x1,y1,x3,y3,rgba,rgba1);
	DrawLine(x1,y1,x4,y4,rgba,rgba1);
	DrawLine(x1,y1,x5,y5,rgba,rgba1);
	DrawLine(x1,y1,x6,y6,rgba,rgba1);
	DrawLine(x1,y1,x7,y7,rgba,rgba1);
	DrawLine(x1,y1,x8,y8,rgba,rgba1);
	DrawLine(x1,y1,x9,y9,rgba,rgba1);
	DrawLine(x1,y1,x10,y10,rgba,rgba1);
	DrawLine(x1,y1,x11,y11,rgba,rgba1);
	DrawLine(x1,y1,x12,y12,rgba,rgba1);
	DrawLine(x1,y1,x13,y13,rgba,rgba1);
	DrawLine(x1,y1,x14,y14,rgba,rgba1);
	DrawLine(x1,y1,x15,y15,rgba,rgba1);
	DrawLine(x1,y1,x16,y16,rgba,rgba1);
	DrawLine(x1,y1,x17,y17,rgba,rgba);*/
}

//-----------------------------------------------------------------------------
int main(int argc, char **argv)
{
//	objData = new objLoader();			// cria o objeto que carrega o modelo
	//objData->load("obj_loader/monkey_head2.obj");	// a carga do modelo é indicada atraves do nome do arquivo. 
	// Inicializações.
	objData = new objLoader();			// cria o objeto que carrega o modelo
	objData->load("monkey_head2.obj");	// a carga do modelo é indicada atraves do nome do arquivo. 
										// Neste caso, deve ser sempre do tipo OBJ.

	InitOpenGL(&argc, argv);
	InitCallBacks();
	InitDataStructures();

	// Ajusta a função que chama as funções do mygl.h
	DrawFunc = MyGlDraw;	

	// Framebuffer scan loop.
	glutMainLoop();

	return 0;
}


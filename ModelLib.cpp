/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004
------------------------------[ ModelLib.cpp ]-------------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Thu Aug 20 2004
Email : alexandrefontoura@oninetspeed.pt

Original code: Vicent Hamm [yaz0r]

-------------------------------[ GNU License ]-------------------------------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

-----------------------------------------------------------------------------
*/

#include <vcl.h>
#pragma hdrstop

#include "ModelLib.h"
#include "tab.h"
#include "HQRLib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


HDC   gl_HDC;
HGLRC gl_HRC;

GLboolean should_rotate=0;
int angle=0;
int mainTab2[5000];
unsigned char* bodyPtr;

int mainTab3[5000];


GLint modele;
GLfloat zoom=-5;
GLboolean wireFrame;

int currentModel=0;

int rs1v1;
int rs1v2;
short int *tab1;
pointTab renderTab5[8000];
pointTab renderTab6[8000];
short int shadeTable[500];
unsigned char *renderV19;
int rs1s2v1;
unsigned char* rs1s2v2;
pointEntry *ptEntryPtr;
pointTab *pointPtr;
pointTab *pointPtr2;
int numOfDataBlocks;
int sizeOfBlocksHeader;
unsigned char* pri1Ptr;
short int numOfPri2;
unsigned char* pri2Ptr2;
unsigned char* pri2Ptr;
int primitiveCounter;
int renderTab2[50000];
int *renderTab3;
int *renderV21;
int numOfPri1;
int numOfPrimitives;
renderTabEntry *renderTabEntryPtr;
renderTabEntry primitiveList[5000];
unsigned char renderTab7[500000];


int numOfPoints;
int angleVert=0;

extern unsigned char palette[3*256];
extern AnsiString bodyPath;

//---------------------------------------------------------------------------

void start(TPanel *Panel1, int model)
{
   currentModel = model;
// 	should_rotate = GL_FALSE;
//	wireFrame = GL_FALSE;

	tab1=tab;

	mainTab2[14]=0;
	mainTab2[13]=0;
	mainTab2[12]=0;
	mainTab2[15]=0;
	mainTab2[16]=40;
	mainTab2[17]=40;
	mainTab2[39]=16384; // model width
	mainTab2[43]=16384; // model height
	mainTab2[47]=16384; // model depth

	renderTab3=&renderTab2[9];

	loadResource(bodyPath.c_str(),model,&bodyPtr);
	if(bodyPtr)
	{
		loadGfxSub(bodyPtr);
	}
   glInit(Panel1->Width, Panel1->Height);
}
//---------------------------------------------------------------------------

void draw_screen( void )
{
	int i;
	int j;
	GLfloat vertex[3];
	GLfloat vertex1[3];
	GLfloat vertex2[3];
	GLfloat vertex3[3];
	pointTab* currentVertex;
	int eax;
	int color;
	int numOfVertex;
	int polyRenderType;
	GLubyte colorTab[4];
	short int* dataPtr;
	short int currentVertexNumber;
	lineCoordinates *lineCoordinatesPtr;
	GLfloat vertexN1;
	GLfloat vertexN2;
	GLfloat vertexN3;
	pointTab* vertexData;
	pointTabShaded* vertexDataShaded;

   /* Clear the color and depth buffers. */
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   /* We don't want to modify the projection matrix. */
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity( );
   glPushMatrix();
   /* Move down the z-axis. */
   glTranslatef( 0.0, -1.5, zoom );
   glRotatef( 20, 1.0 , 0.0, 0.0);
    /* Rotate. */
	glRotatef(-40,0.0,1.0,0.0);

	if(wireFrame)
	{
	    glDisable( GL_CULL_FACE );
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glEnable( GL_CULL_FACE );
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	for(i=0;i<numOfPrimitives;i++)
	{
		if(primitiveList[i].renderType==1)
		{
			eax=*(int*)primitiveList[i].dataPtr;

			polyRenderType=eax&0xFF;
			numOfVertex=(eax&0xFF00)>>8;
			color=(eax&0xFF0000)>>16;

			if(polyRenderType==7 || polyRenderType==8 )
			{
					glBegin( GL_POLYGON );

					dataPtr=(short int*)(primitiveList[i].dataPtr+4);

					vertexDataShaded=(pointTabShaded*)(dataPtr);

					for(j=0;j<numOfVertex;j++)
					{

						color=vertexDataShaded->shader&0xFF;
						colorTab[0]=palette[color*3];
						colorTab[1]=palette[color*3+1];
						colorTab[2]=palette[color*3+2];
						colorTab[3]=0xFF;

						glColor4ubv(colorTab);

						currentVertexNumber=vertexDataShaded->number;

						vertex1[0]=((float)(renderTab5[currentVertexNumber].x))/400;
						vertex1[1]=((float)(renderTab5[currentVertexNumber].y))/400;
						vertex1[2]=((float)(renderTab5[currentVertexNumber].z))/400;
						glVertex3fv(vertex1);
						vertexDataShaded++;
					}

					glEnd( );
			}
			else
			if(polyRenderType==3)
			{
					colorTab[0]=palette[color*3];
					colorTab[1]=palette[color*3+1];
					colorTab[2]=palette[color*3+2];
					colorTab[3]=0x50;

					glColor4ubv(colorTab);

					glBegin( GL_POLYGON );

					dataPtr=(short int*)(primitiveList[i].dataPtr+4);

					vertexDataShaded=(pointTabShaded*)(dataPtr);

					for(j=0;j<numOfVertex;j++)
					{

						currentVertexNumber=vertexDataShaded->number;

						vertex1[0]=((float)(renderTab5[currentVertexNumber].x))/400;
						vertex1[1]=((float)(renderTab5[currentVertexNumber].y))/400;
						vertex1[2]=((float)(renderTab5[currentVertexNumber].z))/400;
						glVertex3fv(vertex1);
						vertexDataShaded++;
					}

					glEnd( );
			}
			else
			{
					colorTab[0]=palette[color*3];
					colorTab[1]=palette[color*3+1];
					colorTab[2]=palette[color*3+2];
					colorTab[3]=0xFF;

					glColor4ubv(colorTab);

					glBegin( GL_POLYGON );

					dataPtr=(short int*)(primitiveList[i].dataPtr+4);

					vertexDataShaded=(pointTabShaded*)(dataPtr);

					for(j=0;j<numOfVertex;j++)
					{

						currentVertexNumber=vertexDataShaded->number;

						vertex1[0]=((float)(renderTab5[currentVertexNumber].x))/400;
						vertex1[1]=((float)(renderTab5[currentVertexNumber].y))/400;
						vertex1[2]=((float)(renderTab5[currentVertexNumber].z))/400;
						glVertex3fv(vertex1);
						vertexDataShaded++;
					}

					glEnd( );
			}

		}

		if(primitiveList[i].renderType==0)
		{
			lineCoordinatesPtr=(lineCoordinates*)primitiveList[i].dataPtr;
            color=(lineCoordinatesPtr->data&0xFF00)>>8;

			colorTab[0]=palette[color*3];
			colorTab[1]=palette[color*3+1];
			colorTab[2]=palette[color*3+2];
			colorTab[3]=0xFF;

			glColor4ubv(colorTab);

			glBegin( GL_LINES );

			currentVertexNumber=lineCoordinatesPtr->p1;

			vertex[0]=((float)(renderTab5[currentVertexNumber].x))/400;
			vertex[1]=((float)(renderTab5[currentVertexNumber].y))/400;
			vertex[2]=((float)(renderTab5[currentVertexNumber].z))/400;
			glVertex3fv(vertex);

			currentVertexNumber=lineCoordinatesPtr->p2;

			vertex[0]=((float)(renderTab5[currentVertexNumber].x))/400;
			vertex[1]=((float)(renderTab5[currentVertexNumber].y))/400;
			vertex[2]=((float)(renderTab5[currentVertexNumber].z))/400;
			glVertex3fv(vertex);

			glEnd();


		}

		if(primitiveList[i].renderType==2)
		{
			circleData* currentCircle;

			currentCircle=(circleData*)primitiveList[i].dataPtr;

			color=(currentCircle->color&0xFF00)>>8;

			colorTab[0]=palette[color*3];
			colorTab[1]=palette[color*3+1];
			colorTab[2]=palette[color*3+2];
			colorTab[3]=0xFF;

			glColor4ubv(colorTab);

			glPointSize(((float)currentCircle->size)/2);

			currentVertexNumber=currentCircle->center;

			vertex[0]=((float)(renderTab5[currentVertexNumber].x))/400;
			vertex[1]=((float)(renderTab5[currentVertexNumber].y))/400;
			vertex[2]=((float)(renderTab5[currentVertexNumber].z))/400;

			glPushMatrix();

			GLUquadric* quadric=gluNewQuadric();

		    glTranslatef(vertex[0], vertex[1] , vertex[2] );

			gluSphere(quadric,((float)currentCircle->size)/400,10,10);

			glPopMatrix();

		}
	}

	glPopMatrix();

   SwapBuffers(gl_HDC);
}
//---------------------------------------------------------------------------

void loadGfxSub(unsigned char * ptr)
{
  int var1;
  int var2;
  int bp;
  int bx;

  if(!((*(short int*)ptr) & 2))
    return;
  
  var1=*(short int*)(ptr+14);
  ptr=ptr+var1+16;
  var1=*(short int*)ptr;
  ptr+=2;
  var1=var1+var1*2;
  ptr=ptr+var1*2;
 
  var2=*(short int*)ptr;
  ptr+=2;
 
  bp=36;
  bx=38;

  while(--var2 >= 0)
  {
    ptr+=38;
    *(short int*)(ptr+6)=(*(short int*)(ptr+6)*bp)/bx;
  };
}
//---------------------------------------------------------------------------

int setupModel(unsigned char * costumePtr)
{

  unsigned int var1;
  unsigned char* ptr3;
//  int *ptr4;
  int *ptr5;

  int coX;
  int coY;
  int coZ;

  unsigned char* ptr6;
  int eax;
  int ebx;
  int ebp;
  int edx;
  int ecx;
  int edi;
  short int flag;
  int temp;

  numOfPri1=numOfDataBlocks=*(short int*)costumePtr;
  costumePtr+=2;

  pri1Ptr=costumePtr;

  sizeOfBlocksHeader=numOfDataBlocks+numOfDataBlocks*2;

  costumePtr=costumePtr+sizeOfBlocksHeader*2;

  numOfPri2=*(short int*)costumePtr; // that's the number of points in the model

  costumePtr+=2; // we jump to the points data

  pri2Ptr2=pri2Ptr=costumePtr; // we save the point data ptr

  renderV19=(unsigned char *)renderTab2;

  renderS1(mainTab2[14],mainTab2[13],mainTab2[12],(pointEntry*)pri2Ptr2); // that's the process of the "base point"

  pri2Ptr2+=38; // jump to the next point data

  ptEntryPtr=(pointEntry*)pri2Ptr2; // that's the structure used to load the points

  if(numOfPri2 -1 !=0 ) // if there is points after the base point
  {
    primitiveCounter=numOfPri2-1; // Since the base point is already processed, we need to load numOfPri2-1 points
    renderV19=(unsigned char *)renderTab3; // the use of renderTab3 is still unknown. It's a table with 36byte long element

    do   // That's the loop that load and convert all the points in the model
    {
      ebx=ptEntryPtr->flag1;  // actualy, there should be 4 flags in that order = ebx,flag,edx,ecx. So this part may be buggy. at the momment
      flag=ebx;
      ebx>>=16;

      edx=ptEntryPtr->flag2;
      ecx=(short int)edx;
      edx>>=16;

      if(flag == 0)
      {
        renderS1(edx,ecx,ebx,ptEntryPtr); // renderS1 load the points, rotate them and store them in renderTab5 (it may do other things too..)
      }
      else
      {
        if(flag == 1)
        {

          //renderS2      // this part seems to be rarely used...

          printf("renderM1\n");
          exit(1);
        }
      }

      renderV19+=36; // next entry in renderTab3

      pri2Ptr2+=38;  // next point data
      ptEntryPtr=(pointEntry*)pri2Ptr2; // we use the structure to load the point data
    }while(--primitiveCounter);
  }

  primitiveCounter = numOfPri1;
  numOfPoints=numOfPri1;

  pointPtr2=(pointTab*)renderTab5;
  pointPtr=renderTab6;

	ptr5=(int*)pri2Ptr2;
	eax=-1;

	temp=*(short int*)ptr5;

	ptr5=(int*)(((unsigned char*)ptr5)+2);

	if(temp) // process shading table
	{
		renderV19=(unsigned char*)shadeTable;
		renderV21=renderTab2;
		primitiveCounter=numOfPri2;
		ptr3=pri2Ptr2=pri2Ptr+18;

		do      // pour chaque poly ?
		{
			temp=*(short int*)ptr3;
			if(temp)
			{
				rs1s2v1=temp;

				mainTab2[21]=(*renderV21)*mainTab2[15];
				mainTab2[22]=(*(renderV21+1))*mainTab2[15];
				mainTab2[23]=(*(renderV21+2))*mainTab2[15];

				mainTab2[24]=(*(renderV21+3))*mainTab2[16];
				mainTab2[25]=(*(renderV21+4))*mainTab2[16];
				mainTab2[26]=(*(renderV21+5))*mainTab2[16];

				mainTab2[27]=(*(renderV21+6))*mainTab2[17];
				mainTab2[28]=(*(renderV21+7))*mainTab2[17];
				mainTab2[29]=(*(renderV21+8))*mainTab2[17];

				do    // pour chaque vertex ?
				{
					short int col1;
					short int col2;
					short int col3;

					short int *colPtr;

					colPtr=(short int*)ptr5;

					col1=*(colPtr++);
					col2=*(colPtr++);
					col3=*(colPtr++);

					eax=mainTab2[21]*col1+mainTab2[22]*col2+mainTab2[23]*col3;
					eax+=mainTab2[24]*col1+mainTab2[25]*col2+mainTab2[26]*col3;
					eax+=mainTab2[27]*col1+mainTab2[28]*col2+mainTab2[29]*col3;

					edi=0;

					if(eax>0)
					{
						eax>>=14;
						ptr6=(unsigned char*)ptr5;
						eax/=*(unsigned short int*)(ptr6+6);
						edi=(unsigned short int)eax;
					}

					*(short int*)renderV19=edi;
					renderV19+=2;
					ptr5+=2;

				}while(--rs1s2v1);

			}
			ptr3=pri2Ptr2=pri2Ptr2+38;
//			ptr4=renderV21=renderV21+9;
		}while(--primitiveCounter);

	}


  return(finishModelSetup((unsigned char*)ptr5));

}
//---------------------------------------------------------------------------

int finishModelSetup(unsigned char* esi)
{

	unsigned char *edi;
	unsigned char *render23;
	unsigned char *render24;
	short int temp;
	int eax;//, ecx;
	short int bp;
	unsigned char temp2;
	short int counter;
	short int temp3;
	short int type;
	short int color;
	float tempFloat;
	int render25;
	short int ax;
	short int bx;
	short int cx;
	lineData* lineDataPtr;
	lineCoordinates* lineCoordinatesPtr;
	short int vertexNumber;
	int point1;
	int point2;
	int polyRenderType;
	short int bestDepth;
	short int shadeValue;
	short int currentDepth;
	short int shadeEntry;

	struct polyHeader
	{
		unsigned char polyRenderType;
		unsigned char numOfVertex;
		unsigned short int colorIndex;
	};

	struct polyVertexHeader
	{
		unsigned short int shadeEntry;
		unsigned short int dataOffset;
	};

	struct computedVertex
	{
		unsigned short int shadeValue;
		unsigned short int vertexNumber;
	};

	polyVertexHeader* currentPolyVertex;
	polyHeader* currentPolyHeader;
	polyHeader* destinationHeader;
	computedVertex* currentComputedVertex;
	pointTab* currentVertex;
	pointTab* destinationVertex;

	int primitiveCounter;
	short int numOfPolygons;

	edi=renderTab7; // coordinate buffer
	numOfPrimitives=0;
	renderTabEntryPtr=primitiveList;

	numOfPolygons=*(short int*)esi;
	esi+=2;

	if(numOfPolygons)
	{
		primitiveCounter=numOfPolygons;

		do // loop that load all the polygones
		{		
			render23=edi;
			currentPolyHeader=(polyHeader*)esi;
//			ecx=*(int*)esi;
			esi+=2;
			polyRenderType=currentPolyHeader->polyRenderType;

			if(polyRenderType>=9)
			{
				destinationHeader=(polyHeader*)edi;

				destinationHeader->polyRenderType	=	currentPolyHeader->polyRenderType-2;
				destinationHeader->numOfVertex		=	currentPolyHeader->numOfVertex;
				destinationHeader->colorIndex		=	currentPolyHeader->colorIndex;

				esi+=2;
				edi+=4;

				counter=destinationHeader->numOfVertex;

				bestDepth=-32000;
				renderV19=edi;

				do
				{

					currentPolyVertex=(polyVertexHeader*)esi;

					shadeValue=currentPolyHeader->colorIndex+shadeTable[currentPolyVertex->shadeEntry];

					currentComputedVertex=(computedVertex*)edi;

					currentComputedVertex->shadeValue=shadeValue;

					currentComputedVertex->vertexNumber=currentPolyVertex->dataOffset/6;

					edi+=4;
					esi+=4;

				}while(--counter);
			}
			else
			if(polyRenderType>=7) // only 1 shade value is used
			{
				destinationHeader=(polyHeader*)edi;

				destinationHeader->polyRenderType	=	currentPolyHeader->polyRenderType-7;
				destinationHeader->numOfVertex		=	currentPolyHeader->numOfVertex;

				color=currentPolyHeader->colorIndex;

				shadeEntry=*(short int*)(esi+2);

				esi+=4;

				*(short int*)(edi+2)=color+shadeTable[shadeEntry];

				edi+=4;
				renderV19=edi;
				bestDepth=-32000;
				counter=destinationHeader->numOfVertex;

				do
				{
					eax=*(short int*)esi;
					esi+=2;

					currentComputedVertex=(computedVertex*)edi;

//					currentComputedVertex->shadeValue=shadeValue;

					currentComputedVertex->vertexNumber=eax/6;
					edi+=4;

//					currentDepth=currentVertex->z;

/*					if(currentDepth>bestDepth)
						bestDepth=currentDepth;*/
				}while(--counter);
			  }
			else // no shade is used
			{
				destinationHeader=(polyHeader*)edi;

				destinationHeader->polyRenderType	=	currentPolyHeader->polyRenderType-2;
				destinationHeader->numOfVertex		=	currentPolyHeader->numOfVertex;
				destinationHeader->colorIndex		=	currentPolyHeader->colorIndex;

				esi+=2;
				edi+=4;

				bestDepth=-32000;
				renderV19=edi;
				eax=0;
				counter=currentPolyHeader->numOfVertex;

				do
				{
					eax=*(unsigned short int*)esi;
					esi+=2;

					currentComputedVertex=(computedVertex*)edi;

//					currentComputedVertex->shadeValue=shadeValue;

					currentComputedVertex->vertexNumber=eax/6;
					edi+=4;


/*					currentDepth=currentVertex->z;

					if(currentDepth>bestDepth)
						bestDepth=currentDepth;*/
				}while(--(counter));
			}

			render24=edi;

//			primitiveList[numOfPrimitives].depth=render25;
			primitiveList[numOfPrimitives].renderType=1;
			primitiveList[numOfPrimitives].dataPtr=render23;
			renderTabEntryPtr++;
			numOfPrimitives++;


			edi=render24;

		}while(--primitiveCounter);
	}

  temp=*(short int*)esi;
  esi+=2;
  if(temp) // pour les lignes (0)
  {
    numOfPrimitives+=temp;
    do
    {
      lineDataPtr=(lineData*)esi;
      lineCoordinatesPtr=(lineCoordinates*)edi;

      if(lineDataPtr->p1%6 != 0 || lineDataPtr->p2%6 !=0)
      {
        printf("lineDataPtr reference is malformed !\n");
        exit(1);
      }

      point1=lineDataPtr->p1/6;
      point2=lineDataPtr->p2/6;
      lineCoordinatesPtr->data=lineDataPtr->data;
      lineCoordinatesPtr->p1=point1;
	  lineCoordinatesPtr->p2=point2;

      renderTabEntryPtr->depth=bestDepth;
      renderTabEntryPtr->renderType=0;
      renderTabEntryPtr->dataPtr=edi;
      renderTabEntryPtr++;

      esi+=8;
      edi+=12;
    }while(--temp);
  }


  temp=*(short int*)esi;
  esi+=2;
  if(temp)
  {
	  circleData* circleDataPtr;
	  circleData* circleData2Ptr;

	  numOfPrimitives+=temp;

	  do
	  {
		circleDataPtr=(circleData*)esi;
		circleData2Ptr=(circleData*)edi;

		circleData2Ptr->center=circleDataPtr->center/6;
		circleData2Ptr->size=circleDataPtr->size;
		circleData2Ptr->color=circleDataPtr->color;

		renderTabEntryPtr->renderType=2;
		renderTabEntryPtr->dataPtr=edi;
		renderTabEntryPtr++;

		esi+=sizeof(circleData);
		edi+=sizeof(circleData);

	  }while(--temp);
  }


	return(0);
}
//---------------------------------------------------------------------------

void renderS1S2(unsigned char * esi, int ecx, pointTab *dest,int* eax)
{
//  int i;
 short int param1;
 short int param2;
 short int param3;

 int ebx;
 int edx;
// int var;
// int var2;
 int edi;
 int esip;
 int ebp;

 short int* tempPtr;

  rs1s2v1=ecx;

 do
 {
  rs1s2v2=esi;
  tempPtr=(short int*)(esi);

  param1=tempPtr[0];
  param2=tempPtr[1];
  param3=tempPtr[2];

  dest->x=((eax[0]*param1+eax[1]*param2+eax[2]*param3)>>14)+mainTab2[18];
  dest->y=((eax[3]*param1+eax[4]*param2+eax[5]*param3)>>14)+mainTab2[19];
  dest->z=((eax[6]*param1+eax[7]*param2+eax[8]*param3)>>14)+mainTab2[20];

  dest++;
  esi=rs1s2v2+6;
 }while(--rs1s2v1);
}
//---------------------------------------------------------------------------

void renderS1S1(int* eax, int* ebp)
{
  int i;
  int edx;
  int esi;
//  int ecx;
  int edi;
  int *ptr;

  int angle;
  int angleVar1; //esi
  int angleVar2; //ecx

  int angle2;
  int angle2Var1; //esi
  int angle2Var2; //ecx

  if(mainTab2[12]) // rotation par vers l'avant
 {
	angle=mainTab2[12]&0x3FF;
	angleVar2=tab1[angle];
	angle+=0x100;
	angle&=0x3FF;
	angleVar1=tab1[angle];

	eax[0]=ebp[0];
	eax[3]=ebp[3];
	eax[6]=ebp[6];

	eax[1]=(ebp[2]*angleVar2+ebp[1]*angleVar1)>>14;
	eax[2]=(ebp[2]*angleVar1-ebp[1]*angleVar2)>>14;
	eax[4]=(ebp[5]*angleVar2+ebp[4]*angleVar1)>>14;
	eax[5]=(ebp[5]*angleVar1-ebp[4]*angleVar2)>>14;
	eax[7]=(ebp[8]*angleVar2+ebp[7]*angleVar1)>>14;
	eax[8]=(ebp[8]*angleVar1-ebp[7]*angleVar2)>>14;

	ebp=eax;

 }
 if(mainTab2[14])
 {
  printf("renderS1S1 -> unhandled maintTab[14] rotation\n");
  exit(1);
 }
 if(mainTab2[13]) // rotation de coté (la plus courante)
 {

  if(ebp==eax)
  {
    ebp=&mainTab2[30];

    for(i=0;i<9;i++)
      *(ebp++)=*(eax++);
  }

  angle=mainTab2[13]&0x3FF;
  angleVar2=tab1[angle]; //esi
  angle+=0x100;
  angle&=0x3FF;
  angleVar1=tab1[angle]; //ecx


  eax[1]=ebp[1];
  eax[4]=ebp[4];
  eax[7]=ebp[7];


  eax[0]=(ebp[0]*angleVar1-ebp[2]*angleVar2)>>14;
  eax[2]=(ebp[0]*angleVar2+ebp[2]*angleVar1)>>14;
  eax[3]=(ebp[3]*angleVar2-ebp[5]*angleVar1)>>14;
  eax[5]=(ebp[5]*angleVar2+ebp[3]*angleVar1)>>14;
  eax[6]=(ebp[6]*angleVar1-ebp[8]*angleVar2)>>14;
  eax[8]=(ebp[6]*angleVar2+ebp[8]*angleVar1)>>14;

  return;


 }
 else
 {
  if(ebp!=eax)
    for(i=0;i<9;i++)
     *(eax++)=*(ebp++);

  return;
 }

}
//---------------------------------------------------------------------------

void renderS1(int edx, int ecx, int ebx, pointEntry* ptr)
{
  int *ebp;
 short int var;
// int* ptr1;

 mainTab2[12]=ebx;
 mainTab2[13]=ecx;
 mainTab2[14]=edx;

 rs1v1=ptr->data1;

 rs1v2=ptr->data2;


  if(rs1v1%6)
    {
      printf("Error: rs1V1\n");
      exit(1);
    }

 var=ptr->param;

 if(var == -1)    // si c'est le premier point
 {
  ebp=&mainTab2[39];

  mainTab2[18]=0;
  mainTab2[19]=0;
  mainTab2[20]=0;
 }
 else
 {


  ebp=(int*)(((unsigned char*)renderTab2)+var);

  mainTab2[18]=renderTab5[ptr->data3/6].x;
  mainTab2[19]=renderTab5[ptr->data3/6].y;
  mainTab2[20]=renderTab5[ptr->data3/6].z;
 }

 renderS1S1((int*)renderV19,ebp); // de renderTab2 vers renderV19

 renderS1S2(pri1Ptr+rs1v1,rs1v2,&renderTab5[rs1v1/6],(int*)renderV19);

}
//---------------------------------------------------------------------------

int renderM2(unsigned char * ptr)
{
  printf("renderM2\n");
 exit(1);
  return(-1);
}
//---------------------------------------------------------------------------

GLvoid CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[], GLfloat fVert3[], GLfloat *fNormalX, GLfloat *fNormalY, GLfloat *fNormalZ)
{
   GLfloat Qx, Qy, Qz, Px, Py, Pz;

   Qx = fVert2[0]-fVert1[0];
   Qy = fVert2[1]-fVert1[1];
   Qz = fVert2[2]-fVert1[2];
   Px = fVert3[0]-fVert1[0];
   Py = fVert3[1]-fVert1[1];
   Pz = fVert3[2]-fVert1[2];

   *fNormalX = Py*Qz - Pz*Qy;
   *fNormalY = Pz*Qx - Px*Qz;
   *fNormalZ = Px*Qy - Py*Qx;

}
//---------------------------------------------------------------------------

bool glCreate(TPanel *Panel1)
{
   gl_HDC = GetDC(Panel1->Handle);

   PIXELFORMATDESCRIPTOR pfd, *ppfd;
   int pixelformat;
   ppfd = &pfd;
   ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
   ppfd->nVersion = 1;
   ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
   ppfd->dwLayerMask = PFD_MAIN_PLANE;
   ppfd->iPixelType = PFD_TYPE_RGBA;
   ppfd->cColorBits = 16;
   ppfd->cDepthBits = 8;
   ppfd->cAccumBits = 0;
   ppfd->cStencilBits = 0;

   if ( (pixelformat = ChoosePixelFormat(gl_HDC, ppfd)) == 0 )
       return false;//MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);

   if (SetPixelFormat(gl_HDC, pixelformat, ppfd) == FALSE)
       return false;//MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);

   gl_HRC = wglCreateContext(gl_HDC);
   if(gl_HRC==NULL)
       return false;
   if(wglMakeCurrent(gl_HDC, gl_HRC)== false)
       return false;

   return true;
}
//---------------------------------------------------------------------------

void glInit(float w, float h)
{
   glViewport( 0, 0, w, h);
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();

   gluPerspective( 60.0, w/h, 1.0, 1024.0 );
   glMatrixMode( GL_MODELVIEW );


   glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
   glClearDepth( 1.0 );
   glEnable(GL_DEPTH_TEST);

   GLfloat specular [] = { 0.0, 0.0, 0.0, 0.0 };
	GLfloat shininess [] = { 0.0 };
//	GLfloat position [] = { 0.0, 0.0, -10.0, 0.0 };

	GLfloat LightAmbient[]=		{ 1.5f, 1.5f, 1.5f, 1.5f };
	GLfloat LightDiffuse[]=		{ 1.5f, 1.5f, 1.5f, 1.5f };
	GLfloat LightPosition[]=	{ 0.0f, 0.0f, -10.0f, 0.0f };

   glCullFace( GL_BACK );
   glFrontFace( GL_CCW );
   glEnable( GL_CULL_FACE );

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

   glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		// Setup The Ambient Light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		// Setup The Diffuse Light
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	// Position The Light
	glEnable(GL_LIGHT1);
}
//---------------------------------------------------------------------------

void glShutDwn(TPanel *Panel1)
{
   if (gl_HRC) wglDeleteContext(gl_HRC);
   if (gl_HDC) ReleaseDC(Panel1->Handle, gl_HDC);
   wglMakeCurrent(NULL, NULL);
   Panel1->Repaint();
}
//---------------------------------------------------------------------------

void Draw()
{
   if(should_rotate)
       angle+=6;
	mainTab2[13] = angle;
	setupModel(bodyPtr+0x1A);
	draw_screen();
}
//---------------------------------------------------------------------------

void setModel(int model)
{
   currentModel = model;
  	loadResource(bodyPath.c_str(),currentModel,&bodyPtr);
 	if(bodyPtr)
  	{
		loadGfxSub(bodyPtr);
       free(bodyPtr);
 	}
}
//---------------------------------------------------------------------------

void setZoom(double z)
{
   zoom += z;
}
//---------------------------------------------------------------------------

void setZoom()
{
   zoom = -5;
}
//---------------------------------------------------------------------------

void setAngle(int a)
{
   angle = a;
}
//---------------------------------------------------------------------------

int getAngle()
{
   return angle;
}
//---------------------------------------------------------------------------

void autorotate()
{
   should_rotate = !should_rotate;
}
//---------------------------------------------------------------------------

void wireframe()
{
   wireFrame = !wireFrame;
}
//---------------------------------------------------------------------------


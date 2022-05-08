/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004
-------------------------------[ ModelLib.h ]--------------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Thu Aug 20 2004
Email : alexandrefontoura@oninetspeed.pt

Original Code: Vicent Hamm [yaz0r]

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

#ifndef ModelLibH
#define ModelLibH
//---------------------------------------------------------------------------

#include <gl/gl.h>
#include <gl/glu.h>

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <process.h>

struct hqr_entry
{
 char fileName[128];
 int size1;
 int remainingSize;
 short int b;
 short int unk;
 unsigned char *ptr;
};

struct subHqr
{
 unsigned char index;
 unsigned int offFromPtr;
 unsigned int size;
 int lastAccessedTime;
};

struct pointTab
{
  short int x;
  short int y;
  short int z;
};

struct pointTabShaded
{
	short int shader;
	short number;
};

struct renderTabEntry
{
  short int depth;
  short int renderType;
  unsigned char* dataPtr;
};

struct pointEntry
{
  short int data1;
  short int data2;
  short int data3;
  short int param;
  int flag1;
  int flag2;
  int field_10;
  int field_14;
  int field_18;
  int field_1C;
  int field_20;
  short int field_24;
};

struct lineCoordinates
{
  int data;
  short int p1;
  short int p2;
};

struct lineData
{
  int data;
  short int p1;
  short int p2;
};

struct circleData
{
	int color;
	short int size;
	short int center;
};

bool glCreate(TPanel *Panel1);
void glInit(float w, float h);
void glShutDwn(TPanel *Panel1);

void start(TPanel *Panel1, int model);
void loadGfxSub(unsigned char * ptr);
void draw_screen( void );
int setupModel(unsigned char * costumePtr);
int finishModelSetup(unsigned char* esi);

void renderS1S2(unsigned char * esi, int ecx, pointTab *dest,int* eax);
void renderS1S1(int* eax, int* ebp);
void renderS1(int edx, int ecx, int ebx, pointEntry* ptr);
int renderM2(unsigned char * ptr);
GLvoid CalculateVectorNormal(GLfloat fVert1[], GLfloat fVert2[], GLfloat fVert3[], GLfloat *fNormalX,GLfloat *fNormalY, GLfloat *fNormalZ);

void Draw();
void setModel(int model);
void setZoom(double z);
void setZoom();
void setAngle(int a);
int getAngle();
void autorotate();
void wireframe();

#endif

#ifndef EntitiesH
#define EntitiesH

#include "HQRlib.h"

struct bodyDataStruct
{
	char body;
	short int index;

	char useColBox;

	int X1;
	int X2;
	int Z1;
	int Z2;
	int Y1;
	int Y2;
};

struct animDataStruct
{
	int anim;
	int index;
};

struct entitiesTableEntry
{
	int numOfBody;
	int numOfAnims;
	bodyDataStruct bodyList[20];
	animDataStruct animList[20];
};

struct entitiesTableStruct
{
	int numOfEntities;
	entitiesTableEntry* entitiesTable;
};

entitiesTableStruct* parseEntities(void);
entitiesTableStruct* parseEntities2(void);

#endif
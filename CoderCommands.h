//---------------------------------------------------------------------------

#ifndef CoderCommandsH
#define CoderCommandsH
//---------------------------------------------------------------------------

typedef struct {
    byte Id;
    short x1, y1, z1, x2, y2, z2;
} TStoryCommand;

int BuilderActions(TStoryCommand *data, unsigned long cmdOpcode);

#endif

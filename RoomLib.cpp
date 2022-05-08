/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004
-------------------------------[ RoomLib.cpp ]-------------------------------

Author: Alexandre Fontoura [alexfont]
Begin : Thu Aug 26 2004
Email : alexandrefontoura@oninetspeed.pt

Original code in Delphi: Kazimierz Król [Zink]

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

#include "RoomLib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

vector<TColor> TPalette;

//---------------------------------------------------------------------------

TBrick loadBrickPtr(unsigned char * ptr, bool isSprite)
{
   TBrick brick;
   int PixCount;
   if(isSprite)
      ptr+=8;

   brick.Width = *(ptr++);
   brick.Height = *(ptr++);
   brick.OffsetX = *(ptr++);
   brick.OffsetY = *(ptr++);
   brick.Lines.resize(brick.Height);
   for(int a=0; a < brick.Height; a++)
   {
       brick.Lines[a].SubCount = *(ptr++);
       brick.Lines[a].SubLines.resize(brick.Lines[a].SubCount);
       for(int b=0; b < brick.Lines[a].SubCount; b++)
       {
           brick.Lines[a].SubLines[b].Flags = *(ptr++);
           PixCount = (brick.Lines[a].SubLines[b].Flags & 0x3F) + 1;
           switch(brick.Lines[a].SubLines[b].Flags & 0xC0)
           {
               case 0x40:
               case 0xC0:
                   brick.Lines[a].SubLines[b].Colours.resize(PixCount);
                   for(int c=0; c < PixCount; c++)
                   {
                       brick.Lines[a].SubLines[b].Colours[c] = *(ptr++);
                   }
                   break;
               case 0x80:
                   brick.Lines[a].SubLines[b].Colours.resize(1);
                   brick.Lines[a].SubLines[b].Colours[0] = *(ptr++);
                   break;
           }
       }
   }
   return brick;
}
//---------------------------------------------------------------------------

void DrawBrick(TBrick brick, TCanvas *Canvas, vector<TColor> palette)
{
   Canvas->FillRect(Rect(0,0,255,255));
   int PixCount, Xpos;
   for(int a=0; a < brick.Height; a++)
   {
       Xpos = brick.OffsetX;
       for(int b=0; b < brick.Lines[a].SubCount; b++)
       {
           PixCount = (brick.Lines[a].SubLines[b].Flags & 0x3F) + 1;
           switch(brick.Lines[a].SubLines[b].Flags & 0xC0)
           {
               case 0x40:
               case 0xC0:
                   for(int c=0; c < PixCount; c++)
                   {
                       Canvas->Pixels[Xpos+c][a+brick.OffsetY] = palette[brick.Lines[a].SubLines[b].Colours[c]];
                   }
                   break;
               case 0x80:
                   for(int c=0; c < PixCount; c++)
                   {
                       Canvas->Pixels[Xpos+c][a+brick.OffsetY] = palette[brick.Lines[a].SubLines[b].Colours[0]];
                   }
                   break;
           }
           Xpos += PixCount;
       }
   }
}
//---------------------------------------------------------------------------

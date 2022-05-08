/*
-------------------------[ LBA Story Coder Source ]--------------------------
Copyright (C) 2004
-------------------------------[ RoomLib.h ]---------------------------------

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

#ifndef RoomLibH
#define RoomLibH

#include <stdio.h>
#include <vector>
#include <fstream.h>
//---------------------------------------------------------------------------

struct TSubLine{
   Byte Flags;
   vector<Byte> Colours;
};

struct TLine{
   Byte SubCount;
   vector <TSubLine>SubLines;
};

struct TBrick{
   Byte Width, Height, OffsetX, OffsetY;
   vector <TLine>Lines;
};

TBrick loadBrickPtr(unsigned char * ptr, bool isSprite);
void DrawBrick(TBrick brick, TCanvas *Canvas, vector<TColor> TPalette);

#endif

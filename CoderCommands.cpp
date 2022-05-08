//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "CoderCommands.h"
#include "LBAStoryCoder_main.h"
#include "SceneLib.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

extern TScene Scene;

/*
    Command types:
    --------------
    01 - Test communication
    10 - Set Track
    11 - Select Track
    12 - Delete Track
    13 - New Track
    20 - Set Zone
    21 - Select Zone
    22 - Delete Zone
    23 - New Zone
    24 - Clone Zone
    30 - Set Actor
    31 - Select Actor
    32 - Delete Actor
    33 - New Actor
    34 - New Sprite Actor (deprecated)
    35 - Clone Actor

    Command results:
    ----------------
    0 - unknown error
    1 - invalid id
    10 - invalid command
    100 - command ok
    1000 - test ok
*/

int BuilderActions(TStoryCommand *data, unsigned long cmdOpcode)
{
    int res;
//    TCopyDataStruct *tmp;
//    TStoryCommand *data;

 //   tmp = Message.CopyDataStruct;
    //data = (TStoryCommand *)tmp->lpData;

    res = 100; // OK

//    Message.Result = 100; // OK

    switch(cmdOpcode)
    {
        case 01: // Test commnication
            res = 1000;
            break;
        case 10: // Set track
            if(data->Id > Scene.numTracks-1) // invalid id
            {
               res = 1;
               break;
            }

            if(data->x1 < -256)
                data->x1 = -256;
            if(data->y1 < 0)
                data->y1 = 0;
            if(data->z1 < -256)
                data->z1 = -256;
            Scene.Tracks[data->Id].X = data->x1;
            Scene.Tracks[data->Id].Y = data->y1;
            Scene.Tracks[data->Id].Z = data->z1;
            // Update form values
            if(data->Id == frm_lba->edt_tracks->Value)
                frm_lba->edt_tracksChange(frm_lba);
            else
                frm_lba->edt_tracks->Value = data->Id;
            frm_lba->pl_scene->ActivePageIndex = 2;

            break;
        case 11: // Select Track
            if(data->Id > Scene.numTracks-1) // invalid id
            {
               res = 1;
               break;
            }

            frm_lba->edt_tracks->Value = data->Id;
            frm_lba->pl_scene->ActivePageIndex = 2;

            break;
        case 12: // Delete Track
            if(Scene.numActors > 0)
            {
                if(data->Id > Scene.numTracks-1) // invalid id
                {
                    res = 1;
                }
                else
                {
                    frm_lba->edt_tracks->Value = data->Id;
                    frm_lba->bt_removetrackClick(frm_lba);
                    frm_lba->pl_scene->ActivePageIndex = 2;
                }
            }
            else
            {
                res = 1;
            }
            break;
        case 13: // New Track
            frm_lba->NewTrack(data->x1, data->y1, data->z1);
            frm_lba->pl_scene->ActivePageIndex = 2;
            break;
        case 20: // Set Zone
            if(data->Id > Scene.numZones-1) // invalid id
            {
               res = 1;
            }
            else
            {
                if(data->x1 < -256)
                    data->x1 = -256;
                if(data->y1 < -256)
                    data->y1 = -256;
                if(data->z1 < -256)
                    data->z1 = -256;

                Scene.Zones[data->Id].X0 = data->x1;
                Scene.Zones[data->Id].Y0 = data->y1;
                Scene.Zones[data->Id].Z0 = data->z1;
                Scene.Zones[data->Id].X1 = data->x2;
                Scene.Zones[data->Id].Y1 = data->y2;
                Scene.Zones[data->Id].Z1 = data->z2;
                // Update form values
                if(data->Id == frm_lba->edt_zones->Value)
                    frm_lba->edt_zonesChange(frm_lba);
                else
                    frm_lba->edt_zones->Value = data->Id;
                frm_lba->pl_scene->ActivePageIndex = 3;
            }

            break;
        case 21: // Select Zone
            if(data->Id > Scene.numZones-1) // invalid id
            {
               res = 1;
            }
            else
            {
                frm_lba->edt_zones->Value = data->Id;
                frm_lba->pl_scene->ActivePageIndex = 3;
            }

            break;
        case 22: // Delete Zone
            if(Scene.numZones > 0)
            {
                if(data->Id > Scene.numZones-1) // invalid id
                {
                    res = 1;
                }
                else
                {
                    frm_lba->edt_zones->Value = data->Id;
                    frm_lba->bt_removezoneClick(frm_lba);
                    frm_lba->pl_scene->ActivePageIndex = 3;
                }
            }
            else
            {
                res = 1;
            }
            break;
        case 23: // New Zone
            frm_lba->NewZone(data->x1, data->y1, data->z1, 0, 0, 0);
            frm_lba->pl_scene->ActivePageIndex = 3;
            break;
        case 24: // Clone Zone
            frm_lba->CloneZone(data->x1, data->y1, data->z1, data->x2, data->y2, data->z2);
            frm_lba->pl_scene->ActivePageIndex = 3;
            break;
        case 29: // New Zone All Dimensions
            frm_lba->NewZone(data->x1, data->y1, data->z1, data->x2, data->y2, data->z2);
            frm_lba->pl_scene->ActivePageIndex = 3;
            break;
        case 30: // Set Actor
            if(data->Id > Scene.numActors-1) // invalid id
            {
               res = 1;
            }
            else
            {
                if(data->x1 < -256)
                    data->x1 = -256;
                if(data->y1 < 0)
                    data->y1 = 0;
                if(data->z1 < -256)
                    data->z1 = -256;

                if(data->Id==0) // Hero
                {
                    Scene.Hero.X = data->x1;
                    Scene.Hero.Y = data->y1;
                    Scene.Hero.Z = data->z1;
                }
                else // rest of Actors
                {
                    Scene.Actors[data->Id-1].X = data->x1;
                    Scene.Actors[data->Id-1].Y = data->y1;
                    Scene.Actors[data->Id-1].Z = data->z1;
                }
                // Update form values
                if(data->Id == frm_lba->edt_actors->Value)
                    frm_lba->edt_actorsChange(frm_lba);
                else
                    frm_lba->edt_actors->Value = data->Id;
                frm_lba->pl_scene->ActivePageIndex = 1;
            }

            break;
        case 31: // Select Actor
            if(data->Id > Scene.numActors-1) // invalid id
            {
               res = 1;
            }
            else
            {
                frm_lba->edt_actors->Value = data->Id;
                frm_lba->pl_scene->ActivePageIndex = 1;
            }

            break;
        case 32: // Delete Actor
            if(Scene.numActors > 1)
            {
                if(data->Id > Scene.numActors) // invalid id
                {
                    res = 1;
                }
                else
                {
                    frm_lba->edt_actors->Value = data->Id;
                    frm_lba->bt_removeClick(frm_lba);
                    frm_lba->pl_scene->ActivePageIndex = 1;
                }
            }
            else
            {
                res = 1;
            }
            break;
        case 33: // New Actor
            frm_lba->NewActor(data->x1, data->y1, data->z1);
            frm_lba->pl_scene->ActivePageIndex = 1;
            break;
        /*case 34: // New Sprite Actor
            frm_lba->NewSpriteActor(data->x1, data->y1, data->z1);
            frm_lba->pl_scene->ActivePageIndex = 1;
            break; */
        case 35: // Clone Actor
            if(data->Id > 0)
            {
                frm_lba->CloneActor(data->x1, data->y1, data->z1);
                frm_lba->pl_scene->ActivePageIndex = 1;
            }
            else
                res = 1;
            break;
        default:
            res = 10;
            break;
    }
    return res;
}

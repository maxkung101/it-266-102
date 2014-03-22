#include "g_local.h"
#include "m_player.h"

// *****************************
// * JMR: Playing Dead
// *****************************

void JMR_PlayDead (edict_t *ent)
{
       pmove_t      pm;
       int index;

       if (ent->client->playing_dead != 1)
       {
       // Check if ent has any powercells at all..
             index = ITEM_INDEX(FindItem("cells"));

             // If not enough cells then notify ent..
             if (ent->client->pers.inventory[index] < 25)
             {
                    gi.centerprintf(ent, "Playing Dead requires 25 PowerCells!\n");
                    return;
             }

// Try to deduct the cells!
             if (ent->client->pers.inventory[index] >= 25)
// Deduct 25 cells from inventory
                    ent->client->pers.inventory[index] -= 25;     

             // We make the weapon model disapear
             ent->s.modelindex2 = 0;

             // This is so that it knows what to do with the animation
             ent->client->anim_priority = ANIM_DEATH;

             // These tell us from what frame to start and end
             // note: They are all in the m_player.h file
             ent->s.frame = FRAME_death201;
             ent->client->anim_end = FRAME_death206;

             // Make the player look from a Deadmans point of view
             ent->client->ps.viewangles[ROLL] = 40;
             ent->client->ps.viewangles[PITCH] = -15;
             //ent->client->ps.viewangles[YAW] = 15;

             // Here I specify the type of movement I want
             // in this case, PM_FREEZE (Found in Q_share.h)
             ent->client->ps.pmove.pm_type = PM_FREEZE;
             pm.s = ent->client->ps.pmove;
             gi.Pmove (&pm);

             // We make a death sound so it apears that
             // eather someone killed us or we KILLed are selfs
             gi.sound (ent, CHAN_VOICE, gi.soundindex(va("*death%i.wav", (rand()%4)+1)), 1, ATTN_NORM, 0);

             // Set the playing_dead variable so the next call to this
             // function will make us stand up again
             ent->client->playing_dead = 1;

             // Make it all happen
             gi.linkentity (ent);

             // leave this function
             return;
       }
       else
       {
             // We walk again
             ent->client->ps.pmove.pm_type = PM_NORMAL;

             // We make the weapon model reapear.
             // Note: I know this is not the best way so if you know
             //       a better way, let me know
             // ent->s.modelindex2 = gi.modelindex ("players/male/weapon.md2");

             // This is so that it knows what to do with the animation
             ent->client->anim_priority = ANIM_BASIC;

             // So it knows what animation to play
             ent->s.frame = FRAME_stand01;
             ent->client->anim_end = FRAME_stand40;

             // Set the playing_dead variable so the next call to this
             // function will make us play dead
             ent->client->playing_dead = 0;

             // Make it Happen
             gi.linkentity (ent);

             // leave
             return;
       }
}

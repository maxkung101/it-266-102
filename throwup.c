// THROWUP.C by SumFuka

#include "g_local.h"
#include "throwup.h"

// this function makes you throw up
void ThrowUpNow(edict_t *self)
{
	// use some local vector variables to work with
	vec3_t   forward, right;
	vec3_t   mouth_pos, spew_vector;
	float rnum;
	int i;

	// set the spew vector, based on the client's view angle
	AngleVectors (self->client->v_angle, forward, right, NULL);

	// Make the spew originate from our mouth
	VectorScale (forward, 24, mouth_pos);
	VectorAdd (mouth_pos, self->s.origin, mouth_pos);
	mouth_pos[2] += self->viewheight;

	// Make the spew come forwards out of our mouth.
	VectorScale (forward, 24, spew_vector);

	// BLOOD ! (copied from SpawnDamage function)
	gi.WriteByte (svc_temp_entity);
	gi.WriteByte (TE_BLOOD);
	gi.WritePosition (mouth_pos);
	gi.WriteDir (spew_vector);
	gi.multicast (mouth_pos, MULTICAST_PVS);

	// say something cool
	rnum = random();
	if (rnum < 0.2)
		gi.bprintf (PRINT_MEDIUM, "Retch !\n");
	else if (rnum < 0.4)
		gi.bprintf (PRINT_MEDIUM, "...Vomit...\n");
	else if (rnum < 0.6)
		gi.bprintf (PRINT_MEDIUM, "Chunder.\n");
	else if (rnum < 0.8)
		gi.bprintf (PRINT_MEDIUM, "Chuck. chuck. chuck.\n");
	else 
		gi.bprintf (PRINT_MEDIUM, "Hmmmmff hmmmf hhhuuuuuuurrrrrllll.\n");

	// make a painful sound
	rnum = random();
	if (rnum < 0.125)
		gi.sound(self, CHAN_VOICE, gi.soundindex("*gurp1.wav"), 1, ATTN_NORM, 0);
	else if (rnum < 0.25)
		gi.sound(self, CHAN_VOICE, gi.soundindex("*gurp2.wav"), 1, ATTN_NORM, 0);
	else if (rnum < 0.375)
		gi.sound(self, CHAN_VOICE, gi.soundindex("*pain50_1.wav"), 1, ATTN_NORM, 0);
	else if (rnum < 0.5)
		gi.sound(self, CHAN_VOICE, gi.soundindex("*pain50_2.wav"), 1, ATTN_NORM, 0);
	else if (rnum < 0.625)
		gi.sound(self, CHAN_VOICE, gi.soundindex("*pain75_1.wav"), 1, ATTN_NORM, 0);
	else if (rnum < 0.75)
		gi.sound(self, CHAN_VOICE, gi.soundindex("*pain75_2.wav"), 1, ATTN_NORM, 0);
	else if (rnum < 0.875)
		gi.sound(self, CHAN_VOICE, gi.soundindex("*pain100_1.wav"), 1, ATTN_NORM, 0);
	else
		gi.sound(self, CHAN_VOICE, gi.soundindex("*pain100_2.wav"), 1, ATTN_NORM, 0);

	// also do a spewing sound
	gi.sound (self, CHAN_VOICE, gi.soundindex("misc/udeath.wav"), 1, ATTN_NORM, 0);
}

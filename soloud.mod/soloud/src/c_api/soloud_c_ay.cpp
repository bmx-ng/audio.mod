/* **************************************************
 *  WARNING: this is a generated file. Do not edit. *
 *  Any edits will be overwritten by the generator. *
 ************************************************** */

/*
SoLoud audio engine
Copyright (c) 2013-2020 Jari Komppa

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
   distribution.
*/

/* SoLoud C-Api Code Generator (c)2013-2020 Jari Komppa http://iki.fi/sol/ */

#include "../include/soloud.h"
#include "../include/soloud_ay.h"

using namespace SoLoud;

extern "C"
{

void Ay_destroy(void * aClassPtr)
{
  delete (Ay *)aClassPtr;
}

void * Ay_create()
{
  return (void *)new Ay;
}

int Ay_load(void * aClassPtr, const char * aFilename)
{
	Ay * cl = (Ay *)aClassPtr;
	return cl->load(aFilename);
}

int Ay_loadMem(void * aClassPtr, const unsigned char * aMem, unsigned int aLength)
{
	Ay * cl = (Ay *)aClassPtr;
	return cl->loadMem(aMem, aLength, false, true);
}

int Ay_loadMemEx(void * aClassPtr, const unsigned char * aMem, unsigned int aLength, int aCopy, int aTakeOwnership)
{
	Ay * cl = (Ay *)aClassPtr;
	return cl->loadMem(aMem, aLength, !!aCopy, !!aTakeOwnership);
}

int Ay_loadFile(void * aClassPtr, File * aFile)
{
	Ay * cl = (Ay *)aClassPtr;
	return cl->loadFile(aFile);
}

void Ay_setVolume(void * aClassPtr, float aVolume)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->setVolume(aVolume);
}

void Ay_setLooping(void * aClassPtr, int aLoop)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->setLooping(!!aLoop);
}

void Ay_setAutoStop(void * aClassPtr, int aAutoStop)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->setAutoStop(!!aAutoStop);
}

void Ay_set3dMinMaxDistance(void * aClassPtr, float aMinDistance, float aMaxDistance)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->set3dMinMaxDistance(aMinDistance, aMaxDistance);
}

void Ay_set3dAttenuation(void * aClassPtr, unsigned int aAttenuationModel, float aAttenuationRolloffFactor)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->set3dAttenuation(aAttenuationModel, aAttenuationRolloffFactor);
}

void Ay_set3dDopplerFactor(void * aClassPtr, float aDopplerFactor)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->set3dDopplerFactor(aDopplerFactor);
}

void Ay_set3dListenerRelative(void * aClassPtr, int aListenerRelative)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->set3dListenerRelative(!!aListenerRelative);
}

void Ay_set3dDistanceDelay(void * aClassPtr, int aDistanceDelay)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->set3dDistanceDelay(!!aDistanceDelay);
}

void Ay_set3dCollider(void * aClassPtr, AudioCollider * aCollider)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->set3dCollider(aCollider);
}

void Ay_set3dColliderEx(void * aClassPtr, AudioCollider * aCollider, int aUserData)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->set3dCollider(aCollider, aUserData);
}

void Ay_set3dAttenuator(void * aClassPtr, AudioAttenuator * aAttenuator)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->set3dAttenuator(aAttenuator);
}

void Ay_setInaudibleBehavior(void * aClassPtr, int aMustTick, int aKill)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->setInaudibleBehavior(!!aMustTick, !!aKill);
}

void Ay_setLoopPoint(void * aClassPtr, double aLoopPoint)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->setLoopPoint(aLoopPoint);
}

double Ay_getLoopPoint(void * aClassPtr)
{
	Ay * cl = (Ay *)aClassPtr;
	return cl->getLoopPoint();
}

void Ay_setFilter(void * aClassPtr, unsigned int aFilterId, Filter * aFilter)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->setFilter(aFilterId, aFilter);
}

void Ay_stop(void * aClassPtr)
{
	Ay * cl = (Ay *)aClassPtr;
	cl->stop();
}

} // extern "C"


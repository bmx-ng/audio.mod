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
#include "../include/soloud_openmpt.h"

using namespace SoLoud;

extern "C"
{

void Openmpt_destroy(void * aClassPtr)
{
  delete (Openmpt *)aClassPtr;
}

void * Openmpt_create()
{
  return (void *)new Openmpt;
}

int Openmpt_load(void * aClassPtr, const char * aFilename)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	return cl->load(aFilename);
}

int Openmpt_loadMem(void * aClassPtr, const unsigned char * aMem, unsigned int aLength)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	return cl->loadMem(aMem, aLength);
}

int Openmpt_loadMemEx(void * aClassPtr, const unsigned char * aMem, unsigned int aLength, int aCopy, int aTakeOwnership)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	return cl->loadMem(aMem, aLength, !!aCopy, !!aTakeOwnership);
}

int Openmpt_loadFile(void * aClassPtr, File * aFile)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	return cl->loadFile(aFile);
}

void Openmpt_setVolume(void * aClassPtr, float aVolume)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->setVolume(aVolume);
}

void Openmpt_setLooping(void * aClassPtr, int aLoop)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->setLooping(!!aLoop);
}

void Openmpt_setAutoStop(void * aClassPtr, int aAutoStop)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->setAutoStop(!!aAutoStop);
}

void Openmpt_set3dMinMaxDistance(void * aClassPtr, float aMinDistance, float aMaxDistance)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->set3dMinMaxDistance(aMinDistance, aMaxDistance);
}

void Openmpt_set3dAttenuation(void * aClassPtr, unsigned int aAttenuationModel, float aAttenuationRolloffFactor)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->set3dAttenuation(aAttenuationModel, aAttenuationRolloffFactor);
}

void Openmpt_set3dDopplerFactor(void * aClassPtr, float aDopplerFactor)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->set3dDopplerFactor(aDopplerFactor);
}

void Openmpt_set3dListenerRelative(void * aClassPtr, int aListenerRelative)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->set3dListenerRelative(!!aListenerRelative);
}

void Openmpt_set3dDistanceDelay(void * aClassPtr, int aDistanceDelay)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->set3dDistanceDelay(!!aDistanceDelay);
}

void Openmpt_set3dCollider(void * aClassPtr, AudioCollider * aCollider)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->set3dCollider(aCollider);
}

void Openmpt_set3dColliderEx(void * aClassPtr, AudioCollider * aCollider, int aUserData)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->set3dCollider(aCollider, aUserData);
}

void Openmpt_set3dAttenuator(void * aClassPtr, AudioAttenuator * aAttenuator)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->set3dAttenuator(aAttenuator);
}

void Openmpt_setInaudibleBehavior(void * aClassPtr, int aMustTick, int aKill)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->setInaudibleBehavior(!!aMustTick, !!aKill);
}

void Openmpt_setLoopPoint(void * aClassPtr, double aLoopPoint)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->setLoopPoint(aLoopPoint);
}

double Openmpt_getLoopPoint(void * aClassPtr)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	return cl->getLoopPoint();
}

void Openmpt_setFilter(void * aClassPtr, unsigned int aFilterId, Filter * aFilter)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->setFilter(aFilterId, aFilter);
}

void Openmpt_stop(void * aClassPtr)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	cl->stop();
}

double Openmpt_getLength(void * aClassPtr)
{
	Openmpt * cl = (Openmpt *)aClassPtr;
	return cl->getLength();
}

} // extern "C"


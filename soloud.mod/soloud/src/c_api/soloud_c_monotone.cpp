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
#include "../include/soloud_monotone.h"

using namespace SoLoud;

extern "C"
{

void Monotone_destroy(void * aClassPtr)
{
  delete (Monotone *)aClassPtr;
}

void * Monotone_create()
{
  return (void *)new Monotone;
}

int Monotone_setParams(void * aClassPtr, int aHardwareChannels)
{
	Monotone * cl = (Monotone *)aClassPtr;
	return cl->setParams(aHardwareChannels);
}

int Monotone_setParamsEx(void * aClassPtr, int aHardwareChannels, int aWaveform)
{
	Monotone * cl = (Monotone *)aClassPtr;
	return cl->setParams(aHardwareChannels, aWaveform);
}

int Monotone_load(void * aClassPtr, const char * aFilename)
{
	Monotone * cl = (Monotone *)aClassPtr;
	return cl->load(aFilename);
}

int Monotone_loadMem(void * aClassPtr, const unsigned char * aMem, unsigned int aLength)
{
	Monotone * cl = (Monotone *)aClassPtr;
	return cl->loadMem(aMem, aLength);
}

int Monotone_loadMemEx(void * aClassPtr, const unsigned char * aMem, unsigned int aLength, int aCopy, int aTakeOwnership)
{
	Monotone * cl = (Monotone *)aClassPtr;
	return cl->loadMem(aMem, aLength, !!aCopy, !!aTakeOwnership);
}

int Monotone_loadFile(void * aClassPtr, File * aFile)
{
	Monotone * cl = (Monotone *)aClassPtr;
	return cl->loadFile(aFile);
}

void Monotone_setVolume(void * aClassPtr, float aVolume)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->setVolume(aVolume);
}

void Monotone_setLooping(void * aClassPtr, int aLoop)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->setLooping(!!aLoop);
}

void Monotone_setAutoStop(void * aClassPtr, int aAutoStop)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->setAutoStop(!!aAutoStop);
}

void Monotone_set3dMinMaxDistance(void * aClassPtr, float aMinDistance, float aMaxDistance)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->set3dMinMaxDistance(aMinDistance, aMaxDistance);
}

void Monotone_set3dAttenuation(void * aClassPtr, unsigned int aAttenuationModel, float aAttenuationRolloffFactor)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->set3dAttenuation(aAttenuationModel, aAttenuationRolloffFactor);
}

void Monotone_set3dDopplerFactor(void * aClassPtr, float aDopplerFactor)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->set3dDopplerFactor(aDopplerFactor);
}

void Monotone_set3dListenerRelative(void * aClassPtr, int aListenerRelative)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->set3dListenerRelative(!!aListenerRelative);
}

void Monotone_set3dDistanceDelay(void * aClassPtr, int aDistanceDelay)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->set3dDistanceDelay(!!aDistanceDelay);
}

void Monotone_set3dCollider(void * aClassPtr, AudioCollider * aCollider)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->set3dCollider(aCollider);
}

void Monotone_set3dColliderEx(void * aClassPtr, AudioCollider * aCollider, int aUserData)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->set3dCollider(aCollider, aUserData);
}

void Monotone_set3dAttenuator(void * aClassPtr, AudioAttenuator * aAttenuator)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->set3dAttenuator(aAttenuator);
}

void Monotone_setInaudibleBehavior(void * aClassPtr, int aMustTick, int aKill)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->setInaudibleBehavior(!!aMustTick, !!aKill);
}

void Monotone_setLoopPoint(void * aClassPtr, double aLoopPoint)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->setLoopPoint(aLoopPoint);
}

double Monotone_getLoopPoint(void * aClassPtr)
{
	Monotone * cl = (Monotone *)aClassPtr;
	return cl->getLoopPoint();
}

void Monotone_setFilter(void * aClassPtr, unsigned int aFilterId, Filter * aFilter)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->setFilter(aFilterId, aFilter);
}

void Monotone_stop(void * aClassPtr)
{
	Monotone * cl = (Monotone *)aClassPtr;
	cl->stop();
}

} // extern "C"


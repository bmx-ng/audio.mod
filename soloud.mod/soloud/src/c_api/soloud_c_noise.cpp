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
#include "../include/soloud_noise.h"

using namespace SoLoud;

extern "C"
{

void Noise_destroy(void * aClassPtr)
{
  delete (Noise *)aClassPtr;
}

void * Noise_create()
{
  return (void *)new Noise;
}

void Noise_setOctaveScale(void * aClassPtr, float aOct0, float aOct1, float aOct2, float aOct3, float aOct4, float aOct5, float aOct6, float aOct7, float aOct8, float aOct9)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->setOctaveScale(aOct0, aOct1, aOct2, aOct3, aOct4, aOct5, aOct6, aOct7, aOct8, aOct9);
}

void Noise_setType(void * aClassPtr, int aType)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->setType(aType);
}

void Noise_setVolume(void * aClassPtr, float aVolume)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->setVolume(aVolume);
}

void Noise_setLooping(void * aClassPtr, int aLoop)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->setLooping(!!aLoop);
}

void Noise_setAutoStop(void * aClassPtr, int aAutoStop)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->setAutoStop(!!aAutoStop);
}

void Noise_set3dMinMaxDistance(void * aClassPtr, float aMinDistance, float aMaxDistance)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->set3dMinMaxDistance(aMinDistance, aMaxDistance);
}

void Noise_set3dAttenuation(void * aClassPtr, unsigned int aAttenuationModel, float aAttenuationRolloffFactor)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->set3dAttenuation(aAttenuationModel, aAttenuationRolloffFactor);
}

void Noise_set3dDopplerFactor(void * aClassPtr, float aDopplerFactor)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->set3dDopplerFactor(aDopplerFactor);
}

void Noise_set3dListenerRelative(void * aClassPtr, int aListenerRelative)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->set3dListenerRelative(!!aListenerRelative);
}

void Noise_set3dDistanceDelay(void * aClassPtr, int aDistanceDelay)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->set3dDistanceDelay(!!aDistanceDelay);
}

void Noise_set3dCollider(void * aClassPtr, AudioCollider * aCollider)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->set3dCollider(aCollider);
}

void Noise_set3dColliderEx(void * aClassPtr, AudioCollider * aCollider, int aUserData)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->set3dCollider(aCollider, aUserData);
}

void Noise_set3dAttenuator(void * aClassPtr, AudioAttenuator * aAttenuator)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->set3dAttenuator(aAttenuator);
}

void Noise_setInaudibleBehavior(void * aClassPtr, int aMustTick, int aKill)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->setInaudibleBehavior(!!aMustTick, !!aKill);
}

void Noise_setLoopPoint(void * aClassPtr, double aLoopPoint)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->setLoopPoint(aLoopPoint);
}

double Noise_getLoopPoint(void * aClassPtr)
{
	Noise * cl = (Noise *)aClassPtr;
	return cl->getLoopPoint();
}

void Noise_setFilter(void * aClassPtr, unsigned int aFilterId, Filter * aFilter)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->setFilter(aFilterId, aFilter);
}

void Noise_stop(void * aClassPtr)
{
	Noise * cl = (Noise *)aClassPtr;
	cl->stop();
}

} // extern "C"


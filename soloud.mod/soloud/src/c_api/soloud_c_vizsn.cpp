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
#include "../include/soloud_vizsn.h"

using namespace SoLoud;

extern "C"
{

void Vizsn_destroy(void * aClassPtr)
{
  delete (Vizsn *)aClassPtr;
}

void * Vizsn_create()
{
  return (void *)new Vizsn;
}

void Vizsn_setText(void * aClassPtr, char * aText)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->setText(aText);
}

void Vizsn_setVolume(void * aClassPtr, float aVolume)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->setVolume(aVolume);
}

void Vizsn_setLooping(void * aClassPtr, int aLoop)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->setLooping(!!aLoop);
}

void Vizsn_setAutoStop(void * aClassPtr, int aAutoStop)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->setAutoStop(!!aAutoStop);
}

void Vizsn_set3dMinMaxDistance(void * aClassPtr, float aMinDistance, float aMaxDistance)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->set3dMinMaxDistance(aMinDistance, aMaxDistance);
}

void Vizsn_set3dAttenuation(void * aClassPtr, unsigned int aAttenuationModel, float aAttenuationRolloffFactor)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->set3dAttenuation(aAttenuationModel, aAttenuationRolloffFactor);
}

void Vizsn_set3dDopplerFactor(void * aClassPtr, float aDopplerFactor)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->set3dDopplerFactor(aDopplerFactor);
}

void Vizsn_set3dListenerRelative(void * aClassPtr, int aListenerRelative)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->set3dListenerRelative(!!aListenerRelative);
}

void Vizsn_set3dDistanceDelay(void * aClassPtr, int aDistanceDelay)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->set3dDistanceDelay(!!aDistanceDelay);
}

void Vizsn_set3dCollider(void * aClassPtr, AudioCollider * aCollider)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->set3dCollider(aCollider);
}

void Vizsn_set3dColliderEx(void * aClassPtr, AudioCollider * aCollider, int aUserData)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->set3dCollider(aCollider, aUserData);
}

void Vizsn_set3dAttenuator(void * aClassPtr, AudioAttenuator * aAttenuator)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->set3dAttenuator(aAttenuator);
}

void Vizsn_setInaudibleBehavior(void * aClassPtr, int aMustTick, int aKill)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->setInaudibleBehavior(!!aMustTick, !!aKill);
}

void Vizsn_setLoopPoint(void * aClassPtr, double aLoopPoint)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->setLoopPoint(aLoopPoint);
}

double Vizsn_getLoopPoint(void * aClassPtr)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	return cl->getLoopPoint();
}

void Vizsn_setFilter(void * aClassPtr, unsigned int aFilterId, Filter * aFilter)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->setFilter(aFilterId, aFilter);
}

void Vizsn_stop(void * aClassPtr)
{
	Vizsn * cl = (Vizsn *)aClassPtr;
	cl->stop();
}

} // extern "C"


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
#include "../include/soloud_queue.h"

using namespace SoLoud;

extern "C"
{

void Queue_destroy(void * aClassPtr)
{
  delete (Queue *)aClassPtr;
}

void * Queue_create()
{
  return (void *)new Queue;
}

int Queue_play(void * aClassPtr, AudioSource * aSound)
{
	Queue * cl = (Queue *)aClassPtr;
	return cl->play(*aSound);
}

unsigned int Queue_getQueueCount(void * aClassPtr)
{
	Queue * cl = (Queue *)aClassPtr;
	return cl->getQueueCount();
}

int Queue_isCurrentlyPlaying(void * aClassPtr, AudioSource * aSound)
{
	Queue * cl = (Queue *)aClassPtr;
	return cl->isCurrentlyPlaying(*aSound);
}

int Queue_setParamsFromAudioSource(void * aClassPtr, AudioSource * aSound)
{
	Queue * cl = (Queue *)aClassPtr;
	return cl->setParamsFromAudioSource(*aSound);
}

int Queue_setParams(void * aClassPtr, float aSamplerate)
{
	Queue * cl = (Queue *)aClassPtr;
	return cl->setParams(aSamplerate);
}

int Queue_setParamsEx(void * aClassPtr, float aSamplerate, unsigned int aChannels)
{
	Queue * cl = (Queue *)aClassPtr;
	return cl->setParams(aSamplerate, aChannels);
}

void Queue_setVolume(void * aClassPtr, float aVolume)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->setVolume(aVolume);
}

void Queue_setLooping(void * aClassPtr, int aLoop)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->setLooping(!!aLoop);
}

void Queue_setAutoStop(void * aClassPtr, int aAutoStop)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->setAutoStop(!!aAutoStop);
}

void Queue_set3dMinMaxDistance(void * aClassPtr, float aMinDistance, float aMaxDistance)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->set3dMinMaxDistance(aMinDistance, aMaxDistance);
}

void Queue_set3dAttenuation(void * aClassPtr, unsigned int aAttenuationModel, float aAttenuationRolloffFactor)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->set3dAttenuation(aAttenuationModel, aAttenuationRolloffFactor);
}

void Queue_set3dDopplerFactor(void * aClassPtr, float aDopplerFactor)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->set3dDopplerFactor(aDopplerFactor);
}

void Queue_set3dListenerRelative(void * aClassPtr, int aListenerRelative)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->set3dListenerRelative(!!aListenerRelative);
}

void Queue_set3dDistanceDelay(void * aClassPtr, int aDistanceDelay)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->set3dDistanceDelay(!!aDistanceDelay);
}

void Queue_set3dCollider(void * aClassPtr, AudioCollider * aCollider)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->set3dCollider(aCollider);
}

void Queue_set3dColliderEx(void * aClassPtr, AudioCollider * aCollider, int aUserData)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->set3dCollider(aCollider, aUserData);
}

void Queue_set3dAttenuator(void * aClassPtr, AudioAttenuator * aAttenuator)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->set3dAttenuator(aAttenuator);
}

void Queue_setInaudibleBehavior(void * aClassPtr, int aMustTick, int aKill)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->setInaudibleBehavior(!!aMustTick, !!aKill);
}

void Queue_setLoopPoint(void * aClassPtr, double aLoopPoint)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->setLoopPoint(aLoopPoint);
}

double Queue_getLoopPoint(void * aClassPtr)
{
	Queue * cl = (Queue *)aClassPtr;
	return cl->getLoopPoint();
}

void Queue_setFilter(void * aClassPtr, unsigned int aFilterId, Filter * aFilter)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->setFilter(aFilterId, aFilter);
}

void Queue_stop(void * aClassPtr)
{
	Queue * cl = (Queue *)aClassPtr;
	cl->stop();
}

} // extern "C"


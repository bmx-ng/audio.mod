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
#include "../include/soloud_bus.h"

using namespace SoLoud;

extern "C"
{

void Bus_destroy(void * aClassPtr)
{
  delete (Bus *)aClassPtr;
}

void * Bus_create()
{
  return (void *)new Bus;
}

void Bus_setFilter(void * aClassPtr, unsigned int aFilterId, Filter * aFilter)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->setFilter(aFilterId, aFilter);
}

unsigned int Bus_play(void * aClassPtr, AudioSource * aSound)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->play(*aSound);
}

unsigned int Bus_playEx(void * aClassPtr, AudioSource * aSound, float aVolume, float aPan, int aPaused)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->play(*aSound, aVolume, aPan, !!aPaused);
}

unsigned int Bus_playClocked(void * aClassPtr, double aSoundTime, AudioSource * aSound)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->playClocked(aSoundTime, *aSound);
}

unsigned int Bus_playClockedEx(void * aClassPtr, double aSoundTime, AudioSource * aSound, float aVolume, float aPan)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->playClocked(aSoundTime, *aSound, aVolume, aPan);
}

unsigned int Bus_play3d(void * aClassPtr, AudioSource * aSound, float aPosX, float aPosY, float aPosZ)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->play3d(*aSound, aPosX, aPosY, aPosZ);
}

unsigned int Bus_play3dEx(void * aClassPtr, AudioSource * aSound, float aPosX, float aPosY, float aPosZ, float aVelX, float aVelY, float aVelZ, float aVolume, int aPaused)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->play3d(*aSound, aPosX, aPosY, aPosZ, aVelX, aVelY, aVelZ, aVolume, !!aPaused);
}

unsigned int Bus_play3dClocked(void * aClassPtr, double aSoundTime, AudioSource * aSound, float aPosX, float aPosY, float aPosZ)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->play3dClocked(aSoundTime, *aSound, aPosX, aPosY, aPosZ);
}

unsigned int Bus_play3dClockedEx(void * aClassPtr, double aSoundTime, AudioSource * aSound, float aPosX, float aPosY, float aPosZ, float aVelX, float aVelY, float aVelZ, float aVolume)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->play3dClocked(aSoundTime, *aSound, aPosX, aPosY, aPosZ, aVelX, aVelY, aVelZ, aVolume);
}

int Bus_setChannels(void * aClassPtr, unsigned int aChannels)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->setChannels(aChannels);
}

void Bus_setVisualizationEnable(void * aClassPtr, int aEnable)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->setVisualizationEnable(!!aEnable);
}

void Bus_annexSound(void * aClassPtr, unsigned int aVoiceHandle)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->annexSound(aVoiceHandle);
}

float * Bus_calcFFT(void * aClassPtr)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->calcFFT();
}

float * Bus_getWave(void * aClassPtr)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->getWave();
}

float Bus_getApproximateVolume(void * aClassPtr, unsigned int aChannel)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->getApproximateVolume(aChannel);
}

unsigned int Bus_getActiveVoiceCount(void * aClassPtr)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->getActiveVoiceCount();
}

unsigned int Bus_getResampler(void * aClassPtr)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->getResampler();
}

void Bus_setResampler(void * aClassPtr, unsigned int aResampler)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->setResampler(aResampler);
}

void Bus_setVolume(void * aClassPtr, float aVolume)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->setVolume(aVolume);
}

void Bus_setLooping(void * aClassPtr, int aLoop)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->setLooping(!!aLoop);
}

void Bus_setAutoStop(void * aClassPtr, int aAutoStop)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->setAutoStop(!!aAutoStop);
}

void Bus_set3dMinMaxDistance(void * aClassPtr, float aMinDistance, float aMaxDistance)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->set3dMinMaxDistance(aMinDistance, aMaxDistance);
}

void Bus_set3dAttenuation(void * aClassPtr, unsigned int aAttenuationModel, float aAttenuationRolloffFactor)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->set3dAttenuation(aAttenuationModel, aAttenuationRolloffFactor);
}

void Bus_set3dDopplerFactor(void * aClassPtr, float aDopplerFactor)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->set3dDopplerFactor(aDopplerFactor);
}

void Bus_set3dListenerRelative(void * aClassPtr, int aListenerRelative)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->set3dListenerRelative(!!aListenerRelative);
}

void Bus_set3dDistanceDelay(void * aClassPtr, int aDistanceDelay)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->set3dDistanceDelay(!!aDistanceDelay);
}

void Bus_set3dCollider(void * aClassPtr, AudioCollider * aCollider)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->set3dCollider(aCollider);
}

void Bus_set3dColliderEx(void * aClassPtr, AudioCollider * aCollider, int aUserData)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->set3dCollider(aCollider, aUserData);
}

void Bus_set3dAttenuator(void * aClassPtr, AudioAttenuator * aAttenuator)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->set3dAttenuator(aAttenuator);
}

void Bus_setInaudibleBehavior(void * aClassPtr, int aMustTick, int aKill)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->setInaudibleBehavior(!!aMustTick, !!aKill);
}

void Bus_setLoopPoint(void * aClassPtr, double aLoopPoint)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->setLoopPoint(aLoopPoint);
}

double Bus_getLoopPoint(void * aClassPtr)
{
	Bus * cl = (Bus *)aClassPtr;
	return cl->getLoopPoint();
}

void Bus_stop(void * aClassPtr)
{
	Bus * cl = (Bus *)aClassPtr;
	cl->stop();
}

} // extern "C"


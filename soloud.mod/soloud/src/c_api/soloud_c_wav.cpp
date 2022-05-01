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
#include "../include/soloud_wav.h"
#include "../include/soloud_waveshaperfilter.h"
#include "../include/soloud_wavstream.h"

using namespace SoLoud;

extern "C"
{

void Wav_destroy(void * aClassPtr)
{
  delete (Wav *)aClassPtr;
}

void * Wav_create()
{
  return (void *)new Wav;
}

int Wav_load(void * aClassPtr, const char * aFilename)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->load(aFilename);
}

int Wav_loadMem(void * aClassPtr, const unsigned char * aMem, unsigned int aLength)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->loadMem(aMem, aLength);
}

int Wav_loadMemEx(void * aClassPtr, const unsigned char * aMem, unsigned int aLength, int aCopy, int aTakeOwnership)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->loadMem(aMem, aLength, !!aCopy, !!aTakeOwnership);
}

int Wav_loadFile(void * aClassPtr, File * aFile)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->loadFile(aFile);
}

int Wav_loadRawWave8(void * aClassPtr, unsigned char * aMem, unsigned int aLength)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->loadRawWave8(aMem, aLength);
}

int Wav_loadRawWave8Ex(void * aClassPtr, unsigned char * aMem, unsigned int aLength, float aSamplerate, unsigned int aChannels)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->loadRawWave8(aMem, aLength, aSamplerate, aChannels);
}

int Wav_loadRawWave16(void * aClassPtr, short * aMem, unsigned int aLength)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->loadRawWave16(aMem, aLength);
}

int Wav_loadRawWave16Ex(void * aClassPtr, short * aMem, unsigned int aLength, float aSamplerate, unsigned int aChannels)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->loadRawWave16(aMem, aLength, aSamplerate, aChannels);
}

int Wav_loadRawWave(void * aClassPtr, float * aMem, unsigned int aLength)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->loadRawWave(aMem, aLength);
}

int Wav_loadRawWaveEx(void * aClassPtr, float * aMem, unsigned int aLength, float aSamplerate, unsigned int aChannels, int aCopy, int aTakeOwnership)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->loadRawWave(aMem, aLength, aSamplerate, aChannels, !!aCopy, !!aTakeOwnership);
}

double Wav_getLength(void * aClassPtr)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->getLength();
}

void Wav_setVolume(void * aClassPtr, float aVolume)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->setVolume(aVolume);
}

void Wav_setLooping(void * aClassPtr, int aLoop)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->setLooping(!!aLoop);
}

void Wav_setAutoStop(void * aClassPtr, int aAutoStop)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->setAutoStop(!!aAutoStop);
}

void Wav_set3dMinMaxDistance(void * aClassPtr, float aMinDistance, float aMaxDistance)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->set3dMinMaxDistance(aMinDistance, aMaxDistance);
}

void Wav_set3dAttenuation(void * aClassPtr, unsigned int aAttenuationModel, float aAttenuationRolloffFactor)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->set3dAttenuation(aAttenuationModel, aAttenuationRolloffFactor);
}

void Wav_set3dDopplerFactor(void * aClassPtr, float aDopplerFactor)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->set3dDopplerFactor(aDopplerFactor);
}

void Wav_set3dListenerRelative(void * aClassPtr, int aListenerRelative)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->set3dListenerRelative(!!aListenerRelative);
}

void Wav_set3dDistanceDelay(void * aClassPtr, int aDistanceDelay)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->set3dDistanceDelay(!!aDistanceDelay);
}

void Wav_set3dCollider(void * aClassPtr, AudioCollider * aCollider)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->set3dCollider(aCollider);
}

void Wav_set3dColliderEx(void * aClassPtr, AudioCollider * aCollider, int aUserData)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->set3dCollider(aCollider, aUserData);
}

void Wav_set3dAttenuator(void * aClassPtr, AudioAttenuator * aAttenuator)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->set3dAttenuator(aAttenuator);
}

void Wav_setInaudibleBehavior(void * aClassPtr, int aMustTick, int aKill)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->setInaudibleBehavior(!!aMustTick, !!aKill);
}

void Wav_setLoopPoint(void * aClassPtr, double aLoopPoint)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->setLoopPoint(aLoopPoint);
}

double Wav_getLoopPoint(void * aClassPtr)
{
	Wav * cl = (Wav *)aClassPtr;
	return cl->getLoopPoint();
}

void Wav_setFilter(void * aClassPtr, unsigned int aFilterId, Filter * aFilter)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->setFilter(aFilterId, aFilter);
}

void Wav_stop(void * aClassPtr)
{
	Wav * cl = (Wav *)aClassPtr;
	cl->stop();
}

void WaveShaperFilter_destroy(void * aClassPtr)
{
  delete (WaveShaperFilter *)aClassPtr;
}

int WaveShaperFilter_setParams(void * aClassPtr, float aAmount)
{
	WaveShaperFilter * cl = (WaveShaperFilter *)aClassPtr;
	return cl->setParams(aAmount);
}

void * WaveShaperFilter_create()
{
  return (void *)new WaveShaperFilter;
}

int WaveShaperFilter_getParamCount(void * aClassPtr)
{
	WaveShaperFilter * cl = (WaveShaperFilter *)aClassPtr;
	return cl->getParamCount();
}

const char * WaveShaperFilter_getParamName(void * aClassPtr, unsigned int aParamIndex)
{
	WaveShaperFilter * cl = (WaveShaperFilter *)aClassPtr;
	return cl->getParamName(aParamIndex);
}

unsigned int WaveShaperFilter_getParamType(void * aClassPtr, unsigned int aParamIndex)
{
	WaveShaperFilter * cl = (WaveShaperFilter *)aClassPtr;
	return cl->getParamType(aParamIndex);
}

float WaveShaperFilter_getParamMax(void * aClassPtr, unsigned int aParamIndex)
{
	WaveShaperFilter * cl = (WaveShaperFilter *)aClassPtr;
	return cl->getParamMax(aParamIndex);
}

float WaveShaperFilter_getParamMin(void * aClassPtr, unsigned int aParamIndex)
{
	WaveShaperFilter * cl = (WaveShaperFilter *)aClassPtr;
	return cl->getParamMin(aParamIndex);
}

void WavStream_destroy(void * aClassPtr)
{
  delete (WavStream *)aClassPtr;
}

void * WavStream_create()
{
  return (void *)new WavStream;
}

int WavStream_load(void * aClassPtr, const char * aFilename)
{
	WavStream * cl = (WavStream *)aClassPtr;
	return cl->load(aFilename);
}

int WavStream_loadMem(void * aClassPtr, const unsigned char * aData, unsigned int aDataLen)
{
	WavStream * cl = (WavStream *)aClassPtr;
	return cl->loadMem(aData, aDataLen);
}

int WavStream_loadMemEx(void * aClassPtr, const unsigned char * aData, unsigned int aDataLen, int aCopy, int aTakeOwnership)
{
	WavStream * cl = (WavStream *)aClassPtr;
	return cl->loadMem(aData, aDataLen, !!aCopy, !!aTakeOwnership);
}

int WavStream_loadToMem(void * aClassPtr, const char * aFilename)
{
	WavStream * cl = (WavStream *)aClassPtr;
	return cl->loadToMem(aFilename);
}

int WavStream_loadFile(void * aClassPtr, File * aFile)
{
	WavStream * cl = (WavStream *)aClassPtr;
	return cl->loadFile(aFile);
}

int WavStream_loadFileToMem(void * aClassPtr, File * aFile)
{
	WavStream * cl = (WavStream *)aClassPtr;
	return cl->loadFileToMem(aFile);
}

double WavStream_getLength(void * aClassPtr)
{
	WavStream * cl = (WavStream *)aClassPtr;
	return cl->getLength();
}

void WavStream_setVolume(void * aClassPtr, float aVolume)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->setVolume(aVolume);
}

void WavStream_setLooping(void * aClassPtr, int aLoop)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->setLooping(!!aLoop);
}

void WavStream_setAutoStop(void * aClassPtr, int aAutoStop)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->setAutoStop(!!aAutoStop);
}

void WavStream_set3dMinMaxDistance(void * aClassPtr, float aMinDistance, float aMaxDistance)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->set3dMinMaxDistance(aMinDistance, aMaxDistance);
}

void WavStream_set3dAttenuation(void * aClassPtr, unsigned int aAttenuationModel, float aAttenuationRolloffFactor)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->set3dAttenuation(aAttenuationModel, aAttenuationRolloffFactor);
}

void WavStream_set3dDopplerFactor(void * aClassPtr, float aDopplerFactor)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->set3dDopplerFactor(aDopplerFactor);
}

void WavStream_set3dListenerRelative(void * aClassPtr, int aListenerRelative)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->set3dListenerRelative(!!aListenerRelative);
}

void WavStream_set3dDistanceDelay(void * aClassPtr, int aDistanceDelay)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->set3dDistanceDelay(!!aDistanceDelay);
}

void WavStream_set3dCollider(void * aClassPtr, AudioCollider * aCollider)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->set3dCollider(aCollider);
}

void WavStream_set3dColliderEx(void * aClassPtr, AudioCollider * aCollider, int aUserData)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->set3dCollider(aCollider, aUserData);
}

void WavStream_set3dAttenuator(void * aClassPtr, AudioAttenuator * aAttenuator)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->set3dAttenuator(aAttenuator);
}

void WavStream_setInaudibleBehavior(void * aClassPtr, int aMustTick, int aKill)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->setInaudibleBehavior(!!aMustTick, !!aKill);
}

void WavStream_setLoopPoint(void * aClassPtr, double aLoopPoint)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->setLoopPoint(aLoopPoint);
}

double WavStream_getLoopPoint(void * aClassPtr)
{
	WavStream * cl = (WavStream *)aClassPtr;
	return cl->getLoopPoint();
}

void WavStream_setFilter(void * aClassPtr, unsigned int aFilterId, Filter * aFilter)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->setFilter(aFilterId, aFilter);
}

void WavStream_stop(void * aClassPtr)
{
	WavStream * cl = (WavStream *)aClassPtr;
	cl->stop();
}

} // extern "C"


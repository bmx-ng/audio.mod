#include "soloud_file.h"
#include "dataqueue.h"

extern "C" {

	#include "brl.mod/blitz.mod/blitz.h"

	int audio_soloud_file_TStreamFile__eof(BBObject * handle);
	void audio_soloud_file_TStreamFile__seek(BBObject * handle, int offset);
	int audio_soloud_file_TStreamFile__length(BBObject * handle);
	int audio_soloud_file_TStreamFile__pos(BBObject * handle);
	int audio_soloud_file_TStreamFile__read(BBObject * handle, unsigned char * dst, int size);
	int audio_soloud_file_TStreamFile__destroy(BBObject * handle);

	SoLoud::File * bmx_soloud_streamfile_new(BBObject * handle);
	void bmx_soloud_streamfile_free(SoLoud::File * file);


}



class TStreamFile : public SoLoud::File {
public:

	TStreamFile(BBObject * handle) : maxHandle(handle) {
		BBRETAIN(maxHandle);
	 }
	
	virtual ~TStreamFile() {
		audio_soloud_file_TStreamFile__destroy(maxHandle);
		BBRELEASE(maxHandle);
	}
	
	virtual int eof() {
		return audio_soloud_file_TStreamFile__eof(maxHandle);
	}
	
	virtual unsigned int read(unsigned char *aDst, unsigned int aBytes) {
		return audio_soloud_file_TStreamFile__read(maxHandle, aDst, aBytes);
	}
	
	virtual unsigned int length() {
		return audio_soloud_file_TStreamFile__length(maxHandle);
	}
	
	virtual void seek(int aOffset) {
		audio_soloud_file_TStreamFile__seek(maxHandle, aOffset);
	}
	
	virtual unsigned int pos() {
		return audio_soloud_file_TStreamFile__pos(maxHandle);
	}
	
private:
	BBObject * maxHandle;
};



SoLoud::File * bmx_soloud_streamfile_new(BBObject * handle) {
	return new TStreamFile(handle);
}

void bmx_soloud_streamfile_free(SoLoud::File * file) {
	delete file;
}


namespace SoLoud
{
	class QueuedSource;

	class QueuedSourceInstance : public AudioSourceInstance
	{
		QueuedSource *mParent;
	public:
		QueuedSourceInstance(QueuedSource *aParent);
		virtual unsigned int getAudio(float *aBuffer, unsigned int aSamplesToRead, unsigned int aBufferSize);
		virtual bool hasEnded();
	};

	class QueuedSource : public AudioSource
	{
	public:
		data_queue * queue;

		QueuedSource();
		virtual ~QueuedSource();
		virtual AudioSourceInstance *createInstance();
		virtual void queueAudio(void * buffer, size_t size);
	};
};



namespace SoLoud
{

	QueuedSourceInstance::QueuedSourceInstance(QueuedSource *aParent)
	{
		mParent = aParent;
	}

	unsigned int QueuedSourceInstance::getAudio(float *aBuffer, unsigned int aSamplesToRead, unsigned int aBufferSize)
	{
		unsigned int offset = 0;
		float tmp[512 * MAX_CHANNELS];
		unsigned int i, j, k;
		unsigned int samples = aSamplesToRead;

		for (i = 0; i < aSamplesToRead; i += 512)
		{
			unsigned int blockSize = (aSamplesToRead - i) > 512 ? 512 : aSamplesToRead - i;

			memset(tmp, 0, 512 * MAX_CHANNELS * sizeof(float) );
			size_t read = bmx_queue_read(mParent->queue, tmp, blockSize * 4 * 2);
			read = read / 8;
			offset += read;

			for (j = 0; j < blockSize; j++)
			{
				for (k = 0; k < mChannels; k++)
				{
					aBuffer[k * aSamplesToRead + i + j] = tmp[j * mChannels + k];
				}
			}
		}

		return samples;

	}

	bool QueuedSourceInstance::hasEnded()
	{
		return 0;
		// This audio source never ends.
		//return bmx_queue_count(mParent->queue) == 0;
	}

	QueuedSource::QueuedSource()
	{
		mBaseSamplerate = 44100.0;
		mChannels = 2;
		queue = bmx_queue_new(9216, 9216);
	}

	QueuedSource::~QueuedSource()
	{
		stop();
	}

	void QueuedSource::queueAudio(void * buffer, size_t size)
	{
		bmx_queue_write(queue, buffer, size);
	}

	AudioSourceInstance * QueuedSource::createInstance() 
	{
		return new QueuedSourceInstance(this);
	}

};

extern "C" {


void bmx_soloud_queued_write(SoLoud::AudioSource * src, void * buffer, size_t size) {
	SoLoud::QueuedSource* source = static_cast<SoLoud::QueuedSource*>(src);
	source->queueAudio(buffer, size);
}

void bmx_soloud_queued_destroy(void * aClassPtr)
{
  delete (SoLoud::QueuedSource *)aClassPtr;
}

void * bmx_soloud_queued_create()
{
  return (void *)new SoLoud::QueuedSource();
}

void bmx_soloud_queued_stop(void * aClassPtr) {
	SoLoud::QueuedSource * cl = (SoLoud::QueuedSource *)aClassPtr;
	cl->stop();
}

void bmx_soloud_queued_setVolume(void * aClassPtr, float aVolume) {
	SoLoud::QueuedSource * cl = (SoLoud::QueuedSource *)aClassPtr;
	cl->setVolume(aVolume);
}

void bmx_soloud_queued_setLooping(void * aClassPtr, int aLoop) {
	SoLoud::QueuedSource * cl = (SoLoud::QueuedSource *)aClassPtr;
	cl->setLooping(!!aLoop);
}

void bmx_soloud_queued_setAutoStop(void * aClassPtr, int aAutoStop) {
	SoLoud::QueuedSource * cl = (SoLoud::QueuedSource *)aClassPtr;
	cl->setAutoStop(!!aAutoStop);
}

size_t bmx_soloud_queued_count(void * aClassPtr) {
	SoLoud::QueuedSource * cl = (SoLoud::QueuedSource *)aClassPtr;
	return bmx_queue_count(cl->queue);
}

}

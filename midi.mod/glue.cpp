/*
 Copyright (c) 2010-2022 Bruce A Henderson
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
*/

#include "RtMidi.h"

extern "C" {
#include "brl.mod/blitz.mod/blitz.h"

	BBObject * audio_midi_TMidiError__create(BBString * message, int type);

	RtMidiIn * bmx_midi_in_create(BBString * clientName, int queueSizeLimit);
	void bmx_midi_in_openPort(RtMidiIn * m, int portNumber, BBString * portName);
	void bmx_midi_in_closePort(RtMidiIn * m);
	void bmx_midi_in_openVirtualPort(RtMidiIn * m, BBString * portName);
	int bmx_midi_in_getPortCount(RtMidiIn * m);
	BBString * bmx_midi_in_getPortName(RtMidiIn * m, int portNumber);
	void bmx_midi_in_free(RtMidiIn * m);
	BBArray * bmx_midi_in_getMessage(RtMidiIn * m, double * timestamp);
	void bmx_midi_in_ignoreTypes(RtMidiIn * m, int midiSysex, int midiTime, int midiSense);
	int bmx_midi_in_isPortOpen(RtMidiIn * m);
	void bmx_midi_in_setBufferSize(RtMidiIn * m, unsigned int size, unsigned int count);

	RtMidiOut * bmx_midi_out_create(BBString * clientName);
	void bmx_midi_out_openPort(RtMidiOut * m, int portNumber, BBString * portName);
	void bmx_midi_out_closePort(RtMidiOut * m);
	void bmx_midi_out_openVirtualPort(RtMidiOut * m, BBString * portName);
	int bmx_midi_out_getPortCount(RtMidiOut * m);
	BBString * bmx_midi_out_getPortName(RtMidiOut * m, int portNumber);
	void bmx_midi_out_sendMessage(RtMidiOut * m, unsigned char * message, int length);
	void bmx_midi_out_free(RtMidiOut * m);
	int bmx_midi_out_isPortOpen(RtMidiOut * m);

	BBString * bmx_midi_getVersion();
	BBArray * bmx_midi_getCompiledApi();

}

void bmx_rtmidi_throw(RtMidiError &error) {
	bbExThrow(audio_midi_TMidiError__create(bbStringFromCString(error.what()), (int)error.getType()));
}

RtMidiIn * bmx_midi_in_create(BBString * clientName, int queueSizeLimit) {
	char * n = (char*)bbStringToUTF8String(clientName);
	RtMidiIn * in = 0;
	
	try {
		in = new RtMidiIn(static_cast<RtMidi::Api>(0), n, queueSizeLimit);
		bbMemFree(n);
	} catch (RtMidiError &error) {
		bbMemFree(n);
		bmx_rtmidi_throw(error);
	}
	
	return in;
}

void bmx_midi_in_openPort(RtMidiIn * m, int portNumber, BBString * portName) {
	char * n = (char*)bbStringToUTF8String(portName);
	
	try {
		m->openPort(portNumber, n);
		bbMemFree(n);
	} catch (RtMidiError &error) {
		bbMemFree(n);
		bmx_rtmidi_throw(error);
	}	
}

void bmx_midi_in_closePort(RtMidiIn * m) {
	try {
		m->closePort();
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
}

void bmx_midi_in_openVirtualPort(RtMidiIn * m, BBString * portName) {
	char * n =(char*)bbStringToUTF8String(portName);
	
	try {
		m->openVirtualPort(n);
		bbMemFree(n);
	} catch (RtMidiError &error) {
		bbMemFree(n);
		bmx_rtmidi_throw(error);
	}
}

int bmx_midi_in_getPortCount(RtMidiIn * m) {
	unsigned int n = 0;
	try {
		n = m->getPortCount();
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
	return n;
}

BBString * bmx_midi_in_getPortName(RtMidiIn * m, int portNumber) {
	try {
		std::string s(m->getPortName(portNumber));
		return bbStringFromUTF8String((unsigned char*)s.c_str());
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
}

void bmx_midi_in_free(RtMidiIn * m) {
	try {
		delete m;
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
}

BBArray * bmx_midi_in_getMessage(RtMidiIn * m, double * timestamp) {
	BBArray * arr = &bbEmptyArray;
	std::vector<unsigned char> message;
	int n;
	
	try {
		*timestamp = m->getMessage(&message);
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
	
	n = message.size();
	
	if (n) {
		arr = bbArrayNew1D("b", n);
		unsigned char *c = (unsigned char*)BBARRAYDATA(arr, arr->dims);
		for(int i=0; i < n; ++i){
			c[i] = message[i];
		}
	}

	return arr;
}

void bmx_midi_in_ignoreTypes(RtMidiIn * m, int midiSysex, int midiTime, int midiSense) {
	try {
		m->ignoreTypes(midiSysex, midiTime, midiSense);
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
}

int bmx_midi_in_isPortOpen(RtMidiIn * m) {
	int res = 0;
	try {
		res = m->isPortOpen();
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
	return res;
}

void bmx_midi_in_setBufferSize(RtMidiIn * m, unsigned int size, unsigned int count) {
	m->setBufferSize(size, count);
}

// --------------------------------------------------------

RtMidiOut * bmx_midi_out_create(BBString * clientName) {
	char * n = (char*)bbStringToUTF8String(clientName);
	RtMidiOut * out = 0;
	
	try {
		out = new RtMidiOut(static_cast<RtMidi::Api>(0), n);
		bbMemFree(n);
	} catch (RtMidiError &error) {
		bbMemFree(n);
		bmx_rtmidi_throw(error);
	}
	
	return out;
}

void bmx_midi_out_openPort(RtMidiOut * m, int portNumber, BBString * portName) {
	char * n = (char*)bbStringToUTF8String(portName);
	
	try {
		m->openPort(portNumber, n);
		bbMemFree(n);
	} catch (RtMidiError &error) {
		bbMemFree(n);
		bmx_rtmidi_throw(error);
	}	
}

void bmx_midi_out_closePort(RtMidiOut * m) {
	try {
		m->closePort();
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
}

void bmx_midi_out_openVirtualPort(RtMidiOut * m, BBString * portName) {
	char * n = (char*)bbStringToUTF8String(portName);
	
	try {
		m->openVirtualPort(n);
		bbMemFree(n);
	} catch (RtMidiError &error) {
		bbMemFree(n);
		bmx_rtmidi_throw(error);
	}
}

int bmx_midi_out_getPortCount(RtMidiOut * m) {
	unsigned int n = 0;
	try {
		n = m->getPortCount();
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
	return n;
}

BBString * bmx_midi_out_getPortName(RtMidiOut * m, int portNumber) {
	try {
		std::string s(m->getPortName(portNumber));
		return bbStringFromUTF8String((unsigned char*)s.c_str());
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
}

void bmx_midi_out_sendMessage(RtMidiOut * m, unsigned char * message, int length) {
	try {
			
		m->sendMessage(message, length);
		
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}

}

void bmx_midi_out_free(RtMidiOut * m) {
	try {
		delete m;
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
}

int bmx_midi_out_isPortOpen(RtMidiOut * m) {
	int res = 0;
	try {
		res = m->isPortOpen();
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
	return res;
}
// --------------------------------------------------------

BBString * bmx_midi_getVersion() {
	try {
		return bbStringFromUTF8String((unsigned char*)RtMidi::getVersion().c_str());
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
}

BBArray * bmx_midi_getCompiledApi() {
	try {
		std::vector<RtMidi::Api> apis;
		RtMidi::getCompiledApi(apis);
		
		if (apis.size() == 0) {
			return &bbEmptyArray;
		}
		
		BBArray * arr = bbArrayNew1D("i", apis.size());
		
		int *s=(int*)BBARRAYDATA( arr,arr->dims );
		
		for (int i = 0; i < apis.size(); i++) {
			s[i] = static_cast<int>(apis[i]);
		}
		
		return arr;
		
	} catch (RtMidiError &error) {
		bmx_rtmidi_throw(error);
	}
}


' Copyright (c) 2016-2019 Bruce A Henderson
'
' This software is provided 'as-is', without any express or implied
' warranty. In no event will the authors be held liable for any damages
' arising from the use of this software.
'
' Permission is granted to anyone to use this software for any purpose,
' including commercial applications, and to alter it and redistribute it
' freely, subject to the following restrictions:
'
'    1. The origin of this software must not be misrepresented; you must not
'    claim that you wrote the original software. If you use this software
'    in a product, an acknowledgment in the product documentation would be
'    appreciated but is not required.
'
'    2. Altered source versions must be plainly marked as such, and must not be
'    misrepresented as being the original software.
'
'    3. This notice may not be removed or altered from any source
'    distribution.
'
SuperStrict

Import "common.bmx"


Type TStreamFile

	Field filePtr:Byte Ptr
	Field stream:TStream
	
	Method Create:TStreamFile(stream:TStream)
		filePtr = bmx_soloud_streamfile_new(Self)
		Self.stream = stream
		stream.Seek(0)
		Return Self
	End Method
	
	Function _eof:Int(sf:TStreamFile) { nomangle }
		Return sf.stream.Eof()
	End Function

	Function _seek(sf:TStreamFile, offset:Int) { nomangle }
		sf.stream.Seek(offset)
	End Function
	
	Function _length:Int(sf:TStreamFile) { nomangle }
		Return sf.stream.Size()
	End Function
	
	Function _pos:Int(sf:TStreamFile) { nomangle }
		Return sf.stream.Pos()
	End Function
	
	Function _read:Int(sf:TStreamFile, dst:Byte Ptr, size:Int) { nomangle }
		Return sf.stream.Read(dst, size)
	End Function

	Method Free()
		If filePtr Then
			bmx_soloud_streamfile_free(filePtr)
			filePtr = Null
		End If
	End Method

End Type

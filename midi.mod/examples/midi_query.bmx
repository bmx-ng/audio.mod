SuperStrict

Framework Audio.Midi
Import BRL.StandardIO

Local midiIn:TMidiIn = New TMidiIn.Create()
Local midiOut:TMidiOut = New TMidiOut.Create()

' Check inputs.
Local nPorts:Int = midiIn.getPortCount()

Print "~nThere are " + nPorts + " MIDI input sources available."

Local portName:String

For Local i:Int = 0 Until nPorts
	Try
		portName = midiIn.getPortName(i)
	Catch error:TMidiError
		ShowError(error)
	End Try
	
	Print "  Input Port #" + (i+1) + ": " + portName
Next

' Check outputs.

nPorts = midiOut.getPortCount()

Print "~nThere are " + nPorts + " MIDI output sources available."

For Local i:Int = 0 Until nPorts
	Try
		portName = midiOut.getPortName(i)
	Catch error:TMidiError
		ShowError(error)
	End Try
	
	Print "  Output Port #" + (i+1) + ": " + portName
Next


midiIn.Free()
midiOut.Free()


End

Function ShowError(error:TMidiError)
	Print "Error : " + error.ToString()
	End
End Function

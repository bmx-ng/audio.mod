"""Regenerate owned FLAC/MP3 test tones; requires ffmpeg and lame on PATH."""
from pathlib import Path
import struct
import subprocess
import tempfile
import wave

namespace = Path(__file__).resolve().parents[2]
with tempfile.TemporaryDirectory() as temp:
	for channels, rate, name in [(1, 44100, "mono"), (2, 48000, "stereo")]:
		source = Path(temp) / (name + ".wav")
		with wave.open(str(source), "wb") as output:
			output.setnchannels(channels)
			output.setsampwidth(2)
			output.setframerate(rate)
			output.writeframes(b"".join(
				struct.pack("<h", ((i + c * 37) % 200 - 100) * 100)
				for i in range(rate) for c in range(channels)))
		flac = namespace / "flacstream.mod/tests/data" / (name + ".flac")
		mp3 = namespace / "mp3stream.mod/tests/data" / (name + ".mp3")
		subprocess.run(["ffmpeg", "-hide_banner", "-loglevel", "error", "-i", str(source),
						"-c:a", "flac", "-y", str(flac)], check=True)
		quality = ["-b", "128"] if channels == 1 else ["-V", "4"]
		subprocess.run(["lame", "--silent", *quality, str(source), str(mp3)], check=True)
		if channels == 1:
			unknown = namespace / "mp3stream.mod/tests/data/unknown.mp3"
			subprocess.run(["ffmpeg", "-hide_banner", "-loglevel", "error", "-i", str(source),
							"-c:a", "libmp3lame", "-write_xing", "0", "-id3v2_version", "0",
							"-y", str(unknown)], check=True)

"""wave_to_h.py - Convert wav files to char arrays
	Usage: python wave_to_h.py <wave> <output>
"""
import wave
import sys

if len(sys.argv) != 3:
	print("Usage: python wave_to_h.py <wave> <output>")
	sys.exit(1)

try: 
	wav = wave.open(sys.argv[1])
	frames = wav.readframes(wav.getnframes())
	with open(sys.argv[2], 'w') as f:
		f.write("const unsigned char music[] = { ")
		f.write(", ".join(hex(int(frame/16)) for frame in frames))
		f.write(" };")
except wave.Error:
	print("Error: could not parse wave file")
except Exception as e:
	print("Error: " + str(e))

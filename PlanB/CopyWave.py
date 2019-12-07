import wave

try:
    orginal = wave.open('weather.wav', 'rb')
    modified = wave.open('copied.wav', 'wb')

    nchannels, sampwidth, framerate, nframes, comptype, compname = orginal.getparams()
    modified.setparams((nchannels, sampwidth, framerate, nframes, comptype, compname))

    original_frames = orginal.readframes(nframes)
    modified.writeframes(original_frames)

finally:
    orginal.close()
    modified.close()

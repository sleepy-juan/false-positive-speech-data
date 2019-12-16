import wave

try:
    FileToMerge1 = wave.open('ok_google1.wav', 'rb')
    FileToMerge2 = wave.open('ok_google2.wav', 'rb')
    MergedFile = wave.open('Merged.wav', 'wb')

    nchannels1, sampwidth1, framerate1, nframes1, comptype1, compname1 = FileToMerge1.getparams()
    nframes2 = FileToMerge2.getnframes()

    MergedFile.setparams((nchannels1, sampwidth1, framerate1, nframes1+nframes2, comptype1, compname1))

    FileToMerge1_Frames = FileToMerge1.readframes(nframes1)
    FileToMerge2_Frames = FileToMerge2.readframes(nframes2)

    MergedFile.writeframes(FileToMerge1_Frames)
    MergedFile.writeframes(FileToMerge2_Frames)

finally:
    FileToMerge1.close()
    FileToMerge2.close()
    MergedFile.close()

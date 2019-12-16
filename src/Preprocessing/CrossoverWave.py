import wave
import random


CrossoverUnit = 20000


try:
    FileToCrossover1 = wave.open('1234567-1.wav', 'rb')
    FileToCrossover2 = wave.open('1234567-2.wav', 'rb')
    CrossoverFile1 = wave.open('Crossover1.wav', 'wb')
    CrossoverFile2 = wave.open('Crossover2.wav', 'wb')

    nchannels1, sampwidth1, framerate1, nframes1, comptype1, compname1 = FileToCrossover1.getparams()
    nchannels2, sampwidth2, framerate2, nframes2, comptype2, compname2 = FileToCrossover2.getparams()

    print(nframes1, nframes2)

    CrossoverFile1.setparams((nchannels1, sampwidth1, framerate1, nframes1, comptype1, compname1))
    CrossoverFile2.setparams((nchannels2, sampwidth2, framerate2, nframes2, comptype2, compname2))

    CrossoverPoint = random.randint(1,min(nframes1-CrossoverUnit,nframes2-CrossoverUnit))

    FileToCrossover1_Frames = FileToCrossover1.readframes(CrossoverPoint)
    FileToCrossover2_Frames = FileToCrossover2.readframes(CrossoverPoint)

    CrossoverFile1.writeframes(FileToCrossover1_Frames)
    CrossoverFile2.writeframes(FileToCrossover2_Frames)

    FileToCrossover1_Frames = FileToCrossover1.readframes(CrossoverUnit)
    FileToCrossover2_Frames = FileToCrossover2.readframes(CrossoverUnit)

    CrossoverFile1.writeframes(FileToCrossover2_Frames)
    CrossoverFile2.writeframes(FileToCrossover1_Frames)

    FileToCrossover1_Frames = FileToCrossover1.readframes(nframes1-CrossoverPoint-CrossoverUnit)
    FileToCrossover2_Frames = FileToCrossover2.readframes(nframes2-CrossoverPoint-CrossoverUnit)

    CrossoverFile1.writeframes(FileToCrossover1_Frames)
    CrossoverFile2.writeframes(FileToCrossover2_Frames)

    print(nframes1, nframes2)


finally:
    FileToCrossover1.close()
    FileToCrossover2.close()
    CrossoverFile1.close()
    CrossoverFile2.close()

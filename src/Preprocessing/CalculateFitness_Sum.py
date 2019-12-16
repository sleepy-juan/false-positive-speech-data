import wave


try:
    FileToCompare1 = wave.open('./modified_N/0/10.wav', 'rb')
    FileToCompare2 = wave.open('./modified_N/40/10.wav', 'rb')

    nframes1 = FileToCompare1.getnframes()
    nframes2 = FileToCompare2.getnframes()

    if nframes1 != nframes2:
        print("Error : Different nframes!")

    FileToCompare1_Frames = FileToCompare1.readframes(nframes1)
    FileToCompare2_Frames = FileToCompare2.readframes(nframes1)

    Difference = 0
    for i in range(nframes1):
        Difference += abs(FileToCompare1_Frames[i]-FileToCompare2_Frames[i])

    print(Difference)

finally:
    FileToCompare1.close()
    FileToCompare2.close()
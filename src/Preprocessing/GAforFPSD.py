import os
import shutil
import wave
import random


def ReadOriginalFiles(SrcPath, DesPath):
    
    file_list_wav = [file for file in os.listdir(SrcPath) if file.endswith(".wav")]

    print ("file_list_wav: {}".format(file_list_wav))

    for file in file_list_wav:
        shutil.copy(SrcPath + file, DesPath)
    
    return file_list_wav


def CrossoverTwoFiles(Path, FileNameToCrossover1, FileNameToCrossover2, Generation):

    CrossoverUnit = 500

    try:
        FileToCrossover1 = wave.open(Path + FileNameToCrossover1, 'rb')
        FileToCrossover2 = wave.open(Path + FileNameToCrossover2, 'rb')
        CrossoverFile1 = wave.open('./modified/' + str(Generation) + '/' + FileNameToCrossover1, 'wb')
        # CrossoverFile2 = wave.open('./modified/' + str(Generation) + '/' + '_'+ FileNameToCrossover2, 'wb')
        CrossoverFile2 = wave.open('./modified/' + str(Generation) + '/' + FileNameToCrossover2, 'wb')

        nchannels1, sampwidth1, framerate1, nframes1, comptype1, compname1 = FileToCrossover1.getparams()
        nchannels2, sampwidth2, framerate2, nframes2, comptype2, compname2 = FileToCrossover2.getparams()

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

    finally:
        FileToCrossover1.close()
        FileToCrossover2.close()
        CrossoverFile1.close()
        CrossoverFile2.close()



def Crossover(Path, Pool, Generation):

    for file in Pool:
        CrossoverTwoFiles(Path, file, random.choice(Pool), Generation)


def CalculateFitness_Sum(File1, File2):
    try:
        FileToCompare1 = wave.open(File1, 'rb')
        FileToCompare2 = wave.open(File2, 'rb')

        nframes1 = FileToCompare1.getnframes()
        nframes2 = FileToCompare2.getnframes()

        if nframes1 != nframes2:
            print("Error : Different nframes!")

        FileToCompare1_Frames = FileToCompare1.readframes(nframes1)
        FileToCompare2_Frames = FileToCompare2.readframes(nframes1)

        Difference = 0
        for i in range(nframes1):
            Difference += abs(FileToCompare1_Frames[i]-FileToCompare2_Frames[i])

    finally:
        FileToCompare1.close()
        FileToCompare2.close()

        return Difference


for i in range(101):
    shutil.rmtree('modified/'+str(i))
    os.makedirs('modified/'+str(i))

InitalPool = ReadOriginalFiles('../audio/original/', './modified/0/')

for i in range(100):

    Pool = os.listdir('./modified/'+str(i)+'/')
    Crossover('./modified/'+str(i)+'/', Pool, i+1)


    # # 차이가 커지도록 프레셔
    # for file in os.listdir('./modified/'+str(i+1)+'/'):
    #     if file.startswith('_'):
    #         FileToCompare1 = './modified/'+str(i+1)+'/'+file
    #         FileToCompare2 = './modified/'+str(i+1)+'/'+file.lstrip('_')
    #         if CalculateFitness_Sum('../audio/original/'+file.lstrip('_'), FileToCompare1) < CalculateFitness_Sum('../audio/original/'+file.lstrip('_'), FileToCompare2):
    #             os.remove(FileToCompare1)
    #         else:
    #             os.remove(FileToCompare2)
    #             os.rename(FileToCompare1, FileToCompare2)

    # 차이가 작도록 프레셔
    # for file in os.listdir('./modified/'+str(i+1)+'/'):
    #     if file.startswith('_'):
    #         FileToCompare1 = './modified/'+str(i+1)+'/'+file
    #         FileToCompare2 = './modified/'+str(i+1)+'/'+file.lstrip('_')
    #         if CalculateFitness_Sum('../audio/original/'+file.lstrip('_'), FileToCompare1) > CalculateFitness_Sum('../audio/original/'+file.lstrip('_'), FileToCompare2):
    #             os.remove(FileToCompare1)
    #         else:
    #             os.remove(FileToCompare2)
    #             os.rename(FileToCompare1, FileToCompare2)
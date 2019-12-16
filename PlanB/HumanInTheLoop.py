import wave
import math
import plotly
from plotly.graph_objs import Scatter, Layout



def CalculateFitness_Average(File1, File2):
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
        
        Average = Difference/nframes1

    finally:
        FileToCompare1.close()
        FileToCompare2.close()

        return Average



def CalculateFitness_RMS(File1, File2):
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
            Difference += abs(FileToCompare1_Frames[i]^2-FileToCompare2_Frames[i]^2)

        RMS = math.sqrt(Difference/nframes1)

    finally:
        FileToCompare1.close()
        FileToCompare2.close()

        return RMS



def CalculateFitness_Square(File1, File2):
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
            Difference += math.sqrt(abs(FileToCompare1_Frames[i]^2-FileToCompare2_Frames[i]^2))

    finally:
        FileToCompare1.close()
        FileToCompare2.close()

        return Difference



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



CriteriaFile = '10'
NormalizationForAvg = CalculateFitness_Average('../audio/original/'+CriteriaFile+'.wav', './modified/200/'+CriteriaFile+'.wav')
NormalizationForRMS = CalculateFitness_RMS('../audio/original/'+CriteriaFile+'.wav', './modified/200/'+CriteriaFile+'.wav')
NormalizationForSqu = CalculateFitness_Square('../audio/original/'+CriteriaFile+'.wav', './modified/200/'+CriteriaFile+'.wav')
NormalizationForSum = CalculateFitness_Sum('../audio/original/'+CriteriaFile+'.wav', './modified/200/'+CriteriaFile+'.wav')


Average = plotly.graph_objs.Scatter(
    x=list(range(201)),
    y=[CalculateFitness_Average('../audio/original/'+CriteriaFile+'.wav', './modified/'+str(i)+'/'+CriteriaFile+'.wav')/NormalizationForAvg for i in range(201)],
    name = 'Average'
)

RMS = plotly.graph_objs.Scatter(
    x=list(range(201)),
    y=[CalculateFitness_RMS('../audio/original/'+CriteriaFile+'.wav', './modified/'+str(i)+'/'+CriteriaFile+'.wav')/NormalizationForRMS for i in range(201)],
    name = 'RMS'
)

Square = plotly.graph_objs.Scatter(
    x=list(range(201)),
    y=[CalculateFitness_Square('../audio/original/'+CriteriaFile+'.wav', './modified/'+str(i)+'/'+CriteriaFile+'.wav')/NormalizationForSqu for i in range(201)],
    name = 'Square'
)

Sum = plotly.graph_objs.Scatter(
    x=list(range(201)),
    y=[CalculateFitness_Sum('../audio/original/'+CriteriaFile+'.wav', './modified/'+str(i)+'/'+CriteriaFile+'.wav')/NormalizationForSum for i in range(201)],
    name = 'Sum'
)


plotly.offline.plot({
    "data": [Average, RMS, Square, Sum],
    "layout": Layout(title="Human in the Loop")
})


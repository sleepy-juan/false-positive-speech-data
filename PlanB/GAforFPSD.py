# def cal_path_distance(path):
#     path_length = 0
#     prev_ = path[0]
#     for next_ in path[1:]:
#         path_length += dist[prev_-1][next_-1]
#         prev_ = next_
#     path_length += dist[next_-1][path[0]-1]
#     return path_length


# def make_starting_pool():
#     pool = []
#     for i in range(population//2):
#         gen = list(range(1,N+1))
#         random.shuffle(gen)
#         pool.append(gen)
#     for i in range(population//2):
#         pool.append(greedy(random.randint(1,N)))
#     # for i in [8296,51,6759,6843,9978]:
#     #     pool.append(greedy(i))
#     return pool



# # Process of each generation
# def one_generation(pool):

#     global record

#     ranked = sorted(pool, key=cal_path_distance)

#     if cal_path_distance(ranked[0]) < record:
#         write_file("solution.csv",ranked[0])
#         record = cal_path_distance(ranked[0])
#         print(record)
    
#     next_pool=ranked[:int(population*0.05)]

#     for i in range(int(population*0.47)):
#         selected1, avoid = rank_selection(ranked)
#         selected2 = rank_selection(ranked, avoid)[0]
#         child1, child2 = crossoverPMX2(selected1, selected2)
#         next_pool.append(child1)
#         next_pool.append(child2)

#     for i in range(int(population*0.01)):
#         new_random = list(range(1,N+1))
#         random.shuffle(new_random)
#         next_pool.append(new_random)

#     next_pool = mutate(next_pool, 0.003)

#     return next_pool


# ############################################################################################
# # Main
# ############################################################################################

# def main():

#     global N, dist, population, generation_limit

#     for i in range(len(sys.argv)):
#         if sys.argv[i] == '-p':
#             population = int(sys.argv[i+1])
#         elif sys.argv[i] == '-f':
#             generation_limit = int(sys.argv[i+1])

#     N = read_file(sys.argv[1])

#     dist = cal_all_distance()

#     pool = make_starting_pool()

#     for i in range(generation_limit):
#         print(i)
#         pool = one_generation(pool)
    
#     with open('result.csv','w') as f:
#         wt = csv.writer(f)
#         wt.writerows(pool)

#     print(record)

# if __name__ == '__main__':
#     main()


########################################################################################################################################################################################
########################################################################################################################################################################################
########################################################################################################################################################################################
import os
import wave
import random


def ReadOriginalFiles(Path):
    file_list_wav = [file for file in os.listdir(Path) if file.endswith(".wav")]

    print ("file_list_wav: {}".format(file_list_wav))

    return file_list_wav


def CrossoverTwoFiles(Path, FileNameToCrossover1, FileNameToCrossover2, Generation):

    CrossoverUnit = 500

    try:
        FileToCrossover1 = wave.open(Path + FileNameToCrossover1, 'rb')
        FileToCrossover2 = wave.open(Path + FileNameToCrossover2, 'rb')
        CrossoverFile1 = wave.open('./modified/' + str(Generation) + '/' + FileNameToCrossover1, 'wb')
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



Pool = ReadOriginalFiles("../audio/original/")
Crossover('../audio/original/', Pool, 0)

for i in range(100):
    Crossover('./modified/'+str(i)+'/', Pool, i+1)

# Survey How-to

1. place the audio files to be tested in the human/gui/voice folder.
2. name them as "1.wav" "2.wav" .. and so on. The numbers must be continuous, and start from 1.
3. open human/gui/processor.js. Change the 'totalQuestions' const as the total number of questions.
4. The javascript processor will record the answers in csv file, which will be automatically downloaded once the test is finished. Ask the testers to hand in the file. 
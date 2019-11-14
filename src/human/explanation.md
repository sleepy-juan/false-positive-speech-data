# The Concept of Human Calibration

To generate the test data set, fitness for both humans and computers must be taken into account. However, it is difficult to apply human fitness for every generation in the evolutionary algorithm as humans are much slower than machines. Therefore, we opted to design a sudo-human fitness function that reflects human behaviour with a satisfactory accuracy. We call the following process 'human calibration' as we compare various bit-comparision sudo-human fitness functions with actual humans on MTurk, choose the best candidate, and calibrate.

1. Generate random dataset with random search.
2. Plot the actual fitness with MTurk.
3. Compare each bit-comparison algorithms with the result from 2, which may be considered the 'true answer.'
4. Apply the best-matching bit-comparison fitness function to GA in place of actual humans.
5. Analyse the resulting test cases with MTurk, along with the changing fitness.

# Organisation
human
|--randomsearch.cpp // generate random dataset with random search
|--mturkplot.cpp // plot the actual fitness with MTurk
|--bitwisefitness.cpp // various bit-comparison fitness functions
|--calibrate.cpp // compare the plot with MTurk with bit-comparison fitness function and yield the best
|--finalcheck.cpp // checks the final test data with MTurk

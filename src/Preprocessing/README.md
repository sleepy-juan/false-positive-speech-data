# Preprocessing

false-positive-speech-data implementation in python version of CS454, KAIST, 2019 Fall





## About the Preprocessing

Plan B is implemented in python and it covers most of functions in plan A. We planed genetic algorithm and we made a prediction as GA will take a lots of time. So we planned to implement with C/C++ to increase efficiency. However, the investigation found the benefits of using Python's library to make it much simpler. Therefore, we have attempted parallel development with Python in order to implement multiple functions more flexibly.





## About the Implementation

### Process

1. 
2. 



### Results

The modified audio files will be saved in `modified` folder.

```
├─modified
│  │ 
│  ├─1
│  │      1.wav
│  │      2.wav
│  │      ...
│  └─2
│  │      1.wav
│  │      2.wav
│  │      ...
│  └─3   
│  ...
```

In  `modified` folder, there are several folders that named as number, and it means number of generation. In the each folder, in contains all the wav files that belongs on that generation.





## How to Run

The project is implemented in python version 3.8

```python
$ python3 Preprocessing.py
```
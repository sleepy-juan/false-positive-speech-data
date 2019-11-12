/*
    cpp_python.cpp
    - IPC(Inter Protocol Communication) between C++ and Python

    created by Juan Lee
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main()
{
    int pipes[2];
    if (pipe(pipes) == -1)
    {
        fprintf(stderr, "Unable to create pipe\n");
        exit(-1);
    }

    int pid = fork();
    if (pid == 0)
    { // Child
        close(1);
        dup2(pipes[1], 1);

        system("export GOOGLE_APPLICATION_CREDENTIALS=../../google_api_key.json && python3 google_api_python.py ../../audio/original/weather.wav 48000");
        exit(0);
    }
    else
    {               // Parent
        wait(NULL); // wait for child to be exited

        char buf[1024] = {0};
        read(pipes[0], buf, 1024);
        printf("%s", buf);
    }

    return 0;
}
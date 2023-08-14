#ifndef INCLUDES_H
#define INCLUDES_H

#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <random>
#include <fstream>
#include <sys/shm.h>
#include <sys/stat.h>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <time.h>

using namespace std;
using namespace std::chrono;

// Function prototypes
int numOfRowsFunc(string file);
void *SharedMemory(size_t size);
int RandInt(int min, int max);
char *ReadStr(void *shmem);
void WriteStr(void *shmem, string package);
int ReadInt(void *shmem);
void WriteInt(void *shmem, int numOfRows);
string *FileReading(string filename, int numOfRows);
void DeleteText(string *text);

#endif

#include "includes.hpp"

int numOfRowsFunc(string file) // function to return the number of rows of the input file
{
    string txt;
    int counter = 0;
    ifstream fileRead(file);
    while (getline(fileRead, txt))
    {
        counter++;
    }
    fileRead.close(); // close the file

    return counter; // return the number of rows
}

void *SharedMemory(size_t size) // function to created the shared memory structure and return it
{
    int prot = PROT_READ | PROT_WRITE; // make memory buffer readable and writable

    int map = MAP_SHARED | MAP_ANONYMOUS; // make buffer public,parents and children are able to have access

    return mmap(NULL, size, prot, map, -1, 0); // create a new mapping between a process address space and file
}

int RandInt(int min, int max)
{
    std::random_device randDevice;  // seed the random number engine
    std::mt19937 gen(randDevice()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(min, max / 2);

    srand(getpid());
    return (distrib(gen) + rand() % max / 2);
}

// const char *semName = "sem";

char *ReadStr(void *shmem)
{
    return (char *)shmem;
}

void WriteStr(void *shmem, string pack)
{
    int var = pack.length();
    char currentArray[var + 1];

    strcpy(currentArray, pack.c_str());

    memcpy(shmem, currentArray, sizeof(currentArray)); // copy the memory block
}

int ReadInt(void *shmem)
{
    int *intToRead = static_cast<int *>(shmem);

    return *intToRead;
}

void WriteInt(void *shmem, int numOfRows)
{
    int pack = RandInt(0, numOfRows); // data package

    memcpy(shmem, &pack, sizeof(pack));
}

string *FileReading(string filename, int numOfRows) // function to read the file
{
    string txt;
    int i;
    ifstream readFile(filename);
    string *txtPtr = new string[numOfRows];

    while (getline(readFile, txt))
    {
        txtPtr[i] = txt;
        i++;
        cout << i << endl;
    }
    readFile.close(); // close the reading file

    return txtPtr;
}

void DeleteText(string *txt) // function to delete the array of txt's
{
    delete[] txt;
}
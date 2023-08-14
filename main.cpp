#include "includes.hpp"

const char *sem1 = "sem1";
const char *sem2 = "sem2";

int main(int argc, char *argv[])
{
    string fileX;     // file name "X"
    int numOfChilds;  // number of children "K"
    int numOfDosages; // number of dosages "N"

    if (argc != 4)
    {
        cout << "Wrong number of arguments!" << endl;
        return 1;
    }
    else
    {
        // define arguments
        fileX = argv[1];
        numOfChilds = atoi(argv[2]);
        numOfDosages = atoi(argv[3]);
    }

    int numOfRows = numOfRowsFunc(fileX); // number of rows of the input text file

    sem_t *semID1 = sem_open(sem1, O_CREAT, 0600, 0); // open semaphore 1
    sem_t *semID2 = sem_open(sem2, O_CREAT, 0600, 0); // open semaphore 2
    sem_post(semID2);                                 //

    void *sharedMem = SharedMemory(40960); // create the shared memory

    string *dataStr = FileReading(fileX, numOfRows); // read the file and put the rows in an array

    pid_t pid;
    for (int i = 0; i < numOfChilds; i++)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (!pid) // CODE FOR CHILD
        {
            int currentTime, counterTime = 0;

            cout << "-----------------------------------------" << endl;
            cout << "-CHILD[" << getpid() << "]:\n"
                 << endl;

            for (int j = 0; j < numOfDosages; j++)
            {
                sem_wait(semID2);

                WriteInt(sharedMem, numOfRows);

                sem_post(semID1);
                sem_wait(semID2);

                clock_t start_t, end_t, total_t;

                start_t = clock(); // start the clock

                string rowStr = ReadStr(sharedMem);
                cout << "Received row: " << rowStr << endl
                     << endl;

                end_t = clock(); // stop the clock

                total_t = (double)(end_t - start_t); // total time of a dosage

                currentTime = total_t;
                counterTime += currentTime;
            }
            cout << "AVERAGE TIME (ms): " << counterTime / numOfDosages << endl;
            exit(0);
        }
        else // CODE FOR PARENT
        {
            int wait_var;

            for (int z = 0; z < numOfDosages; z++)
            {
                sem_wait(semID1);

                int rowNum = ReadInt(sharedMem);

                cout << "Requested row: " << rowNum + 1 << endl; // +1 beacuse the array start from position zero
                sem_post(semID2);

                WriteStr(sharedMem, dataStr[rowNum]);
                sem_post(semID2);
            }
            wait(&wait_var);
        }
    }

    /* MEMORY DEALLOCATION */
    if (sem_unlink(sem1) < 0) // remove the named semaphore
        cout << "sem unlink of parent failed!" << endl;

    if (sem_unlink(sem2) < 0) // remove the named semaphore
        cout << "sem unlink of parent failed!" << endl;

    DeleteText(dataStr);
    return 0;
}

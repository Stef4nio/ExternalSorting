#include <iostream>
#include <fstream>
#include <cstdio>
#include <bits/stdc++.h>


using namespace std;

static const long FILE_SIZE = 500000000;


//Writes as much data as possible and returns amount of written data
int WriteDataToArray(int* array,ifstream& inputStream, int arrayLength)
{
    int iterator = 0;
    while(iterator<arrayLength&&inputStream.read(reinterpret_cast<char*>(array+iterator),sizeof(int)))
    {
        iterator++;
    }
    return iterator;
}

void AppendDataToDisk(int* array, basic_string<char, char_traits<char>, allocator<char>> filepath, int arrayLength)
{
    ofstream outStream;
    outStream.open(filepath,ios::binary|ios::app);
    for(int i = 0;i<arrayLength;i++)
    {
        outStream.write(reinterpret_cast<char*>(array+i),sizeof(int));
    }
    outStream.close();
}

void WriteDataToDisk(int* array, basic_string<char, char_traits<char>, allocator<char>> filepath, int arrayLength)
{
    ofstream outStream;
    outStream.open(filepath,ios::binary);
    for(int i = 0;i<arrayLength;i++)
    {
        outStream.write(reinterpret_cast<char*>(array+i),sizeof(int));
    }
    outStream.close();
}

bool AreAllSteamsClosed(const ifstream * array, int arrayLength)
{
    for(int i = 0;i<arrayLength;i++)
    {
        if(array[i].is_open())
        {
            return false;
        }
    }
    return true;
}


void SortFile(const char *filepath, int RAMsize)
{
    int elementsAmount = RAMsize/sizeof(int);

    ifstream fileStream;
    fileStream.open(filepath, ios::binary);

    int *data = new int[elementsAmount];
    int iterator = 0;
    int chunkNumber = 0;

    while(fileStream.read(reinterpret_cast<char*>(data+iterator),sizeof(int)))
    {
        iterator++;
        if(iterator>=elementsAmount)
        {
            sort(data,data+elementsAmount);
            iterator = 0;
            WriteDataToDisk(data, "Chunk_" + to_string(chunkNumber) + ".dat", elementsAmount);
            chunkNumber++;
        }
    }
    fileStream.close();
    if(iterator>0)
    {
        sort(data,data+iterator);
        ofstream sortedChunkStream;
        sortedChunkStream.open("Chunk_"+to_string(chunkNumber)+".dat",ios::binary);
        for(int i = 0;i<iterator;i++)
        {
            sortedChunkStream.write(reinterpret_cast<char*>(data+i),sizeof(int));
        }
        sortedChunkStream.close();
        chunkNumber++;
    }

    delete[](data);

    int bufferSize = elementsAmount/4;
    int subchunkSize = (elementsAmount-bufferSize)/(chunkNumber+1);

    ifstream subchunksStreams[chunkNumber];
    int *subchunks[chunkNumber];
    int subchunksLocalMinimumIndices[chunkNumber];
    int subchunkCurrSizes[chunkNumber];

    for(int i = 0; i<chunkNumber;i++)
    {
        subchunks[i] = new int[subchunkSize];
    }

    int amountOfElementsInBuffer = 0;
    int *buffer = new int[bufferSize];
    for(int i = 0;i<chunkNumber;i++)
    {
        subchunksLocalMinimumIndices[i] = 0;
        subchunksStreams[i].open("Chunk_"+to_string(i)+".dat",ios::binary);
        subchunkCurrSizes[i] = WriteDataToArray(subchunks[i], subchunksStreams[i], subchunkSize);
    }

    ofstream clearStream;
    clearStream.open(filepath,ios::binary|ios::trunc);
    clearStream.close();

    while(!AreAllSteamsClosed(subchunksStreams,chunkNumber))
    {
        if(amountOfElementsInBuffer<bufferSize)
        {
            int lowestMinSubchunkIndex = 0;
            bool isMinInitialized = false;
            int min = 0;
            for(int i = 0;i<chunkNumber;i++)
            {
                if(subchunksStreams[i].is_open()&&(!isMinInitialized||subchunks[i][subchunksLocalMinimumIndices[i]]<min))
                {
                    min = subchunks[i][subchunksLocalMinimumIndices[i]];
                    lowestMinSubchunkIndex = i;
                    isMinInitialized = true;
                }
            }
            buffer[amountOfElementsInBuffer] = subchunks[lowestMinSubchunkIndex][subchunksLocalMinimumIndices[lowestMinSubchunkIndex]];
            amountOfElementsInBuffer++;
            subchunksLocalMinimumIndices[lowestMinSubchunkIndex]++;
            if(subchunksLocalMinimumIndices[lowestMinSubchunkIndex]>=subchunkCurrSizes[lowestMinSubchunkIndex])
            {
                int tempSize = WriteDataToArray(subchunks[lowestMinSubchunkIndex],subchunksStreams[lowestMinSubchunkIndex],subchunkSize);
                subchunkCurrSizes[lowestMinSubchunkIndex] = tempSize;
                subchunksLocalMinimumIndices[lowestMinSubchunkIndex] = 0;
                if(tempSize == 0)
                {
                    subchunksStreams[lowestMinSubchunkIndex].close();
                }
            }
        } else
        {
            AppendDataToDisk(buffer, filepath, bufferSize);
            amountOfElementsInBuffer = 0;
        }
    }
    if(amountOfElementsInBuffer>0)
    {
        AppendDataToDisk(buffer, filepath, amountOfElementsInBuffer);
    }
    for(int i = 0; i<chunkNumber;i++)
    {
        string file = "Chunk_" + to_string(i) + ".dat";
        remove(file.data());
    }

    delete[](buffer);
    for(int i = 0; i<chunkNumber;i++)
    {
        delete[](subchunks[i]);
    }
}

bool checkIfFileIsSorted(const char* filepath)
{
    ifstream testStream;
    testStream.open(filepath,ios::binary);
    int number;
    int prevNum = 0;
    while(testStream.read(reinterpret_cast<char*>(&number),sizeof(int)))
    {
        if(prevNum>number)
        {
            return false;
        }
        prevNum = number;
    }
    return true;
}

void generateRandomFile(const char* filename)
{
    srand(1448);
    ofstream out;
    out.open(filename,ios::binary);
    int num;
    long numAmount = FILE_SIZE/ sizeof(int);
    for(long i = 0;i<numAmount;i++)
    {
        num = rand() % 100;
        out.write(reinterpret_cast<const char *>(&num), sizeof(num));
    }
    out.close();
}

int main()
{
    //generateRandomFile("fileToSort.dat");


    /*auto t1 = std::chrono::high_resolution_clock::now();
    SortFile("fileToSort.dat",125000000);
    auto t2 = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    std::cout << duration << endl;*/

    bool isSorted = checkIfFileIsSorted("fileToSort.dat");

    cout<<(isSorted?"File is sorted":"File is not sorted")<<endl;

    cout<<"Done!";
    return 0;
}

#include <iostream>
#include <fstream>
#include <cstdio>
#include <bits/stdc++.h>


using namespace std;

static const long FILE_SIZE = 500000;

/*long int GetFileSize(const char* filepath)
{
    struct stat filestatus;
    stat( "test.txt", &filestatus );
    return filestatus.st_size;
}*/

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
    //int elementsAmount = RAMsize/sizeof(int) + 1;
    int elementsAmount = RAMsize/sizeof(int);

    ifstream fileStream;
    fileStream.open(filepath, ios::binary);

    int data[elementsAmount];
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

    int bufferSize = elementsAmount/4;
    int subchunkSize = (elementsAmount-bufferSize)/(chunkNumber+1);

    ifstream subchunksStreams[chunkNumber];
    int subchunks[chunkNumber][subchunkSize];
    int subchunksLocalMinimumIndices[chunkNumber];
    int subchunkCurrSizes[chunkNumber];

    int amountOfElementsInBuffer = 0;
    int buffer[bufferSize];
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
}

int main()
{
    srand(time(NULL));
    ofstream out;
    out.open("fileToSort.dat",ios::binary);
    int num;
    //long numAmount = FILE_SIZE/ sizeof(int);
    long numAmount = 32;
    for(long i = 0;i<numAmount;i++)
    {
        num = rand() % 100;
        out.write(reinterpret_cast<const char *>(&num), sizeof(num));
    }
    out.close();


    /*ofstream sortedChunkStream;
    sortedChunkStream.open("fileToSort.dat",ios::binary);
    for(int i = 0;i<5;i++)
    {
        sortedChunkStream.write(reinterpret_cast<char*>(&arr[i]),sizeof(int));
    }
    sortedChunkStream.close();*/

    SortFile("fileToSort.dat",sizeof(int)*8);

    ifstream testStream;
    testStream.open("fileToSort.dat",ios::binary);
    int number;
    int iter = 0;
    while(testStream.read(reinterpret_cast<char*>(&number),sizeof(int)))
    {
        cout<<number<<endl;
        iter++;
    }

    cout<<"pizdec";
    return 0;
}

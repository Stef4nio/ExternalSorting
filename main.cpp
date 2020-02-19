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

void SortFile(const char *filepath, int RAMsize)
{
    //int elementsAmount = RAMsize/sizeof(int) + 1;
    int elementsAmount = RAMsize/sizeof(int) ;
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
            ofstream sortedChunkStream;
            sortedChunkStream.open("Chunk_"+to_string(chunkNumber)+".dat",ios::binary);
            for(int i = 0;i<elementsAmount;i++)
            {
                sortedChunkStream.write(reinterpret_cast<char*>(data+i),sizeof(int));
            }
            sortedChunkStream.close();
            chunkNumber++;
        }
    }
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
    int subchunkSize = elementsAmount*3/(4*(chunkNumber+1));
}

int main()
{
    int arr[]{1,5,2,6,7,4,6,0,11};
    /*srand(time(NULL));
    ofstream out;
    out.open("fileToSort.dat",ios::binary);
    int num;
    long numAmount = FILE_SIZE/ sizeof(int);
    for(long i = 0;i<numAmount;i++)
    {
        num = rand() % 100;
        out.write(reinterpret_cast<const char *>(&num), sizeof(num));
    }
    out.close();*/
    //sort(arr,arr+9);


    ofstream sortedChunkStream;
    sortedChunkStream.open("fileToSort.dat",ios::binary);
    for(int i = 0;i<5;i++)
    {
        sortedChunkStream.write(reinterpret_cast<char*>(&arr[i]),sizeof(int));
    }
    sortedChunkStream.close();

    ifstream testStream;
    testStream.open("Chunk_2.dat",ios::binary);
    int number[4];
    int iter = 0;
    while(testStream.read(reinterpret_cast<char*>(&number[iter]),sizeof(int)))
    {
        cout<<number[iter]<<endl;
        iter++;
    }

    //SortFile("fileToSort.dat",sizeof(int)*2);

/*    int loh[9];
    ifstream lohStream;
    lohStream.open("Chunk_9.dat",ios::binary);
    for(int i = 0;i<9;i++)
    {
        lohStream.read(reinterpret_cast<char*>(loh+i),sizeof(int));
    }*/
    //remove("Chunk_9.dat");
    cout<<"pizdec";
    return 0;
}

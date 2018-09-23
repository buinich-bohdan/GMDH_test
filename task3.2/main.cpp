#include <iostream>
#include <cstring>

void print_arr(int* arr, int range)
{
    int count = 0;
    for (int i = 0; i < range; ++i)
        for (int j = 0; j < arr[i]; ++j) {
            std::cout << i << std::endl;
            ++count;
            if (count == 1000000)
                return;
        }
}
int find_range(FILE* f, int size)
{
    int range = 0;
    int* buf = new int [size];

    while (!feof(f)) {
      int read = fread(buf, sizeof(int), size, f);
        if (read == 0)
            break;

        for (int i = 0; i < read; ++i)
            if (buf[i] > range)
                range = buf[i];
    }
    range += 1;
    fseek(f, 0, SEEK_SET);
    delete[] buf;
    return range;
}

void counting_sort(FILE *f, int range, int size, int **pcount)
{
    int *counter = new int [range]; //array of elements

    memset(counter, 0, range * sizeof(int));

    int *buf = new int [size]; //buffer for elements

    while (!feof(f))
    {
        int read = fread(buf, sizeof(int), size, f);
        if (read == 0)
            break;

        for (int i = 0; i < read; i++)
            ++counter[buf[i]]; //plus one repetition for an element
    }
    delete[] buf;
    *pcount = counter;
    delete[] counter;
}

int main()
{
    FILE* f; //pointer to the stream buffer
    int range = -1; //maximum value our stream buffer
    int* count; //counter

    f = fopen("/home/bohdan/CLionProjects/GMDH/logfile.txt", "rb"); //our file

    fseek(f , 0 , SEEK_END); //go to end of file
    int n = ftell(f) /sizeof(int); //numeber of elements in file
    std::cout << "number of data items in file: " <<  n << std::endl;
    fseek(f , 0 , SEEK_SET); //back to start of file

    range = find_range(f, n); //maximum element in file
    counting_sort(f, range, n, &count);
    print_arr(count, range);

    return 0;
}
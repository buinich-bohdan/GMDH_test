#include <iostream>


void print_counter(int* arr, int range)
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

int find_range(FILE* f, int bufn)
{
    int range = 0;
    int read;

    int* buf = new int(bufn);

    while (!feof(f)) {
        read = fread(buf, sizeof(int), bufn, f);
        if (read == 0)
            break;

        for (int i = 0; i < read; ++i)
            if (buf[i] > range)
                range = buf[i];
    }
    range += 1;
    fseek(f, 0, SEEK_SET);
    delete buf;
    return range;
}

int counting_sort(FILE* f, int range, int bufn, int** pcounter)
{

    int read;
    int* counter = new int(range);
    int* buf = new int(bufn);//buffer for elements

    while (!feof(f)) {
        read = (int)fread(buf, sizeof(int), bufn, f);
        if (read == 0)
            break;

        for (int i = 0; i < read; i++)
            counter[buf[i]]++; //  plus one repetition for an element
    }

    *pcounter = counter;

    return 0;
}

int main(int argc, const char* argv[])
{
    FILE* f;
    int bufn = 1000000;
    int range = -1;
    int* counter;

    f = fopen("/home/bohdan/CLionProjects/GMDH/task3.1/logfile.txt", "rb");
    range = find_range(f, bufn); //maximum element in file
    counting_sort(f, range, bufn, &counter);
    print_counter(counter, range);

    return 0;
}
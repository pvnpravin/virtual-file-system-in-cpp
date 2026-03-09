#include<stdio.h>
#include<stdlib.h>


// Conditional Pre- Processing
int main()
{
    #ifdef _WIN32
        system("dir");
    #else
        system("ls");
    #endif

    return 0;
}
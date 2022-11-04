#include <stdio.h>
#include <iostream>
#include <string>
#include <complex.h>
#include "linker.hpp"
using namespace std;
int main(int argc, char **argv)
{

   if (argc < 2)
    {
        printf("Too few arguments.\n");
        printf("Usage: %s  <samprate>\n", argv[0]);
        return EXIT_FAILURE;
    }

int samprate = atoi(argv[1]); 
//int prc=0;
// string val of arguments is conv to int no.1.0, 0.5, 0.0,  0.5, 1.0,  0.5, 0.0,  0.5
//float samples_rate[25], signal[25]; float slope[25];
/*int loop_var_1;

std::string line;       //declaring a varb that gets value from console std i/o, read each line by line
    int count = 0;
    while (std::getline(std::cin, line)) //iterate over each line of the stream, condition of the loop is a call to std::getline, extracts lines from stream into line until non-empty
    {   
        float signal = std::stof(line));
        printf("%f",signal);
}
    
  //  int samprate=8;*/
    float* signal = new float[samprate]; 
   // printf(" val of signal  ");
    for(int loop=0;loop<samprate; loop++)
    {
        scanf("%f",&signal[loop]);
    }

   /* for(int loop2=0;loop2<samprate; loop2++)
    { //prc++;
     //printf("%f ",signal[loop2]);
    }*/
    //printf("val of no. signal %d",prc );
     time_error(signal,samprate);
}

//cmd to compile: g++ time_error.cpp temp2.cpp -I ../org/ -o time_error.exe 
//I-> include the path from where it should start looking file, -o -> where o/p should be written 
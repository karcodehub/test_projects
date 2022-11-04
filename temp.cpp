#include <stdio.h>
#include <iostream>
#include <string>
#include <complex.h>
using namespace std;
int main()
{
    //float signal[]}; 
float samples_rate[25], signal[25]; float slope[25];
int loop_var_1;

std::string line;       //declaring a varb that gets value from console std i/o, read each line by line
    int count = 0;
    while (std::getline(std::cin, line)) //iterate over each line of the stream, condition of the loop is a call to std::getline, extracts lines from stream into line until non-empty
    {   
        int sep = line.find(',');
       signal[count] = std::stof(line.substr(0,sep));
        printf("%f",signal[count]);
  return 0;
}
}  
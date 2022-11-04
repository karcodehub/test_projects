#include <stdio.h>
#include <iostream>
#include <string>
#include <complex.h>
#include "linker.hpp"
using namespace std;
int main(int argc, char **argv)
{

   if (argc < 3)
    {
        printf("Too few arguments.\n");
        printf("Usage: %s  <samprate>\n", argv[0]);
        return EXIT_FAILURE;
    }
//float* intrpl = new float[100];
int samprate = atoi(argv[1]); // no of samples
float intr_pt = atof(argv[2]); // interpolating points 
int prc=0;



//printf("val of   and mu %f\n",intr_pt);
//printf("val of no. 1st %d and 2nd %d and 3rd %d  and 4th %d ",argv[0],argv[2],argv[2],argv[3]);
//%s<->argv[0] --> C:\Users\Karthik Lokesh\Desktop\Proj_Arb\interpolator\wrp\intrpl.exe
//%s<->argv[1] --> all signals
//%s<->argv[2] -->400.000000 and then 399.000000 and 398.000000  
//%s<->argv[3] --> all 100 mm values 
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
    float* intrpol = new float[samprate];
    int p=0, proc=0;
   float* slope =new float[samprate]; //val of samprate will be know dynamical so the array is created dynamically 
    float* slp_amp = new float [samprate]; 
    for(int loop=0;loop<samprate; loop++)
    { proc++;
        scanf("%f",&signal[loop]);
    }

//interpolations starts
  /*for(int loop2=0;loop2<samprate-1; loop2++)
    { p++;
      intrpol[loop2] = ((intr_pt * signal[loop2+1]) + ((1 - intr_pt) * signal[loop2]));
     // printf("(%f * %f) + (%f * %f) = %f \n",intr_pt,signal[loop2+1],intr_pt,signal[loop2],intrpol[loop2]);
      //printf("%9.5f",intrpol[loop2]);
    }*/

//printf("val of no. signal cal %d",p );
//printf("val of no. signal proc %d",proc );
//printf("val of no. signal %d",intr_pt );


for(int loop=1;loop<samprate-1;loop+=4)
{

    slope[loop] = (signal[loop+1]- signal[loop-1]);
       cout << "\n\n slope of " << loop+1 << "th sample  is \t" <<signal[loop+1] << "-" <<signal[loop-1]<<"=" << slope[loop] <<"\n";
       slp_amp[loop] = (slope[loop] * signal[loop]);
       cout << "\n slope amplitudde of  " << loop+1 << "th sample  is \t" <<slope[loop] << "*" <<signal[loop]<<"=" << slp_amp[loop] <<"\n\n\n";
        //cout << slp_amp[loop];
     // s[loop] = ((intr_pt + slp_amp[loop]) + ((1 - intr_pt) + slp_amp[loop] ) ; 
        printf("%9.5f",slp_amp[loop]);
}

  
}

//cmd to compile: g++ time_error.cpp temp2.cpp -I ../org/ -o time_error.exe 
//I-> include the path from where it should start looking file, -o -> where o/p should be written 
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
  // float* intrpl = new float[100];
  int samprate = atoi(argv[1]); // no of samples
  float alpha = atof(argv[2]);
  float alpha_const = atof(argv[3]); // interpolating points
  int samp_per_symb = atoi(argv[4]);
  int samp_offset = 0,count = 0;
  float avg_err = 0, all_err = 0.0, err_signal, pr=0; // alpha=0.17,,alpha_const=0.01
  float *signal = new float[samprate]; // it takes Input from STD I/O stores the signal samples
  float *time_err = new float[samprate]; // It stores time error for each symbol (no. of samples)
  float *intrpol = new float[samprate]; // it stores interpolated vales of signal shifted by alpha
  float *slope = new float[samprate]; // val of samprate will be know dynamical so the array is created dynamically
  float *slp_amp = new float[samprate]; // stores slope and amplitude product
//printf("val of samp_per_symb %d\n",samp_per_symb);
  for (int loop = 0; loop < samprate; loop++) // reading signal from std I/O
  {
    
    scanf("%f", &signal[loop]);
    time_err[loop] = 0.0;
    // cout<<time_err[loop];
  }
  
  samp_offset = 0;
  for (int loop = 1; loop < (samprate-samp_per_symb-4); loop += (samp_per_symb))
  { 
    pr++;
    if (alpha > 1)
    {
      samp_offset += 1;
      alpha -= 1;
    }
    else if (alpha < 0)
    {
      samp_offset -= 1;
      alpha += 1;
    }

    intrpol[loop + 0] =     (((1-alpha) * signal[loop-1 + samp_offset]) + (alpha * signal[loop + 0 + samp_offset]));
    intrpol[loop + 1] = (((1-alpha) * signal[loop + 0 + samp_offset]) + (alpha * signal[loop + 1 + samp_offset]));
    intrpol[loop + 2] = (((1-alpha) * signal[loop + 1 + samp_offset]) + (alpha * signal[loop + 2 + samp_offset]));
    //intrpol[loop + 3] = (((1-alpha) * signal[loop + 3 + samp_offset]) + (alpha * signal[loop + 4 + samp_offset]));

    /* cout << "\n\n intrp : " << alpha << " * " << signal[loop + samp_offset] << " + " << 1 - alpha << " * " << signal[loop + 1 + samp_offset] << "=" << intrpol[loop];
     cout << "\n intrp1 : " << alpha << " * " << signal[loop + 1 + samp_offset] << " + " << 1 - alpha << " * " << signal[loop + 2 + samp_offset] << "=" << intrpol[loop + 1];
     cout << "\n intrp2 : " << alpha << " * " << signal[loop + 2 + samp_offset] << " + " << 1 - alpha << " * " << signal[loop + 3 + samp_offset] << "=" << intrpol[loop + 2];
    */
    slope[loop + 1] = (float)(intrpol[loop + 2] - intrpol[loop]); // slope of 2nd point
   
    //cout << "\n\n slope of itp 1 " << loop + 1 << "th sample  is itp2 - itp \t" << intrpol[loop + 2] << "-" << intrpol[loop] << "=" << slope[loop + 1] << "\n";
    
    slp_amp[loop + 1] = (float) (slope[loop + 1] * intrpol[loop +1]); // alphal with amp of 2nd point
                                                              
    //cout << "\n slope amplitudde of  " << loop + 1 << "th sample  is \t" << slope[loop + 1] << "*" << intrpol[loop + 1] << "=" << slp_amp[loop + 1] << "\n\n\n";
    
    time_err[int((loop / samp_per_symb) + 1)] = slp_amp[loop + 1];
    
    all_err = 0; //
    count = 0;
    //cout << "\n avg_err + time_err = " << avg_err << " + " << time_err[int((loop / samp_per_symb) + 1)];

    //loop to add all last 20 errors
    for (int arr = (loop / samp_per_symb) + 1; arr > 0 && count < 20; arr--)
    {
      //cout << time_err[arr] << "+";
      all_err += time_err[arr];
      count++;
    }

    avg_err = (all_err / (20)); // avg of last 5 time error values

    // cout << "\n\nall_err=" << all_err << "\t avg_err=" << avg_err;
    //cout << "\n\n alpha + (avg_err*alpha_const)=  " << alpha << " + " << avg_err << " * " << alpha_const << " = " << (alpha + avg_err * alpha_const);
    
    alpha = alpha + avg_err * alpha_const;
     //printf("%9.5f",time_err[int((loop/samp_per_symb)+1)]);
    printf("%9.5f", (float)samp_offset + alpha);
  }
  //cout<<"pr";
}

// cmd to compile: g++ time_error.cpp temp2.cpp -I ../org/ -o time_error.exe
// I-> include the path from where it should start looking file, -o -> where o/p should be written

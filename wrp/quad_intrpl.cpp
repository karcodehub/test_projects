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
  float beta = atof(argv[2]);
  float beta_const = atof(argv[3]); // interpolating points
  int samp_per_symb = atoi(argv[4]);
  int samp_offset = 0,count = 0;
  float avg_err = 0, all_err = 0.0, err_signal, co_const=.5, co_eff1=0.0, co_eff2=0.0, co_eff3=0.0, co_eff4=0.0; // beta=0.17,,beta_const=0.01
  float *signal = new float[samprate]; // it takes Input from STD I/O stores the signal samples
  float *time_err = new float[samprate]; // It stores time error for each symbol (no. of samples)
  float *intrpol = new float[samprate]; // it stores interpolated vales of signal shifted by beta
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
  for (int loop = 0; loop < samprate-samp_per_symb-4; loop += samp_per_symb)
  { 

    if (beta > 1)
    {
      samp_offset += 1;
      beta -= 1;
    }
    else if (beta < 0)
    {
      samp_offset -= 1;
      beta += 1;
    }
    co_eff4= (co_const* (pow(beta,2)- beta) );
    co_eff3= (-(co_const*pow(beta,2)) + ((1+co_const)*beta));
    co_eff2= (-(co_const*pow(beta,2)) - ((1-co_const)*beta) + 1);
    co_eff1= (co_const* (pow(beta,2)- beta) );


    intrpol[loop] = co_eff4*signal[loop+3+ samp_offset] + co_eff3*signal[loop+2+ samp_offset] 
                    + co_eff2*signal[loop+1+ samp_offset] + co_eff1*signal[loop+ samp_offset];
    
    intrpol[loop +1] = co_eff4*signal[loop+4+ samp_offset] + co_eff3*signal[loop+3+ samp_offset] 
                    + co_eff2*signal[loop+2+ samp_offset] + co_eff1*signal[loop+1+ samp_offset];

    intrpol[loop +2] = co_eff4*signal[loop+5+ samp_offset] + co_eff3*signal[loop+4+ samp_offset] 
                    + co_eff2*signal[loop+3+ samp_offset] + co_eff1*signal[loop+2+ samp_offset];

    // cout << "\n\n intrp : " << beta << " * " << signal[loop + samp_offset] << " + " << 1 - beta << " * " << signal[loop + 1 + samp_offset] << "=" << intrpol[loop];
    // cout << "\n intrp1 : " << beta << " * " << signal[loop + 1 + samp_offset] << " + " << 1 - beta << " * " << signal[loop + 2 + samp_offset] << "=" << intrpol[loop + 1];
    // cout << "\n intrp2 : " << beta << " * " << signal[loop + 2 + samp_offset] << " + " << 1 - beta << " * " << signal[loop + 3 + samp_offset] << "=" << intrpol[loop + 2];
    
    slope[loop + 1] = (intrpol[loop + 2] - intrpol[loop]); // slope of 2nd point
   
    // cout << "\n\n slope of itp 1 " << loop + 1 << "th sample  is itp2 - itp \t" << intrpol[loop + 2] << "-" << intrpol[loop] << "=" << slope[loop + 1] << "\n";
    
    slp_amp[loop + 1] = (slope[loop + 1] * intrpol[loop + 1]); // alphal with amp of 2nd point
                                                              
    // cout << "\n slope amplitudde of  " << loop + 1 << "th sample  is \t" << slope[loop + 1] << "*" << intrpol[loop + 1] << "=" << slp_amp[loop + 1] << "\n\n\n";
    
    time_err[int((loop / samp_per_symb) + 1)] = slp_amp[loop + 1];
    
    all_err = 0; //
    count = 0;
    //cout << "\n avg_err + time_err = " << avg_err << " + " << time_err[int((loop / down_samp) + 1)];

    //loop to add all last 5 errors
    for (int arr = (loop / samp_per_symb) + 1; arr > 0 && count < 20; arr--)
    {
      // cout << time_err[arr] << "+";
      all_err += time_err[arr];
      count++;
    }

    avg_err = (all_err / (20)); // avg of last 5 time error values

    // cout << "\n\nall_err=" << all_err << "\t avg_err=" << avg_err;
    // cout << "\n\n beta + (avg_err*beta_const)=  " << beta << " + " << avg_err << " * " << beta_const << " = " << (beta + avg_err * beta_const);
    
    beta = beta + avg_err * beta_const;
    // printf("%9.5f",time_err[int((loop/samp_per_symb)+1)]);
    printf("%9.5f", (float)samp_offset + beta);
  }
}

// cmd to compile: g++ time_error.cpp temp2.cpp -I ../org/ -o time_error.exe
// I-> include the path from where it should start looking file, -o -> where o/p should be written

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
float avg_err=0,Mu=0.5,all_err=0.0,err_signal,Mu_const=0.1;



//printf("val of   and mu %f\n",intr_pt);
//printf("val of no. 1st %d and 2nd %d and 3rd %d  and 4th %d ",argv[0],argv[2],argv[2],argv[3]);
//%s<->argv[0] --> C:\Users\Karthik Lokesh\Desktop\Proj_Arb\interpolator\wrp\intrpl.exe
//%s<->argv[1] --> all signals
//%s<->argv[2] -->400.000000 and then 399.000000 and 398.000000  
//%s<->argv[3] --> all 100 mm values 
// string val of arguments is conv to int no.1.0, 0.5, 0.0,  0.5, 1.0,  0.5, 0.0,  0.5
//float samples_rate[25], signal[25]; float slope[25];
/*int loop_var_1;


    
  //  int samprate=8;*/
    float* signal = new float[samprate]; 
    float* time_err = new float[samprate];
    float* intrpol = new float[samprate];
    //float* intrp2 = new float[samprate];
    int p=0, proc=0, down_samp=4;
   float* slope =new float[samprate]; //val of samprate will be know dynamical so the array is created dynamically 
    float* slp_amp = new float [samprate]; 
    for(int loop=0;loop<samprate; loop++) // reading signal from std I/O
    { proc++;
        scanf("%f",&signal[loop]);
        time_err[loop]= 0.0;
        //cout<<time_err[loop];
    }
//cout << "samprate/down_samp="<<samprate/down_samp; 
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


for(int loop=0;loop<samprate-1;loop+=down_samp)
{
  cout<<"\nMu="<<Mu<<"\t  signal0="<<signal[loop]<<"+"<<"\t (1-Mu)signal1="<<signal[loop+1];
  cout<<"\nMu="<<Mu<<"\t  signal1="<<signal[loop+1]<<"+"<<"\t (1-Mu)signal2="<<signal[loop+2];
  cout<<"\nMu="<<Mu<<"\t  signal2="<<signal[loop+2]<<"+"<<"\t (1-Mu)signal3="<<signal[loop+3];
  
   intrpol[loop] = ((Mu * signal[loop]) + ((1 - Mu) * signal[loop+1]));
  intrpol[loop+1] = ((Mu * signal[loop+1]) + ((1 - Mu) * signal[loop+2]));
  intrpol[loop+2] = ((Mu * signal[loop+2]) + ((1 - Mu) * signal[loop+3]));
  intrpol[loop+3] = ((Mu * signal[loop+3]) + ((1 - Mu) * signal[loop+4]));

  cout<<"\n intrp:"<<Mu<<"*"<<signal[loop+1]<<"+"<< 1-Mu <<"*"<<signal[loop]<<"="<< intrpol[loop];
  cout<<"\n intrp1:"<<Mu<<"*"<<signal[loop+2]<<"+"<< 1-Mu <<"*"<<signal[loop+1]<<"="<< intrpol[loop+1];
  cout<<"\n intrp2:"<<Mu<<"*"<<signal[loop+3]<<"+"<< 1-Mu <<"*"<<signal[loop+2]<<"="<< intrpol[loop+2];
    slope[loop+1] = (intrpol[loop+2]- intrpol[loop]); //slope of 2nd point
    //slope[loop+2] = (signal[loop+3]- signal[loop+1]);// slope of 3rd point
     cout << "\n\n slope ofitp1 " << loop+1 << "th sample  is itp2 -itp \t" <<intrpol[loop+2] << "-" <<intrpol[loop]<<"=" << slope[loop+1] <<"\n";
       slp_amp[loop+1] = (slope[loop+1] * intrpol[loop+1]);// mul with amp of 2nd point
       //slp_amp[loop+2] = (slope[loop+2] * intrpol[loop+2]);// mul with amp of 3d point
      cout << "\n slope amplitudde of  " << loop+1 << "th sample  is \t" <<slope[loop+1] << "*" <<intrpol[loop+1]<<"=" << slp_amp[loop+1] <<"\n\n\n";
          time_err[int((loop/down_samp)+1)] = slp_amp[loop+1];  
        time_err[int((loop/down_samp)+1)] = (slp_amp[loop+2]+slp_amp[loop+1]) /2;
        //cout<< time_err[int((loop/down_samp)+1)];
        all_err=0;
        cout<< "\n before add:loop  \t" << "\n all_err + time_err \n" << all_err <<"+"<< time_err[int((loop/down_samp)+1)];
       for(int arr=1;arr<(samprate/down_samp)+1;arr++)
        {
          //cout<< "\n inside add:loop \t" << arr<< "\n all_err + time_err\n" << all_err <<"+"<< time_err[int((loop/down_samp)+1)];
          all_err+=time_err[arr];
          
          
        }
        //cout<< "\n\n\n after add:lopp \t" << "\n all_err + time_err\n" << all_err <<"+"<< time_err[int((loop/down_samp)+1)];
        avg_err= (all_err/(samprate/down_samp));
        //cout<< "\nall_err="<< all_err << "\t avg_err=" << avg_err;
        cout<<"\n before update: (Mu+avg_err)*Mu_const="<< Mu<<"+"<<avg_err<<"*"<<Mu_const;
        Mu = Mu + avg_err*Mu_const;
        //cout << "\n Mu="<< Mu;
        //cout<<"\ntime_err"<< loop <<time_err[loop]<<"\n";
        //intrpol[loop] = ((Mu * signal[loop+1]) + ((1 - Mu) * signal[loop]));
        //cout<<"intrpol="<<intrpol[loop];
     // s[loop] = ((intr_pt * slp_amp[loop]) + ((1 - intr_pt) * slp_amp[loop] ) ; 
       // printf("%9.5f",time_err[int((loop/down_samp)+1)]);
}

  /*for(int loop2=0;loop2<(samprate / 4); loop2++)
    { p++;
      intrpol[loop2] = ((intr_pt * signal[loop2+1]) + ((1 - intr_pt) * signal[loop2]));
     // printf("(%f * %f) + (%f * %f) = %f \n",intr_pt,signal[loop2+1],intr_pt,signal[loop2],intrpol[loop2]);
      //printf("%9.5f",time_err[loop2]);
    } */
    
for (int loop3=1;loop3<samprate-1;loop3+=down_samp)
{
  int loop, count=0;
    //val of samprate will be know dynamical so the array is created dynamically 
     
       for(int arr=0;arr<samprate-1;arr++)
        {
          all_err+=time_err[arr];
          //cout<<"\t time_err ="  <<time_err[arr];
          
        }
}

}

//cmd to compile: g++ time_error.cpp temp2.cpp -I ../org/ -o time_error.exe 
//I-> include the path from where it should start looking file, -o -> where o/p should be written 
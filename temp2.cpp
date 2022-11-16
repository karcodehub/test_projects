#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <complex.h>
//#include <filename.h>
#include <fstream>
//#include "linker.hpp"
using namespace std;

int main(int argc, char **argv)
{

   if (argc < 4)
    {
        printf("Too few arguments.\n");
        printf("Usage: %s  <samprate>\n", argv[0]);
        return EXIT_FAILURE;
    }
//float* intrpl = new float[100];
int samprate = atoi(argv[1]); // no of samples
float Mu = atof(argv[2]);
float Mu_const = atof(argv[3]);
int samp_per_symb = atoi(argv[4]); 
int py_loop_no = atoi(argv[5]); //
int prc=0,count=0, ofst_mu_al=0;
float avg_err=0,all_err=0.0,err_signal,samp_offset=0.0;//Mu=0.17,,Mu_const=0.01



//printf("val of samp_per_symb %d\n",samp_per_symb);
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
    float* ofst_mu = new float[samprate];
    //float* intrp2 = new float[samprate];
    int p=0, proc=0, down_samp=4;
   float* slope =new float[samprate]; //val of samprate will be know dynamical so the array is created dynamically 
    float* slp_amp = new float [samprate]; 
    FILE *fptr; ofstream myfile;
    fptr = fopen("C:\\Users\\Karthik Lokesh\\Desktop\\Proj_Arb\\c_arbeit\\temp2.txt","w");
    myfile.open("c_inp.txt", ios::out | ios::app);
     //myfile << "Writing this to a file.\n";
      
    if(fptr == NULL)
   {
      printf("Error!");   
      exit(1);             
   }
    //printf("\n__________\n");
    for(int loop=0;loop<samprate; loop++) // reading signal from std I/O
    { proc++;
        scanf(" %f",&signal[loop]);
        time_err[loop]= 0.0;
        fprintf(fptr,"\n %f",signal[loop]);
        myfile<< signal[loop]<<"  ";
        if(proc>3)
        { proc=0;myfile<<"\n";}
     //   printf(" %f",signal[loop]);
        //cout<<time_err[loop];
    }
   //printf("\n__________%d",proc);
   fclose(fptr);
//cout << "samprate/down_samp="<<samprate<<down_samp; 
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

samp_offset=0;
for(int loop=0;loop<samprate-samp_per_symb;loop+=(samp_per_symb))
{ //cout<<"value of loop="<<loop;
  
  if (Mu > 1)
    {
      samp_offset += 1;
      Mu -= 1;
    }
    else if (Mu < 0)
    {
      samp_offset -= 1;
      Mu += 1;
    }
  /*cout<<"\n samp_offset="<<samp_offset;
  cout<<"\n\nMu="<<Mu<<"\t  signal0="<<signal[loop+ int(samp_offset)]<<"+"<<"\t (1-Mu)signal1="<<signal[loop+1+ int(samp_offset)];
  cout<<"\nMu="<<Mu<<"\t  signal1="<<signal[loop+1+ int(samp_offset)]<<"+"<<"\t (1-Mu)signal2="<<signal[loop+2+ int(samp_offset)];
  cout<<"\nMu="<<Mu<<"\t  signal2="<<signal[loop+2+ int(samp_offset)]<<"+"<<"\t (1-Mu)signal3="<<signal[loop+3+ int(samp_offset)];*/
  myfile<<"\n samp_offset="<<samp_offset;
  myfile<<"\n\nMu="<<Mu<<"\t  signal0="<<signal[loop+ int(samp_offset)]<<"+"<<"\t (1-Mu)signal1="<<signal[loop+1+ int(samp_offset)];
  myfile<<"\nMu="<<Mu<<"\t  signal1="<<signal[loop+1+ int(samp_offset)]<<"+"<<"\t (1-Mu)signal2="<<signal[loop+2+ int(samp_offset)];
  myfile<<"\nMu="<<Mu<<"\t  signal2="<<signal[loop+2+ int(samp_offset)]<<"+"<<"\t (1-Mu)signal3="<<signal[loop+3+ int(samp_offset)];
  
    intrpol[loop] = ((Mu * signal[loop + int(samp_offset)])  + ((1 - Mu) * signal[loop+1+ int(samp_offset)]));
  intrpol[loop+1] = ((Mu * signal[loop+1+ int(samp_offset)]) + ((1 - Mu) * signal[loop+2+ int(samp_offset)]));
  intrpol[loop+2] = ((Mu * signal[loop+2+ int(samp_offset)]) + ((1 - Mu) * signal[loop+3+ int(samp_offset)]));
  intrpol[loop+3] = ((Mu * signal[loop+3+ int(samp_offset)]) + ((1 - Mu) * signal[loop+4+ int(samp_offset)]));

  /*cout<<"\n\n intrp : "<<Mu<<" * "<<signal[loop + int(samp_offset)]<<" + "<< 1-Mu <<" * "<<signal[loop+1+ int(samp_offset)]<<"="<< intrpol[loop];
  cout<<"\n intrp1 : "<<Mu<<" * "<<signal[loop+1+ int(samp_offset)]<<" + "<< 1-Mu <<" * "<<signal[loop+2+ int(samp_offset)]<<"="<< intrpol[loop+1];
  cout<<"\n intrp2 : "<<Mu<<" * "<<signal[loop+2+ int(samp_offset)]<<" + "<< 1-Mu <<" * "<<signal[loop+3+ int(samp_offset)]<<"="<< intrpol[loop+2];
    */
  myfile<<"\n\n intrp : "<<Mu<<" * "<<signal[loop + int(samp_offset)]<<" + "<< 1-Mu <<" * "<<signal[loop+1+ int(samp_offset)]<<"="<< intrpol[loop];
  myfile<<"\n intrp1 : "<<Mu<<" * "<<signal[loop+1+ int(samp_offset)]<<" + "<< 1-Mu <<" * "<<signal[loop+2+ int(samp_offset)]<<"="<< intrpol[loop+1];
  myfile<<"\n intrp2 : "<<Mu<<" * "<<signal[loop+2+ int(samp_offset)]<<" + "<< 1-Mu <<" * "<<signal[loop+3+ int(samp_offset)]<<"="<< intrpol[loop+2];
    slope[loop+1] = (float)(intrpol[loop+2]- intrpol[loop]); //slope of 2nd point
    
   // cout << "\n\n slope of itp1 " << loop+1 << "th sample  is itp2 - itp \t" <<intrpol[loop+2] << "-" <<intrpol[loop]<<"=" << slope[loop+1] <<"\n";
   myfile << "\n\n slope of itp1 " << loop+1 << "th sample  is itp2 - itp1 \t" <<intrpol[loop+2] << "-" <<intrpol[loop]<<"=" << slope[loop+1] <<"\n";
       slp_amp[loop+1] = (float)(slope[loop+1] * intrpol[loop+1]);// mul with amp of 2nd point
      
     // cout << "\n slope amplitudde of  " << loop+1 << "th sample  is \t" <<slope[loop+1] << "*" <<intrpol[loop+1]<<"=" << slp_amp[loop+1] <<"\n\n\n";
     
     myfile << "\n slope amplitudde of  " << loop+1 << "th sample  is \t" <<slope[loop+1] << "*" <<intrpol[loop+1]<<"=" << slp_amp[loop+1] <<"\n\n\n";
          time_err[int((loop/samp_per_symb)+1)] = slp_amp[loop+1];  
        
       
        all_err=0;count=0;
        //cout<< "\n before add:loop  \t" << "\n avg_err + time_err = " << avg_err <<" + "<< time_err[int((loop/down_samp)+1)];
        //cout<< "\n\n loop begin for last 5 err: all_err="; 
        myfile<< "\n before add:loop  \t" << "\n avg_err + time_err = " << avg_err <<" + "<< time_err[int((loop/down_samp)+1)];
        myfile<< "\n\n loop begin for last 5 err: all_err=";       
       for(int arr=(loop/samp_per_symb)+1; arr>0 && count<5;arr--)
        {
        //cout<< time_err[arr] <<"+";
         myfile<< time_err[arr] <<"+";
          all_err+=time_err[arr];
          count++;
        
          
        }
        
        avg_err= (all_err/(5));
        //cout<< "\n\nall_err="<< all_err << "\t avg_err=" << avg_err;
        //cout<<"\n\n Mu + (avg_err*Mu_const)=  "<< Mu<<" + "<<avg_err<<" * "<<Mu_const<<" = "<< (Mu + avg_err*Mu_const);
        myfile<< "\n\nall_err="<< all_err << "\t avg_err=" << avg_err;
        myfile<<"\n\n Mu + (avg_err*Mu_const)=  "<< Mu<<" + "<<avg_err<<" * "<<Mu_const<<" = "<< (Mu + avg_err*Mu_const);
        Mu = Mu + avg_err*Mu_const;
        //cout << "\n Mu="<< Mu;
        //cout<<"\ntime_err"<< loop <<time_err[loop]<<"\n";
        //printf("%9.5f",time_err[int((loop/down_samp)+1)]);
           printf("%9.5f ", (float)(samp_offset + Mu));
          ofst_mu[int(loop/samp_per_symb)]= (samp_offset + Mu);

        myfile <<"\n calculated_mu="<< (float)(samp_offset + Mu);

}
      myfile<<"\n----------\n";
      myfile<<" the val of all Mu =";
    for(int arr2=(samprate/samp_per_symb)-2; arr2>(samprate/samp_per_symb)-12;arr2--)
        {
           
         myfile<< ofst_mu[arr2] <<"+";
          ofst_mu_al+=ofst_mu[arr2];                 
        }
        
        myfile <<"\n returns= "<< (ofst_mu_al/(10));

        //myfile <<"\n returns="<< (ofst_mu[int((samprate/samp_per_symb)-1)] + ofst_mu[int((samprate/samp_per_symb)-2)])/2;
  myfile<<"\n__________________________________________________________________________________\n";
  myfile<<py_loop_no+1;

 myfile.close();

}

//cmd to compile: g++ temp2.cpp -I ../org/ -o temp2.exe 
//I-> include the path from where it should start looking file, -o -> where o/p should be written 
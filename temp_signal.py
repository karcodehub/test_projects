import math
import random
import subprocess
from locale import atof

import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import butter, freqz, lfilter, sosfilt


def butter_lowpass_filter(data, cutoff, fs, order=5):
    sos = butter(order, cutoff, fs=fs, btype='low', analog=False, output="sos")
    y = sosfilt(sos, data)
    return y

# generate Signal for input
symbol_rate = 1
fs = 400
no_symb= 1000 # no. of symbols
T = symbol_rate * no_symb       # value taken in seconds
n = T * fs # int(T * fs) # indicates total samples

t = np.linspace(0, T, n, endpoint=False)
samp_per_symb=4 # no. of samples per symb to calculate slope, we are considering 1st sample out of 1st 25 samples
up_samp_const = int( fs / symbol_rate)
up_samp= up_samp_const * samp_per_symb # no. of sample per symb to feed the filter 

order = 8 # sin wave can be approx represented as quadratic, symb rate
# fs = up_samp     # total no. of samples 
cutoff = symbol_rate  # desired cutoff frequency of the filter, Hz ,      slightly higher than actual 1.2 Hz
 
# Setting standard filter requirements.

data = np.ndarray((no_symb*up_samp_const), dtype=float)
    # 600= 6 symbol and 100 samples per symbol 
sampled_data = np.ndarray(int((no_symb*samp_per_symb)), dtype=float)
symb = np.ndarray(no_symb, dtype=float)
symb_last = np.ndarray(int(no_symb/samp_per_symb), dtype=float)
mu = 0.35 #interpolating constant
Mu_const=0.05
avg_last=0.0

#mm = np.arange(no_symb, dtype=float)
y_axis = np.arange((up_samp_const), dtype=float)
x_axis = np.arange((up_samp_const), dtype=float)
y1_axis = np.arange((up_samp_const), dtype=float)
x1_axis = np.arange((up_samp_const), dtype=float)
y2_axis = np.arange(no_symb, dtype=float)
x2_axis = np.arange(no_symb-1, dtype=float)

random.seed(0)
for i in range(0, no_symb):
    symb[i] = random.choice([-1, 1])

for i in range(len(symb)):
    data[i*up_samp_const:up_samp_const*(i+1)] = symb[i]

#for i in range(0, no_symb):
 #   mm[i] = (random.randint(0, 10**1)/ 10**1)


# Filtering and plotting
y = butter_lowpass_filter(data, cutoff, fs, order)
#print(len(y))
for i in range(0,int( up_samp_const)): #up_samp_const 400
    sampled_data = y[i::int (up_samp_const/samp_per_symb)] #y 
    
    #sampled_data_down = sampled_data[0::3]
    #np.savetxt('input_sig.txt', [sampled_data], delimiter='\n')
    #with open('C:\\Users\\Karthik Lokesh\\Desktop\\Proj_Arb\\c_arbeit\\input_sig.txt', 'w') as f:
     #   for line in sampled_data:
      #      f.write(line)
       #     f.write('\n')
    #print("__________\n","sampled_data=",len(sampled_data))
    #print(sampled_data) 
    proc = subprocess.Popen([ 
        "C:\\Users\Karthik Lokesh\\Desktop\\Proj_Arb\\interpolator\\temp3.exe", 
        "%f" % len(sampled_data),
        "%f" % mu,
        "%f" % Mu_const,
        "%f" % samp_per_symb,
        "%f" % i], # output to std I/O path 
        stdout=subprocess.PIPE, stdin=subprocess.PIPE)

# Generate 
    bytes = b""
    for sample in sampled_data:
        bytes += b"%f\n" % (np.real(sample)) # each sample of symbol type converting it to float and sending it in bytes (instead of string)
        #print(sample)
    stdout, stderr = proc.communicate(bytes) # wrtings argument to std in to C prog, then wait till excu of process, ret to py.
    #print(stdout)

    output=(stdout.decode("utf-8")) # convert Python bytes object to String
    #print(output)

    output_fl=(output.split())
    plot_fl = []

    plot_fl = [float(x) for x in output_fl]
    #print(plot_fl)
    #y2_axis=plot_fl
    #if (i==30):
     #   plt.plot(x2_axis, y2_axis , marker="+", label = 'mean_alpha')
      #  plt.show()
    symb_last = plot_fl[int(-(100)):]
    print("\n loop=",i,":  mean=",np.mean(symb_last))#last alphas=",symb_last, 
    #print("\n \n loop=",i,"no. of symb", no_symb, "samples per symb", samp_per_symb,"alpha=",mu,"alpha mul_const=", Mu_const)
   # print("\n mean=",np.mean(symb_last), "\t std deviation=", np.std(symb_last) )
    #print('_________________________________________________________________________________________')

    y_axis[i] = np.mean(symb_last)
    #y1_axis= sampled_data_down
    #y1_axis = y1_axis[0:99]   
    x_axis [i] =  i
    y1_axis [i] = np.std(symb_last)
    x1_axis [i] = i
    #mul_error[num]=output[-1]

plt.plot(x_axis, y_axis , marker="+", label = 'mean_alpha')
plt.plot(x1_axis, y1_axis , marker="x", label = 'std_div',linestyle="-.")
#plt.plot(sampled_data, marker="x")
#plt.plot(x2_axis, y2_axis , marker="+", label = 'mean_alpha')
plt.show()

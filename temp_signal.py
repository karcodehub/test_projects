from locale import atof
import math
import numpy as np
import subprocess
from scipy.signal import butter, lfilter, freqz
import matplotlib.pyplot as plt
import random


def butter_lowpass(cutoff, fs, order=5):
    nyq = 0.5 * fs # Nyquist Frequency
    normal_cutoff = cutoff / nyq
    b, a = butter(order, normal_cutoff, btype='low', analog=False)
    return b, a

def butter_lowpass_filter(data, cutoff, fs, order=5):
    b, a = butter_lowpass(cutoff, fs, order=order)
    y = lfilter(b, a, data)
    return y

# Setting standard filter requirements.
order = 10 # sin wave can be approx represented as quadratic, symb rate
fs = 600.0     # total no. of samples 
cutoff = 6  # desired cutoff frequency of the filter, Hz ,      slightly higher than actual 1.2 Hz

b, a = butter_lowpass(cutoff, fs, order)


# generate Signal for input
T = 1.0       # value taken in seconds
n = int(T * fs) # indicates total samples
t = np.linspace(0, T, n, endpoint=False)
no_symb=10 # no. of symbols
samp_per_symb=4 # no. of samples per symb to calculate slope, we are considering 1st sample out of 1st 25 samples
up_samp_const=100
up_samp= up_samp_const * samp_per_symb # no. of sample per symb to feed the filter 
 
data = np.ndarray((no_symb*up_samp), dtype=float) # 600= 6 symbol and 100 samples per symbol 
sampled_data = np.ndarray(int((no_symb*samp_per_symb)), dtype=float)
symb = np.ndarray(no_symb, dtype=float)
symb_last = np.ndarray(int(no_symb/samp_per_symb), dtype=float)
mu = 0.35 #interpolating constant
Mu_const=0.0025
avg_last=0.0

#mm = np.arange(no_symb, dtype=float)
y_axis = np.arange(samp_per_symb*up_samp_const, dtype=float)
x_axis = np.arange(samp_per_symb*up_samp_const, dtype=float)
y1_axis = np.arange(samp_per_symb*up_samp_const, dtype=float)
x1_axis = np.arange(samp_per_symb*up_samp_const, dtype=float)

random.seed(0)
for i in range(0, no_symb):
    symb[i] = random.choice([-1, 1])

for i in range(len(symb)):
    data[i*up_samp:up_samp*(i+1)] = symb[i]

#for i in range(0, no_symb):
 #   mm[i] = (random.randint(0, 10**1)/ 10**1)


# Filtering and plotting
y = butter_lowpass_filter(data, cutoff, fs, order)
#print(len(y))
for i in range(0,int(samp_per_symb*up_samp_const)): #up_samp
    sampled_data = y[i::int (up_samp_const)]
    #sampled_data_down = sampled_data[0::3]
   
    proc = subprocess.Popen([ 
        "C:\\Users\Karthik Lokesh\\Desktop\\Proj_Arb\\interpolator\\temp2.exe", 
        "%f" % len(sampled_data),
        "%f" % mu,
        "%f" % Mu_const,
        "%f" % samp_per_symb], # output to std I/O path 
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

    symb_last = plot_fl[int(-(no_symb/samp_per_symb)):]
    #print("\n \n no. of symb", no_symb, "samples per symb", samp_per_symb,"alpha=",mu,"alpha mul_const=", Mu_const)
   # print("\n mean=",np.mean(symb_last), "\t std deviation=", np.std(symb_last) )
    #print('_________________________________________________________________________________________')

    y_axis[i] = np.mean(symb_last)
    #y1_axis= sampled_data_down
    #y1_axis = y1_axis[0:99]   
    x_axis [i] =  i
    y1_axis [i] = np.std(plot_fl)
    x1_axis [i] = i
    #mul_error[num]=output[-1]

plt.plot(x_axis, y_axis , marker="+", label = 'mean_alpha')
#plt.plot(x1_axis, y1_axis , marker="x", label = 'std_div',linestyle="-.")
#plt.plot(sampled_data, marker="x")
plt.show()

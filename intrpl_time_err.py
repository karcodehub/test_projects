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
no_symb=1000 # no. of symbols
up_samp=100 # no. of sample per symb to feed the filter 
down_samp=25 # no. of samples per symb to calculate slope, we are considering 1st sample out of 1st 25 samples
data = np.ndarray((no_symb*up_samp), dtype=float) # 600= 6 symbol and 100 samples per symbol 
sampled_data = np.ndarray(int((no_symb*up_samp) / down_samp), dtype=float)
symb = np.ndarray(no_symb, dtype=float)
mu = 0.5 #interpolating constant
Mu_const=0.01

#mm = np.arange(no_symb, dtype=float)
y_axis = np.arange(no_symb, dtype=float)
x_axis = np.arange(no_symb, dtype=float)
y1_axis = np.arange(no_symb, dtype=float)
x1_axis = np.arange(no_symb-1, dtype=float)

for i in range(0, no_symb):
    symb[i] = random.choice([-1,1])

for i in range(len(symb)):
    data[i*up_samp:up_samp*(i+1)] = symb[i]

#for i in range(0, no_symb):
 #   mm[i] = (random.randint(0, 10**1)/ 10**1)


#print(symb) 
#print(type(symb))

# Filtering and plotting
y = butter_lowpass_filter(data, cutoff, fs, order)

#for i in range(0,no_symb): #up_samp
sampled_data = y[75::down_samp]
sampled_data_down = sampled_data[0::3]
#print(y1_axis)
    #print(type(len(sampled_data))) # class int
    #print(type(mm[i])) #--> nummpy float
    #print(type(len(mm))) # class int
    #print(len(sampled_data))
proc = subprocess.Popen([ 
     "C:\\Users\Karthik Lokesh\\Desktop\\Proj_Arb\\interpolator\\wrp\\intrpl.exe", 
     "%f" % len(sampled_data),
     "%f" % mu,
     "%f" % Mu_const], # output to std I/O path 
     stdout=subprocess.PIPE, stdin=subprocess.PIPE)

# Generate 
bytes = b""
for sample in sampled_data:
    bytes += b"%f\n" % (np.real(sample)) # each sample of symbol type converting it to float and sending it in bytes (instead of string)
    print(sample)
stdout, stderr = proc.communicate(bytes) # wrtings argument to std in to C prog, then wait till excu of process, ret to py.
#print(stdout)
    #print(len(stdout))
    #print(type(stdout))
output=(stdout.decode("utf-8")) # convert Python bytes object to String
print(output)
    
    #print(type(output))
    #print(len(output))
output_fl=(output.split())
#plot_fl = []

plot_fl = [float(x) for x in output_fl]
#print(plot_fl)
    #print([float(x) for x in output_fl])

    #float_op= atof(output)
    #print(float(output[-1]))
    #for i in symb:
        #print(float_op[i])

    #er = stdout.split(b"\t")
    
    #error= float(er[-1])
        
    #print((er[-1]))
    #err=struct.unpack('b',b'5.0817e-0080.6709371.01240.9985311.000520.20916')
    #print(err)
    #print(error)
#print('_________________________________________________________________________________________')

y_axis = plot_fl
y1_axis= sampled_data_down
y1_axis = y1_axis[0:99]   
 #x_axis [i] =  i
    #y1_axis [i] = 
    #x1_axis [i] = i
    #mul_error[num]=output[-1]

plt.plot(x_axis, y_axis , marker="+", label = 'interpolator')
#plt.plot(x1_axis, y1_axis , marker="x", label = 'lowpass',linestyle="-.")
#plt.plot(sampled_data, marker="x")
plt.show()
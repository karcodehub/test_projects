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
symbol_rate = 1 # rate at which generated symb as to be generated
fs = 400 # total no. of samples per symb (ouput of lowpass filter)
no_symb= 1000 # no. of symbols
T = symbol_rate * no_symb #       # value taken in seconds
n = T * fs # int(T * fs) # indicates total samples in a gen signal

t = np.linspace(0, T, n, endpoint=False)
samp_per_symb=4 # no. of samples per symb before upsampling( before low pass filter)
up_samp_const = int( fs / symbol_rate)
up_samp= up_samp_const * samp_per_symb # no. of sample per symb to feed the filter 

order = 8 # sin wave can be approx represented as quadratic, symb rate
cutoff = symbol_rate  # desired cutoff frequency of the filter, Hz ,      slightly higher than actual 1.2 Hz
 
# Setting standard filter requirements.

data = np.ndarray((no_symb*up_samp_const), dtype=float) # gen signal ip to lowpass 400*1000
sampled_data = np.ndarray(int((no_symb*samp_per_symb)), dtype=float)#4*1000
symb = np.ndarray(no_symb, dtype=float)
symb_last = np.ndarray(int(no_symb/samp_per_symb), dtype=float)
mu = 0.35 #interpolating constant quad&cubic=0.5
Mu_const=0.045 # quad&cubic=0.125
avg_last=0.0

y_axis = np.arange((up_samp_const * no_symb), dtype=float) # 400
x_axis = np.arange(up_samp_const * no_symb, dtype=float)#x_axis = np.arange((up_samp_const), dtype=float)
y1_axis = np.arange((up_samp_const * no_symb), dtype=float)
x1_axis = np.arange(up_samp_const * no_symb, dtype=float) #x1_axis = np.arange((up_samp_const), dtype=float)
y2_axis = np.arange(no_symb-2, dtype=float) # -1
x2_axis = np.arange(no_symb-2, dtype=float)# -2 for quad and cubic --> in loop:samprate-samp_per_symb-4, -4 because we consider 6 samples for 1 cal of delat oe beta
y3_axis = np.arange(up_samp_const, dtype=float) # -1
x3_axis = np.arange(up_samp_const, dtype=float)
y4_axis = np.arange(up_samp_const, dtype=float) # -1
x4_axis = np.arange(up_samp_const, dtype=float)

random.seed(0) # randomness is const=> each time similar type of signal gen
for i in range(0, no_symb):
    symb[i] = random.choice([-1, 1])

for i in range(len(symb)):
    data[i*up_samp_const:up_samp_const*(i+1)] = symb[i]

#1st->loc - (Mean) where the peak of the bell exists.
#2->scale - (Standard Deviation) how flat the graph distribution should be.
#3->size - The shape of the returned array.


#for i in range(0, no_symb):
 #   mm[i] = (random.randint(0, 10**1)/ 10**1) # various mu are generated


# Filtering and plotting
y = butter_lowpass_filter(data, cutoff, fs, order) # print(len(y))= 400000
#1st is the NumPy array, containing the sample data.
#2nd is the axis along which the mean can be calculated, Its default value is 0.
#3rd is the degree of freedom which is a correction to the standard deviation.
def signaltonoise(a, axis, ddof):
	a = np.asanyarray(a)
	m = a.mean(axis)
	sd = a.std(axis = axis, ddof = ddof)
	return np.where(sd == 0, 0, m / sd)

random.seed(0)
noise = np. random. normal(0, .1, y.shape)
data_noise = y + noise

snr= (np.std(data_noise) / np.std(noise))
print("snr_db=", 20 * np.log10(snr))
for i in range(0,int( up_samp_const)): #up_samp 400 loops
    sampled_data = data_noise[i::int (up_samp_const/samp_per_symb)] # 400/4 , print(len(sampled_data))= 4000
    
    #np.savetxt('input_sig.txt', [sampled_data], delimiter='\n')
    #with open('C:\\Users\\Karthik Lokesh\\Desktop\\Proj_Arb\\c_arbeit\\input_sig.txt', 'w') as f:
     #   for line in sampled_data:
      #      f.write(line)
       #     f.write('\n')
    #print("__________\n","sampled_data=",len(sampled_data))
    #print(sampled_data) 
    proc = subprocess.Popen([ 
        "C:\\Users\Karthik Lokesh\\Desktop\\Proj_Arb\\interpolator\\wrp\\cubic_intrpl.exe", 
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
    #print("len of plot_fl=",len(plot_fl))
    #y2_axis=[plot_fl[i] for i in range(len(plot_fl)) if i % 2 != 0]
    y2_axis=plot_fl
    symb_last = plot_fl[int(-(200)):]
    non_convg=plot_fl[::-1]
    #non_convg=plot_fl[-700:]
    non_convg_idx = np.where((non_convg > (np.mean(symb_last)+0.05)) | (non_convg < (np.mean(symb_last)-0.05)))
    #print((non_convg_idx))
    non_convg_val=(non_convg_idx[0])
    if (len(non_convg_val) != 0):

        #print((non_convg_val))
       # print("len of non_convg_val=",len(non_convg_val))
        y3_axis[i]= (998- int(non_convg_val[0]))
    else:
        y3_axis[i]=000
    #y3_axis[i]= len(non_convg_idx[0])
    x3_axis[i]=i
    snr= (np.std(sampled_data) / np.std(noise))
    #print("snr_db=", 20 * np.log10(snr))
    print("\n loop=",i,":  std=",20 * np.log10(snr))
    # if (i==104 or i==107 or i==109 or i==108 or i==307):
    #    plt.plot(x2_axis, y2_axis , marker="+", label = 'mean_alpha')
    #    plt.legend(loc="upper right")
    #    plt.xlabel("time offest",color='b')
    #    plt.ylabel("Time-error for all symbs(1k)", color='b')
    #    plt.grid(color = 'green', linestyle = '--', linewidth = 0.5)
    #    plt.show()#last alphas=",symb_last, 
    #print("\n \n loop=",i,"no. of symb", no_symb, "samples per symb", samp_per_symb,"alpha=",mu,"alpha mul_const=", Mu_const)
   # print("\n mean=",np.mean(symb_last), "\t std deviation=", np.std(symb_last) )
    #print('_________________________________________________________________________________________')
    
    y_axis[i] = np.mean(symb_last)
    #y1_axis= sampled_data_down
    #y1_axis = y1_axis[0:99]   
    #x_axis [i] =  i
    y1_axis [i] = np.std(symb_last)
    #x1_axis [i] = i
    #mul_error[num]=output[-1]
    
    snr= (np.std(plot_fl) / np.std(noise))
    x4_axis[i]= 20 * np.log10(snr)

    y4_axis[i]= np.std(plot_fl)
#-----------
#snr= (np.std(sampled_data) / np.std(noise))
#print("snr_db=", 20 * np.log10(snr))

std= np.std(plot_fl)
# plt.subplot(3,1,1)
# plt.plot(x_axis, y , marker="+", label = 'Pure_signal', color='b')
# plt.legend(loc="upper left")
# plt.xlabel("No. of symbs",color='b')
# plt.ylabel("Amplitude", color='b')
# plt.grid(color = 'green', linestyle = '--', linewidth = 0.5)




# plt.subplot(3,1,2)
# plt.plot(x1_axis, y1_axis , marker="x", label = 'std_div',linestyle="-.", color='c')
# plt.legend(loc="upper left")
# plt.xlabel(" time offest ", color='c')
# plt.ylabel("Std-div for all symbs(1k)", color='c')
# plt.grid(color = 'green', linestyle = '--', linewidth = 0.5)

# plt.subplot(3,1,2)
# plt.plot(x1_axis, noise , marker="x", label = 'Noise signal',linestyle="-.", color='c')
# plt.legend(loc="upper left")
# plt.xlabel(" No. of symbs ", color='c')
# plt.ylabel("Amplitude of Noise", color='c')
# plt.grid(color = 'blue', linestyle = '--', linewidth = 0.5)

# plt.subplot(3,1,3)
# plt.plot(x1_axis, data_noise , marker="+", label = "Noise_generation_std=0.1" , color='b')
# plt.legend(loc="upper left")
# plt.xlabel("No. of symbs ", color='c')
# plt.ylabel("Amplitude of Signal+Noise", color='c')
# plt.grid(color = 'green', linestyle = '--', linewidth = 0.5)

# plt.subplot(3,1,3)
# plt.plot(x4_axis, y4_axis , marker="+", label = "Noise_generation_std=0.1" , color='b')
# plt.legend(loc="upper left")
# plt.xlabel("SNR ", color='c')
# plt.ylabel("STD Dev", color='c')
# plt.grid(color = 'green', linestyle = '--', linewidth = 0.5)

# #plt.plot(sampled_data, marker="x")
# #plt.plot(x2_axis, y2_axis , marker="+", label = 'mean_alpha')

# plt.suptitle("Cubic Interpolator")
# plt.grid(color = 'green', linestyle = '--', linewidth = 0.1)

plt.plot(x3_axis, y3_axis , marker="+", label = "noise= 0.4" , color='b')
plt.legend(loc="upper right")
plt.xlabel(" time offest ", color='c')
plt.ylabel("Index of last Symbol rejected", color='c')
plt.title("Noise-Quad corridor=0.1, Mu=.35 Mu_const=0.45" , loc = 'left')


#plt.title("SNR of Signal" , loc = 'left')
plt.show()

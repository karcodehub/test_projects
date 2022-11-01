import math
import struct
import numpy as np
import subprocess
import matplotlib.pyplot as plt

symrate = 2 #freq or symbol rate (for a duration [1 here] how many symbol are generated)
#cutoffrq = symrate
samplpersym = 4 #(how many samples to be considered for per symbol)
duration = 1 # within this time entire signal should be processed
samprate = symrate * samplpersym #      2 * 4



# generate Signal for input
#no_rept = int(duration * symrate / len(sym))
#signal = np.repeat(np.tile(sym, no_rept), samplpersym)
time = 1/samprate * np.arange(int(samprate * duration)) #
timeError=.002
no_signal=12
y_axis = np.arange(no_signal, dtype=float)
x_axis = np.arange(no_signal, dtype=float)
for num in range(1,no_signal):

    signal=.5 * np.sin((2 * np.pi * symrate * time) + num*2*np.pi/no_signal) + .5 # shifting plane to positive adding .5
#((np.pi)/2)) is phase difference added on purpose to time errpr detection
#print(signal)
    #print(signal)
    print(f'\n\nthe signal with phase diff of',math.degrees(num*2*np.pi/no_signal))
    proc = subprocess.Popen([
        "C:\\Users\Karthik Lokesh\\Desktop\\Proj_Arb\\generate\\wrp\\time_error.exe", "%f" % (samprate)],
        stdout=subprocess.PIPE, stdin=subprocess.PIPE)

# Generate Input
    bytes = b""
    for sample in signal:
        bytes += b"%f\n" % (np.real(sample)) # each sample of symbol type converting it to float and sending it in bytes (instead of string)

    stdout, stderr = proc.communicate(bytes) # wrtings argument to std in to C prog, then wait till excu of process, ret to py.

    #output=(stdout.decode("utf-8")) # convert Python bytes object to String
    #print(stdout)
    er = stdout.split(b"\t")
   
    error= float(er[-1])
    
    print(float(er[-1]))
    #err=struct.unpack('b','byt')
    #print(err)
    y_axis[num]=error
    x_axis[num] = num*360/no_signal
    #mul_error[num]=output[-1]

print(y_axis)
print(x_axis)
plt.plot(x_axis, y_axis , marker="s")
plt.show()

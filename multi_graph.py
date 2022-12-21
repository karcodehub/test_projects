import matplotlib.pyplot as plt
import numpy as np


y_axis = np.arange(20, dtype=float) # 400
x_axis = np.arange(50,1050,50, dtype=float)#x
y1_axis = np.arange(20, dtype=float) # 400
y2_axis = np.arange(20, dtype=float) # 400
y3_axis = np.arange(20, dtype=float) # 400
y4_axis = np.arange(20, dtype=float) # 400
y5_axis = np.arange(20, dtype=float) # 400
#print(x_axis)
#------------------Data:Mu_Const=0.04 and Noise_std=0.1-------------------
y_axis= [11,19,13,8,5,4,8,3,24,12,8,8,4,72,12,29,25,40,24,71]
y1_axis= [10,20,16,1,13,8,8,0,16,32,4,16,20,72,28,32,8,24,20,52]
y2_axis= [2,1,4,5,0,4,0,0,12,8,4,8,4,92,24,40,32,36,48,76]
y3_axis= [5,7,0,0,0,3,1,8,16,8,24,16,31,33,32,39,29,35,33,80]
y4_axis= [13,38,14,5,5,2,10,9,0,8,8,16,16,80,28,48,24,12,28,36]
y5_axis= [11,24,6,9,1,9,4,0,12,8,0,28,13,107,48,32,8,16,13,51]
#------------------------------------------------------------------------------
#-------Mu_Const=0.025 and Noise_std=0.1----------------------------
# y_axis= [18,36,55,20,29,11,19,18,45,21,12,16,0,48,24,4,8,4,4,8]
# y1_axis= [17,62,68,50,21,17,8,6,23,20,24,16,8,32,8,8,4,4,4,0]
# y2_axis= [19,64,67,33,14,16,3,8,28,8,8,36,8,24,20,20,0,8,0,16]
# y3_axis= [14,51,47,30,4,11,4,23,23,16,13,8,4,56,40,20,15,4,4,13]
# y4_axis= [21,52,83,59,25,18,12,11,5,8,18,16,6,34,16,8,4,4,0,0]
# y5_axis= [23,51,79,55,31,26,7,2,13,13,16,12,12,27,13,11,1,0,0,8]
#-------------------------------------------------------------------------------
plt.xticks(np.arange(50,1050,50, dtype=float))

plt.plot(x_axis, y_axis , marker="+", label = "cubic-Der" , color='b')
plt.plot(x_axis, y1_axis , marker="+", label = "cubic-EL" , color='g')
plt.plot(x_axis, y2_axis , marker="+", label = "Quad-EL" , color='r')
plt.plot(x_axis, y3_axis , marker="+", label = "Quad-Der" , color='c')
plt.plot(x_axis, y4_axis , marker="+", label = "Lin-Der" , color='m')
plt.plot(x_axis, y5_axis , marker="+", label = "Lin-EL" , color='y')
plt.legend(loc="upper left")

plt.xlabel("Last Symbol Corridor ", color='c')
plt.ylabel("Total symbs", color='c')
plt.grid(color = 'green', linestyle = '--', linewidth = 0.5)

#plt.title("Mu_Const=0.025 and Noise_std=0.1" , loc = 'left')
plt.title("Mu_Const=0.04 and Noise_std=0.1" , loc = 'left')
plt.show()
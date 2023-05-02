import matplotlib.pyplot as plt
import pandas as pd
import sys


data1 = pd.read_csv(sys.argv[1])
data2 = pd.read_csv(sys.argv[2])
#data3 = pd.read_csv(sys.argv[3])

label1 = sys.argv[1].split('_results')[0]
label2 = sys.argv[2].split('_results')[0]
#label3 = sys.argv[3].split('_results')[0]



x1 = data1['n'].values
y1 = data1['time[ms]'].values

x2 = data2['n'].values
y2 = data2['time[ms]'].values

#x3 = data3['n'].values
#y3 = data3['time[ms]'].values

plt.plot(x1, y1, label=label1)
plt.plot(x2, y2, label=label2)
#plt.plot(x3, y3, label=label3)

plt.legend(title='Algoritmos', title_fontsize='large', fontsize='medium')

plt.xlabel('n')
plt.ylabel('time[ms]')

plt.title('Line Plot for Matrix Multiplication')

plt.show()

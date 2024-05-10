import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import linregress
from scipy.optimize import curve_fit

# Task 1
data = np.loadtxt('histo_data.txt')

# histogram
bin_size = 0.1
num_bins = int((np.max(data) - np.min(data)) / bin_size)
hist, bins, _ = plt.hist(data, bins=num_bins, density=True, alpha=0.6, color='#0437F2',label='Data')
bin_centers = (bins[:-1] + bins[1:]) / 2

# exponential fitting
def exp(x, a, b):
    return a * np.exp(-b * x)

params, _ = curve_fit(exp, bin_centers, hist)
x = np.linspace(np.min(data), np.max(data), num_bins)
plt.plot(x, exp(x, *params), color='#F33A6A', linewidth=1.8, label=f'Exponential fit: y={params[0]:.2f}e^(-{params[1]:.2f}x)')
plt.title('Histogram with Exponential Fit')
plt.legend()
plt.savefig('histo_result.pdf')
plt.show()


# Task 2 (b)
column_names = ['t', 'A', 'B', 'C']
data = pd.read_csv('thoron_decay.txt',  delim_whitespace=True, skiprows=4, names=column_names)

# average
data['average_count_rate'] = (data['A'] + data['B'] + data['C']) / 3.
data['ln_average_count_rate'] = np.log(data['average_count_rate'])

# time intervall [100 : 300]s
filtered_data = data[(data['t'] >= 100) & (data['t'] <= 300)]

# linear fit
slope, intercept, r_value, p_value, std_err = linregress(filtered_data['t'], filtered_data['ln_average_count_rate'])

# plot
fig, ax = plt.subplots()

ax.scatter(data['t'], data['ln_average_count_rate'], label='Log of average count rate', color='#6495ED')
ax.plot(filtered_data['t'], intercept + slope * filtered_data['t'], color = '#FFBF00',linewidth=3, label=f'Linear fit: y={intercept:.2f}+{slope:.2f}x')

ax.set_xlabel('Time [s]')
ax.set_ylabel('Average Count Rate [ln(1/s)]')
ax.set_title('Count Rate Over Time with Linear Fit')
ax.legend()

plt.savefig('decay_result.pdf')
plt.show()


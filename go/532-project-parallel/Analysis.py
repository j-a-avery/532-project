
# coding: utf-8

# # CSCI 532 Semester Project
# 
# James Avery

# ## Problem #3
# 
# >Write a C/C++/Matlab/Java program to compute insertion sort and merge sort. (You can use the code from the textbooks by Deitel and Deitel or from the web.) Obtain the run time of both routines.
# 
# >The input data should be an int array containing random element values (between, say, 0 and 1023). Obtain run time T with 1D (input) array of size of $n = 16$, $256$, $4096$, $65536$, $1048576$ (i.e. $2^p$, where $p = 4$, $8$, $12$, $16$, $20$). The run time for each $n$ should be averaged with about $\left\lfloor{\frac{512}{p \times p}}\right\rfloor$ runs. Each run for a given $n$ should use a different random input.
# 
# >Plot (with Excel, Matlab, or other available tools) the run time for both routines on one plot, with the $x$ axis in $p$ values, and $y$ axis in $\log{T}$. Label on the plot which curve is for insertion sort and which is for merge sort.
# 
# >Submit C/C++ programs and plot, with instructions in readme.txt on how to build and run the program. (Include the Dev-C++/MS Visual Studio/Java NetBeans project file.)

# In[2]:


import numpy as np
import matplotlib.pyplot as plt
import datetime
from IPython.display import Markdown


# ## Step 1: Run the program

# In[3]:


#Run the program
print("Starting run at {}.\n".format(str(datetime.datetime.now())))

get_ipython().run_line_magic('time', '!./project equal-batches demo')

print("\nFinished run at {}.\n".format(str(datetime.datetime.now())))


# Just to be safe, list the contents of the directory to make sure the data files exist.

# In[3]:


get_ipython().system('ls *.csv')


# ## Step 2: Prepare the data for processing

# Load the run-times into numpy arrays for processing.
# 
# **Note that this will only work if the program was run with the `equal-batches` flag set.** Numpy requires that each row have the same number of columns.

# In[4]:


insertion = np.loadtxt(
    './insertionsort.csv', dtype='int64', delimiter=',')
merge = np.loadtxt(
    './mergesort.csv', dtype='int64', delimiter=',')


# The data is stored in rows of the format $n, r_1, r_2, \ldots r_i$, where $n$ is the size of the array, and $r_i$ is the run-time in nanoseconds of the $i^{\textrm{th}}$ run, so a little data muging is necessary. The first column becomes the labels, and the subsequent columns are retained as data.

# In[5]:


insertion_labels = insertion[:, 0]
insertion = insertion[:, 1:]
merge_labels = merge[:, 0]
merge = merge[:, 1:]


# The `*_labels` arrays *should* contain exactly the same data. If they don't, something has gone wrong. If they do, then it's safe to remove one of them and just use the other for all labels.

# In[6]:


if not np.all(insertion_labels == merge_labels):
    raise ValueError(
        "The two data sets were not tested on arrays of the same sizes." +
            "\n\tInsertion Sort was tested with arrays of sizes:\n\t\t" +
            str(insertion_labels) +
            "\n\tMerge Sort was tested with arrays of sizes:\n\t\t" +
            str(merge_labels))
else:
    labels = insertion_labels.copy()
    del merge_labels, insertion_labels


# Find the means of each run-time

# In[7]:


insertion_mean, merge_mean = insertion.mean(axis=1), merge.mean(axis=1)


# ## Step 3: Graph results

# In[43]:


plt.rcParams['figure.figsize'] = [10, 10]
plt.plot(labels, insertion_mean, label='Insertion Sort')
plt.plot(labels, merge_mean, label='Merge Sort')
plt.legend()
plt.xscale('log')
plt.yscale('log')
plt.xlabel("Array size $n$")
plt.ylabel('Run Time (ns)')
plt.title("Average Run Times of Insertion Sort and Merge Sort Compared")

table = "| $n$ | Insertion Sort | Merge Sort |\n|:---|:---:|:---:|\n"
for i in range(len(labels)):
    table += "| {n} | {ins:.5} | {ms:.5} |\n".format(
        n=labels[i], 
        ins=insertion_mean[i], 
        ms=merge_mean[i]
    )
Markdown(table)


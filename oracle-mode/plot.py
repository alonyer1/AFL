import matplotlib.pyplot as plt
import numpy as np
import argparse

dic = {"0": "00"}
for i in range(1,13):
    dic[str(i)] = str(i-1)
def medians(input_files):
    data = []  # This will hold the data read from each file
    for i in input_files:
        file = prefix + dic[str(i)] + ".txt"
        with open(file, 'r') as f:
            print("file",i,"loaded.\n")
            numbers = list(map(float, f.readlines()[1:]))  # Read numbers, starting from second line
            data.append(numbers)
    print("\nAverages:")
    for arr in data:
        print(np.average(arr))
    print("\nMedians:")
    for arr in data:
        print(np.median(arr))
    print("\nDeviations:")
    for arr in data:
        print(np.std(arr))
    
                
    
def histogram(bucket_size, prefix, input_files):
    data = []  # This will hold the data read from each file
    min_value = float('inf')
    max_value = float('-inf')
    
    for i in input_files:
        file = prefix + dic[str(i)] + ".txt"
        with open(file, 'r') as f:
            print("file",i,"loaded.\n")
            numbers = list(map(float, f.readlines()[1:]))  # Read numbers, starting from second line
            data.append(numbers)
            min_value = min(min_value, min(numbers))  # Track min and max across all files
            max_value = max(max_value, max(numbers))

    # Compute the bucket edges (these are shared across all histograms)
    bins = np.arange(min_value, 500, bucket_size)
    #bins = np.append(bins, max_value)  # Make sure the max value falls within the last bin
    fig, ax1 = plt.subplots()
    print("Buckets arranged.\n")
    # Plot the histograms
    colors = ['red', 'yellow', 'blue', 'purple']
    #ax1.hist(data,bins, label=[f'Difference at location {input_files[i]}' for i in range(len(data))])
    for i in range(len(data)):
        ax1.hist(data[i], bins, alpha=0.5, label=f'Difference at index {input_files[i]}')
        print("Buckets arranged.\n")
    ax2 = ax1.twinx()
    ax2.set_ylabel("frequency (%)",fontsize=18)
    #ax2.tick_params(axis='y')
    #ax2.hist(data2,bins, alpha=1.0, label=[f'String difference at location {i}' for i in range(len(data))])
    ax1.set_ylim(0, 100000)
    ax2.set_ylim(0, 100)
    print("Buckets arranged2.\n")
    #plt.yscale('log')
    ax1.set_xlabel("Function execution time (#cycles)", fontsize=18)
    ax1.set_ylabel("Number of calls",fontsize=18)
    ax1.legend(fontsize=14)
    plt.title("Runtime of a function that compares 2 strings char-by-char\n(Intentional branch misses)", fontsize=20)
    plt.show()

if __name__ == "__main__":
    prefix = "results/cache3-"
    input_files= range(0,13,2)
    histogram(1, prefix, input_files)
    medians(input_files)

import matplotlib.pyplot as plt
import scipy.stats as stats
import numpy as np
import argparse

dic = {"0": "00"}
colors = ['b','g','r','c','m','y','k','saddlebrown','orchid','purple','peru','grey','orange']
#random.shuffle(colors)
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
    #ax1.hist(data,bins, label=[f'Difference at location {input_files[i]}' for i in range(len(data))])
    for i in range(len(data)):
        ax1.hist(data[i], bins, alpha=0.5, color=colors[input_files[i]], label=f'Difference at index {input_files[i]}')
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

def histogramSteps(bucket_size, prefix, input_files):
    data = []  # This will hold the data read from each file
    min_value = float('-inf')
    max_value = float('inf')
    
    for i in input_files:
        file = prefix + dic[str(i)] + ".txt"
        with open(file, 'r') as f:
            print("file",i,"loaded.\n")
            numbers = [int(line) for line in f.readlines()[1:]]
            data.append(numbers)
            min_value = min(min_value, min(numbers))  # Track min and max across all files
            max_value = max(max_value, max(numbers))

    # Compute the bucket edges (these are shared across all histograms)
    bins = np.arange(0, 500+bucket_size, bucket_size)
    #bins = np.append(bins, max_value)  # Make sure the max value falls within the last bin
    fig, ax1 = plt.subplots()
    print("Buckets arranged.\n")
    # Plot the histograms
    
    #ax1.hist(data,bins, label=[f'Difference at location {input_files[i]}' for i in range(len(data))])
    for i in range(len(data)):
        ax1.hist(data[i], bins, alpha=1, color=colors[input_files[i]], label=f'Difference at index {input_files[i]}', histtype="step")
        print("Buckets arranged.\n")
    ax1.set_xlim(250, 390)
    ax2 = ax1.twinx()
    ax2.set_ylabel("frequency (%)",fontsize=14)
    #ax2.tick_params(axis='y')
    #ax2.hist(data2,bins, alpha=1.0, label=[f'String difference at location {i}' for i in range(len(data))])
    ax1.set_ylim(0, 40000)
    ax2.set_ylim(0, 40)
    print("Buckets arranged2.\n")
    #plt.yscale('log')
    ax1.set_xlabel("Function execution time (#cycles)", fontsize=14)
    ax1.set_ylabel("Number of calls",fontsize=14)
    ax1.legend(fontsize=12)
    #plt.title("Runtime of a function that compares 2 strings char-by-char\n(Intentional branch misses)", fontsize=20)
    #plt.show()

def candlesticks(prefix, input_files):
    data = []  # This will hold the data read from each file
    for i in input_files:
        file = prefix + dic[str(i)] + ".txt"
        with open(file, 'r') as f:
            print("file",i,"loaded.\n")
            numbers = [int(line) for line in f.readlines()[1:]]
            data.append(numbers)
    fig, ax = plt.subplots()
    for i, sample in enumerate(data):
        # Calculate statistics
        mean = np.mean(sample)
        print("mean:"+str(mean))
        ci_low, ci_high = stats.t.interval(df=len(sample)-1, loc=mean, scale=stats.sem(sample), confidence=0.95)
        ci_low2, ci_high2 = stats.t.interval(df=len(sample)-1, loc=mean, scale=stats.sem(sample), confidence=0.999)

        # Plot the range as a vertical line
        ax.vlines(i, ci_low2, ci_high2, color='black', linestyle='dotted')

        # Plot the confidence interval as a bar
        ax.vlines(i, ci_low, ci_high, color='blue', alpha=0.5, linewidth=10)

        # Plot the mean as a horizontal line
        ax.hlines(mean, i-0.1, i+0.1, color='red', linewidth=2)

    # Set x ticks
    ax.set_xticks(range(len(data)))
    ax.set_xticklabels(['Difference\nat {}'.format(input_files[i]) for i in input_files])
    # Set labels
    #ax.set_xlabel('Sample')
    ax.set_ylabel('Time measure (#cycles)', fontsize=18)
    plt.title("Runtime of a function that compares 2 strings char-by-char (branch mispredictions)", fontsize=20)
    # Display the plot
    plt.show()



if __name__ == "__main__":
    prefix = "results/"
    '''for i in range(11):
        plt.clf()
        input_files = [i,i+2]
        histogramSteps(2, prefix, input_files)
        plt.savefig(f'plots/plotplot{i}.png')'''
    input_files = range(0,13)
    candlesticks(prefix, input_files)
    #medians(input_files)

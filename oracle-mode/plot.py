import matplotlib.pyplot as plt
import numpy as np

def histogram(bucket_size, input_files):
    data = []  # This will hold the data read from each file
    data2 = []
    min_value = float('inf')
    max_value = float('-inf')
    
    for i, file in enumerate(input_files):
        with open(file, 'r') as f:
            print("file",i,"loaded.\n")
            numbers = list(map(float, f.readlines()[1:]))  # Read numbers, starting from second line
            numbers2 = [t/1000.0 for t in numbers]
            data.append(numbers)
            data2.append(numbers2)
            min_value = min(min_value, min(numbers))  # Track min and max across all files
            max_value = max(max_value, max(numbers))

    # Compute the bucket edges (these are shared across all histograms)
    bins = np.arange(min_value, 500, bucket_size)
    #bins = np.append(bins, max_value)  # Make sure the max value falls within the last bin
    fig, ax1 = plt.subplots()
    print("Buckets arranged.\n")
    # Plot the histograms
    colors = ['red', 'yellow', 'blue', 'purple']
    #ax1.hist(data,bins, label=[f'String difference at location {i*5}' for i in range(len(data))])
    for i in range(len(data)):
        ax1.hist(data[i], bins, alpha=0.5, label=f'String difference at location {i}')
        print("Buckets arranged.\n")
    ax2 = ax1.twinx()
    ax2.set_ylabel("% of all calls to 'func'",fontsize=18)
    #ax2.tick_params(axis='y')
    #ax2.hist(data2,bins, alpha=1.0, label=[f'String difference at location {i}' for i in range(len(data))])
    ax1.set_ylim(0, 100000)
    ax2.set_ylim(0, 100)
    print("Buckets arranged2.\n")
    #plt.yscale('log')
    ax1.set_xlabel("\nDelta of time before and after function execution (#cycles)", fontsize=18)
    ax1.set_ylabel("Number of calls to 'func'",fontsize=18)
    ax1.legend(fontsize=14)
    plt.title("Runtime of a function that compares 2 strings char-by-char\n(Intentional cache misses)", fontsize=20)
    plt.show()

if __name__ == "__main__":
    input_files=["results/00.txt"]
    for i in range(0,10,2):
        input_files.append("results/"+str(i)+".txt")
    histogram(1, input_files)

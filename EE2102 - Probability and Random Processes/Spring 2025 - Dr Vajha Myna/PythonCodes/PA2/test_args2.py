import sys
import pandas as pd

def process_csv(file_path):
    # Read and display the CSV file
    try:
        df = pd.read_csv(file_path, skiprows=0)
        print("Reading contents of ",  file_path, ":\n")
        return df;
    except Exception as e:
        print("Error reading CSV file: {e}")

if __name__ == "__main__":        
    # total arguments
    n = len(sys.argv)
    print("Total arguments passed:", n)

    # Arguments passed
    print("\nName of Python script:", sys.argv[0])

    print("\nArguments passed:",n)
    assert(n >= 2)

    mu_x = int(sys.argv[1]);
    print("mean of X", mu_x)

    var_x = int(sys.argv[2]);
    print("Variance of X", var_x)

    #read the mmse samples file
    input_fn= sys.argv[3];
    print(input_fn)
    mmse_samples = process_csv(input_fn);
    print(mmse_samples)
    N = len(mmse_samples);
    print("N=",N);
    mmse_samples_array = mmse_samples.to_numpy();
    print(mmse_samples_array)
    # prints below 0th sample value
    print(mmse_samples_array[0][0])
    #prints below sigmasquare corresponding to 0th sample
    print(mmse_samples_array[0][1])
    #similarly parse the third argument if mode is 0 or 1 to get p or lambda


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

    mode_value = int(sys.argv[1]);
    print("Testing mode:", mode_value)

    #read the samples file
    input_fn= sys.argv[2];
    uniform_samples = process_csv(input_fn);
    print(uniform_samples)
    N = len(uniform_samples);
    print("N=",N);
    #similarly parse the third argument if mode is 0 or 1 to get p or lambda


import argparse as ap
import os
import matplotlib.pyplot as plt
import numpy as np

# Globals
x_done = False

def main():
    parser = ap.ArgumentParser(description='Take in Config file names')
    parser.add_argument('-n', '--hbm_none_fName', help='Name of config file for HBM simulation with no ECC')
    parser.add_argument('-b', '--hbm_bch_fname', help='Name of config file for HBM simulation with BCH ECC')
    parser.add_argument('-r', '--hbm_RS_fName', help='Name of config file for HBM simulation with Reed Solomon ECC')
    args = parser.parse_args()

    # booleans to determine which simulations run
    # can be expanded later to include other ECC schemes
    HBM_none = False
    HBM_BCH = False
    HBM_RS = False

    # run simulation for config files
    for name in vars(args):
        if name != None:
            if(name == 'hbm_none_fName' and getattr(args, name) != None):
                print('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_none_out.txt')
                os.system('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_none_out.txt')
                HBM_none = True
            elif(name == 'hbm_BCH_fName' and getattr(args, name) != None):
                print('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_BCH_out.txt')
                os.system('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_BCH_out.txt')
                HBM_BCH = True
            elif(name == 'hbm_RS_fName' and getattr(args, name) != None):
                print('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_RS_out.txt')
                os.system('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_RS_out.txt')
                HBM_RS = True
            else:
                print('No simulation run for ' + str(name))

    x = []
    # x_none = []
    y_none = []
    # x_BCH = []
    y_BCH = []
    # x_RS = []
    y_RS = []

    if(HBM_none):
        read_results(x, y_none, 'HBM_none_out.txt')
        y_none = np.array(y_none)
    if(HBM_BCH):
        read_results(x, y_BCH, 'HBM_BCH_out.txt')
        y_BCH = np.array(y_BCH)
    if(HBM_RS):
        read_results(x, y_RS, 'HBM_RS_out.txt')
        y_RS = np.array(y_RS)

    x = np.array(x)
    if(HBM_none):
        plt.plot(x, y_none, color='red', label='HBM_none')
    if(HBM_BCH):
        plt.plot(x, y_BCH, color='blue', label='HBM_BCH')
    if(HBM_RS):
        plt.plot(x, y_RS, color='green', label='HBM_RS')

    plt.legend(loc='upper left')
    plt.title("Comparison of Different ECC Schemes", fontsize=16, fontweight='bold')
    plt.xlabel("Weeks")
    plt.ylabel("P(Fault-Cumu)")
    plt.show()


def read_results(x, y, fName):
    global x_done
    with open(fName, 'r') as f:
        f.readline()  # read the first line that holds the column names
        lines = f.readlines()
        for line in lines:
            if x_done == False:
                x.append(line.split(',')[0])  # x is set to weeks
            y.append(line.split(',')[4])  # y is set to P(Fault-Cumu)
        x_done = True


if __name__ == "__main__":
    main()
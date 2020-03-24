import argparse as ap
import os

def main():
    parser = ap.ArgumentParser(description='Take in Config file names')
    parser.add_argument('-n', '--hbm_none_fName', help='Name of config file for HBM simulation with no ECC')
    parser.add_argument('-b', '--hbm_bch_fname', help='Name of config file for HBM simulation with BCH ECC')
    parser.add_argument('-r', '--hbm_RS_fName', help='Name of config file for HBM simulation with Reed Solomon ECC')
    args = parser.parse_args()

    # run simulation for config files
    for name in vars(args):
        print(name)
        if name != None:
            if(name == 'hbm_none_fName'):
                print('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_none_out.txt')
                os.system('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_none_out.txt')
            elif(name == 'hbm_BCH_fName'):
                print('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_BCH_out.txt')
                os.system('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_BCH_out.txt')
            else:
                print('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_RS_out.txt')
                os.system('./faultsim --configfile configs/' + str(getattr(args, name)) + ' --outfile HBM_RS_out.txt')



if __name__ == "__main__":
    main()
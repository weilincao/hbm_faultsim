import pandas as pd
import sys
import subprocess


def comp_run(file_name,iterations):
    try:
        f_out = open("comp.csv","w")
        f_out.write("dram_module,sim_num,sim_stat,trans_1bit,trans_1word,trans_1col,trans_1row,trans_1bank,trans_nbank,trans_nrank,"
                    +"perm_1bit,perm_1word,perm_1col,perm_1row,perm_1bank,perm_nbank,perm_nrank\n")
        f_out.close()

        file_path = "../configs/"+file_name

        for i in range(0,iterations):
            subprocess.run(["../faultsim","--configfile",file_path,"--outfile","out.txt"])
            df = pd.read_csv("synop.csv")
            df = df.loc[df['sim_stat'] == 2]
            df.to_csv("comp.csv",mode="a",index=False,header=False)
    finally:
        f_out.close()


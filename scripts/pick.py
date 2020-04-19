import pandas as pd


def filter_and_print(csv_name):
    df = pd.read_csv("comp.csv")

    f_out = open(csv_name,"w")
    f_out.write("dram_module,sim_num,sim_stat,trans_1bit,trans_1word,trans_1col,trans_1row,trans_1bank,trans_nbank,trans_nrank,"
    +"perm_1bit,perm_1word,perm_1col,perm_1row,perm_1bank,perm_nbank,perm_nrank\n")
    x = []

    x.append(df.loc[df['trans_1bit'] > 0])
    x.append(df.loc[df['trans_1word'] >0])
    x.append(df.loc[df['trans_1col'] > 0])
    x.append(df.loc[df['trans_1row'] >0])
    x.append(df.loc[df['trans_1bank'] > 0])
    x.append(df.loc[df['trans_nbank'] >0])
    x.append(df.loc[df['trans_nrank'] > 0])


    x.append(df.loc[df['perm_1bit'] > 0])
    x.append(df.loc[df['perm_1word'] >0])
    x.append(df.loc[df['perm_1col'] > 0])
    x.append(df.loc[df['perm_1row'] >0])
    x.append(df.loc[df['perm_1bank'] > 0])
    x.append(df.loc[df['perm_nbank'] >0])
    x.append(df.loc[df['perm_nrank'] > 0])


    for i in x:
        i.to_csv(csv_name,mode="a",index=False,header=False)


    f_out.close()



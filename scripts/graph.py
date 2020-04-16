import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import sys



if(len(sys.argv) == 3):
    csv_name = sys.argv[1]
    graph_name  = sys.argv[2]

    df = pd.read_csv(csv_name)
    df1 = df.iloc[:,3:]
    values = []
    for i in range(0,len(df1.columns)):
        values.append(df1.iloc[:,i].sum())
    faults = ['t_1bit','t_1word','t_1col','t_1row','t_1bank','t_nbank','t_nrank','p_1bit','p_1word','p_1col','p_1row','p_1bank','p_nbank','p_nrank']
   
    y_pos = np.arange(len(faults))
    plt.bar(y_pos,values,align='center')
    plt.xticks(y_pos,faults,rotation='vertical')
    plt.ylabel('Fault number')
    plt.xlabel('Fault Type')
    plt.title(graph_name)
    plt.tight_layout()
    plt.savefig(graph_name + ".png")
else:
    print("Wrong number of arguments")

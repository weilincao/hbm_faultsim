import sys
import data_comp
import pick
import pandas as pd
import matplotlib as plt



if(len(sys.argv) == 4):
    file_name  = sys.argv[1]
    iterations = int(sys.argv[2])
    output_file = sys.argv[3]
    data_comp.comp_run(file_name,iterations)
    pick.filter_and_print(output_file)
else:
    print("Wrong number of arguments, Please follow this: \"python3 test_and_graph.py FILE_NAME.ini ITERATIONS OUTPUT.CSV\"")




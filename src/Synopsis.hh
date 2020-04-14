#ifndef SYNOPSIS_H
#define SYNOPSIS_H

#include <stdlib.h>
#include <iostream>


#define TRANS_FAULT_AMNT 7 
#define PERM_FAULT_AMNT 7

extern int DRAMMODULES;

class Synopsis{

    public: 
    int dram_module;
    int sim_num; // the simulation number
    int sim_stat; //The status of a simulation instance. 0 - no faults, 1 - Failure, 2 - faults but corrected/detected
    int trans_faults[TRANS_FAULT_AMNT]; // transient fault count for each type of transient fault
    int perm_faults[PERM_FAULT_AMNT]; // permanent fault count for each type of permanent fault
    
    Synopsis(void); 
    static void init_file(const char* filename);
    void print_to_csv(void);
    static void file_closure(void);  
    static FILE* csv_fp; 

};

#endif


#ifndef SYNOPSIS_H
#define SYNOPSIS_H

#include <stdlib.h>
#include <iostream>


#define TRANS_FAULT_AMNT 7 
#define PERM_FAULT_AMNT 7

class Synopsis{

    public: 
    int dram_module; //which dram module cause the fault
    int sim_stat; //The status of a simulation instance. 0 - no faults, 1 - Failure, 2 - faults but corrected/detected
    int trans_faults[TRANS_FAULT_AMNT]; // transient fault count for each type of transient fault
    int perm_faults[PERM_FAULT_AMNT]; // permanent fault count for each type of permanent fault
    uint64_t failure_time; //if a failure happens to occur, we record when it happend (i.e. what year). If no faiulres occure then we mark it with a 0
    int ecc_scheme; // What ecc scheme was used? 0 - none, 1 - BCH, 2 - reed solomon, tec. 
    
    Synopsis(void); 
    static void init_file(char* filename);
    void print_to_csv(void);
    static void file_closure(void); 
    
    private: 
    static FILE* csv_fp; 

};

#endif


#include "Synopsis.hh"
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

int DRAMMODULES;


FILE* Synopsis::csv_fp = NULL;

Synopsis::Synopsis(void){
    this->sim_stat = 0; 
    this->sim_num = 0 ; 
    for(int i = 0 ; i < TRANS_FAULT_AMNT; i++)
        this->trans_faults[i] = 0;

    for(int i = 0 ; i < PERM_FAULT_AMNT; i++)
        this->perm_faults[i] = 0;
    


}


void Synopsis::init_file(const char* filename){
    FILE *fp_write = fopen(filename,"w");
    
    fprintf(fp_write,"dram_module,sim_num,sim_stat,trans_1bit,trans_1word,trans_1col,trans_1row,trans_1bank,trans_nbank,trans_nrank,"
           "perm_1bit,perm_1word,perm_1col,perm_1row,perm_1bank,perm_nbank,perm_nrank\n");

    fclose(fp_write);

    Synopsis::csv_fp = fopen(filename,"a");
}

void Synopsis::print_to_csv(void){

    char buff1[1000]; //Just a quick buffer we can use, we don't expect the amount to go voer 1000
    char buff2[1000];
    buff1[0] = '\0';

    sprintf(buff2,"%i, ",this->dram_module);
    strcat(buff1,buff2);    

    sprintf(buff2,"%i, ",this->sim_num);
    strcat(buff1,buff2);
    
    sprintf(buff2,"%i, ",this->sim_stat) ;
    strcat(buff1,buff2);


    for(int i = 0 ; i < TRANS_FAULT_AMNT ; i++){
        sprintf(buff2,"%i, ",this->trans_faults[i]) ;
        strcat(buff1,buff2);
    }
    
    for(int i = 0 ; i < PERM_FAULT_AMNT-1 ; i++){
        sprintf(buff2,"%i, ",this->perm_faults[i]) ;
        strcat(buff1,buff2);
    }


    sprintf(buff2,"%i\n", this->perm_faults[PERM_FAULT_AMNT-1]);
    strcat(buff1,buff2);

 

    fprintf(Synopsis::csv_fp,buff1);



}


void Synopsis::file_closure(void){

    fclose(Synopsis::csv_fp);
}






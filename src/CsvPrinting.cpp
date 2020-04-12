#include"CsvPrinting.hh"
#include<iostream>

CsvPrint CSVPRINTING;

CsvPrint::CsvPrint(){};

void CsvPrint::init(void){
    this->fp_write = fopen("out.csv","w");

     fprintf(this->fp_write,"trans_1bit,trans_1word,trans_1col,trans_1row,trans_1bank,trans_nbank,trans_nrank"
                   "perm_1bit,perm_1word,perm_1col,perm_1row,perm_1bank,perm_nbank,perm_nrank\n");

     fclose(this->fp_write);

     this->fp_append = fopen("out.csv","a");

}


void CsvPrint::append_str(char* str){

    fprintf(this->fp_append,str); 

}


void CsvPrint::clean_up(void){

    fclose(this->fp_write);
    fclose(this->fp_append);


}




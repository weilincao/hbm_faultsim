#ifndef CSVPRINTING_H
#define CSVPRINTING_H

//#define CSV_OUT

#include<iostream>
class CsvPrint{
    private:
    FILE *fp_write;
    FILE *fp_append;

    public:
    CsvPrint();
    void init(void);
    void append_str(char* str);
    void clean_up(void);
};



extern CsvPrint CSVPRINTING; 

#endif

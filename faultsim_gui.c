#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <stdlib.h>
#include <string.h>


#include <iostream>
#include <fstream>
#include <string>
#include "src/Settings.hh"
#include "src/ConfigParser.hh"


#define VAR_AMNT 43
#define SIM_SIZE 9
#define ORG_SIZE 12
#define FAULT_SIZE 6
#define ECC_SIZE 2
#define FIT_SIZE 14

//Make global of buttons and text box

GtkWidget *save_file;
GtkWidget *load_file;
GtkWidget *run_button;
GtkWidget *run_file;
GtkWidget *fixed1;
GtkWidget *window;
GtkWidget *s[SIM_SIZE];
GtkWidget *o[ORG_SIZE];
GtkWidget *f[FAULT_SIZE];
GtkWidget *e[ECC_SIZE];
GtkWidget *fi[FIT_SIZE];
GtkWidget *file_name;
GtkBuilder *builder;



void set_up_globals();
void set_up_default();
int main(int argc, char* argv[]){
    gtk_init(&argc,&argv);
    builder = gtk_builder_new_from_file("faultsim.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder,"window"));
    //Just necessary for window when exit out of window
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    
    //creates table for signals (makes our life easier)
    gtk_builder_connect_signals(builder,NULL);

    set_up_globals();
    set_up_default();
    // displays window
    gtk_widget_show(window);

    //will watch for signals
    gtk_main();

    return EXIT_SUCCESS;
}


extern "C" void on_save_file_clicked(GtkButton *b){

    const gchar* st[VAR_AMNT];


    int offset = 0; //offset for st array 

    for(int i = 0 ; i < SIM_SIZE; i++,offset++)
        st[offset] = gtk_entry_get_text(GTK_ENTRY(s[i]));
    for(int i = 0 ; i < ORG_SIZE; i++,offset++)
        st[offset] = gtk_entry_get_text(GTK_ENTRY(o[i])); 

    for(int i = 0 ; i < FAULT_SIZE; i++,offset++)
        st[offset] = gtk_entry_get_text(GTK_ENTRY(f[i])); 
    
    for(int i = 0 ; i < ECC_SIZE; i++,offset++)
        st[offset] = gtk_entry_get_text(GTK_ENTRY(e[i]));; 

    for(int i = 0 ; i < FIT_SIZE; i++,offset++)
        st[offset] = gtk_entry_get_text(GTK_ENTRY(fi[i]));; 
    
    
    const gchar* f_name = gtk_entry_get_text(GTK_ENTRY(file_name));

    char* temp = "configs/";

    char* full_path = (char*) malloc(sizeof(char)*(strlen(temp)+strlen((const char*)f_name)+1));

    strcpy(full_path,temp);
    strcat(full_path,f_name);


    FILE *f = fopen(full_path, "w+");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    
    fprintf(f,"\[Sim]\n"
    "sim_mode = %s \n"
    "interval_s = %s\n"
    "scrub_s = %s\n"
    "max_s = %s\n"
    "n_sims = %s\n"
    "continue_running = %s\n"
    "verbose = %s\n"
    "debug = %s\n"
    "output_bucket_s = %s\n\n"
    "\[Org]\n"
    "organization = %s\n"
    "chips_per_rank = %s\n"
    "chip_bus_bits = %s\n"
    "ranks = %s\n"
    "banks = %s\n"
    "rows = %s\n"
    "cols = %s\n"
    "cube_model = %s\n"
    "cube_addr_dec_depth = %s\n"
    "cube_ecc_tsv = %s\n"
    "cube_redun_tsv = %s\n"
    "data_block_bits = %s\n\n"
    "\[Fault]\n"
    "faultmode = %s\n"
    "enable_permanent = %s\n"
    "enable_transient = %s\n"
    "enable_tsv = %s\n"
    "fit_factor = %s\n"
    "tsv_fit = %s\n\n"
    "\[ECC]\n"
    "repairmode = %s\n"
    "symbol_size_bits = %s\n\n"
    "\[FIT]\n"
    "trans_1bit = %s\n"
    "trans_1word = %s\n"
    "trans_1col = %s\n"
    "trans_1row = %s\n"
    "trans_1bank = %s\n"
    "trans_nbank = %s\n"
    "trans_nrank = %s\n"
    "perm_1bit = %s\n"
    "perm_1word = %s\n"
    "perm_1col = %s\n"
    "perm_1row = %s\n"
    "perm_1bank = %s\n"
    "perm_nbank = %s\n"
    "perm_nrank = %s",
    st[0],st[1],st[2],st[3],st[4],st[5],st[6],st[7],st[8],st[9],st[10],st[11],st[12],st[13],st[14],st[15],st[16],st[17],st[18],st[19],st[20],st[21],st[22],st[23],st[24],st[25],st[26],st[27],
    st[28],st[29],st[30],st[31],st[32],st[33],st[34],st[35],st[36],st[37],st[38],st[39],st[40],st[41],st[42]);

    fclose(f);
    free(full_path);

}

extern "C" void on_run_button_clicked(GtkButton *b){
    const  gchar* rf  = gtk_entry_get_text(GTK_ENTRY(run_file));

    char* executable = "./faultsim";
    char* arg0 = "--configfile" ;
    char* temp_arg1 = "configs/";
    char* arg2 = "--outfile";
    char* arg3 = "out.txt";
    
    char* arg1 = (char*) malloc(sizeof(char)*(strlen(temp_arg1)+ strlen((char*)rf) + 1)); 
    strcpy(arg1,temp_arg1);
    strcat(arg1,rf);
    
    char** args = (char**) malloc(sizeof(char*)*6);

    args[0] = executable;
    args[1] = arg0;
    args[2] = arg1;
    args[3] = arg2;
    args[4] = arg3;
    args[5] = NULL; 

    int p = fork();
    if(p == 0){
            execvp(args[0],&args[0]);
            exit(1);

    }
}



void set_up_globals(){

    save_file = GTK_WIDGET(gtk_builder_get_object(builder,"save_file"));
    load_file = GTK_WIDGET(gtk_builder_get_object(builder,"load_file"));
    run_button = GTK_WIDGET(gtk_builder_get_object(builder,"run_button"));
    run_file = GTK_WIDGET(gtk_builder_get_object(builder,"run_file"));
    file_name = GTK_WIDGET(gtk_builder_get_object(builder,"file_name"));
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder,"fixed1"));

    char buff[1000]; //buffer for strings (assumes strings are no larger than 1000)
    for(int i = 0 ;  i < SIM_SIZE; i++){
        sprintf(buff,"s%i",i);
        s[i] = GTK_WIDGET(gtk_builder_get_object(builder,buff));
    }    
    for(int i = 0 ;  i < ORG_SIZE; i++){
        sprintf(buff,"o%i",i);
        o[i] = GTK_WIDGET(gtk_builder_get_object(builder,buff));
    }
    for(int i = 0 ;  i < FAULT_SIZE; i++){
        sprintf(buff,"f%i",i);
        f[i] = GTK_WIDGET(gtk_builder_get_object(builder,buff));
    }
    for(int i = 0 ;  i < ECC_SIZE; i++){
        sprintf(buff,"e%i",i);
        e[i] = GTK_WIDGET(gtk_builder_get_object(builder,buff));
    }
    for(int i = 0 ;  i < FIT_SIZE; i++){
        sprintf(buff,"fi%i",i);
        fi[i] = GTK_WIDGET(gtk_builder_get_object(builder,buff));
    }
}


void set_up_default(){

    for(int i = 0 ;  i < SIM_SIZE; i++)
        gtk_entry_set_text(GTK_ENTRY(s[i]),"0");
    for(int i = 0 ;  i < ORG_SIZE; i++)
        gtk_entry_set_text(GTK_ENTRY(o[i]),"0");
    for(int i = 0 ;  i < FAULT_SIZE; i++)
        gtk_entry_set_text(GTK_ENTRY(f[i]),"0");
    for(int i = 0 ;  i < ECC_SIZE; i++)
        gtk_entry_set_text(GTK_ENTRY(e[i]),"0");
    for(int i = 0 ;  i < FIT_SIZE; i++)
        gtk_entry_set_text(GTK_ENTRY(fi[i]),"0");

}

bool ini_settings_update (void) {

  std::string f_path = "configs/";
  const char* f_name = gtk_entry_get_text(GTK_ENTRY(file_name));

  f_path += f_name;
  std::ifstream ini_file(f_path);
  if (!ini_file) {
    std::cerr << "Unable to open " << f_path << std::endl;
    return false;
  }
	parser((char*)f_path.c_str());
  return true;
}

struct Settings settings;
extern "C" void on_load_file_clicked(GtkButton *b) {

  if ( !ini_settings_update() ) return;

  gtk_entry_set_text(GTK_ENTRY(s[0]), std::to_string(settings.sim_mode).c_str());
  gtk_entry_set_text(GTK_ENTRY(s[1]), std::to_string(settings.interval_s).c_str());
  gtk_entry_set_text(GTK_ENTRY(s[2]), std::to_string(settings.scrub_s).c_str());
  gtk_entry_set_text(GTK_ENTRY(s[3]), std::to_string(settings.max_s).c_str());
  gtk_entry_set_text(GTK_ENTRY(s[4]), std::to_string(settings.n_sims).c_str());
  gtk_entry_set_text(GTK_ENTRY(s[5]), std::to_string(settings.continue_running).c_str());
  gtk_entry_set_text(GTK_ENTRY(s[6]), std::to_string(settings.verbose).c_str());
  gtk_entry_set_text(GTK_ENTRY(s[7]), std::to_string(settings.debug).c_str());
  gtk_entry_set_text(GTK_ENTRY(s[8]), std::to_string(settings.output_bucket_s).c_str());

  gtk_entry_set_text(GTK_ENTRY(o[0]), std::to_string(settings.organization).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[1]), std::to_string(settings.chips_per_rank).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[2]), std::to_string(settings.chip_bus_bits).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[3]), std::to_string(settings.ranks).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[4]), std::to_string(settings.banks).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[5]), std::to_string(settings.rows).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[6]), std::to_string(settings.cols).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[7]), std::to_string(settings.cube_model).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[8]), std::to_string(settings.cube_addr_dec_depth).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[9]), std::to_string(settings.cube_ecc_tsv).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[10]), std::to_string(settings.cube_redun_tsv).c_str());
  gtk_entry_set_text(GTK_ENTRY(o[11]), std::to_string(settings.data_block_bits).c_str());

  gtk_entry_set_text(GTK_ENTRY(f[0]), std::to_string(settings.faultmode).c_str());
  gtk_entry_set_text(GTK_ENTRY(f[1]), std::to_string(settings.enable_permanent).c_str());
  gtk_entry_set_text(GTK_ENTRY(f[2]), std::to_string(settings.enable_transient).c_str());
  gtk_entry_set_text(GTK_ENTRY(f[3]), std::to_string(settings.enable_tsv).c_str());
  gtk_entry_set_text(GTK_ENTRY(f[4]), std::to_string(settings.fit_factor).c_str());
  gtk_entry_set_text(GTK_ENTRY(f[5]), std::to_string(settings.tsv_fit).c_str());

  gtk_entry_set_text(GTK_ENTRY(e[0]), std::to_string(settings.repairmode).c_str());
  gtk_entry_set_text(GTK_ENTRY(e[1]), std::to_string(settings.symbol_size_bits).c_str());

  gtk_entry_set_text(GTK_ENTRY(fi[0]), std::to_string(settings.trans_1bit).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[1]), std::to_string(settings.trans_1word).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[2]), std::to_string(settings.trans_1col).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[3]), std::to_string(settings.trans_1row).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[4]), std::to_string(settings.trans_1bank).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[5]), std::to_string(settings.trans_nbank).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[6]), std::to_string(settings.trans_nrank).c_str()); 
  gtk_entry_set_text(GTK_ENTRY(fi[7]), std::to_string(settings.perm_1bit).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[8]), std::to_string(settings.perm_1word).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[9]), std::to_string(settings.perm_1col).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[10]), std::to_string(settings.perm_1row).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[11]), std::to_string(settings.perm_1bank).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[12]), std::to_string(settings.perm_nbank).c_str());
  gtk_entry_set_text(GTK_ENTRY(fi[13]), std::to_string(settings.perm_nrank).c_str());

}

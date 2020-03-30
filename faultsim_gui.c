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

//Make global of buttons and text box

GtkWidget *save_file;
GtkWidget *load_file;
GtkWidget *run_button;
GtkWidget *run_file;
GtkWidget *fixed1;
GtkWidget *window;
GtkWidget *s0;
GtkWidget *s1;
GtkWidget *s2;
GtkWidget *s3;
GtkWidget *s4;
GtkWidget *s5;
GtkWidget *s6;
GtkWidget *s7;
GtkWidget *s8;
GtkWidget *o0;
GtkWidget *o1;
GtkWidget *o2;
GtkWidget *o3;
GtkWidget *o4;
GtkWidget *o5;
GtkWidget *o6;
GtkWidget *o7;
GtkWidget *o8;
GtkWidget *o9;
GtkWidget *o10;
GtkWidget *o11;
GtkWidget *f0;
GtkWidget *f1;
GtkWidget *f2;
GtkWidget *f3;
GtkWidget *f4;
GtkWidget *f5;
GtkWidget *e0;
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

    const  gchar* st0  = gtk_entry_get_text(GTK_ENTRY(s0));
    const  gchar* st1  = gtk_entry_get_text(GTK_ENTRY(s1));
    const  gchar* st2  = gtk_entry_get_text(GTK_ENTRY(s2));
    const  gchar* st3  = gtk_entry_get_text(GTK_ENTRY(s3));
    const  gchar* st4  = gtk_entry_get_text(GTK_ENTRY(s4));
    const  gchar* st5  = gtk_entry_get_text(GTK_ENTRY(s5));
    const  gchar* st6  = gtk_entry_get_text(GTK_ENTRY(s6));
    const  gchar* st7  = gtk_entry_get_text(GTK_ENTRY(s7));
    const  gchar* st8  = gtk_entry_get_text(GTK_ENTRY(s8));

    const  gchar* st9  = gtk_entry_get_text(GTK_ENTRY(o0));
    const  gchar* st10  = gtk_entry_get_text(GTK_ENTRY(o1));
    const  gchar* st11  = gtk_entry_get_text(GTK_ENTRY(o2));
    const  gchar* st12  = gtk_entry_get_text(GTK_ENTRY(o3));
    const  gchar* st13  = gtk_entry_get_text(GTK_ENTRY(o4));
    const  gchar* st14  = gtk_entry_get_text(GTK_ENTRY(o5));
    const  gchar* st15  = gtk_entry_get_text(GTK_ENTRY(o6));
    const  gchar* st16  = gtk_entry_get_text(GTK_ENTRY(o7));
    const  gchar* st17  = gtk_entry_get_text(GTK_ENTRY(o8));
    const  gchar* st18  = gtk_entry_get_text(GTK_ENTRY(o9));
    const  gchar* st19  = gtk_entry_get_text(GTK_ENTRY(o10));
    const  gchar* st20  = gtk_entry_get_text(GTK_ENTRY(o11));

    const  gchar* st21  = gtk_entry_get_text(GTK_ENTRY(f0));
    const  gchar* st22  = gtk_entry_get_text(GTK_ENTRY(f1));
    const  gchar* st23  = gtk_entry_get_text(GTK_ENTRY(f2));
    const  gchar* st24  = gtk_entry_get_text(GTK_ENTRY(f3));
    const  gchar* st25  = gtk_entry_get_text(GTK_ENTRY(f4));
    const  gchar* st26  = gtk_entry_get_text(GTK_ENTRY(f5));
    
    const  gchar* st27  = gtk_entry_get_text(GTK_ENTRY(e0));

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
    "repairmode = %s\n\n"
    "\[ReedSolomon]\n"
    "symbol_size_bits = 8\n",
    st0,st1,st2,st3,st4,st5,st6,st7,st8,st9,st10,st11,st12,st13,st14,st15,st16,st17,st18,st19,st20,st21,st22,st23,st24,st25,st26,st27);

    fprintf(f, "\n[FIT]\n"
"trans_1bit = 14.2\n"
"trans_1word = 1.4\n"
"trans_1col = 1.4\n"
"trans_1row = 0.2\n"
"trans_1bank = 0.8\n"
"trans_nbank = 0.3\n"
"trans_nrank = 0.9\n"
"perm_1bit = 18.6\n"
"perm_1word = 0.3\n"
"perm_1col = 5.6\n"
"perm_1row = 8.2\n"
"perm_1bank = 10.0\n"
"perm_nbank = 1.4\n"
"perm_nrank = 2.8");

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
    s0 = GTK_WIDGET(gtk_builder_get_object(builder,"s0"));
    s1 = GTK_WIDGET(gtk_builder_get_object(builder,"s1"));
    s2 = GTK_WIDGET(gtk_builder_get_object(builder,"s2"));
    s3 = GTK_WIDGET(gtk_builder_get_object(builder,"s3"));
    s4 = GTK_WIDGET(gtk_builder_get_object(builder,"s4"));
    s5 = GTK_WIDGET(gtk_builder_get_object(builder,"s5"));
    s6 = GTK_WIDGET(gtk_builder_get_object(builder,"s6"));
    s7 = GTK_WIDGET(gtk_builder_get_object(builder,"s7"));
    s8 = GTK_WIDGET(gtk_builder_get_object(builder,"s8"));


    o0 = GTK_WIDGET(gtk_builder_get_object(builder,"o0"));
    o1 = GTK_WIDGET(gtk_builder_get_object(builder,"o1"));
    o2 = GTK_WIDGET(gtk_builder_get_object(builder,"o2"));
    o3 = GTK_WIDGET(gtk_builder_get_object(builder,"o3"));
    o4 = GTK_WIDGET(gtk_builder_get_object(builder,"o4"));
    o5 = GTK_WIDGET(gtk_builder_get_object(builder,"o5"));
    o6 = GTK_WIDGET(gtk_builder_get_object(builder,"o6"));
    o7 = GTK_WIDGET(gtk_builder_get_object(builder,"o7"));
    o8 = GTK_WIDGET(gtk_builder_get_object(builder,"o8"));
    o9 = GTK_WIDGET(gtk_builder_get_object(builder,"o9"));
    o10 = GTK_WIDGET(gtk_builder_get_object(builder,"o10"));
    o11 = GTK_WIDGET(gtk_builder_get_object(builder,"o11"));

    f0 = GTK_WIDGET(gtk_builder_get_object(builder,"f0"));
    f1 = GTK_WIDGET(gtk_builder_get_object(builder,"f1"));
    f2 = GTK_WIDGET(gtk_builder_get_object(builder,"f2"));
    f3 = GTK_WIDGET(gtk_builder_get_object(builder,"f3"));
    f4 = GTK_WIDGET(gtk_builder_get_object(builder,"f4"));
    f5 = GTK_WIDGET(gtk_builder_get_object(builder,"f5"));

    e0 = GTK_WIDGET(gtk_builder_get_object(builder,"e0"));
}


void set_up_default(){

    gtk_entry_set_text(GTK_ENTRY(s0),"2");
    gtk_entry_set_text(GTK_ENTRY(s1),"3600");
    gtk_entry_set_text(GTK_ENTRY(s2),"10800");
    gtk_entry_set_text(GTK_ENTRY(s3),"220752000");
    gtk_entry_set_text(GTK_ENTRY(s4),"100000");
    gtk_entry_set_text(GTK_ENTRY(s5),"1");
    gtk_entry_set_text(GTK_ENTRY(s6),"1");
    gtk_entry_set_text(GTK_ENTRY(s7),"1");
    gtk_entry_set_text(GTK_ENTRY(s8),"7257600");



    gtk_entry_set_text(GTK_ENTRY(o0),"0");
    gtk_entry_set_text(GTK_ENTRY(o1),"18");
    gtk_entry_set_text(GTK_ENTRY(o2),"4");
    gtk_entry_set_text(GTK_ENTRY(o3),"1");
    gtk_entry_set_text(GTK_ENTRY(o4),"8");
    gtk_entry_set_text(GTK_ENTRY(o5),"16384");
    gtk_entry_set_text(GTK_ENTRY(o6),"2048");
    gtk_entry_set_text(GTK_ENTRY(o7),"0");
    gtk_entry_set_text(GTK_ENTRY(o8),"0");
    gtk_entry_set_text(GTK_ENTRY(o9),"0");
    gtk_entry_set_text(GTK_ENTRY(o10),"0");
    gtk_entry_set_text(GTK_ENTRY(o11),"512");

    gtk_entry_set_text(GTK_ENTRY(f0),"1");
    gtk_entry_set_text(GTK_ENTRY(f1),"1");
    gtk_entry_set_text(GTK_ENTRY(f2),"1");
    gtk_entry_set_text(GTK_ENTRY(f3),"0");
    gtk_entry_set_text(GTK_ENTRY(f4),"1.0");
    gtk_entry_set_text(GTK_ENTRY(f5),"1.0");

    gtk_entry_set_text(GTK_ENTRY(e0),"0");
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

  gtk_entry_set_text(GTK_ENTRY(s0), std::to_string(settings.sim_mode).c_str());
  gtk_entry_set_text(GTK_ENTRY(s1), std::to_string(settings.interval_s).c_str());
  gtk_entry_set_text(GTK_ENTRY(s2), std::to_string(settings.scrub_s).c_str());
  gtk_entry_set_text(GTK_ENTRY(s3), std::to_string(settings.max_s).c_str());
  gtk_entry_set_text(GTK_ENTRY(s4), std::to_string(settings.n_sims).c_str());
  gtk_entry_set_text(GTK_ENTRY(s5), std::to_string(settings.continue_running).c_str());
  gtk_entry_set_text(GTK_ENTRY(s6), std::to_string(settings.verbose).c_str());
  gtk_entry_set_text(GTK_ENTRY(s7), std::to_string(settings.debug).c_str());
  gtk_entry_set_text(GTK_ENTRY(s8), std::to_string(settings.output_bucket_s).c_str());

  gtk_entry_set_text(GTK_ENTRY(o0), std::to_string(settings.organization).c_str());
  gtk_entry_set_text(GTK_ENTRY(o1), std::to_string(settings.chips_per_rank).c_str());
  gtk_entry_set_text(GTK_ENTRY(o2), std::to_string(settings.chip_bus_bits).c_str());
  gtk_entry_set_text(GTK_ENTRY(o3), std::to_string(settings.ranks).c_str());
  gtk_entry_set_text(GTK_ENTRY(o4), std::to_string(settings.banks).c_str());
  gtk_entry_set_text(GTK_ENTRY(o5), std::to_string(settings.rows).c_str());
  gtk_entry_set_text(GTK_ENTRY(o6), std::to_string(settings.cols).c_str());
  gtk_entry_set_text(GTK_ENTRY(o7), std::to_string(settings.cube_model).c_str());
  gtk_entry_set_text(GTK_ENTRY(o8), std::to_string(settings.cube_addr_dec_depth).c_str());
  gtk_entry_set_text(GTK_ENTRY(o9), std::to_string(settings.cube_ecc_tsv).c_str());
  gtk_entry_set_text(GTK_ENTRY(o10), std::to_string(settings.cube_redun_tsv).c_str());
  gtk_entry_set_text(GTK_ENTRY(o11), std::to_string(settings.data_block_bits).c_str());

  gtk_entry_set_text(GTK_ENTRY(f0), std::to_string(settings.faultmode).c_str());
  gtk_entry_set_text(GTK_ENTRY(f1), std::to_string(settings.enable_permanent).c_str());
  gtk_entry_set_text(GTK_ENTRY(f2), std::to_string(settings.enable_transient).c_str());
  gtk_entry_set_text(GTK_ENTRY(f3), std::to_string(settings.enable_tsv).c_str());
  gtk_entry_set_text(GTK_ENTRY(f4), std::to_string(settings.fit_factor).c_str());
  gtk_entry_set_text(GTK_ENTRY(f5), std::to_string(settings.tsv_fit).c_str());

  gtk_entry_set_text(GTK_ENTRY(e0), std::to_string(settings.repairmode).c_str());

}

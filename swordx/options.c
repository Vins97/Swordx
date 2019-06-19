#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "main.h"
const char* const short_options = "ho:rfe:am:i:s";
const struct option long_options[] = {
  { "help", 0, NULL, 'h' },
  { "output", 1, NULL, 'o' },
  { "recursive", 0, NULL, 'r' },
  { "follow", 0, NULL, 'f' },
  { "explude", 1, NULL, 'e' },
  { "alpha", 0, NULL, 'a' },
  { "min", 1, NULL, 'm' },
  { "ignore", 1, NULL, 'i' },
  { "sortbyoccurrency", 0, NULL, 's' },
  { "log", 1, NULL, 'l' }, 
  { NULL, 0, NULL, 0 }
};

void printUsage(int);
optValues_t * optionSwitcher(int,char**);

void printUsage (int exit_code){
  printf ("\nUsage:  ./swordx [options][input] oppure [input][input]... oppure [directoryinput] \n");
  printf ("-h  -help  Show help.\n"
          "-o  -output Set output name\n"
          "-r  -recursive Import recursively directory file\n"
          "-f  -follow Follow links (only with directories)\n"
          "-e <file>  -exploude <file> Exploude selected file (only with directories)\n "
          "-a  -alpha Read only letters\n"
          "-m <num> -min <num> Not show words occurrency under this limits\n "
          "-i <file> -ignore <file> Ignore words in the selected file\n"
          "-s -sortbyoccurrency Sort word by occurrency\n"
          "-l <file> -log <file> Create a log file\n"
          "Include regex in apexes to use regular espressions \n");
  exit (exit_code);
}

optValues_t * optionSwitcher(int argc, char **argv){	
	optValues_t * opt = malloc(sizeof(optValues_t));
	int nextInput = 1;
	int next_option;
	string path;
	do {
		next_option = getopt_long_only (argc, argv, short_options,long_options, NULL);		         
		switch (next_option){
			case 'h':  
			    nextInput++; 
				printUsage (0);
			case 'o':  
				strcpy(opt->outputName,optarg);
				opt->outFLAG=1;
				nextInput=nextInput+2; 
				break;    
			case 'r':   
				opt->recursiveFLAG=1;
				nextInput++; 
				break;
			case 'f':   
				opt->followFLAG=1;
				nextInput++; 
				break;
			case 'e':   
				strcpy(opt->exploudeName,optarg);
				opt->exploudeFLAG=1;
				nextInput=nextInput+2; 
				break;
			case 'a':   
				opt->alphaFLAG=1;
				nextInput++; 
				break;
			case 'm':
				opt->minFLAG=1;
				opt->minLenght=atoi(optarg);
				nextInput=nextInput+2;
				break;
			case 'i':   
				strcpy(opt->ignoreName,optarg);
				opt->ignoreFLAG =1;
				nextInput=nextInput+2;
				break;
			case 's':   
				opt->sortByOccurrencyFLAG= 1;
				nextInput++; 
				break;
			case 'l':
				strcpy(opt->logName,optarg);
				opt->logFLAG =1;
				nextInput+2;
				break;
			case '?':
				exit(-1);
				break;
			case -1:    /* Done with options.  */
			  break;
			default:    /* Something else: unexpected.  */
			  abort ();
		}		
	}while (next_option != -1);
	opt->indexArgv = nextInput;
	return opt;
}

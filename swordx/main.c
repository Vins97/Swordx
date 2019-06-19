#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <glob.h>
#include <ctype.h>
#include "main.h"
#include "wordList.h"
#include "sorting.h"


//return 1 if is a regular file from path
int isRegularFile(const char *path){
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}
//return 1 if is a regular directory from path
int isRegularDirectory(const char *path){
	struct stat buf;
	stat(path,&buf);
	return S_ISDIR(buf.st_mode);
}

//from the word list delete words occour in the file selected
void ignoreWord(node_w* root,string nIgnore){
	FILE *f;
	f = fopen(nIgnore,"r");
	string word;
	if(f==NULL)
		perror("File storage to ignore word not correct");
	while (fgets(word, sizeof(word), f) != NULL){
		word[strlen(word) - 1] = '\0'; 
		if(strlen(word)!=0)
			deleteNode(root,word);
		}
    fclose(f);
	} 
//da modificare continue per implementare il log
int readWordsFromFile(node_w * root,string nameFile,optValues_t *opt){
	FILE *r;
	r=fopen(nameFile,"r");
	string temp;
	if (r==NULL){
		perror("File not found");
		return 0;
	}
	do{ 
		fscanf(r,ALPHA,temp);
		if(opt->alphaFLAG)
			alphabeticWord(temp) ? _insert(root,temp):continue;
		if(opt->minFLAG)
			strlen(temp)>=opt->minLenght ? _insert(root,temp):continue;
		_insert(root,temp)
	}while(!feof(r));
	fclose(r);
	return 1;

}
//return 1 if it not contains numbers
int alphabeticWord(string word){
	for(i=0;i<=strlen(word);i++){
		if(word[i]==isdigit)
			return 0;
		}
	return 1;	
}
//read file from filelist
void dRead(fileList_t * fList,node_w * root,optValues_t* opt){
	do{
		strlen(fList->nameFile)==0 ? : readWordsFromFile(root,fList->nameFile,opt);
		fList = fList->next;
		}while(fList!=NULL);
}
//delete file from the directory list of file(usable whith exploudeFileFlag)
void directoryFileExploude(fileList_t * fList,string nameFile){
	if(fileListDelete(fList,nameFile))
		printf("File %s explouded",nameFile);
	else
		perror("File to exploude incorrect");
}	
//write words from the BST to the outputfile recursively
void printTreeOut(node_w * root,FILE *out){
    if (root != NULL) {
        printTreeOut(root->left,out);
        if(strlen(root->word)>0)
			fprintf(out,"%s %d \n", root->word,root->occurrency);
        printTreeOut(root->right,out);
    }
}
void fOut(node_w *root,string outputN,int outFLAG){
	FILE *out;
	outFLAG ? (out = fopen(strcat(outputN,".out"),"w")) : (out = fopen("swordx.out","w"));		
	printTreeOut(root,out);
	fclose(out);
}
void printLog(string log,string name){
	FILE *f;
    f = fopen(strcat(name,".log"), "a+"); // a+ (create + append) option will allow appending which is useful in a log file
    if (f == NULL) 
		perror("Errore nel log file");
    fprintf(f, strcat(log,"\n");
    fclose(f);
}
//manage directory whith recursive flag and followflag
void openDirectory(fileList_t * fList,const string nameDir,int recursiveFLAG,int followFLAG){
		DIR *dir;
		struct dirent *entry;
		dir = opendir(nameDir);
		if (!dir)
			return;
		while((entry=readdir(dir)) != NULL){
			//controllo se nella directory esistono father o file nascosti (.nomefile)
			if(recursiveFLAG&&(entry->d_type==DT_DIR)){
				string path;
				if ( (!strcmp( entry->d_name, "."  ))||(!strcmp( entry->d_name, ".." ))||(entry->d_name[0] == '.'))
					continue;
				snprintf(path,sizeof(path),"%s/%s",nameDir,entry->d_name);
				//if there is the recursive flag, recall the openDirectory method
				openDirectory(fList,path,recursiveFLAG,followFLAG);
			}
			else if (entry->d_type==DT_REG){
				string path;
				//check if there is already the / to write the path file in the list correctly
				if((nameDir[(strlen(nameDir)-1)]-47)==0)
					snprintf(path,sizeof(path),"%s%s",nameDir,entry->d_name);
				else
					snprintf(path,sizeof(path),"%s/%s",nameDir,entry->d_name);
				fileListPush(fList,path);
			}
			else if ((entry->d_type==DT_LNK)&&followFLAG){
				string path;
				string realP;
				snprintf(path,sizeof(path),"%s/%s",nameDir,entry->d_name);
				realpath(path,realP);
				fileListPush(fList,realP);
				}
			}
		closedir(dir);
		return;
	}
int regExpression(string wildCard,fileList_t * fList){
	glob_t paths;
	int rtVal;
	rtVal = glob(wildCard,GLOB_NOCHECK|GLOB_NOSORT,NULL,&paths);
	if(!rtVal){
		int i;
		for(i=0;i<paths.gl_pathc;i++){
			fileListPush(fList,paths.gl_pathv[i]);	
			}		
		globfree(&paths);
		return 1;
	}
	else
		return 0;
}


void freeMemAllocated(node_w  *root,fileList_t *files,optValues_t * opt){
	free(root);
	free(files);
	free(opt);
}

int main (int argc, char **argv){
	node_w  *root = (node_w *)malloc(sizeof(node_w));	
	int nextInput;

	
    fileList_t * files = malloc(sizeof(fileList_t));
   	optValues_t * opt = malloc(sizeof(optValues_t));
   	opt = optionSwitcher(argc,argv);
    nextInput = opt->indexArgv;
	while(nextInput<argc){
			if(isRegularFile(argv[nextInput])){
				if(readWordsFromFile(root,argv[nextInput],opt)
					printf("File %s loaded \n",argv[nextInput]);
				nextInput++;
				continue;	
				}
			else if (isRegularDirectory(argv[nextInput])){
				openDirectory(files,argv[nextInput],opt->recursiveFLAG,opt->followFLAG);
				if(opt->exploudeFLAG){
					directoryFileExploude(files,opt->exploudeName);
				}
				dRead(files,root,opt->alphaFLAG);
			}
			else if(regExpression(argv[nextInput],files))
				dRead(files,root,0);
			else 
				printf("Input data not correct");
		nextInput++;
	}
	
	if(opt->ignoreFLAG&&isRegularFile(opt->ignoreName))
		ignoreWord(root,opt->ignoreName);
	if(opt->sortByOccurrencyFLAG){
		analisys_t * list = malloc(sizeof(analisys_t));
		list=sortByOccurrency(root);
		
	}//stampare la lista in output
	else{	
		fOut(root,opt->outputName,opt->outFLAG);
	}
	
	freeMemAllocated(root,files,opt);
	return 0;


}

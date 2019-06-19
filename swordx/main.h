typedef char string[1024];
typedef struct analisys{
	string word;
	int occurrency;
	struct analisys *next;
}analisys_t;
typedef struct log{
	string fileName;
	int regWords;
	int ingWords;
	float exeTime;
	}

typedef struct optValues{
	string outputName;
	string exploudeName;
	string ignoreName;
	string logName;
	int minLenght;
	int minFLAG;
	int sortByOccurrencyFLAG;
	int recursiveFLAG;
	int followFLAG;
	int alphaFLAG;
	int indexArgv;
	int outFLAG;
	int exploudeFLAG;
	int ignoreFLAG;
	int logFLAG;
}optValues_t;
typedef struct fileList{
	string path;
	log saved;
	struct fileList *next;	
}fileList_t;

typedef struct nodeWord{
    int occurrency;
    string word;
    struct nodeWord *left, *right;
}node_w;

extern string log;

static const char ALPHANUMERIC[] = "%127[a-zA-Zàèìòùáéíóú1-9]%*[^a-zA-Zàèìòùáéíóú1-9]";


int readWordsFromFile(node_w *,string,optValues_t *);
int isRegularFile(const char *);
int isRegularDirectory(const char *);
void dRead(fileList_t *,node_w *,optValues_t* );
void ignoreWord(node_w * ,string );
void fOut(node_w *,string,int);
void directoryFileExploude(fileList_t *,string);
void openDirectory(fileList_t *,const string,int,int);
int regExpression(string,fileList_t *);

optValues_t * optionSwitcher(int argc, char **argv);




void push(analisys_t *,string,int);

void fileListPush(fileList_t *,string);

void deleteWord(analisys_t * ,string );
void deleteOccurrency(analisys_t * ,int);
int fileListDelete(fileList_t * ,string);


node_w* newNode(string,int);
void inOrder(node_w *);
analisys_t* sortByOccurrency(node_w* );
node_w* insert(node_w * , int , string);
node_w* minValueNode(node_w* );
node_w* deleteNode(node_w* ,string);


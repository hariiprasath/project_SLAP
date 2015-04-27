#include <Python.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

# define MAX 50

//exception object definition
static PyObject *lyricsSearchError;

typedef struct hashDataStorage
{
	int count;
	char str[200];
	struct hashDataStorage* next;
} hashData;

typedef struct hashPointerStorage
{
	hashData* point;
} hashPointer;


void printTable();
hashData* createNewHashElement(char input[]);
void insertIntoHashTable(char str[]);
char* searchInTableForHighest();
void dataFromFile(char str[]);
int hashMe(char* str);

hashPointer arr[MAX];
void initializeTable()
{
	int i;
	for(i=0;i<MAX;i++)
	{
		arr[i].point=NULL;
	}
}
hashData* createNewHashElement(char input[])	//Dynamically allocates memory for the hash table to be hashed and initializes it
{
	hashData* newElement=malloc(sizeof(hashData));
	newElement->count=1;
	strcpy(newElement->str,input);
	newElement->next=NULL;
	return newElement;
}

void insertIntoHashTable(char str[])
{
	int key=hashMe(str);
	hashData* ptr;
	if(arr[key].point==NULL)
		arr[key].point=createNewHashElement(str);
	else
	{
		ptr=arr[key].point;
		while(ptr->next!=NULL)
		{
			if(strcmp(str,ptr->str)==0)
			{
				ptr->count++;
				return;
			}
			ptr=ptr->next;
		}
		if(strcmp(str,ptr->str)==0)
		{
			ptr->count++;
			return;
		}
		ptr->next=createNewHashElement(str);
	}
}

char* searchInTableForHighest()
{
	int key=1,i,j,k,flag=0;
	hashData*ptr= arr[key].point;
	FILE *de2bugOut;
	de2bugOut=fopen("/home/hari/Desktop/project_SLAP/Repository/soothu666.txt","w");
	fputs("All the way till here\n",de2bugOut);

	hashData *a[5];
	for(i=0;i<MAX;i++)
	{
		ptr=arr[i].point;
		if(ptr!=NULL)
		{
			flag=1;
			a[0]=ptr;
			break;
		}
	}
	fputs("Second stop\n",de2bugOut);

	for(i=4;i>0;i--)
		a[i]=a[0];
	if(flag==0)
		return 0;
	for(i=0;i<MAX;i++)
	{
		ptr=arr[i].point;
		while(ptr!=NULL)
		{
			for(k=0;k<5;k++)
			{
				if(a[k]==a[k+1]&&k<4)
					for(j=k+1;j<5;j++)
						a[j]=ptr;
				if(ptr->count>a[k]->count)
				{
					for(j=k+1;j<5;j++)
					{
						a[j]=a[j-1];
					}
					a[k]=ptr;
					break;
				}
			}
			ptr=ptr->next;
		}
	}
	fputs("Third stop\n",de2bugOut);
			fclose(de2bugOut);
	if(a[0]==NULL)
	{
		FILE *d1ebugOut;
		d1ebugOut=fopen("/home/hari/Desktop/project_SLAP/Repository/soothuError.txt","w");
		fputs("All the way till here\n",d1ebugOut);
		fclose(d1ebugOut);
		return NULL;
	}
	/*for(i=0;i<5;i++)
		printf("%s -> %d\n",a[i]->str,a[i]->count);
	*/
	char outTemp[1500],fileNameVar[200],*pos;
//	char* outString=malloc(sizeof(char)*1500);
	char outString[1500];
	strcpy(outString,"");						//this variable will contain the final string to return
	//strcpy(fileNameVar,"/home/vedant/Desktop/Project/");	//local directory
	FILE *fp;
	strcpy(outString,"");
	for(i=0;i<5;i++)
	{
		strcpy(fileNameVar,"/home/hari/Desktop/project_SLAP/Repository/Lyrics/");
		strcat(outString,"\\\"");
		strcat(fileNameVar,a[i]->str);
		fp=fopen(fileNameVar,"r");
		fgets(outTemp,1500,fp);
		strcat(outString,outTemp);
		if(outString[strlen(outString)-2]==' '||outString[strlen(outString)-2]=='\n')
			outString[strlen(outString)-2]='\0';
		else if (outString[strlen(outString)-1]==' '||outString[strlen(outString)-1]=='\n')
			outString[strlen(outString)-1]='\0';
		strcat(outString,"\\\"");
		strcat(outString," - ");
		fgets(outTemp,1500,fp);
		strcat(outString,outTemp);
		if(outString[strlen(outString)-2]==' '||outString[strlen(outString)-2]=='\n')
			outString[strlen(outString)-2]='\0';
		else if (outString[strlen(outString)-1]==' '||outString[strlen(outString)-1]=='\n')
			outString[strlen(outString)-1]='\0';
		strcat(outString,"\\n");
		fgets(outTemp,1500,fp);
		if(strcmp(outTemp,"\n")==0)
			fgets(outTemp,1500,fp);
		strcat(outString,outTemp);
		if(outString[strlen(outString)-2]==' '||outString[strlen(outString)-2]=='\n')
			outString[strlen(outString)-2]='\0';
		else if (outString[strlen(outString)-1]==' '||outString[strlen(outString)-1]=='\n')
			outString[strlen(outString)-1]='\0';
		strcat(outString,"\\n");
		fgets(outTemp,1500,fp);
		if(strcmp(outTemp,"\n")==0)
			fgets(outTemp,1500,fp);
		strcat(outString,outTemp);
		if(outString[strlen(outString)-2]==' '||outString[strlen(outString)-2]=='\n')
			outString[strlen(outString)-2]='\0';
		else if (outString[strlen(outString)-1]==' '||outString[strlen(outString)-1]=='\n')
			outString[strlen(outString)-1]='\0';
		strcat(outString,"\\n");
		fgets(outTemp,1500,fp);
		if(strcmp(outTemp,"\\n")==0)
			fgets(outTemp,1500,fp);
		strcat(outString,outTemp);
		if(outString[strlen(outString)-2]==' '||outString[strlen(outString)-2]=='\n')
			outString[strlen(outString)-2]='\0';
		else if (outString[strlen(outString)-1]==' '||outString[strlen(outString)-1]=='\n')
			outString[strlen(outString)-1]='\0';
		strcat(outString,"\\n");
		strcat(outString,"\\t");
		fclose(fp);
	}
	
	for(i=0;i<5;i++)
	{
		strcat(outString,a[i]->str);
		strcat(outString,"\\t");
	}
	//printf("%s",outString);
	FILE *debugOut;
	debugOut=fopen("/home/hari/Desktop/project_SLAP/Repository/soothu.txt","w");
	fputs("All the way till here\n",debugOut);
	fclose(debugOut);
	return outString;
}
void dataFromFile(char* str)
{
	FILE *fp;
	int f;			
	for(f=0;str[f]!='\0';f++){
		str[f]=tolower(str[f]);
	}
	//printf("%s ",str);
	char inp[10000],*internal;
	fp=fopen("/home/hari/Desktop/project_SLAP/Repository/wordListOut.txt","r");
	while(fgets(inp,10000,fp))
	{
		internal=strtok(inp," \n");
		if(strcmp(str,inp)==0)
		{
			internal=strtok(NULL," \n");
			do
			{
				insertIntoHashTable(internal);
				internal=strtok(NULL," \n");
			}
			while(internal!=NULL);
			return;
		}
	}
	fclose(fp);
}

void printTable()
{
	int i;
	hashData *traverse;
	for(i=0;i<50;i++)
	{
		traverse=arr[i].point;
		while(traverse!=NULL)
		{
			printf("\nCount for %s is %d with key %d\n",traverse->str,traverse->count,hashMe(traverse->str));
			traverse=traverse->next;
		}
	}
}

int hashMe(char* str)
{
	return (tolower(str[0])-'a'+200)%MAX;
}

static PyObject * lyricsSearch_search(PyObject *self, PyObject *args)
{
	const char *line;
	FILE *debugOut;
	debugOut=fopen("/home/hari/Desktop/project_SLAP/Repository/soothu.txt","w");
	fputs("I make changes\n",debugOut);

	if(!PyArg_ParseTuple(args, "s", &line))
		return NULL;
		
	initializeTable();
	fputs("Initialized\n",debugOut);
	//char line[100],*input;
	fputs(line,debugOut);
	int i=0;
	//scanf("%[^\n]s",line);
	strcat(line," ");
	fclose(debugOut);
	char ch=line[i];
	char* word2;
	word2=(char*)malloc(sizeof(char)*20);
	while(ch!=' '&&ch!='\0'&&ch!='\n'){
		int j=0;
		while(ch!=' '&&ch!='\0'&&ch!='\n'){
			ch=line[i];                         //Take a char from string
			word2[j++]=line[i++];                    //Input that letter into string
		}
		word2[j--]='\0';
		word2[j--]='\0';
		//printf("%s<<",word2);
		ch=line[i];
		dataFromFile(word2);
	}
	char *sts;
	sts= searchInTableForHighest();
	return PyString_FromString(sts);
	//return Py_BuildValue("s", sts);
}	

//The Module’s Method Table
static PyMethodDef lyricsSearch_methods[] = {
	{"search", lyricsSearch_search, METH_VARARGS, "Searches music repository by lyrics"},
	{NULL, NULL, 0, NULL} /* Sentinel */
};

//The Module's Initialization Function
PyMODINIT_FUNC initlyricsSearch(void){
	PyObject *m;
    m = Py_InitModule("lyricsSearch", lyricsSearch_methods);

    if (m == NULL)
        return;

    lyricsSearchError = PyErr_NewException("lyricsSearch.error", NULL, NULL);
    Py_INCREF(lyricsSearchError);
    PyModule_AddObject(m, "error", lyricsSearchError);
}

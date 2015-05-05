#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX_SIZE 830             //Specify the length of the array of string
#define MAX_HITS 100            
#define MAX_ARTIST 338   		//SPECIFY THE MAX NUMBER OF ARTISTS
/*       
 * 
 * 
 * 		THIS IS NOT FINAL I HAVE TO MAKE IT WORK FOR VARIABLE SET SIZES
 *
 * 
 */
typedef struct sng
{
	char song_name[60];
	char file_name[60];
}song;

song arr[MAX_SIZE];
typedef struct Hit
{
	int pos;
	float inpos;
	float change;
	int hit_pos;
}searchhit;


typedef struct node
{
	char song_name[60];
	struct node* next;
}node_t;
typedef struct artist
{
	char artist_name[60];
	struct node* head;
}artist_t;

artist_t artists[MAX_ARTIST];

char* isSubstring(char str1[],char str2[])
{
	return strstr(str1,str2);
}

char* toLower(char str[])
{
	int i=0;
	char* lower=malloc((sizeof(char)*strlen(str))+1);
	for(i=0;i<strlen(str);i++)
	{
		if(isalpha((int)str[i]))
			lower[i]=(char)(tolower((int)(str[i])));
		else
		lower[i]=str[i];
	}
	return lower;
}

float posPercent(char haystack[],char needle[])
{
	int i,j,ct=0;
	float temp;
	for(i=0;i<strlen(haystack);i++)
	{
		for(j=0;j<strlen(needle);j++)
		{
			if(haystack[i]==needle[j] && i==j)
			ct++;
		}
	}
	temp=(((float)ct/(float)strlen(needle)));
	temp=temp*100;
	return temp;
}

float editDistance(char str1[],char str2[])
{
	int i=0,j=0,left=0,up=0,diag=0,cost=0;
	int change;
	int len1=strlen(str1);
	int len2=strlen(str2);
	int arr[len1+1][len2+1];
	for(i=0;i<=len2;i++)
	{
		arr[0][i]=i;
	}
	for(i=0;i<=len1;i++)
	{
		arr[i][0]=i;
	}


	for(i=1;i<=len2;i++)
	{
		for(j=1;j<=len1;j++)
		{
			up=arr[j-1][i];
			left=arr[j][i-1];
			diag=arr[j-1][i-1];
			
			if(str1[j-1]==str2[i-1])
			{	
				cost=0;
			}
			else
			{
				cost=1;
			}
			
			up++;
			left++;
			diag+=cost;
			
			if(up<=left&&up<=diag)
			arr[j][i]=up;
			else if(left<=up&&left<=diag)
			arr[j][i]=left;
			else
			arr[j][i]=diag;
		}
	}

	change= arr[len1][len2];
	float percent_change=((float)change)/((float)strlen(str1));
	percent_change*=100;
	return percent_change;
}

void insertSong(int index,char* song_name)
{
	node_t* newnode=malloc(sizeof(node_t));
	strcpy(newnode->song_name,song_name);
	newnode->next=artists[index].head;
	artists[index].head=newnode;
}

char* printSongs(node_t* head)
{
	char *songs;
	songs=malloc(sizeof(char)*2000);
	while(head!=NULL)
	{
		strcat(strcat(songs,"\n"),head->song_name);
		head=head->next;
	}
	strcat(songs,"\n\n");
	return songs;
}

char* song_lines(char* str)
{
	FILE* fptr=fopen(str,"r");
	int ct=0;
	if(fptr)
	printf("opened")
	else
	{
		printf("failed");
		exit(1);
	}
	char* output=malloc(sizeof(char)*1000);
	char line[200];
	while(ct<6)
	{	
		if(ct>2)
		{
		fscanf(fptr,"%s",line);
		strcat(output,strcat(line,"\\n"));
		ct++;
		}
	}
	return output;
}

char* song_details(char* fname)
{
	int i=0,flag=0;
    char artist[150], songName[150];
    strcpy(artist,"");
    strcpy(songName,"");
    char* output=malloc(sizeof(char)*300);
    for(i=0;i<strlen(fName);i++)
    {
    	if(fName[i]==':')
    	{
    		artist[flag]='\0';
    		break;
    	}
    	if(fName[i]=='_')
    		artist[flag]=' ';
    	else
    		artist[flag]=fName[i];
    	flag++;
    }
    i++;
	flag=0;
    for(;fName[i]!='\0';i++)
    {
    	if(fName[i]=='.')
    	{
    		if(fName[i+1]=='t')
    		{
    			songName[flag]='\0';
    			break;
    		}
    		else
    		{
    			songName[flag]=fName[i];
    			flag++;
    			continue;
    		}    			
    	}
    	if(fName[i]=='_')
    		songName[flag]=' ';
    	else
    		songName[flag]=fName[i];
    	flag++;
    }
    
	strcat(output,"\"");
	strcat(output,songName);
	strcat(output,"\" -");
	strcat(output,artist);
	strcat(output,"\n");
	return output;
}



char* Songmain(char *str)
{
	searchhit hit[100];
	FILE * fptr=fopen("new.txt","r");
	if(!fptr)
	{	
	printf("not opened");
	return 0;
}
	char temp[60];
	char line[60];
	int i=0;
	int flag=1;
	while(fscanf(fptr,"%s",line))             //Looping through the file_names.txt(I used  fscanf because it does not take 									//the \n into the buffer
		 {
			 
			 if(strcmp(temp,line)==0)		//condition to exit the file after reading it
			 break;
			

				if(flag%2==0)
				{
				strcpy(arr[i].file_name,line);
				i++;
			}
				else
				{
				strcpy(arr[i].song_name,line);
				
				
			}
							
			flag++;
			
			strcpy(temp,line); //fscanf is repeating the last string again and again so I checked it with a temp string
	   }


	   // ---------------| Searching Part Starts from here |-----------------
	  	   
	  	   
	  	   
char * low_needle=toLower(str);
char* low_hay;
char* token_hay;
char* temp_needle;
								/* Substring technique*/

	
	temp_needle=strtok(low_needle," ");
	int fk=0;
	while(temp_needle != NULL)
	{
		fk++;
		temp_needle=strtok(NULL," ");
	}
	char* token_needle[fk];

	fk=0;
	
	
	low_needle=toLower(str);
	
	temp_needle=strtok(low_needle," ");
	while(temp_needle != NULL)
	{
		token_needle[fk]=malloc(strlen(temp_needle)+1);
		strcpy(token_needle[fk],temp_needle);
		fk++;
		temp_needle=strtok(NULL," ");
	}
	
	int j=0;  int hits=0; int tok=0;
// after this replace temp_needle with token_needle[i]		

	
		/* -----SEARCHING FOR HITS STARTS HERE-----*/
		

for(j=0;j<fk;j++)
{
	
for(i=0;i<MAX_SIZE;i++)
{
	low_hay=toLower(arr[i].song_name);
	
	tok=0;
	if(isSubstring(low_hay,token_needle[j]))
	{
	
	token_hay=strtok(low_hay,"_");
	
	/* -----DEBUGGING-----*/
	//printf("haystack :%s needle:%s change=%.2f Inposition= %.2f\n",token_hay,token_needle[j],editDistance(token_hay,token_needle[j]),posPercent(token_hay,token_needle[j]));
	while( token_hay != NULL ) 
   {	

	if(posPercent(token_hay,token_needle[j])>=50 )
	{
		if(editDistance(token_hay,token_needle[j])<50)
		{
			hit[hits].change=editDistance(token_hay,token_needle[j]);
			hit[hits].inpos=posPercent(token_hay,token_needle[j]);
			hit[hits].pos=i;
			hit[hits].hit_pos=tok;
			hits++;
			/* -----DEBUGGING-----*/
			//printf("%s, percent inPos=%.2f , percent change=%.2f\n",arr[i].song_name,posPercent(token_hay,token_needle[j]),editDistance(token_hay,token_needle[j]));
			break;
		}
	}

	tok++;	
	token_hay=strtok(NULL,"_");
   }
   
	}
	else
	{
		low_hay=toLower(arr[i].song_name);
		token_hay=strtok(low_hay,"_");
	
	while( token_hay != NULL ) 
   {
	   if(editDistance(token_hay,token_needle[j])<30)
	   {
		   	hit[hits].change=editDistance(token_hay,token_needle[j]);
			hit[hits].inpos=-1;
			hit[hits].pos=i;
			hit[hits].hit_pos=tok;
			hits++;
			/* -----DEBUGGING-----*/
		   //printf("%s ,No substring but change=%.2f\n",arr[i].song_name,editDistance(token_hay,token_needle[j]));
		   break;
	   }
	   tok++;
	   token_hay=strtok(NULL,"_");
   }
}
}

				/* -----SEARCHING FOR HITS ENDS HERE-----*/


}

int layer1=0;
int layer2=0;
int layer3=0;
int layer4=0;

int results[hits];
int counter=0;
for(i=0;i<hits;i++)
{
	for(j=i+1;j<hits;j++)
	{
		if(hit[i].pos==hit[j].pos)
		{
			/* -----DEBUGGING-----*/
			//printf("%d). Song=%s HIT_POS=%d PERCENT INPOS=%.2f PERCENT TO CHANGE=%.2f \n",(j+1),arr[hit[j].pos].song_name,hit[j].hit_pos,hit[j].inpos,hit[j].change);
			layer1=1;
			results[counter]=hit[j].pos;
			counter++;
		}
	}
}

if(layer1==0)
{
	for(i=0;i<hits;i++)
	{
		if(hit[i].inpos>50 && hit[i].hit_pos<2)
		{
			layer2=1;
			/* -----DEBUGGING-----*/
			//printf("%d). Song=%s HIT_POS=%d PERCENT INPOS=%.2f PERCENT TO CHANGE=%.2f \n",(i+1),arr[hit[i].pos].song_name,hit[i].hit_pos,hit[i].inpos,hit[i].change);
			results[counter]=hit[i].pos;
			counter++;
		}
	}
}

if(layer2==0 && layer1==0)
{
	for(i=0;i<hits;i++)
	{
		if(hit[i].inpos<0 && hit[i].change<50)
		{
			layer3=1;
			/* -----DEBUGGING-----*/
			//printf("%d). Song=%s HIT_POS=%d PERCENT INPOS=%.2f PERCENT TO CHANGE=%.2f \n",(i+1),arr[hit[i].pos].song_name,hit[i].hit_pos,hit[i].inpos,hit[i].change);
			results[counter]=hit[i].pos;
			counter++;		
		}
	}
}

if(layer1==0 && layer2==0 && layer3==0)
{
for(i=0;i<hits;i++)
{
	layer4=1;
	/* -----DEBUGGING-----*/
	/*printf("%d). Song=%s HIT_POS=%d PERCENT INPOS=%.2f PERCENT TO CHANGE=%.2f \n",(i+1),arr[hit[i].pos].song_name
	,hit[i].hit_pos,hit[i].inpos,hit[i].change);*/
			results[counter]=hit[i].pos;
			counter++;
}
}

if(layer4==0 && layer1==0 && layer2==0 && layer3==0 )
{
	
	return NULL;
}


				/* -----CREATING FORMATED OUTPUT-----*/

char* output;
output=malloc(sizeof(char)*2000);
char* delim="\\t";
char address[200];
for(i=0,j=0;i<5;i++)
{	
	if(j<counter)
	{
	strcat(address,"location");
	strcat(address,arr[results[j]].file_name);	
	strcat(output,song_details(address));
	strcat(output,song_lines);
	j++;
	}
	else
	{
		j=0;
		i--;
	}
}




for(i=0,j=0;i<5;i++)
{	
	if(j<counter)
	{
	strcat(strcat(output,"\\t"),arr[results[j]].file_name);
	j++;
	}
	else
	{
		j=0;
		i--;
	}
}



/* -----DEBUGGING-----*/
//printf("\nHITS=%d\n",hits);	

	   return output;
   }
   
   
char* Artistmain(char *str)
{

	searchhit hit[100];
	FILE* fptr;
	int ct=0;int i=0;
	char* token;
	int newline=0;
	char temp[400];
	fptr=fopen("IaMdANGEROUS.txt","r");
	
	if(!fptr)
	{
		printf("file cannot be opened\n");
		exit(1);
	}
	char line[400];
	while(fgets(line,400,fptr))
	{
		int x=strlen(line);
		line[x-1]='\0';
		if(strcmp(temp,line)==0)
		break;
		token=strtok(line," "); 
		strcpy(artists[ct].artist_name,token);
		while(token != NULL)
		{
			token=strtok(NULL," ");
			if(token)
			{
				if(strcmp(token,"\n")==0)
				newline++;
			insertSong(ct,token);
		}
		
		}
		ct++;
		strcpy(temp,line);
	}
	

int flag=0;

char * low_needle=toLower(str);
char* low_hay;
char* token_hay;
char* temp_needle;
								/* Substring technique*/
								
								//SEARCH STARTS HERE
	
	temp_needle=strtok(low_needle," ");
	int fk=0;
	while(temp_needle != NULL)
	{
		fk++;
		temp_needle=strtok(NULL," ");
	}
	char* token_needle[fk];
	fk=0;
	
	low_needle=toLower(str);
	temp_needle=strtok(low_needle," ");
	while(temp_needle != NULL)
	{
		token_needle[fk]=malloc(strlen(temp_needle)+1);
		strcpy(token_needle[fk],temp_needle);
		fk++;
		temp_needle=strtok(NULL," ");
	}

	
	int j=0;  int hits=0; int tok=0;
// after this replace temp_needle with token_needle[i]		

		/* -----SEARCHING FOR HITS STARTS HERE-----*/

for(j=0;j<fk;j++)
{
	//printf("-----input token:%s------\n",token_needle[j]);
for(i=0;i<MAX_ARTIST;i++)
{
	low_hay=toLower(artists[i].artist_name);
	
	tok=0;
	if(isSubstring(low_hay,token_needle[j]))
	{
	
	token_hay=strtok(low_hay,"_");
	
	while( token_hay != NULL ) 
   {	
	   /*------STATS FOR DEBUGGING CERTAIN QUERIES------*/
	    //printf("haystack :%s needle:%s change=%.2f Inposition= %.2f\n",token_hay,token_needle[j],editDistance(token_hay,token_needle[j]),posPercent(token_hay,token_needle[j]));
	   

	if(posPercent(token_hay,token_needle[j])>=50 )
	{
		if(editDistance(token_hay,token_needle[j])<=50)
		{
			hit[hits].change=editDistance(token_hay,token_needle[j]);
			hit[hits].inpos=posPercent(token_hay,token_needle[j]);
			hit[hits].pos=i;
			hit[hits].hit_pos=tok;
			hits++;
			/*------STATS FOR DEBUGGING CERTAIN QUERIES------*/
			//printf("%s, percent inPos=%.2f , percent change=%.2f\n",artists[i],posPercent(token_hay,token_needle[j]),editDistance(token_hay,token_needle[j]));
			break;
		}
		
		
	}
	
			if(editDistance(token_hay,token_needle[j])<40)   // INPOS IS -1 TO CHECK FOR CHANGE
		{
			hit[hits].change=editDistance(token_hay,token_needle[j]);
			hit[hits].inpos=-1;
			hit[hits].pos=i;
			hit[hits].hit_pos=tok;
			hits++;
			/*------STATS FOR DEBUGGING CERTAIN QUERIES------*/
			//printf("%s, percent inPos=%.2f , percent change=%.2f\n",artists[i],posPercent(token_hay,token_needle[j]),editDistance(token_hay,token_needle[j]));
			break;
		}


	tok++;	
	token_hay=strtok(NULL,"_");
   }
   
	}

		else
		{
		
		low_hay=toLower(artists[i].artist_name);
		token_hay=strtok(low_hay,"_");
		
		/*------STATS FOR DEBUGGING CERTAIN QUERIES------*/
		//printf("haystack :%s needle:%s change=%.2f Inposition= %.2f\n",token_hay,token_needle[j],editDistance(token_hay,token_needle[j]),posPercent(token_hay,token_needle[j]));	
	while( token_hay != NULL ) 
   {
	   if(editDistance(token_hay,token_needle[j])<50)
	   {
		   	hit[hits].change=editDistance(token_hay,token_needle[j]);
			hit[hits].inpos=-1;
			hit[hits].pos=i;
			hit[hits].hit_pos=tok;
			hits++;
			/*------STATS FOR DEBUGGING CERTAIN QUERIES------*/
		   //printf("%s ,No substring but change=%.2f\n",artists[i],editDistance(token_hay,token_needle[j]));
		   break;
	   }
	   tok++;
	   token_hay=strtok(NULL,"_");
   }
}

}

										//ENDS HERE
	
	
}
			/* -----SEARCHING FOR HITS ENDS HERE-----*/

int layer1=0;
int layer2=0;
int layer3=0;
int layer4=0;


int results[hits];
int counter=0;

for(i=0;i<hits;i++)
{
	for(j=i+1;j<hits;j++)
	{
		if(hit[i].pos==hit[j].pos)
		{
			/*------STATS FOR DEBUGGING CERTAIN QUERIES------*/
			//printf("%d). Artist=%s HIT_POS=%d PERCENT INPOS=%.2f PERCENT TO CHANGE=%.2f \n",(j+1),artists[hit[j].pos].artist_name,hit[j].hit_pos,hit[j].inpos,hit[j].change);
			//printSongs(artists[hit[j].pos].head);
			layer1=1;
			results[counter]=hit[j].pos;
			counter++;
			//printf("lay1=%d\n",layer1);
		}
	}
}

if(layer1==0)
{
	for(i=0;i<hits;i++)
	{
		if(hit[i].inpos>50 && hit[i].hit_pos<2)
		{
			
			/*------STATS FOR DEBUGGING CERTAIN QUERIES------*/
			//printf("%d). Artist=%s HIT_POS=%d PERCENT INPOS=%.2f PERCENT TO CHANGE=%.2f \n",(i+1),artists[hit[i].pos].artist_name,hit[i].hit_pos,hit[i].inpos,hit[i].change);
			//printSongs(artists[hit[i].pos].head);
			layer2=1;
			results[counter]=hit[i].pos;
			counter++;
			//printf("lay2=%d\n",layer2);
		}
	}
}

if(layer2==0 && layer1==0)
{
	for(i=0;i<hits;i++)
	{
		if(hit[i].inpos<0 && hit[i].change<40)
		{
			
			/*------STATS FOR DEBUGGING CERTAIN QUERIES------*/
			//printf("%d). Artist=%s HIT_POS=%d PERCENT INPOS=%.2f PERCENT TO CHANGE=%.2f \n",(i+1),artists[hit[i].pos].artist_name,hit[i].hit_pos,hit[i].inpos,hit[i].change);
			//printSongs(artists[hit[i].pos].head);
			layer3=1;
			results[counter]=hit[i].pos;
			counter++;
			//printf("lay3=%d\n",layer3);
		}
	}
}

if(layer1==0 && layer2==0 && layer3==0)
{
for(i=0;i<hits;i++)
{
	/*------STATS FOR DEBUGGING CERTAIN QUERIES------*/
	//printf("%d). Artist=%s HIT_POS=%d PERCENT INPOS=%.2f PERCENT TO CHANGE=%.2f \n",(i+1),artists[hit[i].pos].artist_name,hit[i].hit_pos,hit[i].inpos,hit[i].change);
	//printSongs(artists[hit[i].pos].head);
	layer4=1;
	results[counter]=hit[i].pos;
	counter++;
	//printf("lay4=%d\n",layer4);
}
}

if(layer4==0 && layer1==0 && layer2==0 && layer3==0 )
{
	//printf("No results found :("); 
	return NULL;
}


char* output=malloc(sizeof(char)*8000);
for(i=0,j=0;i<5;i++)
{	
	if(j<counter)
	{
	strcat(strcat(output,artists[results[j]].artist_name),printSongs(artists[results[j]].head));
	j++;
	}
	else
	{
		j=0;
		i--;
	}
}


/*------STATS FOR DEBUGGING CERTAIN QUERIES------*/
//printf("HITS=%d\n",hits);	


		fclose(fptr);
		return output;
	}	
			 
void main()
{
	char str[60];
	printf("Enter artist:\n");
	scanf("%[^\n]s",str);
	printf("%s",Artistmain(str));
	printf("Enter song:");
	while(getchar()!='\n');
	scanf("%[^\n]s",str);
	printf("%s",Songmain(str));
}		 

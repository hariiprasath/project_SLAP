#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
void listByArtist(char*fName);
void replaceName(char* a);
int main()
{
	fstream fin;
	char samp[150];
	//fin.open("/home/vedant/Desktop/Project/LyricsWikia/file_list.txt",ios::in);
	fin.open("/home/vedant/Desktop/Project/SongNames.txt",ios::in);
	do
	{
		fin.getline(samp,150,' ');	
		fin.getline(samp,150,'\n');
		listByArtist(samp);
	}while(!fin.eof());
	return 0;
}


void listByArtist(char*fName)							//Lyrics Wikia
{
    fstream fin,rand,temp;
    ifstream foutin;
    fstream foutout;
    
    int i,flag=0;
    char artist[150],songName[150],outArtist[150];
    char outSongName[150];
    strcpy(artist,"");
    //cout<<"Started";
    strcpy(songName,"");
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
	strcpy(outArtist,artist);
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
    //cout<<flag<<endl;
    strcpy(outSongName,songName);
    //Search if Artist Exists, if yes, add to that
    //If no, add at end
    replaceName(outSongName);
    replaceName(outArtist);
    char inp[150];
    int check=0;
    foutin.open("/home/vedant/Desktop/Project/IaMdANGEROUS.txt",ios::in);
    foutin.seekg(0,ios::beg);
    while(!foutin.eof())
    {
		foutin>>inp;
		
		cout<<endl<<inp<<"\t"<<outArtist<<"\t	 this"<<endl;
		if(strcmp(inp,outArtist)==0)
			check=1;
	}
	cout<<check;
	foutin.close();
	foutout.open("/home/vedant/Desktop/Project/IaMdANGEROUS.txt",ios::out|ios::in);
	//foutout.seekp(0,ios::beg);
    if(check==0)
    {
		foutout.seekp(0,ios::end);
		///cout<<"Printing "<<outArtist<<" "<<outSongName<<endl;
		foutout<<outArtist<<" "<<outSongName<<endl;
    }
    else
    {
		foutout.seekp(-1,ios::end);
		foutout<<' '<<outSongName<<endl;
		
	}
    foutout.close();
}
void replaceName(char* a)
{
	int i;
	for(i=0;a[i]!='\0';i++)
	{
		if(a[i]==' ')
		{
			if(a[i+1]=='\0')
			{
				a[i]='\0';
				return;
			}
			a[i]='_';
		}
	}
}


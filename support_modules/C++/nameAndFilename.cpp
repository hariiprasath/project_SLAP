#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void isolateNameAndSave(char*fName);
void replaceName(char* a);
int main()
{
	fstream fin;
	char samp[150];
	//fin.open("/home/vedant/Desktop/Project/LyricsWikia/file_list.txt",ios::in);
	fin.open("/home/vedant/Desktop/Project/Output/file_list.txt",ios::in);
	do
	{
		fin>>samp;					
		isolateNameAndSave(samp);
	}while(!fin.eof());
	return 0;
}
void isolateNameAndSave(char*fName)							
{
    fstream fin,rand;
    char inName[100];
    char songName[100];
    strcpy(inName,"/home/vedant/Desktop/Project/Output/");
    strcat(inName,fName);
    strcpy(songName,"");
    rand.open(inName,ios::in);
    rand.seekg(0,ios::beg);
    if(!rand.eof())
    {
		rand.getline(songName,100,'\n');
	}
    rand.close();
    replaceName(songName);
    fin.open("/home/vedant/Desktop/Project/SongNames.txt",ios::out|ios::app);
    fin.seekp(0,ios::beg);
    fin<<songName<<" "<<fName<<endl;
    
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

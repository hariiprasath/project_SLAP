#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
void listByArtist(char*word,char* songName);
void replaceName(char* a);
int main()
{
	fstream fin;
	char samp1[150],*word,*song;
	int pos=0;
	//fin.open("/home/vedant/Desktop/Project/LyricsWikia/file_list.txt",ios::in);
	fin.open("/home/vedant/Desktop/Project/actual3.txt",ios::in);
	do
	{
		fin.getline(samp1,150,'\n');	
		word=strtok(samp1," \n");
		song=strtok(NULL," \n");
		//cout<<"Position: "<<fin.tellg()<<endl;
		listByArtist(word,song);
	}while(!fin.eof());
	return 0;
}


void listByArtist(char*word,char* songName)							//Lyrics Wikia
{
    ifstream foutin;
    fstream foutout;
    //cout<<"\nFunctionStart";
    char inp[150],tempo[150];
    int check=0;
    //cout<<"\nAttemptingToOpen wordListOut.txt";
    foutin.open("/home/vedant/Desktop/Project/wordListOut.txt",ios::in);
    //cout<<"\nOpened wordListOut.txt";
    foutin.seekg(0,ios::beg);
    foutin>>tempo;
    while(!foutin.eof())
    {
		
		//inp=strtok(tempo," \n");
		strcpy(inp,tempo);
		if(inp==NULL)
			break;
		//cout<<endl<<inp<<"\t"<<word<<"\t	 this"<<check<<endl;
		if(strcmp(inp,word)==0)
		{
			check=1;
			break;
		}
		foutin>>tempo;
	}
	//cout<<check<<"<< Check\n";
	foutin.close();
	//cout<<"\ncomingClosedFile";
	foutout.open("/home/vedant/Desktop/Project/wordListOut.txt",ios::out|ios::in);
	//cout<<"comingOpenedNext";
	//foutout.seekp(0,ios::beg);
    if(check==0)
    {
		//cout<<"coming";
		foutout.seekp(-1,ios::end);
		//cout<<"Printing "<<word<<" "<<songName<<endl;
		foutout<<'\n'<<word<<" "<<songName<<'\n';
    }
    else
    {
		//cout<<"PrintingIntoFile"<<songName;
		foutout.seekp(-1,ios::end);
		foutout<<' '<<songName<<endl;
		
	}
    foutout.close();
}

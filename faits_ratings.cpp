//g++ faits_ratings.cpp -o ratings -lcurl
//./ratings ratings.csv faits_ratings.sql

#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream lecture(argv[1], ios::in);
	ofstream ecriture(argv[2], ios::out | ios::trunc);

	string insert  = "INSERT INTO Rating Values(\'";
	char caractere;
	
	if(lecture && ecriture)
	{
		string line ="";
		string insertion="";
		getline(lecture,line);
		ecriture << insert;
		while(lecture.get(caractere))
		{
			if(caractere == '\n')	//Si one saut de ligne est \n
			{
				//if(caractere == '\r') //Si one saut de ligne est \r\n
				//{
				//lecture.get(caractere); // saut \n
				ecriture << insertion;
				
				insertion = "";
				ecriture << "\');" << "\n";
				insertion += insert;
			}
			else if(caractere == '\'')
			{
				insertion += '\\';
				insertion += caractere;
			}
			else
			{
				insertion += caractere;
			}
		}
		lecture.close();
		ecriture.close();
	}
 	else
	{
		cerr << "Impossible d'ouvrir un des fichiers." << endl;
	}
	return 0;
}
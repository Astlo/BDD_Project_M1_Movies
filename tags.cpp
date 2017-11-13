#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream lecture(argv[1], ios::in);
	ofstream ecriture(argv[2], ios::out | ios::trunc);

	string insert  = "INSERT INTO Tags Values(\'";
	char caractere;
	
	if(lecture && lecture2 && ecriture)
	{
		string line ="";
		string insertion="";
		getline(lecture,line);	
		getline(lecture2,line);	
		ecriture << insert;
		lecture.get(caractere);
		while(caractere != ',')
		{
			insertion += caractere;
		}
		insertion += ',';
		while(lecture.get(caractere))
		{
			if(caractere == '\n')
			{
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
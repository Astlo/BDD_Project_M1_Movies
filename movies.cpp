#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
	ifstream lecture(argv[1], ios::in);
	ifstream lecture2(argv[2], ios::in);
	ofstream ecriture(argv[3], ios::out | ios::trunc);

	string insert  = "INSERT INTO Movies Values(\'";
	char caractere;
	
	if(lecture && lecture2 && ecriture)
	{
		string line ="";
		string insertion="";
		getline(lecture,line);	
		ecriture << insert;
		while(lecture.get(caractere))
		{
			if(caractere == '\n')
			{
				insertion = insertion.substr(0, insertion.size()-1);
				ecriture << insertion;
				insertion = "";
				ecriture << "\');" << "\n";
				insertion += insert;
			} 
			else if(caractere == '\"')
			{
				lecture.get(caractere);
				while(caractere != '\"')
				{
					insertion += caractere;
					lecture.get(caractere);
				}
			} 
			else if(caractere == ',')
			{
				ecriture << insertion << "\',\'";
				insertion = "";
			}
			else
			{
				insertion += caractere;
			}
		}
		lecture.close();
		lecture2.close();
		ecriture.close();
	}
 	else
	{
		cerr << "Impossible d'ouvrir un des fichiers." << endl;
	}
	return 0;
}
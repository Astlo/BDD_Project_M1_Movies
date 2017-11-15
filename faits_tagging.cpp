//g++ faits_tagging.cpp -o tagging -lcurl

//./tagging ml-latest/tags.csv faits_tagging.sql



#include <iostream>

#include <fstream>

#include <string>

#include <curl/curl.h>



using namespace std;



int main(int argc, char const *argv[])

{

	ifstream lecture(argv[1], ios::in);

	ofstream ecriture(argv[2], ios::out | ios::trunc);



	string insert  = "INSERT INTO Tagging Values(";

	char caractere;

	

	if(lecture && ecriture)

	{

		string line ="";

		string insertion="";

		getline(lecture,line);

		ecriture << insert;

		while(lecture.get(caractere))

		{

			for(int i=0; i<2; ++i)

			{

				while(caractere != ',')

				{

					insertion += caractere;

					lecture.get(caractere);

				}

				insertion += caractere;

				lecture.get(caractere);

			}

			insertion += '\'';

			while(caractere != ',')

			{

				if(caractere == '\"')

				{

					lecture.get(caractere);

					while(caractere != '\"')

					{

						if(caractere == '\'')

						{

							insertion += ' ';

						}

						else if(caractere == '&')

						{

							insertion += "and";

						}

						else if(caractere == ',')

						{

							insertion += " ";

						}

						else if(caractere == '\\')

						{

							insertion += ' ';

						}

						else

						{

							insertion += caractere;

						}

						lecture.get(caractere);

					}

				} 

				else if(caractere == ',')

				{

					insertion += " ";

					insertion = "";

				}

				else if(caractere == '\'')

				{

					insertion += ' ';

				}

				else if(caractere == '\\')

				{

					insertion += ' ';

				}

				else if(caractere == '&')

				{

					insertion += "and";

				}

				else

				{

					insertion += caractere;

				}

				

				lecture.get(caractere); // saut \n

			}

			lecture.get(caractere);

			insertion += '\'';

			insertion += ',';

			//while(caractere == '\n')	//Si le saut de ligne est \n

			//{

			while(caractere != '\r') //Si le saut de ligne est \r\n

			{	

				insertion += caractere;

				lecture.get(caractere);

				

			}

				

				lecture.get(caractere); // saut \n

				ecriture << insertion;

				ecriture << ");" << "\n";

				insertion = "";

				insertion += insert;

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
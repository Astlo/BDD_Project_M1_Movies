//g++ temps.cpp -o temps -lcurl
//./temps ml-latest/ratings.csv temps.sql

#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;

std::string timeStampToDay(long  timestamp)
{
    const time_t rawtime = (const time_t)timestamp;

    struct tm * dt;
    char timestr[30];
    char buffer [30];

    dt = localtime(&rawtime);
    // use any strftime format spec here
	strftime(timestr, sizeof(timestr), "%d", dt);
    sprintf(buffer,"%s", timestr);
    std::string stdBuffer(buffer);
    return stdBuffer;
}

std::string timeStampToMonth(long  timestamp)
{
    const time_t rawtime = (const time_t)timestamp;

    struct tm * dt;
    char timestr[30];
    char buffer [30];

    dt = localtime(&rawtime);
    // use any strftime format spec here
    strftime(timestr, sizeof(timestr), "%m", dt);
    sprintf(buffer,"%s", timestr);
    std::string stdBuffer(buffer);
    return stdBuffer;
}

std::string timeStampToYear(long  timestamp)
{
    const time_t rawtime = (const time_t)timestamp;

    struct tm * dt;
    char timestr[30];
    char buffer [30];

    dt = localtime(&rawtime);
    // use any strftime format spec here
	strftime(timestr, sizeof(timestr), "%Y", dt);
    sprintf(buffer,"%s", timestr);
    std::string stdBuffer(buffer);
    return stdBuffer;
}

int main(int argc, char const *argv[])
{
	ifstream lecture(argv[1], ios::in);
	ofstream ecriture(argv[2], ios::out | ios::trunc);

	string insert  = "INSERT INTO Temps Values(";
	string str_timestamp = "";
	char caractere;
	
	if(lecture && ecriture)
	{
		string line ="";
		string insertion="";
		getline(lecture,line);
		ecriture << insert;

		for(int i=0; i<3; ++i)
		{
			while(caractere != ',')
			{
				lecture.get(caractere);
			}
			lecture.get(caractere);
		}
		
		while(lecture.get(caractere))
		{

			//if(caractere == '\n')	//Si one saut de ligne est \n
			//{
			if(caractere == '\r') //Si one saut de ligne est \r\n
			{
				lecture.get(caractere); // saut \n
				


				ecriture << insertion;
				
				  std::string::size_type sz;   // alias of size_t

				long timestamp = std::stol (str_timestamp,&sz);
				std::string year = timeStampToYear(timestamp);
				std::string month = timeStampToMonth(timestamp);
				std::string day = timeStampToDay(timestamp);
				
				insertion = "";
				ecriture << str_timestamp;
				ecriture << "," << day << "," << month << "," << year << ");" << "\n";
				insertion += insert;

				for(int i=0; i<3; ++i)
				{
					while(caractere != ',')
					{
						lecture.get(caractere);
					}
					lecture.get(caractere);
				}
			}
			else if(caractere == '\'')
			{

			}
			else
			{
				str_timestamp += caractere;
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
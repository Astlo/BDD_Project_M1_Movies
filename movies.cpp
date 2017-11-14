//g++ movies.cpp -o movies -lcurl
//./movies ml-latest/movies.csv ml-latest/links.csv movies.sql

#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>

using namespace std;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

string imdbid(ifstream & links)
{
	char carac;
	string id;
	while(carac != '\n')
	{
		if(carac == ',')
		{
			links.get(carac);
			while(carac != ',')
			{
				id += carac;
				links.get(carac);
			}
		}
		links.get(carac);
	}

	return id;
}

string recupString(string imdbapi, int & i)
{
	string value = "";
	while(imdbapi.at(i) != '\"')
	{
		if(imdbapi.at(i) == '\'')
		{
			value += " ";
			++i;
		}
		else if(imdbapi.at(i) == '&')
		{
			value += "and";
			++i;
		}
		else
		{
			value += imdbapi.at(i);
			++i;	
		}
	}

	if (value == "" || value == "N/A")
	{
		value = "NULL";
	}
	else
	{
		value = '\'' + value + '\'';
	}

	return value;
}

string recupInt(string imdbapi, int & i)
{
	string value = "";
	while(imdbapi.at(i) != '\"')
	{
		if(imdbapi.at(i) == ',')
		{
			//Ne rien faire
		}
		else
		{	
			value += imdbapi.at(i);
		}
		++i;
	}

	if (value == "" || value == "N/A")
	{
		value = "NULL";
	}

	return value;
}

string recupDollar(string imdbapi, int & i)
{
	string value = "";
	if(imdbapi.at(i) == '$')
	{
		++i;
	}
	while(imdbapi.at(i) != '\"')
	{
		if(imdbapi.at(i) == ',')
		{
			//Ne rien faire
		}
		else
		{
			value += imdbapi.at(i);
		}
		++i;
	}

	if (value == "" || value == "N/A")
	{
		value = "NULL";
	}

	return value;
}

string recupDate(string imdbapi, int & i)
{
	string value = "to_date(\'";
	while(imdbapi.at(i) != '\"')
	{
		
		if(imdbapi.at(i) == ' ')
		{
			value += "-";
		}
		else
		{
			value += imdbapi.at(i);
		}
		++i;
	}

	if (value == "to_date(\'" || value == "to_date(\'N/A")
	{
		value = "NULL";
	}
	else
	{ 
		value += "\', \'DD-Mon-YY\')";
	}

	return value;
}


string extraction(string imdbapi)
{
	int i = 0;
	string key;
	string donnee = "";
	while(i != imdbapi.length())
	{

		if(imdbapi.at(i) == ',' && imdbapi.at(i+1) == '"')
		{
			i = i+2;
			key = "";
			while(imdbapi.at(i) != '"')
			{
				key += imdbapi.at(i);
				++i;
			}

			i = i+3;
			if(key == "Year") {
				donnee += recupInt(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Rated")
			{
				donnee += recupString(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Released")
			{
				donnee += recupDate(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Runtime")
			{
				string tmp;
				tmp = recupInt(imdbapi, i);
				if(tmp != "NULL")
				{
					donnee += tmp.substr(0, tmp.size()-4);
				}
				else
				{
					donnee += "NULL";
				}
				donnee += ",";
			} 
			else if(key == "Director")
			{
				donnee += recupString(imdbapi, i);
				donnee += ",";
			}
			else if(key == "Actors")
			{
				donnee += recupString(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Language")
			{
				donnee += recupString(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Country")
			{
				donnee += recupString(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Awards")
			{
				donnee += recupString(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Metascore")
			{
				donnee += recupInt(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "imdbRating")
			{				
				donnee += recupInt(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "imdbVotes")
			{
				donnee += recupInt(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "DVD")
			{
				donnee += recupDate(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "BoxOffice")
			{
				donnee += recupDollar(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Production")
			{
				donnee += recupString(imdbapi, i);
			}
		}
		i++;
	}
	return donnee;
}


int main(int argc, char const *argv[])
{
	CURL *curl;
	CURLcode res;
	std::string readBuffer, URL;

	ifstream lecture(argv[1], ios::in);
	ifstream lecture2(argv[2], ios::in);
	ofstream ecriture(argv[3], ios::out | ios::trunc);

	string insert  = "INSERT INTO Movies Values(";
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
			lecture.get(caractere);
		}
		insertion += ',';
		insertion += '\'';
		while(lecture.get(caractere))
		{
			//if(caractere == '\n')	//Si one saut de ligne est \n
			//{
				if(caractere == '\r') //Si one saut de ligne est \r\n
				{
				lecture.get(caractere); // saut \n			
			
				ecriture << insertion << "\',";

				URL = "http://www.omdbapi.com/?apikey=b67cd4fd&i=tt";
				URL += imdbid(lecture2);

				curl = curl_easy_init();
				readBuffer = "";
				if(curl) {
					curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
					res = curl_easy_perform(curl);
					curl_easy_cleanup(curl);
				}
				ecriture << extraction(readBuffer);

				insertion = "";
				ecriture << ");" << "\n";
				insertion += insert;lecture.get(caractere);
				while(caractere != ',')
				{
					insertion += caractere;
					lecture.get(caractere);
				}
				insertion += ',';
				insertion += '\'';

			} 
			else if(caractere == '\"')
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
					else
					{
						insertion += caractere;
					}
					lecture.get(caractere);
				}
			} 
			else if(caractere == ',')
			{
				ecriture << insertion << "\',\'";
				insertion = "";
			}
			else if(caractere == '\'')
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
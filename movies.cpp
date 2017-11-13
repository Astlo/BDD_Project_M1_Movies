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

string recup(string imdbapi, int & i)
{
	string value = "";
	while(imdbapi.at(i) != '\"')
	{
		if(imdbapi.at(i) == '\'')
		{
			value += "\\";
		}
		value += imdbapi.at(i);
		++i;
	}

	if (value == "" || value == "N/A")
	{
		value = "null";
	}
	else
	{
		value = '\'' + value + '\'';
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
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Rated")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Released")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Runtime")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Director")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			}
			else if(key == "Actors")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Language")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Country")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Awards")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Metascore")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "imdbrating")
			{				
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "imdbVotes")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "DVD")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "BoxOffice")
			{
				donnee += recup(imdbapi, i);
				donnee += ",";
			} 
			else if(key == "Production")
			{
				donnee += recup(imdbapi, i);
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

	string insert  = "INSERT INTO Movies Values(\'";
	char caractere;
	
	if(lecture && lecture2 && ecriture)
	{
		string line ="";
		string insertion="";
		getline(lecture,line);	
		getline(lecture2,line);	
		ecriture << insert;
		while(lecture.get(caractere))
		{
			if(caractere == '\n')
			{
				//insertion = insertion.substr(0, insertion.size()-1);
				ecriture << insertion;

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
				insertion += insert;
			} 
			else if(caractere == '\"')
			{
				lecture.get(caractere);
				while(caractere != '\"')
				{
					if(caractere == '\'')
					{
						insertion += '\\';
						insertion += caractere;
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
				insertion += '\\';
				insertion += caractere;
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
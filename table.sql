-- @tables.sql

prompt *************************************************************
prompt ******************** DROP TABLE *****************************
prompt *************************************************************

DROP TABLE Movies CASCADE CONSTRAINT;
DROP TABLE Tag CASCADE CONSTRAINT;
DROP TABLE Temps CASCADE CONSTRAINT;
DROP TABLE Rating CASCADE CONSTRAINT;
DROP TABLE Tagging CASCADE CONSTRAINT;

prompt *************************************************************
prompt ******************** CREATE TABLE ***************************
prompt *************************************************************

prompt
prompt ******************** Movies ***************************

CREATE TABLE Movies
(
	movieId NUMBER NOT NULL,
	movieTitle VARCHAR2(200) NOT NULL,
	movieGenres VARCHAR2(200),
	movieYear NUMBER NOT NULL,
	movieRated VARCHAR(20),
	movieReleased DATE,
	movieRuntime NUMBER,
	movieDirector VARCHAR2(40),
	movieActors VARCHAR2(200),
	movieLanguage VARCHAR2(40),
	movieCountry VARCHAR2(200),
	movieAwards VARCHAR2(40),
	movieMetascore NUMBER,
	movieImdbRating NUMBER,
	movieImdbVotes NUMBER,
	movieDVD DATE,
	movieBoxOffice NUMBER,
	movieProduction VARCHAR2(40),
	PRIMARY KEY (movieId),
	CONSTRAINT check_Movies_movieId CHECK (movieId >= 0),
	CONSTRAINT check_Movies_movieYear CHECK (movieYear >= 1888),
	CONSTRAINT check_Movies_movieRuntime CHECK (movieRuntime > 0),
	CONSTRAINT check_Movies_movieMetascore CHECK (movieMetascore BETWEEN 0 and 100),
	CONSTRAINT check_Movies_movieImdbRating CHECK (movieImdbRating BETWEEN 0 and 10),
	CONSTRAINT check_Movies_movieImdbVotes CHECK (movieImdbVotes >= 0),
	CONSTRAINT check_Movies_movieDVD CHECK (movieDVD >= movieReleased),
	CONSTRAINT check_Movies_movieBoxOffice CHECK (movieBoxOffice >= 0)
);

prompt
prompt ******************** Temps ***************************

CREATE TABLE Temps
(
	colonne_timestamp TIMESTAMP NOT NULL,
	jour NUMBER,
	mois NUMBER,
	annee NUMBER,
	PRIMARY KEY (colonne_timestamp)
);

prompt
prompt ******************** Fait : Rating ***************************

CREATE TABLE Rating
(
	userId NUMBER NOT NULL,
	movieId NUMBER NOT NULL,
	colonne_timestamp TIMESTAMP NOT NULL,
	rating NUMBER NOT NULL,
	PRIMARY KEY (userId, movieId, colonne_timestamp),
	CONSTRAINT fk_Rating_movieId FOREIGN KEY (movieId) REFERENCES Movies(movieId),
	CONSTRAINT fk_Rating_colonne_timestamp FOREIGN KEY (colonne_timestamp) REFERENCES Temps(colonne_timestamp)
);

prompt
prompt ******************** Fait : Tagging ***************************

CREATE TABLE Tagging
(
	userId NUMBER NOT NULL,
	movieId NUMBER NOT NULL,
	userTag VARCHAR2(200) NOT NULL,
	colonne_timestamp TIMESTAMP NOT NULL,
	relevance NUMBER NOT NULL,
	PRIMARY KEY (userId, movieId, userTag),
	CONSTRAINT fk_Tagging_movieId FOREIGN KEY (movieId) REFERENCES Movies(movieId),
	CONSTRAINT fk_Tagging_colonne_timestamp FOREIGN KEY (colonne_timestamp) REFERENCES Temps(colonne_timestamp)
);
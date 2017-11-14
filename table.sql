prompt *************************************************************
prompt ******************** DROP TABLE *****************************
prompt *************************************************************

DROP TABLE Table_Faits CASCADE CONSTRAINTS;
DROP TABLE Temps CASCADE CONSTRAINTS;
DROP TABLE Tags CASCADE CONSTRAINTS;
DROP TABLE Movies CASCADE CONSTRAINTS;

prompt ************************************************************
prompt *********************** CREATE TABLE ***********************
prompt ************************************************************

prompt
prompt ************************** Movies **************************
prompt

CREATE TABLE Movies
(
	movieId NUMBER NOT NULL,
	movieTitle VARCHAR2(200) NOT NULL,
	movieGenres VARCHAR2(200),
	movieYear NUMBER,
	movieRated CHAR(10),
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
	PRIMARY KEY (movieId)
);

prompt
prompt *************************** Tags ***************************
prompt

CREATE TABLE Tags
(
	tagId NUMBER NOT NULL,
	tag VARCHAR2(200) NOT NULL,
	PRIMARY KEY (tagId),
	CONSTRAINT check_Tag_tagId CHECK (tagId >= 0)
);

/*

 Dateiname              : Hangman.c

 Kurzbeschreibung       :HangmanSPIEL-SIMULATION


 EingabeParameter       :VOID

 Rückgabeparameter      : 0 (Programm beenden )

 Author            	    :Hamza Sliti

 Mat.Nr                 :11131474

 Version          	    :2

 Datum letzte Änderung  :16.12.2020

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 Funktionsname : Ersetzen
 Kurzbeschreibung der Aufgabe der Funktion:    Überprüft ob richtig oder falsch geraten wurde und ersetzt richtig geratene Buchstaben


 Eingaben  : char wort, char ungeraten, char geraten, int falsch, int richtig
 Ausgaben  : 0

 Autor     : Hamza Sliti

 Version   : 2

 Datum letzte Änderung  :16.12.2020

 */

int Ersetzen(char* wort, char* ungeraten, char geraten, int* falsch,
		int* richtig) {

	int a = 0;						//Hilfsvariable

	a = *richtig;			//Inhalt von richtig auf a abspeichern

	while (*wort != '\0') {		//Solange zu erratendes Wort nicht zuende

		if (*wort == geraten) {	//Wenn Buchstabe des zu erratenden Wortes gleich dem geratenen Buchstaben
			*ungeraten = geraten;//Erste Stelle von ungeraten durch den Buchstaben ersetzen
			*richtig = *richtig + 1;	//richtig um 1 erhöhen
		}

		wort++;				//nächster Buchstabe des WortesF
		ungeraten++;			//nächste Stelle in ungeraten
	}

	if (a == *richtig) {				//Falls keine Buchstaben ersetzt wurden
		*falsch = *falsch + 1;			//erhöhe falsch um 1
	}

	return 0;
}

int main(void) {

	int size = 0, laenge = 0, pos = 0, i = 0, falsch = 0, fehlversuche = 0,
			richtig = 0;
	int* anzahlfalsch = NULL;
	int* anzahlrichtig = NULL;
	char *Wort = NULL;
	char *ungeraten = NULL;
	const char erlaubt[] =
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
	char raten = { '0' }, flush = { '0' };

	anzahlfalsch = &falsch;	//Adresse von "falsch" auf "anzahlfalsch" speichern
	anzahlrichtig = &richtig;//Adresse von "richtig" auf "anzahlrichtig" speichern

	printf(
			"***HANGMAN EINSTELLUNGEN***\nBitte geben Sie zuerst die Länge des zu erratenden Wortes ein:");

	scanf("%d", &size);				//Größe des zu erratenden Wortes einlesen
	scanf("%c", &flush); //  "\n" auf Flush einlesen, um eine neue Eingabe zu ermöglichen

	Wort = (char *) calloc(size, sizeof(int)); //Speicher in passender Größe reservieren

	printf(
			"\nGeben Sie nun ihr zu erratendes Wort ein (Zeichenvorrat a-z und A-Z sowie Leerzeichen ):");

	fgets(Wort, 100, stdin); //Zu erratendes Wort einlesen

	do {

		laenge = strlen(Wort);		//Länge des eingelesenen Wortes rausfinden
		pos = strspn(Wort, erlaubt);//Position des ersten unerlaubten Zeichens rausfinden

		if (laenge != pos + 1) {//Falls Position ungleich der Länge des Strings (unerlaubtes Zeichen vorhanden)

			printf(
					"\nEs sind nur Zeichenvorrat a-z und A-Z sowie Leerzeichen zulässig!");	//Fehlermeldung
			printf(
					"\nBitte geben Sie die Länge ihres zu erratenden Wortes ein:");
			scanf("%d", &size);	//Größe des neu einzulesenden Wortes einlesen
			scanf("%c", &flush);
			Wort = (char *) calloc(size, sizeof(int));//Speicher in der Größe reservieren
			printf("Geben Sie nun das zu erratende Wort ein:");

			fgets(Wort, 100, stdin);						//Wort neu einlesen

			laenge = strlen(Wort);	//Länge des eingelesenen Wortes rausfinden
			pos = strspn(Wort, erlaubt);

		};
	} while (laenge != pos + 1);//Solange ungültige Zeichen vorhanden neu einlesen

	ungeraten = (char *) calloc(size, sizeof(int));	//Speicher reservieren für ungeratene Buchstaben

	for (i = 0; i < size; i++) {//Pro eingelesenen Buchstaben ein "-" auf ungeraten Speichern

		ungeraten[i] = '-';
	}
	i = 0;											//Zählvariable zurücksetzen

	printf("\nGeben Sie die Anzahl der Fehlversuche ein:");
	scanf("%d", &fehlversuche);				//Anzahl der Fehlversuche einlesen

	for (i = 0; i < 25; i++) {//Damit eingelesenes Wort während Spiel nicht sichtbar, 50 mal \n ausgeben
		printf("\n");
	}
	i = 0;											//Zählvariable zurücksetzen

	printf("***DAS SPIEL BEGINNT***");

	while (falsch < fehlversuche && richtig != laenge - 1) {//Solange Fehlversuche nicht aufgebraucht und Wort nicht errraten
		scanf("%c", &flush);//"\n" auf Flush speichern, um neue Eingabe zu ermöglichen
		printf("\nRaten Sie nun einen Buchstaben:");
		scanf("%c", &raten);					//Geratenen Buchstaben einlesen

		Ersetzen(Wort, ungeraten, raten, anzahlfalsch, anzahlrichtig); //Funktion Ersetzen aufrufen

		printf("%s\n", ungeraten);					//String ungeraten ausgeben

		printf("\nFehlversuche (maximal %d):", fehlversuche);//Mögliche Fehlversuche anzeigen
		for (i = 0; i < falsch; i++) {					//Fehlversuche anzeigen
			printf("|");
		}
	}

	if (falsch == fehlversuche) {			//Falls Fehlversuche aufgebraucht
		printf("\nDu hast das Spiel leider VERLOREN");			//Verloren
	} else if (richtig == laenge - 1) {			//Falls alle Buchstaben erraten
		printf("\nHerzlichen Glückwunsch! Du hast gewonnen!");	//Gewonnen
	}

	return 0;
}

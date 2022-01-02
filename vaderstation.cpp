/* 
Applikation: Väderstation
Skapad av: Emelie Johansen
Skapad: 2022-01-02
Version: 1.0.0
*/

/*
Det här programmet är en vaderstation som börjar med att be användaren mata in namn och temperatur
för ett antal valfria städer. Temperaturen kontrolleras så att den ligger mellan -60 och +60 grader.
Efter detta kan användaren söka efter en viss temperatur och om den hittas så skrivs namnet på staden 
och den tillhörande temperaturen på skärmen. Annars visas ett meddelande om att den inte kunde hittas.
Sökningen sker linjärt genom hela arrayen.

Sedan sorteras de inmatade städerna efter temperatur där den med lägst temperatur kommer först. 

Efter det får användaren söka efter en temperatur igen, men den här gången sker sökningen binärt.

Programmet avslutas med att städerna med högst respektive lägst temperatur skrivs ut på skärmen och
sedan ett avslutsmeddelande.
*/

#include <iostream>

using namespace std;

// Skapa klassen Stad med tillhörande medlemsvariabler och metoder
// för att kunna lagra städernas namn och temperaturer
class Stad {

    // Klassen innehåller två attribut
    // namn innehåller stadens namn
    // temp innehåller stadens temperatur
    string namn;
    int temp;

    // Alla metoder i klassen är publika och kan användas av alla
    // som kommer åt objekten
    public:

        // Metod för att returnera en sträng med bägge värden från ett objekt
        string toString() {
            string tempString;
            tempString = (namn + " " + to_string(temp));
            return (tempString);
        }

        // Metod för att hämta attributet 'namn'
        string getNamn() {
            return namn;
        }

        // Metod för att hämta attributet 'temp'
        int getTemp() {
            return temp;
        }

        // Metod för att sätta objektets värden (attribut) 
        void setValues(string s, int t) {
            namn = s;
            temp = t;
        }

};

// Metod för att hitta den högsta temperaturen i arrayen och
// returnera indexnumret för den post som var högst
int hogstTemp(Stad stader[], int n) {
    int index = 0;
    int hogst = stader[index].getTemp();
    
    for(int i=0; i < n; i++) {    
        if (hogst < stader[i].getTemp()) {
            hogst = stader[i].getTemp();
            index = i;
        }
    }
    return index;
}

// Metod för att hitta den lägsta temperaturen i arrayen och
// returnera indexnumret för den post som var lägst
int lagstTemp(Stad stader[], int n) {
    int index = 0;
    int lagst = stader[index].getTemp();
    
    for(int i=0; i < n; i++) {    
        if (lagst > stader[i].getTemp()) {
            lagst = stader[i].getTemp();
            index = i;
        }
    }
    return index;
}

// Metod för att hitta en stad med en temperatur som
// motsvarar eftersökt temperatur. Metoden söker 
// linjärt genom hela arrayen
int linSok(Stad stader[], int sokTemp, int n) {
    for(int i=0; i < n; i++) {    
        if (sokTemp == stader[i].getTemp()) {
            return i;
        }
    }
    return -1;
}

// Metod för att sortera hela arrayen med hjälp av
// algoritmen bubblesort
void bubbleSort(Stad stader[], int n) {
    string tempStad;
    int tempTemp;
    for(int i=0; i < n; i++) {
         for(int j=0; j < n; j++) {
             if (stader[j].getTemp() > stader[j+1].getTemp()) {
                tempStad = stader[j].getNamn();
                tempTemp = stader[j].getTemp();
                stader[j].setValues(stader[j+1].getNamn(), stader[j+1].getTemp());
                stader[j+1].setValues(tempStad, tempTemp);
            }
        }
    }
}

// Metod för att hitta en stad med en temperatur som
// motsvarar eftersökt temperatur. Metoden söker 
// binärt genom hela arrayen
int binSok(Stad stader[], int v, int h, int sokTemp)
{
	if (h >= v) {
		int mitten = v + (h - v) / 2;

        // Om värdet finns i mitten kan vi returnera det direkt
		if (stader[mitten].getTemp() == sokTemp)
			return mitten;

        // Om värdet är mindre än mitten så kan det
        // bara finnas i den vänstra delen av arrayen
		if (stader[mitten].getTemp() > sokTemp) {
			return binSok(stader, v, mitten - 1, sokTemp);
        } else {
            // Annars kan värdet bara finnas i den
            // högra delen av arrayen
            return binSok(stader, mitten + 1, h, sokTemp);
        }
	}
    // Om värdet inte hittas i arrayen returneras -1
	return -1;
}
        
int main() {

    // Variabler för att lagra användarens inmatningar
    string inputNamn, tempStad;
    int inputTemp, sokTemperatur, tempTemp;

    // Variabel för att lagra sökresultatet från sökmetoderna
    int sokRes;

    // Variabel för att användas i while-loopen där temperatur kontrolleras
    bool tempNotOk = true;

    // Antal element i arrayen
    int n = 4;

    // Skapa en array med plats för fyra objekt av typen Stad
    Stad stader[n];

    // Rensa skärmen
    cout << "\033[2J\033[1;1H";
    cout << "\n";
    
    // Skriv ut ett välkomstmeddelande
    cout << "Hej och välkommen till väderstationen!\n";
    cout << "I det här programmet kommer du att få lägga in " << n << " städer med tillhörande temperaturer.\n";
    cout << "Efter det kommer du att kunna söka efter städer med en specifik temperatur.\n";
    cout << "Programmet avslutas med att skriva ut vilken stad som har den högsta respektive lägsta temperaturen.\n";

    // Loop för att få användaren att mata in de fyra städerna och
    // tillhörande temperaturer. Inmatad temperatur kontrolleras
    // så att inte gränsvärdena överskrids. (-60 till +60 grader)
    for(int i=0; i < n; i++) {
        cout << "\n\nAnge namn på stad nr " << i+1 << " av " << n << ": ";
        cin >> inputNamn;
        while(tempNotOk) {
            cout << "Ange temperatur i " << inputNamn << ": ";
            cin >> inputTemp;
            if (inputTemp >= -60 && inputTemp <= 60) {
                tempNotOk = false;
            } else {
                cout << "\nTemperaturen måste ligga mellan -60 och +60 grader. Försök igen!\n";
            }
        }
        
        // Återställ tempNotOk för while-loopen
        tempNotOk = true;

        // Anrop av den inbyggda metoden setValues för att sätta värden
        // på objekten i arrayen
        stader[i].setValues(inputNamn, inputTemp);
    }
    
    // Skriv ut två blankrader
    cout << "\n\n";
    
    // Be användaren ange vilken temperatur som ska sökas i arrayen med städer
    cout << "\nVilken temperatur vill du söka efter med linjärsökning? Ange värde: ";
    cin >> sokTemperatur;

    // Anropa metoden linSok för att söka linjärt i arrayen om temperaturen finns där 
    sokRes = linSok(stader, sokTemperatur, n);

    // Visa resultatet av sökningen
    if (sokRes == -1) {
        cout << "\nKunde tyvärr inte hitta någon stad med temperaturen " << sokTemperatur << " grader.";
    } else {
        cout << "\nStaden " << stader[sokRes].getNamn() << " har eftersökt temperatur på " << stader[sokRes].getTemp() << " grader.\n";
    }

// Avkommentera nedan om du vill se hur arayen ser ut osorterad
/*
    // Skriv ut alla objekt som finns i arrayen innan bubblesort
    cout << "\nInnan bubblesort...\n";
    for(int i=0; i < n; i++) {
        cout << "\nstader[" << i << "].toString(): " << stader[i].toString() << "\n";
    }
*/  
    // Sortera städerna efter temperatur genom att anropa metoden bubblesort
    bubbleSort(stader, n);

// Avkommentera nedan om du vill se hur arayen ser ut sorterad
/*
    // Skriv ut alla objekt som finns i arrayen efter bubblesort
    cout << "\nEfter bubblesort...\n";
    for(int i=0; i < n; i++) {
        cout << "\nstader[" << i << "].toString(): " << stader[i].toString() << "\n";
    }
*/

    // Be användaren ange vilken temperatur som ska sökas i arrayen (binärsök) med städer
    cout << "\nVilken temperatur vill du söka efter med binärsökning? Ange värde: ";
    cin >> sokTemperatur;

    // Anropa metoden binSok för att söka binärt i arrayen om temperaturen finns där
    sokRes = binSok(stader, 0, n, sokTemperatur);

    // Visa resultatet av sökningen
    if (sokRes == -1) {
        cout << "\nKunde tyvärr inte hitta någon stad med temperaturen " << sokTemperatur << " grader. (binärsökning)\n";
    } else {
        cout << "\nStaden " << stader[sokRes].getNamn() << " har eftersökt temperatur på " << stader[sokRes].getTemp() << " grader. (binärsökning)\n";
    }

    // Anropa metoden hogstTemp för att ta reda på vilken stad som har högst temperatur i arrayen
    // och skriv ut den på skärmen
    cout << "Staden med högst temperatur är " << stader[hogstTemp(stader, n)].getNamn() << " med " << 
        stader[hogstTemp(stader, n)].getTemp() << " grader.\n";

    // Anropa metoden lagstTemp för att ta reda på vilken stad som har lägst temperatur i arrayen
    // och skriv ut den på skärmen
    cout << "Staden med lägst temperatur är " << stader[lagstTemp(stader, n)].getNamn() << " med " << 
        stader[lagstTemp(stader, n)].getTemp() << " grader.\n";

    // Skriv ut en avslutande hälsning
    cout << "Tack för att du använde väderstationen!\n";

    return 0;
}


/* 
Utvärdering

I den här uppgiften fick jag chansen att lära mig mer om klasser, objekt, medlemsattribut 
och tillhörande metoder. För mig var detta väldigt nytt och lite svårare än de tidigare 
uppgifterna. 

Det var också intressant att få lite inblick i olika typer av sök- och sorteringsalgoritmer
med linjärsök, binärsök och bubblesort. 

Användarvänligheten är hög eftersom alla frågor är logiska och självförklarande. Programmet 
skriver löpande ut information på skärmen åt användaren.

På en riktig väderstation skulle alla mätvärden samlas in automatiskt från olika sensorer som
är utplacerade i världen. I mitt program får användaren själv mata in värden vilket är lite
konstigt. Framtida versioner av programmet kanske skulle kunna koppla upp sig mot en publik 
vädertjänst som har alla mätvärden i en databas. 

Framtida versioner bör också kompletteras med robusta felkontroller som kontrollerar alla
inmatningar användaren gör innan variablarna används i simulatorn. Oväntade fel behöver
också fångas upp och hanteras på ett snyggt sätt så att informativa felmeddelanden skrivs
ut på skärmen.
*/

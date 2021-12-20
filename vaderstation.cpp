
#include <iostream>
#include <string>
using namespace std;
class Stad {
    string namn;
    int temp;
    public:
        // Metod för att returnera en sträng med bägge värden från ett objekt
        string toString() {
            string tempString;
            tempString = (namn + " " + to_string(temp));
            return (tempString);
        }
        // Metod för att sätta objektets värden (attribut) 
        void setValues(string s, int t) {
            namn = s;
            temp = t;
        }
        //TODO
        //int linsok(fält städer, int n, int söktemp)
        //TODO
        // void bubblesort(fält städer, int n)
        //TODO
        // hogstTemp
        //TODO
        // lagstTemp
};
int main() {
    // Variabler för att lagra användarens inmatningar
    string inputNamn;
    int inputTemp;
    // Variabel för att användas i while-loopen där temperatur kontrolleras
    bool tempNotOk = true;
    // Skapa en array med plats för fyra objekt av typen Stad
    Stad stader[4];
    // Loop för att få användaren att mata in de fyra städerna och
    // tillhörande temperaturer. Inmatad temperatur kontrolleras
    // så att inte gränsvärdena överskrids. (-60 till +60 grader)
    for(int i=0; i < 4; i++) {
        cout << "\n\nAnge namn på stad nr " << i+1 << " av 4: ";
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
    // Skriv ut alla objekt som finns i arrayen
    for(int i=0; i < 4; i++) {
        cout << "stader[" << i << "].toString(): " << stader[i].toString() << "\n";
    }
    
    return 0;
}
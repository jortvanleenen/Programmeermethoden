#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

// Forward declaratie van toonInfoBlok()
void toonInfoblok();

// Forward declaratie van vraagConverteerParams()
int vraagConverteerParams();

/**
 * Programmeermethoden - Opdracht 2: Netjes (16/10/2021)
 *
 * Gemaakt met: Code::Blocks, CLion
 * Naam: main2.cpp
 * Compiler: MSVC (Microsoft Visual C++ compiler) 14.16.27023
 *
 * Dit programma verwijdert commentaar en corrigeert foutieve witruimte aan het
 * begin van regels. Daarnaast analyseert het het Collatz-vermoeden van getallen
 * buiten commentaar in het invoerbestand en telt het hoe vaak drie kleine,
 * verschillende letters op volgorde voorkomen.
 * (Zie voor een uitleg van het Collatz-vermoeden de desbetreffende functie.)
 *
 * De gebruiker zal worden gevraagd naar een invoerpad voor het invoerbestand,
 * een uitvoerpad voor het uitvoerbestand, een tabgrootte in spaties als nummer
 * en drie kleine, verschillende letters voor het tellen van het drietal.
 *
 * Tot slot drukt het programma bij succes een rapport van de analyse, telling
 * en witruimte-correctie af op het scherm.
 *
 * @return geeft EXIT_SUCCESS bij succes en EXIT_FAILURE bij fout
 */
int main() {

  toonInfoblok();

  // Wanneer vraagConverteerParams() geen 0 teruggeeft, is er iets misgegaan
  if (vraagConverteerParams() == 0) {
    return EXIT_SUCCESS;
  } else {
    return EXIT_FAILURE;
  }
}

/**
 * Controleert de diepte van de regel, rekening houdend met geplaatste
 * accolades.
 *
 * @param kar het huidige karakter
 * @param volgende_kar het volgende karakter
 * @param diepte de huidige diepte
 * @param correct_gepaard 'false' wanneer er een negatieve diepte voorkomt: '}{'
 */
void controleerDiepte(char kar, char volgende_kar, int &diepte,
                      bool &correct_gepaard) {
  // Wij controleren de diepte van het volgende kar om ervoor te zorgen dat,
  // voordat wij een sluitende accolade plaatsen, de diepte gecorrigeerd is
  if (kar == '{') {
    diepte++;
  }
  else if (volgende_kar == '}') {
    diepte--;
  }

  if (correct_gepaard && diepte < 0) {
    correct_gepaard = false;
  }
}

/**
 * Controleert of wij ons binnen of buiten commentaar gaan bevinden door te
 * kijken naar het huidige (en volgende) karakter.
 *
 * @param kar het huidige karakter
 * @param volgende_kar het volgende karakter
 * @param in_commentaar 'true' wanneer in commentaar, anders 'false'
 */
void controleerCommentaar(char kar, char volgende_kar, bool &in_commentaar) {
  // '//'-commentaar eindigt altijd met een '\n'-karakter
  if (kar == '/' && volgende_kar == '/') {
    in_commentaar = true;
  } else if (in_commentaar && kar == '\n') {
    in_commentaar = false;
  }
}

/**
 * Maakt van hoofdletters kleine letters. Indien geen hoofdletter wordt gegeven
 * als parameter, blijft het karakter volkomen ongewijzigd.
 *
 * @param kar het karakter waarvan een kleine letter gemaakt moet worden
 */
void maakKleineLetter(char &kar) {
  if (kar >= 'A' && kar <= 'Z') {
    kar += ' ';
  }
}

/**
 * Controleert of één van de drie karakters (het drietal) voorkomt in het
 * ingevoerde karakter. Tevens houdt het bij welke er al zijn voorgekomen en
 * telt het hoe vaak het gehele drietal is voorgekomen.
 *
 * @param kar het karakter waarvoor het drietal gecheckt moet worden
 * @param eerste_letter het eerste karakter van het drietal
 * @param tweede_letter het tweede karakter van het drietal
 * @param derde_letter het derde karakter van het drietal
 * @param aantal_in_optreden huidige aantal karakters van drietal op volgorde
 * @param aantal_drietallen totaal aantal keer dat het drietal is voorgekomen
 */
void controleerDrietal(char kar, char eerste_letter, char tweede_letter,
                       char derde_letter, int &aantal_in_optreden,
                       int &aantal_drietallen) {

  maakKleineLetter(kar);

  if (kar == eerste_letter) {
    // De eerste letter van het drietal is voorkomen
    aantal_in_optreden = 1;
  } else if (kar == tweede_letter) {
    // Als a al voorbij is gekomen, heeft de reeks een lengte van 1
    // Als a nog niet voorbij is gekomen, wordt de reeks herstart
    aantal_in_optreden >= 1 ? aantal_in_optreden++ : aantal_in_optreden = 0;
  } else if (kar == derde_letter) {
    // Als ab al voorbij is gekomen heeft de reeks minimaal een lengte van 2
    // is het drietal compleet, of wordt de reeks herstart
    aantal_in_optreden >= 2 ? aantal_in_optreden++ : aantal_in_optreden = 0;
  }

  // Alle karakters van het drietal zijn voorgekomen op de juiste volgorde
  if (aantal_in_optreden == 3) {
    aantal_drietallen++;
    aantal_in_optreden = 0;
  }
}

/**
 * Controleert het Collatz-vermoeden voor een gegeven nummer. Het telt het
 * aantal iteraties totdat het gegeven nummer gelijk is aan 1 of INT_MAX wordt
 * bereikt.
 *
 * Het Collatz-vermoeden houdt het volgende in:
 * - Wanneer een getal (x) is even: x / 2
 * - Wanneer een getal (x) is oneven: x * 3 + 1
 * Dit wordt herhaald met de uitkomst van de voorgaande iteratie. Het vermoeden
 * bestaat dat dit voor alle gehele positieve getallen uiteindelijk zal leiden
 * tot x = 1.
 *
 * @param nummer het nummer waarvoor het Collatz-vermoeden gecontroleerd wordt
 */
void controleerCollatz(int nummer) {

  int teller = 0;

  std::cout << nummer << ": ";

  while (nummer != 1) {
    teller++;

    if (nummer % 2 == 0) {
      nummer /= 2;
    } else {
      // Wanneer 'nummer' groter is dan INT_MAX / 3 stoppen wij de executie,
      // aangezien de volgende berekening 'nummer' * 3 + 1 zal doen, waardoor
      // we gegarandeerd boven INT_MAX uit zullen komen
      if (nummer > INT_MAX / 3) {
        std::cout << "INT_MAX bereikt op " << nummer << " na ";
        // Gebruikt om de while-loop te verlaten
        nummer = 1;
      } else {
        nummer = nummer * 3 + 1;
      }
    }
  }

  if (teller == 1) {
    std::cout << teller << " iteratie.\n";
  } else {
    std::cout << teller << " iteraties.\n";
  }
}

/**
 * Drukt een rapport over het converteren af op het scherm van de gebruiker.
 *
 * @param diepte de huidige diepte
 * @param aantal_drietallen het aantal voorgekomen drietallen
 * @param correct_gepaard 'false' wanneer er een negatieve diepte voorkwam: '}{'
 */
void geefRapport(int diepte, int aantal_drietallen, bool correct_gepaard) {

  if (correct_gepaard) {
    std::cout << "De accolades waren correct gepaard.\n";
  } else {
    std::cout << "De accolades waren incorrect gepaard.\n";
  }

  if (diepte == 0) {
    std::cout << "Er bevonden zich een gelijk aantal accolades.\n";
  } else {
    std::cout << "Er bevond" << (abs(diepte) == 1 ? " " : "en ")
              << "zich " << abs(diepte)
              << " accolade" << (abs(diepte) == 1 ? " " : "s ")
              << "te " << (diepte < 0 ? "weinig" : "veel") << "!\n";
  }

  std::cout << "Het drietal kwam " << aantal_drietallen << "x voor.\n";
}

/**
 * Converteert het invoerbestand naar het uitvoerbestand, waarbij het gebruik
 * maakt van enkele functies: controleerCommentaar(), controleerDiepte(),
 * controleerCollatz(), controleerDrietal() en geefRapport().
 *
 * @param invoer een ifstream object met het invoerbestand
 * @param uitvoer een ofstream object met het uitvoerbestand
 * @param tab tabgrootte in aantal spaties als nummer
 * @param eerste_letter het eerste karakter van het drietal
 * @param tweede_letter het tweede karakter van het drietal
 * @param derde_letter het derde karakter van het drietal
 */
void converteerBestand(std::ifstream &invoer, std::ofstream &uitvoer, int tab,
                       char eerste_letter, char tweede_letter,
                       char derde_letter) {

  char volgende_kar;
  bool in_commentaar = false;
  // Wij gaan ervan uit dat de accolades juist gepaard zijn, tenzij het
  // tegendeel tijdens het controleren van de diepte wordt bewezen
  bool correct_gepaard = true;

  // Aangezien wij altijd aan het begin van een regel beginnen met converteren,
  // start de while-loop met begin_van_de_regel = true
  bool begin_van_de_regel = true;

  int aantal_drietallen = 0;
  int aantal_in_optreden = 0;

  int nummer = 0;

  char kar = static_cast<char>(invoer.get());

  int diepte = 0;
  // Er wordt in de while-loop gecheckt of het volgende karakter '}' is.
  // Aangezien een '}' als eerste karakter dan dus zou worden gemist, checken
  // we deze hier
  if (invoer && kar == '}') {
    diepte--;
  }

  // Stop door het bestand heen gaan als er een fout is opgetreden, of wanneer
  // het einde is bereikt
  while (invoer) {

    volgende_kar = static_cast<char>(invoer.get());

    // Controleert of wij ons in commentaar bevinden
    controleerCommentaar(kar, volgende_kar, in_commentaar);

    // Wanneer wij alle al bestaande witruimte aan het begin van de regel
    // hebben verwijderd, plaatsen wij een bepaald aantal spaties, afhankelijk
    // van de door de gebruiker gekozen tabgrootte en de huidige diepte
    if (begin_van_de_regel && (kar != ' ' && kar != '\t')) {
      begin_van_de_regel = false;
      int aantal_spaties = diepte * tab;
      for (int i = 0; i < aantal_spaties; i++) {
        uitvoer.put(' ');
      }
    }

    if (!in_commentaar) {
      if (!begin_van_de_regel) {
        uitvoer.put(kar);
      }

      // Controleren we alleen buiten commentaar, want nummers binnen
      // commentaar tellen niet mee
      if (kar >= '0' && kar <= '9') {
        nummer = 10 * nummer + (kar - '0');
      }

      // Controleren we alleen buiten commentaar, want accolades binnen
      // commentaar tellen niet mee
      controleerDiepte(kar, volgende_kar, diepte, correct_gepaard);

      // Wanneer wij het laatste cijfer van een nummer hebben opgeslagen, dat
      // niet gelijk staat aan nul, roepen we controleerCollatz() aan
      if (!(volgende_kar >= '0' && volgende_kar <= '9') && nummer > 0) {
        controleerCollatz(nummer);
        // Reset het nummer nadat het Collatz-vermoeden ervoor is berekend
        nummer = 0;
      }
    }

    // Controleren we overal, omdat de volgorde ook mocht voorkomen binnen
    // commentaar
    controleerDrietal(kar, eerste_letter, tweede_letter, derde_letter,
                      aantal_in_optreden, aantal_drietallen);

    if (kar == '\n') {
      begin_van_de_regel = true;
    }

    kar = volgende_kar;
  }

  // Als wij uit de while-loop zijn en het komt niet door EOF, is er een fout
  // opgetreden
  if (!invoer.eof()) {
    std::cerr << "Het converteren is vroegtijdig beëindigd vanwege een fout.\n";
  }

  std::cout << "\n";
  geefRapport(diepte, aantal_drietallen, correct_gepaard);

}

/**
 * Controleert of het aangeleverde karakter een kleine letter is.
 *
 * @param kar het karakter dat gecontroleerd dient te worden
 * @return 'true' wanneer het karakter een kleine letter is, anders 'false'
 */
bool isKleineLetter(char kar) {
  return kar >= 'a' && kar <= 'z';
}

/**
 * Vraagt de gebruiker naar een invoerpad, uitvoerpad, tabgrootte en drie
 * letters die zullen worden gebruikt als drietal.
 *
 * Vervolgens zal converteerBestand() aangeroepen worden om aan de hand van de
 * geleverde parameters een bestand te converteren.
 *
 * @return geeft EXIT_SUCCESS bij succes en EXIT_FAILURE bij fout
 */
int vraagConverteerParams() {

  std::string invoer_pad;
  std::cout << "Geef het invoerbestand en druk op Enter:\n";
  std::cin >> invoer_pad;

  std::ifstream invoer{invoer_pad};
  // Wanneer er een probleem is met het openen van de stream geven we 'fout' aan
  if (!invoer) {
    std::cerr << "Invoerbestand niet gevonden!\n";
    return EXIT_FAILURE;
  }

  std::ofstream uitvoer;
  // Blijf proberen een uitvoer stream aan te maken totdat het gelukt is
  do {
    std::string uitvoer_pad;
    std::cout << "Geef het uitvoerbestand en druk op Enter:\n(Indien het"
                 " uitvoerbestand reeds bestaat, zal deze worden overschreven.)\n";
    std::cin >> uitvoer_pad;

    uitvoer.open(uitvoer_pad);
  } while (!uitvoer);

  int tab = 0;
  std::cout << "Geef de gewenste tabgrootte in spaties als nummer"
               " en druk op Enter:\n";
  std::cin >> tab;

  // Deze variabelen worden gebruikt om de drie letters van het drietal op
  // te slaan
  char eerste_letter;
  char tweede_letter;
  char derde_letter;

  // Blijf vragen om drie letters, totdat er drie kleine, verschillende
  // letters zijn ingevoerd
  do {
    std::cout << "Geef aub drie verschillende, kleine letters."
                 " Druk na de invoer op Enter:\n";
    std::cin >> eerste_letter >> tweede_letter >> derde_letter;

    // Geef een foutmelding als de drie letters niet uniek zijn
    if (eerste_letter == tweede_letter || eerste_letter == derde_letter ||
        tweede_letter == derde_letter) {
      std::cout << "Incorrecte invoer, geef enkel verschillende letters!\n";
    }

    // Geef een foutmelding als het geen kleine letters zijn
    if (!(isKleineLetter(eerste_letter) && isKleineLetter(tweede_letter) &&
          isKleineLetter(derde_letter))) {
      std::cout << "Incorrecte invoer, geef enkel kleine letters!\n";
    }

  } while (eerste_letter == tweede_letter || eerste_letter == derde_letter ||
           tweede_letter == derde_letter || (!(isKleineLetter(eerste_letter) &&
                                               isKleineLetter(tweede_letter) &&
                                               isKleineLetter(derde_letter))));

  converteerBestand(invoer, uitvoer, tab, eerste_letter, tweede_letter,
                    derde_letter);

  return EXIT_SUCCESS;
}

/**
 * Toont het infoblok aan de gebruiker.
 */
void toonInfoblok() {
  std::cout << "Programmeermethoden - Opdracht 2: Netjes (17/10/2021)\n"
               "Dit programma probeert taken van een compiler na te bootsen.\n"
               "Zo verwijdert het commentaar en corrigeert het foutieve wit-\n"
               "ruimte aan het begin van regels van het invoerbestand.\n\n"
               "Tevens analyseert het programma het Collatz-vermoeden voor\n"
               "getallen buiten commentaar in het invoerbestand en telt\n"
               "het hoe vaak drie verschillende letters op volgorde staan.\n\n"
               "De resultaten van de analyse, telling en witruimte-correctie\n"
               "worden achteraf in een rapport op het scherm afgedrukt.\n\n";
}

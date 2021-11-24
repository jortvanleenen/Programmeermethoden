#include <iostream>
#include <ctime>

using namespace std;

/**
 * Programmeermethoden - Opdracht 1: ABC-Formule (23/09/2021)
 *
 * Gemaakt met: Code::Blocks, CLion
 * Naam: main1.cpp
 * Compiler: MSVC (Microsoft Visual C++ compiler)
 *
 * Dit programma dient als toelatingstoets voor de Universiteit Leiden.
 * Gebruikers zullen worden gevraagd om hun geboortedatum, waarna een leeftijds-
 * verificatie wordt uitgevoerd (10-100 jaar oud). Vervolgens moet de eind-
 * gebruiker zijn/haar geboortedag weten. Tot slot moet een rekenvraag en,
 * indien van toepassing, een culturele meerkeuzevraag worden beantwoord.
 *
 * Indien de rekenvraag goed wordt beantwoord, zal een beta-studie worden
 * aangeraden. Zo niet, dan wordt de culturele meerkeuzevraag gesteld. Indien
 * deze goed wordt beantwoord, zal de gebruiker een alpha-studie worden
 * aangeraden. Indien beide vragen foutief worden beantwoord, wordt de gebruiker
 * gesuggereerd eens naar een hogeschool te kijken.
 *
 * @return returns 0 bij succes en 1 bij fout
 */
int main() {

  // Maak gebruik van een datum tussen 1900 en 2100
  const int kHuidigJaar = 2021;
  const int kHuidigeMaand = 9;
  const int kHuidigeDag = 27;

  cout << "Programmeermethoden - Opdracht 1: ABC-Formule (23/09/2021)\n"
          "Dit programma dient als toelatingstoets voor de UL. U zult uw\n"
          "geboortedatum moeten invoeren voor leeftijdsverificatie, om\n"
          "vervolgens uw geboortedag in te moeten voeren.\n\n"
          "Tot slot worden uw academische vaardigheden getoets d.m.v.\n"
          "een rekenvraag en, indien nodig, een culturele meerkeuzevraag.\n"
          "Succes!\n\n";

  cout << "Vul je geboortejaar als nummer in en druk op Enter:\n";
  // Het geboortejaar van de eindgebruiker
  int geboortejaar;
  cin >> geboortejaar;
  if (cin.fail()) {
    cerr << "Vul een numerieke waarde in als geboortejaar!";
    return 1;
  }

  // De leeftijd van de eindgebruiker
  int leeftijd;
  leeftijd = kHuidigJaar - geboortejaar;

  // Wij gebruiken het domein 9-101 voor de leeftijden 10-100 aangezien
  // de exacte leeftijd zonder maand en dag nog niet berekend kan worden
  if (leeftijd < 9 || leeftijd > 101) {
    cerr <<
         "Wij laten alleen mensen met een leeftijd van 10-100 jaar toe, sorry!";
    return 1;
  }

  cout << "Vul je geboortemaand als nummer in en druk op Enter:\n";
  // De geboortemaand van de eindgebruiker
  int geboortemaand;
  cin >> geboortemaand;
  if (cin.fail()) {
    cerr << "Vul een numerieke waarde in als geboortemaand!";
    return 1;
  }

  if (geboortemaand < 1 || geboortemaand > 12) {
    cerr << "Vul een nummer van 1-12 in als geboortemaand!";
    return 1;
  }

  // Corrigeert verkeerd gerekend jaar wanneer iemand nog jarig is in het
  // ingestelde huidige
  if (geboortemaand > kHuidigeMaand) {
    leeftijd--;
  }

  if (leeftijd < 9 || leeftijd > 101) {
    cerr <<
         "Wij laten alleen mensen met een leeftijd van 10-100 jaar toe, sorry!";
    return 1;
  }

  cout << "Vul je geboortedag als nummer in en druk op Enter:\n";
  // De geboortedag van de eindgebruiker
  int geboortedag;
  cin >> geboortedag;
  if (cin.fail()) {
    cerr << "Vul een numerieke waarde in als geboortedag!";
    return 1;
  }

  if (geboortedag < 1 || geboortedag > 31) {
    cerr << "Vul een nummer van 1-31 in als geboortedag!";
    return 1;
  }

  if (geboortedag == 29 && geboortemaand == 2 && geboortejaar % 4 != 0) {
    cerr << "Vul aub een correcte datum in!";
    return 1;
  }

  if (geboortedag == 31 && (geboortemaand == 2 || geboortemaand == 4 ||
                             geboortemaand == 6 || geboortemaand == 9 ||
                             geboortemaand == 11)) {
    cerr << "Vul aub een correcte datum in!";
    return 1;
  }

  // Het aantal maanden dat de eindgebruiker oud is
  int maanden;

  // Berekent het aantal maanden rekening houdend met de geboortedag
  if (geboortemaand > kHuidigeMaand || (geboortedag > kHuidigeDag &&
                                         geboortemaand == kHuidigeMaand)) {
    // Aantal al verstreken maanden dit en vorig jaar sinds verjaardag
    maanden = 12 + kHuidigeMaand - geboortemaand;
  } else {
    // Aantal al verstreken maanden dit jaar sinds verjaardag
    maanden = kHuidigeMaand - geboortemaand;
  }

  // Corrigeert verkeerd gerekend jaar wanneer iemand nog jarig is in het
  // ingestelde huidige in de ingestelde huidige maand
  if (geboortedag > kHuidigeDag && geboortemaand == kHuidigeMaand) {
    leeftijd--;
  }

  // Aangezien we nu de correcte leeftijd hebben kunnen we uitsluiten op 1-100
  if (leeftijd < 10 || leeftijd > 100) {
    cerr <<
         "Wij laten alleen mensen met een leeftijd van 10-100 jaar toe, sorry!";
    return 1;
  }

  if (geboortedag == kHuidigeDag) {
    cout << (geboortemaand == kHuidigeMaand ?
             "Krijg nou wat, een jarige, gefeliciteerd!\n\n" :
             "Krijg nou wat, een maandige, gefeliciteerd!\n\n");
  }

  cout << "Je bent momenteel " << leeftijd << " jaar en " <<
       maanden << " maanden jong!\n";
  if (leeftijd > 30) {
    cout << "Wist u dat dit gelijk staat aan " << 12 * leeftijd + maanden <<
         " maanden?\n\n";
  } else {
    cout << "Wist je dat dit gelijk staat aan " << 12 * leeftijd + maanden <<
         " maanden?\n\n";
  }

  if (leeftijd > 30) {
    cout << "Vul de eerste letter van uw geboortedag in en druk op Enter:\n"
            "(Bijvoorbeeld: Maandag -> m, Woensdag -> w)\n";
  } else {
    cout << "Vul de eerste letter van je geboortedag in en druk op Enter:\n"
            "(Bijvoorbeeld: Maandag -> m, Woensdag -> w)\n";
  }

  // Eerste letter van de geboortedag van de eindgebruiker
  char geboorte_letter_1;
  // Tweede letter van de geboortedag van de eindgebruiker
  char geboorte_letter_2;

  cin >> geboorte_letter_1;
  // Wanneer aan de eerste letter niet kan worden afgeleid welke dag wordt
  // bedoeld, dienen we een tweede letter te vragen
  if (geboorte_letter_1 == 'd' || geboorte_letter_1 == 'z') {
    if (leeftijd > 30) {
      cout << "Vul de tweede letter van uw geboortedag in en druk op Enter:\n"
              "(Bijvoorbeeld: Dinsdag -> i, Zondag -> o)\n";
    } else {
      cout << "Vul de tweede letter van je geboortedag in en druk op Enter:\n"
              "(Bijvoorbeeld: Dinsdag -> i, Zondag -> o)\n";
    }
    cin >> geboorte_letter_2;
  }

  // Wij maken gebruik van het feit dat 1 januari 1901 op een dinsdag valt
  int verstreken_jaren = geboortejaar - 1901;
  int schrikkeljaren = verstreken_jaren / 4;
  // Als het geboortejaar zelf een schrikkeljaar is corrigeert dit bovenstaande
  if (geboortejaar % 4 == 0) {
    schrikkeljaren++;
  }

  // Het aantal verstreken dagen in het geboortejaar
  int verstreken_dagen_geboorte_jaar = geboortedag;
  // Wij willen alleen verder rekenen met volledige, gepasseerde maanden,
  // aangezien we al rekening hebben gehouden met de geboortedag hierboven
  geboortemaand--;

  // Als er geen gehele maanden te berekenen zijn, slaan we de berekening over
  if (geboortemaand != 0) {
    int maanden_met_31_dagen = geboortemaand / 2 + 1;
    // Houdt rekening met het feit dat juli en augustus beiden 31 dagen hebben
    if (geboortemaand < 7 && geboortemaand % 2 == 0) {
      maanden_met_31_dagen--;
    }
    int maanden_met_30_dagen = geboortemaand - maanden_met_31_dagen;

    // Bij de maand februari moeten we rekening houden met het schrikkeljaar
    if (geboortemaand >= 2) {
      geboortejaar % 4 == 0 ? verstreken_dagen_geboorte_jaar += 29 :
          verstreken_dagen_geboorte_jaar += 28;
      // Februari is geen maand met 30 dagen en is mee rekening gehouden
      maanden_met_30_dagen--;
    }

    verstreken_dagen_geboorte_jaar += maanden_met_30_dagen * 30 +
                                 maanden_met_31_dagen * 31 - 1;
  }

  // Het totaal aantal verstreken dagen
  int verstreken_dagen = 365 * (verstreken_jaren - schrikkeljaren) +
                     366 * schrikkeljaren + verstreken_dagen_geboorte_jaar;

  // De dag in de week als nummer (0 = dinsdag, 1 = woensdag, ..., 6 = maandag)
  int dag = (verstreken_dagen % 7);

  // Aangezien we gebruik maken van 1 jan 1901 = dinsdag, nemen we dinsdag
  // als 0-waarde bij onze weekdag representatie
  if (!((geboorte_letter_1 == 'm' && dag == 6) ||
        (geboorte_letter_1 == 'd' && geboorte_letter_2 == 'i' && dag == 0) ||
        (geboorte_letter_1 == 'w' && dag == 1) ||
        (geboorte_letter_1 == 'd' && geboorte_letter_2 == 'o' && dag == 2) ||
        (geboorte_letter_1 == 'v' && dag == 3) ||
        (geboorte_letter_1 == 'z' && geboorte_letter_2 == 'a' && dag == 4) ||
        (geboorte_letter_1 == 'z' && geboorte_letter_2 == 'o' && dag == 5))) {
    if (leeftijd > 30) {
      cerr << "Helaas, dat is niet de dag waarop u bent geboren!";
    } else {
      cerr << "Helaas, dat is niet de dag waarop je bent geboren!";
    }
    return 1;
  }

  // Seeding van de pseudo-random-generator
  srand(time(NULL));

  int a = rand() % 10000 + 1;
  int b = rand() % 20001 - 10000;
  int c = rand() % 20001 - 10000;

  cout << "Juist! Geef nu aan hoeveel oplossingen (0, 1, 2) de volgende\n"
          "vergelijking heeft:\n";

  cout << a << "x^2 "
       << ((b >= 0) ? "+ " : "- ")
       << abs(b) << "x "
       << ((c >= 0) ? "+ " : "- ")
       << abs(c) << " = 0\n\n";

  // Het aantal oplossingen dat de eindgebruiker denkt dat de vergelijking heeft
  int geraden_aantal_oplossingen;
  cin >> geraden_aantal_oplossingen;

  double discriminant = (double) b * b - 4.0 * a * c;
  // Het echte aantal oplossingen dat de vergelijking heeft
  int aantal_oplossingen;

  if (discriminant < 0) {
    aantal_oplossingen = 0;
    cout << "Deze vergelijking heeft geen oplossing! :(\n\n";
  } else if (discriminant == 0) {
    aantal_oplossingen = 1;
    double x = (double) -b / (2 * a);
    cout << "De oplossing van deze vergelijking is: x = " << x << "\n\n";
  } else {
    aantal_oplossingen = 2;
    double x1 = (-b + sqrt(discriminant)) / (2 * a);
    double x2 = (-b - sqrt(discriminant)) / (2 * a);
    cout << "De oplossingen van deze vergelijking zijn: x = " << x1
         << " en x = " << x2 << "\n\n";
  }

  // Wanneer de eindgebruiker het aantal oplossingen correct heeft geraden,
  // wordt deze toegelaten aan de Universiteit Leiden
  if (aantal_oplossingen == geraden_aantal_oplossingen) {
    if (leeftijd > 30) {
      cout << "U heeft het aantal oplossingen goed geraden!\n"
              "Gefeliciteerd, u bent geschikt voor een beta studie!";
    } else {
      cout << "Je hebt het aantal oplossingen goed geraden!\n"
              "Gefeliciteerd, je bent geschikt voor een beta studie!";
    }
    return 0;
  }

  if (leeftijd > 30) {
    cout << "Jammer, u bent niet zo van de cijfertjes.\n"
            "We gaan nu kijken of u geschikt bent voor een alpha studie.\n"
            "Tik de letter van het juiste antwoord in.\n\n";
  } else {
    cout << "Jammer, je bent niet zo van de cijfertjes.\n"
            "We gaan nu kijken of je geschikt bent voor een alpha studie.\n"
            "Tik de letter van het juiste antwoord in.\n\n";
  }

  // De computer kiest een random getal, elk getal leidt tot een andere vraag
  int vraag = rand() % 2;

  if (vraag == 1) {
    if (leeftijd < 30) {
      cout << "Wat was Shakespeares eerste geschreven stuk?\n"
              "\ta. Romeo and Juliette\n\tb. King Henry VI\n\tc. Othello\n\t"
              "d. A Midsummer Night's Dream\n";
    } else {
      cout << "\tWat was Frankenstein zijn eerste naam?\n\n"
              "\ta. Harry\n\tb. Viktor\n\tc. Robert\n\td. Herman\n";
    }
  } else {
    if (leeftijd < 30) {
      cout << "Welke beroemde artist schilderde 'Waterlelies'?\n"
              "\ta. Manet\n\tb. Monet\n\tc. Rembrandt\n\td. Vermeer\n";
    } else {
      cout << "\tWelke schilderstijl was de eerste?\n\n"
              "\ta. Impressionisme\n\tb. Realisme\n\tc. Kubisme\n\t"
              "d. Surrealisme\n\t";
    }
  }

  char antwoord;
  cin >> antwoord;

  // Het juiste antwoord op alle vragen is b (of B)
  if (antwoord == 'b' || antwoord == 'B') {
    if (leeftijd > 30) {
      cout << "B is inderdaad het goede antwoord!\n\n"
              "Gefeliciteerd, u bent geschikt voor aan alpha studie!\n"
              "Nu kunt u in het centrum van Leiden studeren!";
    } else {
      cout << "B is inderdaad het goede antwoord!\n\n"
              "Gefeliciteerd, je bent geschikt voor aan alpha studie!\n"
              "Nu kan je in het centrum van Leiden studeren!";
    }
  } else {
    if (leeftijd > 30) {
      cout << "Het goede antwoord was b.\n\n"
              "Sorry, de universiteit is toch niets voor u.\n"
              "Misschien de Hogeschool proberen?";
    } else {
      cout << "Het goede antwoord was b.\n\n"
              "Sorry, de universiteit is toch niets voor jou.\n"
              "Misschien de Hogeschool proberen?";
    }
  }
  return 0;
}
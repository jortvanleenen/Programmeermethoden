/*
 * Programmeermethoden - Opdracht 4: Koffiesweeper (13/12/2021)
 *
 * Gemaakt met: Code::Blocks, CLion
 * Naam: main.cpp
 * Compiler: G++ 7.2.0 (via MingW-W64-builds 5.0.3)
 * Minimale C++-versie: C++17
 *
 * Dit bestand bevat main() welke met behulp van functie-aanroepen zal
 * vragen om enige parameters voor het aanmaken van een Koffiebord-object. Na
 * het aanmaken van dit object zullen functies uit de Koffiebord-klasse worden
 * aangeroepen om het spel te spelen.
 */

#include "koffiebord.h"
#include "stapel.h"
#include <ctime>
#include <iostream>

/**
 * Toont het infoblok aan de gebruiker.
 */
void toonInfoblok() {
  std::cout << "Programmeermethoden - Opdracht 4: Koffiesweeper (13/12/2021)\n"
               "Dit programma stelt de gebruiker in staat om een\n"
               "kindvriendelijke variant van Minesweeper te spelen, genaamd:\n"
               "Koffiesweeper. Het werkt via de command-line.\n"
               "Stop (S/s) \t- verlaat het programma\n"
               "Open (O/o) \t- open een vakje binnen het spel\n"
               "Markeer (M/m) \t- markeer een vakje binnen het spel\n"
               "Terug (T/t) \t- maak de voorgaande stap ongedaan\n"
               "Random (R/r) \t- open een willekeurig vakje in het spel\n\n";
}

/**
 * Speelt Koffiesweeper als computer met behulp van willekeurige zetten.
 *
 * @param bord het te spelen Koffiebord-object
 */
void speelAlsComputer(Koffiebord& bord) {
  while (bord.getEindstand() == Eindstand::onbepaald) {
    bord.open(true);
  }
}

/**
 * Bewaart de resultaten van de door de computer gespeelde potjes in een
 * 'gewonnen' en 'verloren' array en drukt de resultaten achteraf af.
 *
 * @param breedte breedte van het koffiebord
 * @param hoogte hoogte van het koffiebord
 * @param koffie_percentage percentage koffiemokken in het koffiebord
 * @param aantal_spellen aantal te spelen zetten
 */
void computerRapport(int breedte, int hoogte, int koffie_percentage,
                     int aantal_spellen) {
  int* gewonnen_borden{new int[aantal_spellen]{}};
  int* verloren_borden{new int[aantal_spellen]{}};

  for (int i{0}; i < aantal_spellen; i++) {
    Koffiebord bord{breedte, hoogte, koffie_percentage};
    speelAlsComputer(bord);
    if (bord.getEindstand() == Eindstand::gewonnen) {
      gewonnen_borden[i] = bord.getTotaalAantalZetten();
    } else {
      verloren_borden[i] = bord.getTotaalAantalZetten();
    }
  }

  for (int i{0}; i < aantal_spellen; i++) {
    std::cout << "Spel " << i + 1 << ": ";
    // 0 zetten is onmogelijk, juiste aantal staat dus in andere array
    if (gewonnen_borden[i] == 0) {
      std::cout << verloren_borden[i] << " Zet(ten). (Verloren)\n";
    } else {
      std::cout << gewonnen_borden[i] << " Zet(ten). (Gewonnen)\n";
    }
  }

  delete[] gewonnen_borden;
  delete[] verloren_borden;
}

/**
 * Speelt een potje Koffiesweeper als mens via menu-opties.
 *
 * @param breedte breedte van het koffiebord
 * @param hoogte hoogte van het koffiebord
 * @param koffie_percentage percentage koffiemokken in het koffiebord
 */
void speelAlsMens(int breedte, int hoogte, int koffie_percentage) {
  char invoer{};
  Stapel stapel{};
  Koffiebord bord{breedte, hoogte, koffie_percentage};

  do {
    bord.drukAf();

    std::cout << "[S]top, [O]pen, [M]arkeer, [T]erug, [R]andom\n";
    invoer = static_cast<char>(toupper(vraagInvoer()));
    switch (invoer) {
      case 'S':
        // Exit menu vanwege while-conditie
        break;
      case 'O':
        stapel.push(Koffiebord::maakKopie(bord));
        // Als het openen mislukt, is de staat van het bord niet veranderd
        if (!bord.open(false)) {
          stapel.pop(bord);
        }
        break;
      case 'M':
        bord.markeer();
        break;
      case 'T':
        // Een zet terug heeft weinig zin als je al gewonnen hebt
        if (bord.getEindstand() == Eindstand::gewonnen || stapel.is_leeg()) {
          std::cout << "Kan geen zet ongedaan maken, herstart of zet eerst!\n";
        } else {
          stapel.pop(bord);
        }
        break;
      case 'R':
        stapel.push(Koffiebord::maakKopie(bord));
        if (!bord.open(true)) {
          stapel.pop(bord);
        }
        break;
      default:
        std::cout << "Onbekende actie, probeer het nogmaals!\n";
        break;
    }
  } while (invoer != 'S');
}

/**
 * Toont de gebruiker het infoblok waarna om enige parameters zal worden
 * gevraagd. Met deze parameters wordt een Koffiebord-object gemaakt, waarmee
 * vervolgens het spel zal worden gespeeld.
 *
 * @return geeft EXIT_SUCCESS bij succes
 */
int main() {
  toonInfoblok();

  srand(time(nullptr));

  std::cout << "Geef de gewenste hoogte van het speelveld (1-100):\n";
  int hoogte{vraagGetal(1, 100)};
  std::cout << "Geef de gewenste breedte van het speelveld (1-100):\n";
  int breedte{vraagGetal(1, 100)};
  std::cout << "Geef het gewenste percentage koffiekoppen in het spel (0-100):"
               "\n";
  int koffie_percentage{vraagGetal(0, 100)};

  int aantal_spellen{1};

  char speelt_computer_invoer{};
  do {
    std::cout << "Wil je dat de computer voor je speelt? ([J]a/[N]ee):\n";
    speelt_computer_invoer = static_cast<char>(toupper(vraagInvoer()));
  } while (speelt_computer_invoer != 'J' && speelt_computer_invoer != 'N');

  bool computer_speelt{speelt_computer_invoer == 'J'};

  if (computer_speelt) {
    std::cout << "Geef het gewenste aantal spellen dat de computer dient te "
                 "spelen:\n";
    // Alleen de computer mag meerdere spellen spelen
    aantal_spellen = vraagGetal(1, 500);
    computerRapport(breedte, hoogte, koffie_percentage, aantal_spellen);
  } else {
    speelAlsMens(breedte, hoogte, koffie_percentage);
  }

  return EXIT_SUCCESS;
}

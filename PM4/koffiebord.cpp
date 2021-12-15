/*
 * Implementeert alle functies uit koffiebord.h en is verantwoordelijk voor het
 * spelen van het Koffiesweeper-spel.
 *
 * Gemaakt met: Code::Blocks, CLion
 * Naam: koffiebord.cpp
 * Compiler: G++ 7.2.0 (via MingW-W64-builds 5.0.3)
 */

#include "koffiebord.h"
#include <iostream>

/**
 * Constructor van Koffiebord-object.
 *
 * @param breedte_invoer gewenste breedte van het koffiebord
 * @param hoogte_invoer gewenste hoogte van het koffiebord
 * @param koffie_percentage gewenste percentage koffiemokken in het koffiebord
 */
Koffiebord::Koffiebord(int breedte_invoer, int hoogte_invoer,
                       int koffie_percentage) {
  hoogte = hoogte_invoer;
  breedte = breedte_invoer;

  Vakje* rij_boven{maakRij(koffie_percentage)};
  ingang = rij_boven;

  for (int i{0}; i < hoogte_invoer - 1; i++) {
    Vakje* rij_onder{maakRij(koffie_percentage)};
    rij_boven = verbindTweeRijen(rij_boven, rij_onder, true);
  }
}

/**
 * Destructor van Koffiebord-object.
 */
Koffiebord::~Koffiebord() {
  Vakje* iterator_vakken{ingang};
  Vakje* iterator_volgende_rij{ingang->buren[4]};
  Vakje* temp{ingang};

  while (iterator_vakken != nullptr || iterator_volgende_rij != nullptr) {
    if (iterator_vakken != nullptr) {
      iterator_vakken = iterator_vakken->buren[2];
    } else {
      temp = iterator_volgende_rij;
      iterator_vakken = iterator_volgende_rij->buren[2];
      iterator_volgende_rij = iterator_volgende_rij->buren[4];
    }
    delete temp;
    temp = iterator_vakken;
  }
}

/**
 * Retourneert de eindstand van het bord.
 *
 * @return onbepaald, gewonnen of verloren
 */
Eindstand Koffiebord::getEindstand() const {
  return eindstand;
}

/**
 * Retourneert het totale aantal gezette zetten.
 *
 * @return het totale aantal gezette zetten
 */
int Koffiebord::getTotaalAantalZetten() const {
  return totaal_aantal_zetten;
}

/**
 * Maakt een onafhankelijke/op zichzelf staande kopie van een dubbele pointer
 * rij bestaande uit koffiebord-vakjes.
 *
 * @param originele_rij de rij waarvan een kopie gemaakt dient te worden
 * @return een kopie van de originele rij
 */
Vakje* Koffiebord::kopieerRij(Vakje* originele_rij) {
  Vakje* nieuw_vakje{new(std::nothrow) Vakje{}};
  if (!nieuw_vakje) {
    std::cerr << "Kon geen geheugen vrijmaken!\n";
  }
  *nieuw_vakje = *originele_rij;
  Vakje* kopie_rij{nieuw_vakje};

  originele_rij = originele_rij->buren[2];
  while (originele_rij != nullptr) {
    Vakje* volgend_nieuw_vakje{new(std::nothrow) Vakje{}};
    if (!volgend_nieuw_vakje) {
      std::cerr << "Kon geen geheugen vrijmaken!\n";
    }
    *volgend_nieuw_vakje = *originele_rij;

    nieuw_vakje->buren[2] = volgend_nieuw_vakje;
    volgend_nieuw_vakje->buren[6] = nieuw_vakje;

    nieuw_vakje = volgend_nieuw_vakje;
    originele_rij = originele_rij->buren[2];
  }

  return kopie_rij;
}

/**
 * Maakt een onafhankelijke/op zichzelf staande kopie van een koffiebord.
 *
 * @param bord het bord waarvan een kopie gemaakt dient te worden
 * @return een kopie van het originele bord
 */
Koffiebord Koffiebord::maakKopie(const Koffiebord& bord) {
  Koffiebord kopie_bord{bord};
  Vakje* originele_rij_onder{bord.ingang->buren[4]};
  Vakje* kopie_rij_boven{kopieerRij(bord.ingang)};
  kopie_bord.ingang = kopie_rij_boven;

  for (int i{0}; i < bord.hoogte - 1; i++) {
    Vakje* kopie_rij_onder{kopieerRij(originele_rij_onder)};
    kopie_rij_boven = verbindTweeRijen(kopie_rij_boven,
                                       kopie_rij_onder, false);
    originele_rij_onder = originele_rij_onder->buren[4];
  }

  return kopie_bord;
}

/**
 * Vindt een vakje binnen het koffiebord.
 *
 * @param kolom gewenste kolom
 * @param rij gewenste rij
 * @return gewenste vakje
 */
Vakje* Koffiebord::vindVakje(int kolom, int rij) {
  int huidige_kolom{1};
  int huidige_rij{1};
  Vakje* huidige_vakje{ingang};

  while (huidige_kolom < kolom && huidige_rij < rij) {
    huidige_vakje = huidige_vakje->buren[3];
    huidige_kolom++;
    huidige_rij++;
  }
  while (huidige_kolom < kolom) {
    huidige_vakje = huidige_vakje->buren[2];
    huidige_kolom++;
  }
  while (huidige_rij < rij) {
    huidige_vakje = huidige_vakje->buren[4];
    huidige_rij++;
  }

  return huidige_vakje;
}

/**
 * Drukt de huidige stand van het koffiebord af in de command-line.
 */
void Koffiebord::drukAf() {
  Vakje* iterator_rij{ingang};
  Vakje* begin_rij{ingang};
  std::cout << "Aantal koffiekoppen: " << totaal_aantal_koffie
            << " | Aantal zetten: " << totaal_aantal_zetten << '\n';
  do {
    if (!iterator_rij->is_geopend) {
      if (iterator_rij->is_gemarkeerd) {
        std::cout << 'K';
      } else {
        std::cout << '#';
      }
    } else {
      if (iterator_rij->heeft_koffie) {
        std::cout << 'X';
      } else if (iterator_rij->omliggende_koffie == 0) {
        std::cout << '-';
      } else {
        std::cout << iterator_rij->omliggende_koffie;
      }
    }

    if (iterator_rij->buren[2] == nullptr) {
      iterator_rij = begin_rij->buren[4];
      begin_rij = begin_rij->buren[4];
      std::cout << '\n';
    } else {
      iterator_rij = iterator_rij->buren[2];
    }

  } while (begin_rij != nullptr);

  if (eindstand == Eindstand::verloren) {
    std::cout << "Je hebt verloren. Doe een zet terug of begin overnieuw.\n";
  } else if (eindstand == Eindstand::gewonnen) {
    std::cout << "Je hebt gewonnen! Herstart het spel om opnieuw te spelen!\n";
  }

}

/**
 * Opent de buurvakjes van een vakje op recursieve wijze als deze nul buren
 * met koffie heeft.
 *
 * @param vakje het te openen vakje
 */
void Koffiebord::openVakjeRecursief(Vakje* vakje) {
  vakje->is_geopend = true;
  totaal_aantal_geopend++;

  if (vakje->omliggende_koffie == 0) {
    for (auto& i: vakje->buren) {
      if (i != nullptr && !i->is_geopend) {
        if (i->is_gemarkeerd) {
          i->is_gemarkeerd = false;
        }
        openVakjeRecursief(i);
      }
    }
  }

}

/**
 * Opent een vakje van het koffiebord mits het spel niet voorbij is en het
 * geselecteerde vakje niet gemarkeerd of reeds geopend is.
 *
 * @param open_random 'true' wanneer er willekeurig een vak wordt gekozen
 * @return 'true' als het succesvol een vak heeft kunnen openen, anders 'false'
 */
bool Koffiebord::open(bool open_random) {
  if (eindstand != Eindstand::onbepaald) {
    std::cout << "Kan geen verdere zet doen, het spel is voorbij!\n";
    return false;
  }

  int rij{};
  int kolom{};
  Vakje* vakje{};
  do {
    if (open_random) {
      rij = rand() % hoogte + 1;
      kolom = rand() % breedte + 1;
    } else {
      vraagCoordinaat(kolom, rij);
    }
    vakje = vindVakje(kolom, rij);
    if (vakje->is_gemarkeerd && !open_random) {
      std::cout << "Je mag een gemarkeerd veld niet openen!\n";
      return false;
    }
    if (vakje->is_geopend && !open_random) {
      std::cout << "Je kan een reeds geopend veld niet openen!\n";
      return false;
    }
  } while (vakje->is_geopend || vakje->is_gemarkeerd);

  totaal_aantal_zetten++;

  if (!heeft_geopend_vak) {
    heeft_geopend_vak = true;

    if (vakje->heeft_koffie) {
      vakje->heeft_koffie = false;
      totaal_aantal_koffie--;
      for (auto& i: vakje->buren) {
        if (i != nullptr) {
          i->omliggende_koffie--;
        }
      }
    }
  }

  openVakjeRecursief(vakje);

  if (vakje->heeft_koffie) {
    eindstand = Eindstand::verloren;
  }
  if (totaal_aantal_geopend + totaal_aantal_koffie
      == hoogte * breedte) {
    eindstand = Eindstand::gewonnen;
  }
  return true;
}

/**
 * Wisselt de gemarkeerde staat van het geselecteerde veld.
 */
void Koffiebord::markeer() {
  if (eindstand != Eindstand::onbepaald) {
    std::cout << "Kan niet markeren, het spel is voorbij!\n";
    return;
  }

  int rij{};
  int kolom{};
  Vakje* vakje{};
  do {
    vraagCoordinaat(kolom, rij);
    vakje = vindVakje(kolom, rij);
    if (vakje->is_geopend) {
      std::cout << "Je mag een geopend veld niet markeren!\n";
    }
  } while (vakje->is_geopend);

  vakje->is_gemarkeerd = !vakje->is_gemarkeerd;
}

/**
 * Vraagt de gebruiker om een rij en kolom binnen het speelveld, groter dan 0.
 *
 * @param rij de gewenste rij
 * @param kolom de gewenste kolom
 */
void Koffiebord::vraagCoordinaat(int& kolom, int& rij) const {
  std::cout << "Voer de gewenste kolom in:\n";
  kolom = vraagGetal(1, breedte);

  std::cout << "Voer de gewenste rij in:\n";
  rij = vraagGetal(1, hoogte);
}

/**
 * Verbind twee dubbele pointer rijen bestaande uit koffiebord-vakjes van
 * dezelfde lengte met elkaar en retourneert de ingang van de onderste rij.
 *
 * @param rij_boven ingang van de boven te plaatsen rij
 * @param rij_onder ingang van de onder te plaatsen rij
 * @param controleerKoffie 'true' als we koffie moeten controleren voor buren
 * @return ingang van de na verbinding onder geplaatste rij
 */
Vakje* Koffiebord::verbindTweeRijen(Vakje* rij_boven, Vakje* rij_onder,
                                    bool controleerKoffie) {
  Vakje* vakje_boven{rij_boven};
  Vakje* vakje_onder{rij_onder};

  // Vakje_boven (x) met omliggende buren en boven met onder verbonden:
  // 7 0 1     7      0      1
  // 6 X 2 --> X(y>7) X(y>0) X(y>1)
  // 5 4 3     Y(x>5) Y(x>4) Y(x>3)
  while (vakje_boven != nullptr && vakje_onder != nullptr) {

    vakje_boven->buren[5] = vakje_onder->buren[6];
    if (controleerKoffie && vakje_onder->buren[6] != nullptr
        && vakje_onder->buren[6]->heeft_koffie) {
      vakje_boven->omliggende_koffie++;
    }

    vakje_boven->buren[4] = vakje_onder;
    if (controleerKoffie && vakje_onder->heeft_koffie) {
      vakje_boven->omliggende_koffie++;
    }

    vakje_boven->buren[3] = vakje_onder->buren[2];
    if (controleerKoffie && vakje_onder->buren[2] != nullptr
        && vakje_onder->buren[2]->heeft_koffie) {
      vakje_boven->omliggende_koffie++;
    }

    vakje_onder->buren[7] = vakje_boven->buren[6];
    if (controleerKoffie && vakje_boven->buren[6] != nullptr
        && vakje_boven->buren[6]->heeft_koffie) {
      vakje_onder->omliggende_koffie++;
    }

    vakje_onder->buren[0] = vakje_boven;
    if (controleerKoffie && vakje_boven->heeft_koffie) {
      vakje_onder->omliggende_koffie++;
    }

    vakje_onder->buren[1] = vakje_boven->buren[2];
    if (controleerKoffie && vakje_boven->buren[2] != nullptr
        && vakje_boven->buren[2]->heeft_koffie) {
      vakje_onder->omliggende_koffie++;
    }

    vakje_boven = vakje_boven->buren[2];
    vakje_onder = vakje_onder->buren[2];
  }

  return rij_onder;
}

/**
 * Maakt een dubbele pointer rij bestaande uit vakjes van het koffiebord.
 *
 * @param koffie_percentage het percentage vakjes dat koffie dient te bevatten
 * @return ingang-vakje van de gehele dubbele pointer rij
 */
Vakje* Koffiebord::maakRij(int koffie_percentage) {
  Vakje* vakje{new(std::nothrow) Vakje{}};
  if (!vakje) {
    std::cerr << "Kon geen geheugen vrijmaken!\n";
  }
  Vakje* begin{vakje};
  vakje->heeft_koffie = ((rand() % 100 + 1) < koffie_percentage);
  if (vakje->heeft_koffie) {
    totaal_aantal_koffie++;
  }

  for (int j{0}; j < breedte - 1; j++) {
    Vakje* volgende_vakje{new(std::nothrow) Vakje{}};
    if (!volgende_vakje) {
      std::cerr << "Kon geen geheugen vrijmaken!\n";
    }
    if ((rand() % 100 + 1) < koffie_percentage) {
      volgende_vakje->heeft_koffie = true;
      // Wanneer het volgende vakje koffie bevat dan heeft het huidige vakje
      // er een buur bij met koffie aangezien ze naast elkaar liggen
      vakje->omliggende_koffie++;
      totaal_aantal_koffie++;
    }
    vakje->buren[2] = volgende_vakje;
    volgende_vakje->buren[6] = vakje;
    if (vakje->heeft_koffie) {
      volgende_vakje->omliggende_koffie++;
    }
    vakje = volgende_vakje;
  }

  return begin;
}

/**
 * Vraagt de gebruiker om een karakter waarbij newline-karakters worden
 * genegeerd.
 *
 * @return het eerste karakter niet gelijk aan newline
 */
char vraagInvoer() {
  char invoer{static_cast<char>(std::cin.get())};
  while (invoer == '\n') {
    invoer = static_cast<char>(std::cin.get());
  }
  char ruim_op{invoer};
  while (ruim_op != '\n') {
    ruim_op = static_cast<char>(std::cin.get());
  }
  return invoer;
}

/**
 * Vraagt de gebruiker om een getal. Voorgaande newline-karakters worden
 * genegeerd.
 *
 * Bijvoorbeeld: [enter]34hshf4hh3 -> 3443; Bij max van 500: 3443 -> 344.
 *
 * @param min het minimale getal dat geretourneerd dient te worden
 * @param max het maximale getal dat geretourneerd dient te worden
 * @return het getal gehaald uit de invoer van de gebruiker tussen min en max
 */
int vraagGetal(int min, int max) {
  int getal{};
  char invoer{static_cast<char>(std::cin.get())};
  while (invoer == '\n') {
    invoer = static_cast<char>(std::cin.get());
  }

  do {
    do {
      if ((invoer >= '0' && invoer <= '9') &&
          (10 * getal + (invoer - '0') <= max)) {
        getal = 10 * getal + (invoer - '0');
      }
      invoer = static_cast<char>(std::cin.get());
    } while (invoer != '\n' && invoer);

    if (getal < min) {
      std::cout << "Vul een getal groter dan " << min - 1 << " in!\n";
    }
  } while (getal < min);

  return getal;
}


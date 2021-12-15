/*
 * Header-file van koffiebord.cpp.
 *
 * Gemaakt met: Code::Blocks, CLion
 * Naam: koffiebord.h
 * Compiler: G++ 7.2.0 (via MingW-W64-builds 5.0.3)
 */

#ifndef PM4_KOFFIEBORD_H
#define PM4_KOFFIEBORD_H

enum class Eindstand {
  onbepaald,
  gewonnen,
  verloren
};

class Vakje {
public:
  bool heeft_koffie{false};
  bool is_gemarkeerd{false};
  bool is_geopend{false};
  int omliggende_koffie{0};
  Vakje* buren[8]{};
};

class Koffiebord {
private:
  Vakje* ingang{};
  Eindstand eindstand{Eindstand::onbepaald};
  bool heeft_geopend_vak{false};
  int totaal_aantal_koffie{0};
  int totaal_aantal_geopend{0};
  int totaal_aantal_zetten{0};
  int hoogte{1};
  int breedte{1};

  void vraagCoordinaat(int& kolom, int& rij) const;

  Vakje* vindVakje(int kolom, int rij);

  void openVakjeRecursief(Vakje* vakje);

  static Vakje* kopieerRij(Vakje* originele_rij);

  Vakje* maakRij(int koffie_percentage);

  static Vakje* verbindTweeRijen(Vakje* rij_boven, Vakje* rij_onder,
                                 bool controleerKoffie);

public:
  Koffiebord() = default;

  Koffiebord(int breedte_invoer, int hoogte_invoer, int koffie_percentage);

  ~Koffiebord();

  void drukAf();

  bool open(bool open_random);

  void markeer();

  static Koffiebord maakKopie(const Koffiebord& bord);

  [[nodiscard]] Eindstand getEindstand() const;

  [[nodiscard]] int getTotaalAantalZetten() const;
};

char vraagInvoer();

int vraagGetal(int min, int max);

#endif

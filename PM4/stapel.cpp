/*
 * Implementeert alle functies uit stapel.h en is verantwoordelijk voor het
 * bijhouden van een stapel Koffiebord-objecten.
 *
 * Gemaakt met: Code::Blocks, CLion
 * Naam: stapel.cpp
 * Compiler: G++ 7.2.0 (via MingW-W64-builds 5.0.3)
 */

#include "stapel.h"
#include <iostream>

/**
 * Haalt alle elementen van de stapel wanneer deze wordt ge-deconstruct.
 */
Stapel::~Stapel() {
  Koffiebord bord{};
  while (!is_leeg()) {
    pop(bord);
  }
}

/**
 * Zet een Koffiebord-object op de stapel.
 *
 * @param bord het Koffiebord-oject dat op de stapel gezet dient te worden
 */
void Stapel::push(const Koffiebord& bord) {
  Element* nieuw_element{new(std::nothrow) Element{}};
  if (!nieuw_element) {
    std::cerr << "Kon geen geheugen vrijmaken!\n";
  }

  nieuw_element->bord = bord;
  nieuw_element->volgende = bovenste;
  bovenste = nieuw_element;
}

/**
 * Haalt een Koffiebord-object van de stapel en retourneert deze met behulp
 * van Return by Reference.
 *
 * @param bord het Koffiebord-object dat wordt gevuld met die van de stapel
 */
void Stapel::pop(Koffiebord& bord) {
  Element* temp{bovenste};
  bord = bovenste->bord;
  bovenste = bovenste->volgende;
  delete temp;
}

/**
 * Retourneert een bool die aangeeft of de stapel leeg is.
 *
 * @return 'true' wanneer de stack leeg is, anders 'false'
 */
bool Stapel::is_leeg() {
  return bovenste == nullptr;
}

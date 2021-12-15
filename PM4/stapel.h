/*
 * Header-file van stapel.cpp.
 *
 * Gemaakt met: Code::Blocks, CLion
 * Naam: stapel.h
 * Compiler: G++ 7.2.0 (via MingW-W64-builds 5.0.3)
 */

#ifndef PM4_STAPEL_H
#define PM4_STAPEL_H

#include "koffiebord.h"

class Element {
public:
  Element* volgende{nullptr};
  Koffiebord bord{};
};

class Stapel {
private:
  Element* bovenste{nullptr};

public:
  ~Stapel();

  bool is_leeg();

  void push(const Koffiebord& bord);

  void pop(Koffiebord& bord);
};

#endif

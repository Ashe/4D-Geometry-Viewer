// Simplex.h
// A class storing a 5-cell polytope

#ifndef POLYTOPES_SIMPLEX_H
#define POLYTOPES_SIMPLEX_H

#include "Polytope.h"

namespace App {

  // Store information necessary to render a 4D simplex
  class Simplex : public Polytope {

    public:

      // Constructor
      Simplex();

      // Show information about the simplex
      virtual void showPolytopeInfo() override;
  };
}

#endif

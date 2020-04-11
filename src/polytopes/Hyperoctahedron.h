// Hyperoctahedron.h
// A class storing a 16-cell polytope

#ifndef POLYTOPES_HYPEROCTAHEDRON_H
#define POLYTOPES_HYPEROCTAHEDRON_H

#include "Polytope.h"

namespace App {

  class Hyperoctahedron : public Polytope {

    public:

      // Constructor
      Hyperoctahedron();

      // Show information about the hyperoctahedron
      virtual void showPolytopeInfo() override;
  };
}

#endif

// Hypercube.h
// A class storing an 8-cell polytope 

#ifndef POLYTOPES_HYPERCUBE_H
#define POLYTOPES_HYPERCUBE_H

#include "Polytope.h"

namespace App {

  // Store information necessary to render a 4D cube
  class Hypercube : public Polytope {

    public:

      // Constructor
      Hypercube();

      // Show information about the hypercube
      virtual void showPolytopeInfo() override;
  };
}

#endif

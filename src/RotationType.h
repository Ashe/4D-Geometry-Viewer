// RotationType.h
// An enum describing rotations

#ifndef ROTATIONTYPE_H
#define ROTATIONTYPE_H

namespace App {

  // Unique 4D rotations
  enum RotationType {
      XY, XZ, XW, YZ, YW, ZW };

  // String versions of enum
  constexpr const char* rotationTypes[6] = {
      "XY", "XZ", "XW", "YZ", "YW", "ZW"};
}

#endif

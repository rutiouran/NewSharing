/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
    

  private:
    void DefineMaterials();
    G4Material* world_mat;
    G4Material* tracker_mat;

    G4Material* shie_mat;
    G4Material* shie_mat2_Pb;

    G4Material* vach_mat;

    G4Material* hewi_mat;

    G4Material* Alch_mat;

    G4Material* CoWa_mat;

    G4Material* D2O;
    

    G4LogicalVolume** fLogicalTarget;
};

#endif

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"
#include "DetectorConstruction.hh"
#include "Run.hh"

//class G4Run;
class Run;
class DetectorConstruction;
class PrimaryGeneratorAction;

class RunAction : public G4UserRunAction
{
  public:
    RunAction(DetectorConstruction*, PrimaryGeneratorAction*);
    virtual ~RunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

 private:
    Run* fRun;
    DetectorConstruction* fDetector;
    PrimaryGeneratorAction* fPrimary;
};

#endif

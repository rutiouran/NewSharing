#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

#include "HeavyWaterHit.hh"

class EventAction : public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();

  virtual void BeginOfEventAction(const G4Event* event);
  virtual void EndOfEventAction(const G4Event* event);

private:
  HeavyWaterHitsCollection* GetHitsCollection(G4int hcID, const G4Event* event) const;

  // data members
  G4int fheavywaterHCID;
};
#endif

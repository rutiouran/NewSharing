#include "TargetHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<TargetHit>* TargetHitAllocator=0;

TargetHit::TargetHit()
 : G4VHit(),
   fTrackID(-1),
   fTargetNb(-1),
   fKin(0.),
   fPid(0),
   fPosition(G4ThreeVector())
{}

TargetHit::~TargetHit() 
{}

TargetHit::TargetHit(const TargetHit& right)
  : G4VHit()
{
  fTrackID   = right.fTrackID;
  fTargetNb  = right.fTargetNb;
  fKin       = right.fKin;
  fPid       = right.fPid;
  fPosition  = right.fPosition;
}

const TargetHit& TargetHit::operator=(const TargetHit& right)
{
  fTrackID   = right.fTrackID;
  fTargetNb  = right.fTargetNb;
  fKin       = right.fKin;
  fPid       = right.fPid;
  fPosition  = right.fPosition;

  return *this;
}

G4bool TargetHit::operator==(const TargetHit& right) const
{
  return ( this == &right ) ? true : false;
}

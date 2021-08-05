#include "StackingAction.hh"

#include <G4Track.hh>

StackingAction* StackingAction::instance = nullptr ;

StackingAction::StackingAction()
: G4UserStackingAction()
{
  if (instance)
  throw std::logic_error("StackingAction already exists") ;

  instance = this ;

  G4cout << "Create StackingAction" << G4endl ;
}

G4ClassificationOfNewTrack StackingAction::ClassifyNewTrack(const G4Track* track)
{
  nParticlesPerId[ track->GetDefinition()->GetPDGEncoding() ]++ ;

#if 0
  if ( !killNeutrons )
    return fUrgent ;

  if ( track->GetDefinition()->GetPDGEncoding() == 2112 )
    return fKill ;
#endif

  return fUrgent ;
}


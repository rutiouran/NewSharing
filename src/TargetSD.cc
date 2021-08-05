#include "TargetSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "g4root.hh"

TargetSD::TargetSD(const G4String& name,
                   const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

TargetSD::~TargetSD() 
{}

void TargetSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection 
    = new TargetHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce
  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 
}

G4bool TargetSD::ProcessHits(G4Step* step, 
                                     G4TouchableHistory*)
{
  //G4int pid = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();

  // energy deposit

  //if(step->GetTrack()->GetParticleDefinition()->GetPDGEncoding()!=14 && edep==0.)
  //return false;

  TargetHit* newHit = new TargetHit();

  newHit->SetTrackID(step->GetTrack()->GetTrackID());
  newHit->SetTargetNb(step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
  newHit->SetKineticEnergy(step->GetTrack()->GetKineticEnergy());
  newHit->SetPid(step->GetTrack()->GetParticleDefinition()->GetPDGEncoding());
  newHit->SetPosition(step->GetTrack()->GetPosition());
  fHitsCollection->insert( newHit );

  return true;
}

void TargetSD::EndOfEvent(G4HCofThisEvent*)
{}

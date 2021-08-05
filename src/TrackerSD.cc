#include "TrackerSD.hh"
#include "TrackerHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "g4root.hh"

TrackerSD::TrackerSD(const G4String& name,
                         const G4String& hitsCollectionName) 
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

TrackerSD::~TrackerSD() 
{}

void TrackerSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection 
    = new TrackerHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce
  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);

  // Create hits
  fHitsCollection->insert(new TrackerHit());
}

G4bool TrackerSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  G4int pid = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();

  // energy deposit
//  G4double edep = step->GetTotalEnergyDeposit();

  //if (edep==0.) return false;

  TrackerHit* newHit = new TrackerHit();

  newHit->SetTrackID(step->GetTrack()->GetTrackID());
  newHit->SetPos(step->GetPostStepPoint()->GetPosition());
  newHit->SetKineticEnergy(step->GetTrack()->GetKineticEnergy());

  fHitsCollection->insert(newHit);

  auto analysisManager = G4AnalysisManager::Instance();

  auto localPos = newHit->GetPos();

  if(pid == 2112)
  {
  analysisManager->FillNtupleDColumn(1, 0, step->GetTrack()->GetKineticEnergy());
  analysisManager->FillNtupleDColumn(1, 1, localPos.x()/CLHEP::m);
  analysisManager->FillNtupleDColumn(1, 2, localPos.y()/CLHEP::m);
  analysisManager->FillNtupleDColumn(1, 3, localPos.z()/CLHEP::m);
  analysisManager->AddNtupleRow(1);
  }

  return true;
}

void TrackerSD::EndOfEvent(G4HCofThisEvent*)
{}

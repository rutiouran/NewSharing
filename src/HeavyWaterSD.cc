#include "HeavyWaterSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "g4root.hh"

HeavyWaterSD::HeavyWaterSD( const G4String& name, 
                            const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name),
   fHitsCollection(nullptr)
{
  collectionName.insert(hitsCollectionName);
}

HeavyWaterSD::~HeavyWaterSD() 
{}

void HeavyWaterSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection 
    = new HeavyWaterHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce
  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection ); 

  // Create hits
  fHitsCollection->insert(new HeavyWaterHit());
}

G4bool HeavyWaterSD::ProcessHits(G4Step* step, 
                                     G4TouchableHistory*)
{  
  //Energy deposit
  auto edep = step->GetTotalEnergyDeposit();
 
  //Step length
  G4double stepLength = 0.;
  if( step->GetTrack()->GetDefinition()->GetPDGCharge() != 0)
  {
    stepLength = step->GetStepLength();
  }

  if(edep == 0. && stepLength == 0.) return false;

  HeavyWaterHit* newHit = new HeavyWaterHit();
  newHit->SetTrackID(step->GetTrack()->GetTrackID());
  newHit->Add(edep, stepLength);
  fHitsCollection->insert(newHit);

  //Fill histograms and ntuple
//  auto analysisManager = G4AnalysisManager::Instance();
//
//  G4int pid = step->GetTrack()->GetParticleDefinition()->GetPDGEncoding();
//  
//  G4int ParentID = step->GetTrack()->GetParentID();
//  if(pid == 2112)
//  G4cout << "pid: " << pid << ", edep: " << edep << ", step: " << step << G4endl; 
//  
//  if(pid<1e9)
//  {
//     analysisManager->FillH1(2, pid);
//     G4cout << "Fill pid" << G4endl;
//  }
//  else
//  {
//     analysisManager->FillH1(3, pid);
//     G4cout << "Fill pid" << G4endl;
//  }
//
//  analysisManager->FillNtupleDColumn(2, 0, pid);
//  analysisManager->AddNtupleRow(2);

  //Avoid double counting
  //if(pid == 2112) step->GetTrack()->SetTrackStatus(fStopAndKill);

  return true;
}

void HeavyWaterSD::EndOfEvent(G4HCofThisEvent*)
{}

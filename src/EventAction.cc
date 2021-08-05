#include "EventAction.hh"
#include "RunAction.hh"

#include "G4SDManager.hh"
#include "HeavyWaterHit.hh"
#include "HeavyWaterSD.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include "g4root.hh"
#include <iomanip>

EventAction::EventAction()
: G4UserEventAction(),
  fheavywaterHCID(-1)
{}

EventAction::~EventAction()
{}

HeavyWaterHitsCollection* EventAction::GetHitsCollection(G4int hcID, const G4Event* event) const
{
  auto hitsCollection
    = static_cast<HeavyWaterHitsCollection*>(
        event->GetHCofThisEvent()->GetHC(hcID));

  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    G4Exception("B4cEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }

  return hitsCollection;
}

void EventAction::BeginOfEventAction(const G4Event*)
{}

void EventAction::EndOfEventAction(const G4Event* event)
{
  // Get hits collections IDs (only once)
  if(fheavywaterHCID == -1)
  {
  fheavywaterHCID = G4SDManager::GetSDMpointer()->GetCollectionID("HeavyWaterHitsCollection");
  }

  // Get hits collection
  auto heavywaterHC = GetHitsCollection(fheavywaterHCID, event);

  // Get hit with total value
  auto heavywaterHit = (*heavywaterHC)[heavywaterHC->entries()-1];

  // Fill histograms, ntuple
  //

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // fill ntuple
  analysisManager->FillNtupleDColumn(0, 0, heavywaterHit->GetEdep());
  analysisManager->FillNtupleDColumn(0, 1, heavywaterHit->GetTrackLength());
  analysisManager->AddNtupleRow(0);



//  //Get hits collection IDs (only once)
//  if(fTargetHCID == -1)
//  {
//    fTargetHCID
//       = G4SDManager::GetSDMpointer()->GetCollectionID("TargetHitsCollection");
//  }
//
//  // Get hits collection
//  auto targetHC = GetTargetHitsCollection(fTargetHCID, event);
//  if(targetHC == 0) return;
//
//  // Get hit with total values
//  if(targetHC->entries()<=0) return;
//
//  //Fill histograms, ntuple
//  //
//
//  //Get analysis manager
//  auto analysisManager = G4AnalysisManager::Instance();
//
//  G4double Edep = 0.; // The total energy deposit
//  G4double edep[copyNb] = {0}; // The energy deposit per target
//  G4int arr[targetHC->entries()-1] = {0};
//
//  for(long unsigned int i=0; i<targetHC->entries(); i++)
//  {
//     Edep += (*targetHC)[i]->GetEdep();
//     edep[(*targetHC)[i]->GetTargetNb()] += (*targetHC)[i]->GetEdep();
//
//     analysisManager->FillNtupleIColumn(1+copyNb, (*targetHC)[i]->GetPid());
//
//     if((*targetHC)[i]->GetPid()==1000280630 && arr[(*targetHC)[i]->GetTrackID()]==0)
//     {
//       analysisManager->FillNtupleDColumn(2+copyNb, (*targetHC)[i]->GetPosition().z()/CLHEP::m);
//       arr[(*targetHC)[i]->GetTrackID()]++;
//     }
//  }
//
//  analysisManager->FillNtupleDColumn(0, Edep);
//  for(G4int i=0; i<copyNb; i++)
//  {
//    analysisManager->FillNtupleDColumn(i+1, edep[i]);
//  }
//  analysisManager->AddNtupleRow();
}

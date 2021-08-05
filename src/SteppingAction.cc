#include "SteppingAction.hh"
#include "Run.hh"
#include "EventAction.hh"

#include "g4root.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction(EventAction* event)
: G4UserSteppingAction(), 
  fEventAction(event)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  auto analysisManager  = G4AnalysisManager::Instance();

  // count processes
  // 
  const G4StepPoint* endPoint = step->GetPostStepPoint();
  const G4VProcess*  process  = endPoint->GetProcessDefinedStep();

  G4String name = step->GetTrack()->GetParticleDefinition()->GetParticleName();
  G4double energy = step->GetTrack()->GetKineticEnergy();
  G4double depth = 0.;

  Run* run = static_cast<Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->CountProcesses(process); // Get the number of Process

  if(step->GetTrack()->GetTrackID() > 1 && step->GetTrack()->GetCurrentStepNumber()==1)
  {
    run->ParticleCount(name, energy); // Get the number and energy of particle
  }

//  if(step->GetTrack()->GetCurrentStepNumber()==1 && step->GetTrack()->GetTrackID()>1)
//  {
//     run->ParticleCount(name, energy);
//     if(step->GetTrack()->GetParticleDefinition()->GetPDGEncoding() == 1000280630)
//     {
//     depth = step->GetTrack()->GetPosition().z();
//     analysisManager->FillNtupleDColumn(0, depth);
//     analysisManager->AddNtupleRow();
//     }
//  }

  // energy deposit
  //
//  G4double edepStep = aStep->GetTotalEnergyDeposit();
//  if (edepStep <= 0.) return;
//  fEventAction->AddEdep(edepStep);
}

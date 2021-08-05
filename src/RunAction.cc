#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "Run.hh"

#include "g4root.hh"
#include "G4RunManager.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "StackingAction.hh"

RunAction::RunAction(DetectorConstruction* det, PrimaryGeneratorAction* prim)
: G4UserRunAction(),
  fRun(0), fDetector(det), fPrimary(prim)
{
  //Set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);
  
  //Create analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using" << analysisManager->GetType() << G4endl;

  //Create directories
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);

  //Book histograms, ntuple
  //

  //ntuple
  analysisManager->CreateNtuple("EdepTrackLen", "EdepTrackLen");
  analysisManager->CreateNtupleDColumn("Ehwt");
  analysisManager->CreateNtupleDColumn("Lhwt");
  analysisManager->FinishNtuple();

//  analysisManager->CreateNtuple("pid", "pid");
//  analysisManager->CreateNtupleDColumn("Pid1");
//  analysisManager->FinishNtuple();

  analysisManager->CreateNtuple("neutronEnergy", "neutronEnergy");
  analysisManager->CreateNtupleDColumn("neutronEnergy1");
  analysisManager->CreateNtupleDColumn("neutronfluxx");
  analysisManager->CreateNtupleDColumn("neutronfluxy");
  analysisManager->CreateNtupleDColumn("neutronfluxz");
  analysisManager->FinishNtuple();

//  analysisManager->CreateNtuple("Target", "Target");
//  for(G4int i=1; i<4; i++)
//  {
//  analysisManager->CreateNtupleDColumn("neutronEnergyinshield"+std::to_string(i));
//  analysisManager->CreateNtupleDColumn("neutronfluxxinshield"+std::to_string(i));
//  analysisManager->CreateNtupleDColumn("neutronfluxyinshield"+std::to_string(i));
//  }
//  analysisManager->FinishNtuple();
}

RunAction::~RunAction()
{
  auto particleMap = StackingAction::Instance()->getNumberOfParticlesPerID();

  for(auto particle : particleMap)
  {
     std::cout << "pid: " << particle.first << ", #: " << particle.second << std::endl;
  }

  delete G4AnalysisManager::Instance();
}

G4Run* RunAction::GenerateRun()
{
  fRun = new Run(fDetector);
  return fRun;
}

void RunAction::BeginOfRunAction(const G4Run*)
{ 
  //Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  //Open an output file	
  G4String fileName = "output";
  analysisManager->OpenFile(fileName);  
}

void RunAction::EndOfRunAction(const G4Run*)
{
  if (isMaster) fRun->EndOfRun();

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();
  analysisManager->CloseFile();
}

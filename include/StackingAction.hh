#ifndef StackingAction_h
#define StackingAction_h

#include <G4UserStackingAction.hh>
#include <G4UImessenger.hh>
#include <globals.hh>

#include <map>

class G4Track ;

class StackingAction : public G4UserStackingAction
{
		//singleton stuff
  static StackingAction* instance ;
protected :
  StackingAction() ;
  static void initInstance() { new StackingAction ; }
  virtual ~StackingAction() { instance = nullptr ; }
public :
  static StackingAction* Instance()
  {
    if ( !instance )
    initInstance() ;
    return instance ;
  }

  public :
  virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* track) ;

  void setKillNeutrons( G4bool kill ) { killNeutrons = kill ; }
  void reset() { nParticlesPerId.clear() ; }

  const std::map<G4int , G4int>& getNumberOfParticlesPerID() const { return nParticlesPerId ; }

protected :
  std::map<G4int , G4int> nParticlesPerId = {} ;

  G4bool killNeutrons = false ;
} ;

#endif //StackingAction_h

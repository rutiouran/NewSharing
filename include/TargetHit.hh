#ifndef TargetHit_h
#define TargetHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class TargetHit : public G4VHit
{
  public:
    TargetHit();
    TargetHit(const TargetHit&);
    virtual ~TargetHit();

    // operators
    const TargetHit& operator=(const TargetHit&);
    G4bool operator==(const TargetHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // Set methods
    void SetTrackID(G4int track) {fTrackID = track;};
    void SetTargetNb(G4int target) {fTargetNb = target;};
    void SetKineticEnergy(G4double dkin) {fKin = dkin;};
    void SetPid(G4int pid) {fPid = pid;};
    void SetPosition(G4ThreeVector pos) {fPosition = pos;};

    // Get methods
    G4int GetTrackID() const {return fTrackID;};
    G4int GetTargetNb() const {return fTargetNb;};
    G4double GetKineticEnergy() const {return fKin;};
    G4double GetPid() const {return fPid;};
    G4ThreeVector GetPosition() const {return fPosition;};

  private:
    G4int fTrackID;
    G4int fTargetNb;
    G4double fKin;
    G4double fPid;
    G4ThreeVector fPosition;
};

typedef G4THitsCollection<TargetHit> TargetHitsCollection;

extern G4ThreadLocal G4Allocator<TargetHit>* TargetHitAllocator;

inline void* TargetHit::operator new(size_t)
{
  if(!TargetHitAllocator)
      TargetHitAllocator = new G4Allocator<TargetHit>;
  return (void *) TargetHitAllocator->MallocSingle();
}

inline void TargetHit::operator delete(void *hit)
{
  TargetHitAllocator->FreeSingle((TargetHit*) hit);
}

#endif

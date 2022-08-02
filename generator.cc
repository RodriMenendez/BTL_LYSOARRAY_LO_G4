#include "generator.hh"

MyPrimaryGenerator :: MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1); /*Number of particles*/

    // Add to constructor what we want to use in macro files or modify per event or it will be overwritten 
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName ="geantino";
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);
    
        G4double GenX=(-0.005/2+0.005*G4UniformRand());
        //G4double GenX = 0.;
        G4double GenZ=(-0.005/2+0.005*G4UniformRand());
        //G4double GenZ = 0.;
        G4double GenY=-0.021;
        G4ThreeVector pos(GenX*m,GenY*m,GenZ*m);
        G4ThreeVector mom(0., 0.,0.);
        fParticleGun->SetParticlePosition (pos);
        fParticleGun->SetParticleMomentumDirection (mom);
        //fParticleGun->SetParticleMomentum (511. *keV);
        fParticleGun->SetParticleMomentum (0.*GeV);
        fParticleGun->SetParticleDefinition(particle);
       
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{

    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleDefinition *particle= fParticleGun->GetParticleDefinition();

    // Example for particle definition (not used in this executable)
    
    if (particle == G4Geantino::Geantino())
    {
        // Silicon particle
        G4int Z= 14;
        G4int A= 32;
        G4double charge = 0.*eplus;
        G4double energy = 0.*keV;

        G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(Z,A,energy);

        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(charge);

    }
    
    
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

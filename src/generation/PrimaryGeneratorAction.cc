#include "generation/PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    // Criar um canhão de partículas com 1 partícula por evento
    fParticleGun = new G4ParticleGun(1);

    // Obter a tabela de partículas
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    
    // Escolher o tipo de partícula (geantino)
    G4ParticleDefinition* particle = particleTable->FindParticle("geantino");

    // Configurar o canhão de partículas
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.)); // Disparo para +Z
    fParticleGun->SetParticleEnergy(1.0 * GeV); // Energia de 1 GeV
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -0.4 * m)); // Posição inicial
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    // Gerar um evento primário usando o canhão de partículas
    fParticleGun->GeneratePrimaryVertex(anEvent);
}

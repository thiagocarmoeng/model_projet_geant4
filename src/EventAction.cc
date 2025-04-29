#include "EventAction.hh"

#include "G4Event.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"

#include <iomanip>
#include <filesystem>  // NOVO! Para garantir que diretório existe.

EventAction::EventAction()
{
    // Garante que o diretório existe
    std::filesystem::create_directories("app/output");

    csvFile.open("app/output/output.csv", std::ios::out);
    txtFile.open("app/output/output.txt", std::ios::out);

    if (csvFile.is_open()) {
        csvFile << "EventID,ParticleName,PositionX(mm),PositionY(mm),PositionZ(mm),Energy(MeV)\n";
    }
}

EventAction::~EventAction()
{
    if (csvFile.is_open()) csvFile.close();
    if (txtFile.is_open()) txtFile.close();
}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
    // Nenhuma ação necessária no início
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    if (!event) return;

    G4PrimaryVertex* primaryVertex = event->GetPrimaryVertex();
    if (!primaryVertex) return;

    G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
    if (!primaryParticle) return;

    G4ThreeVector position = primaryVertex->GetPosition();
    G4double energy = primaryParticle->GetKineticEnergy();
    G4int eventID = event->GetEventID();

    G4String particleName = "Unknown";
    if (primaryParticle->GetG4code()) {
        particleName = primaryParticle->GetG4code()->GetParticleName();
    }

    // Salva no CSV
    if (csvFile.is_open()) {
        csvFile << eventID << ","
                << particleName.data() << ","  // <- Melhor usar .data() para compatibilidade
                << position.x() / mm << ","
                << position.y() / mm << ","
                << position.z() / mm << ","
                << energy / MeV << "\n";
    }

    // Salva no TXT
    if (txtFile.is_open()) {
        txtFile << "EventID: " << eventID << "\n"
                << "Particle: " << particleName << "\n"
                << "Position (mm): ("
                << std::fixed << std::setprecision(2)
                << position.x() / mm << ", "
                << position.y() / mm << ", "
                << position.z() / mm << ")\n"
                << "Energy (MeV): "
                << energy / MeV << "\n"
                << "-------------------------------------------\n";
    }
}

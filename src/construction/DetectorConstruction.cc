#include "construction/DetectorConstruction.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction()
{
    // Construtor vazio
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    // Instância do gerenciador de materiais
    G4NistManager* nist = G4NistManager::Instance();

    // -----------------------------
    // 1. Criação do Mundo
    // -----------------------------

    // Material do mundo (ar)
    G4Material* worldMaterial = nist->FindOrBuildMaterial("G4_AIR");

    // Dimensões do mundo (cubo de 1 metro de lado)
    G4double worldSize = 1.0 * m;

    // Sólido do mundo
    G4Box* solidWorld = new G4Box("World",
                                  0.5 * worldSize,
                                  0.5 * worldSize,
                                  0.5 * worldSize);

    // Volume lógico do mundo
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld,
                                                      worldMaterial,
                                                      "World");

    // Volume físico do mundo
    G4VPhysicalVolume* physWorld = new G4PVPlacement(
        nullptr,               // Sem rotação
        G4ThreeVector(),        // Sem translação
        logicWorld,             // Volume lógico
        "World",                // Nome
        nullptr,                // Sem mãe (é o mundo)
        false,                  // Não replicado
        0,                      // Número da cópia
        true                    // Verificar sobreposição
    );

    // 🔥 Deixar o mundo invisível (para enxergar o que tem dentro)
    logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

    // -----------------------------
    // 2. Criação de um Cubo Detector
    // -----------------------------

    // Material do cubo (água)
    G4Material* boxMaterial = nist->FindOrBuildMaterial("G4_WATER");

    // Dimensões do cubo (20 cm de aresta)
    G4double boxSize = 20.0 * cm;

    // Sólido do cubo
    G4Box* solidBox = new G4Box("Box",
                                0.5 * boxSize,
                                0.5 * boxSize,
                                0.5 * boxSize);

    // Volume lógico do cubo
    G4LogicalVolume* logicBox = new G4LogicalVolume(solidBox,
                                                    boxMaterial,
                                                    "Box");

    // Volume físico do cubo, posicionado no centro do mundo
    new G4PVPlacement(
        nullptr,                // Sem rotação
        G4ThreeVector(0, 0, 0),  // No centro do mundo
        logicBox,                // Volume lógico
        "Box",                   // Nome
        logicWorld,              // Volume mãe (o mundo)
        false,                   // Não replicado
        0,                       // Número da cópia
        true                     // Verificar sobreposição
    );

    // 🔥 Definir atributos visuais do cubo
    G4VisAttributes* visBox = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0, 0.3)); // Azul claro
    visBox->SetVisibility(true);
    visBox->SetForceSolid(true); // Aparência sólida
    logicBox->SetVisAttributes(visBox);

    // -----------------------------
    // Retorna o volume físico do mundo
    // -----------------------------

    return physWorld;
}

#include "construction/DetectorConstruction.hh"
#include "generation/PrimaryGeneratorAction.hh"
#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "QGSP_BERT.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "EventAction.hh"


#include <memory>

int main(int argc, char** argv)
{
    // Instancia o RunManager
    auto runManager = std::make_unique<G4RunManager>();

    // Define mandatory initialization classes
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new QGSP_BERT());
    runManager->SetUserAction(new EventAction());
    runManager->SetUserAction(new PrimaryGeneratorAction());
    
    // ⚡ AQUI: Inicializa a geometria ANTES de abrir a interface
    runManager->Initialize();

    // Inicializa o visualizador
    auto visManager = std::make_unique<G4VisExecutive>();
    visManager->Initialize();

    // Obtem o UImanager
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if (argc == 1) {
        // Modo Interativo
        auto ui = std::make_unique<G4UIExecutive>(argc, argv);
        UImanager->ApplyCommand("/control/execute macros/interactive.mac");
        ui->SessionStart();
    } else {
        // Executa macro fornecida como argumento
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);

        // 🔥 Espera interação mesmo depois da execução do macro!
        auto ui = std::make_unique<G4UIExecutive>(argc, argv);
        if (ui->IsGUI()) {
            ui->SessionStart();
        }
    }

    return 0;
}

📦 MeuProjetoGeant4 — Guia Rápido
Este projeto é um exemplo básico de simulação usando o Geant4, focado em visualizar a geometria e registrar eventos de partículas em arquivos .csv e .txt.

🔥 Estrutura do Projeto
makefile
Copiar
Editar
MeuProjetoGeant4/
├── app/
│   ├── main.cc                  # Arquivo principal da aplicação
│   └── output/                  # Pasta de saída dos resultados (gerada em tempo de execução)
│       ├── output.csv           # Resultados da simulação em formato CSV
│       └── output.txt           # Resultados da simulação em formato de texto (TXT)
├── build/                       # Diretório de build gerado automaticamente pelo CMake (não versionado)
├── include/
│   ├── construction/
│   │   └── DetectorConstruction.hh   # Definições da construção da geometria
│   ├── generation/
│   │   └── PrimaryGeneratorAction.hh # Definições da geração primária de partículas
│   └── EventAction.hh                # Definições da ação de eventos
├── macros/
│   └── interactive.mac          # Script de macro para inicialização automática da simulação
├── src/
│   ├── construction/
│   │   └── DetectorConstruction.cc   # Implementação da construção da geometria
│   ├── generation/
│   │   └── PrimaryGeneratorAction.cc # Implementação da geração primária
│   └── EventAction.cc                # Implementação da ação de eventos
├── CMakeLists.txt                # Script de configuração do projeto (compilação via CMake)
└── README.md                     # Documentação e instruções do projeto


🚀 Como Compilar
Abra o terminal e entre na raiz do projeto:
bash
Copiar
Editar
cd MeuProjetoGeant4

Crie e entre na pasta de build/:
bash
Copiar
Editar
mkdir -p build
cd build

Execute o CMake para gerar o projeto:
bash
Copiar
Editar
cmake ..

Compile:
bash
Copiar
Editar
make -j$(nproc)

🧪 Como Executar
Modo Interativo (com interface gráfica):
bash
Copiar
Editar
./MeuProjetoGeant4

Vai carregar automaticamente macros/interactive.mac.

Modo Batch (executar qualquer macro manualmente):
bash
Copiar
Editar
./MeuProjetoGeant4 macros/interactive.mac

Usando o campo Session da interface: Digite:
plaintext
Copiar
Editar
/ control/execute macros/interactive.mac

📊 Onde ficam os resultados?
Após rodar a simulação:
app/output/output.csv → Dados de eventos (formato planilha).

app/output/output.txt → Relatório dos eventos (formato texto legível).

Cada evento salvo contém:

Número do evento (EventID)

Nome da partícula

Posição inicial (x, y, z)

Energia inicial

🎯 Observações Importantes
A geometria é exibida em modo wireframe.

As partículas são lançadas a partir do centro (0,0,0).

10 eventos são gerados automaticamente pelo interactive.mac.

As bibliotecas gráficas (OpenGL + Qt) são usadas para visualização (OGLIQt).

CMake já está preparado para compilar automaticamente todos os arquivos.

❓ Dúvidas rápidas

Problema	                        Solução
Arquivos de saída vazios	        Verifique se os eventos realmente ocorreram (/run/beamOn)
Visualização não abre	            Certifique-se que o Geant4 foi compilado com Qt e OpenGL
"command not found" ao chamar macro	Lembre de usar /control/execute macros/interactive.mac na sessão!

⚡ Rápido de lembrar
Ação                | Comando
Inicializar sistema | /run/initialize
Abrir OpenGL Qt     | /vis/open OGLIQt
Gerar 10 eventos    | /run/beamOn 10
Executar macro      | /control/execute macros/interactive.mac

💬 Dica extra:
Se quiser testar diferentes quantidades de partículas, altere /run/beamOn 10 para /run/beamOn 1000, etc.

📚 Referências Oficiais
Documentação Geant4:
https://geant4.web.cern.ch/

Guia para Usuários do Geant4 (Application Developers Guide):
https://geant4-userdoc.web.cern.ch/UsersGuides/ForApplicationDeveloper/html/

# model_projet_geant4

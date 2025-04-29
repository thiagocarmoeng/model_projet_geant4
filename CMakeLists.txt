cmake_minimum_required(VERSION 3.16)
project(MeuProjetoGeant4)

# Executa o geant4-config para obter as flags
execute_process(
  COMMAND geant4-config --cflags
  OUTPUT_VARIABLE Geant4_CFLAGS
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
  COMMAND geant4-config --libs
  OUTPUT_VARIABLE Geant4_LIBRARIES
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Parsear os cflags para separar includes e flags
separate_arguments(Geant4_CFLAGS_LIST UNIX_COMMAND "${Geant4_CFLAGS}")

# Definir os arquivos fonte
set(SOURCES
  app/main.cc
  src/construction/DetectorConstruction.cc
  src/generation/PrimaryGeneratorAction.cc
  src/EventAction.cc  
)

# Criar o executável
add_executable(${PROJECT_NAME} ${SOURCES})

# Adicionar flags de compilação
target_compile_options(${PROJECT_NAME} PRIVATE ${Geant4_CFLAGS_LIST})

# Adicionar os includes do Geant4
target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_SOURCE_DIR}/include
  ${Geant4_CFLAGS_LIST}
)

# Linkar bibliotecas do Geant4
target_link_libraries(${PROJECT_NAME} PRIVATE ${Geant4_LIBRARIES})

# Definir o padrão C++ usado
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# Mensagem final
message(STATUS "✅ Configuração concluída usando geant4-config para MeuProjetoGeant4")

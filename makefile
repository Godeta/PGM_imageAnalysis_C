# ==========================================
#   Makefile pour le projet, il fait appel à la librairie Unity pour les tests unitaires
#   PGM image analysis - Le programme prend en paramètre une image .pgm et écrit dans un fichier si l'image est conforme.
# ==========================================

#On détecte l'OS qui fait tourner le makefile et on modifie les commandes en fonction
ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # si on est pas dans un terminal bash
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=.exe
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=.out
endif

C_COMPILER=gcc
ifeq ($(shell uname -s), Darwin)
C_COMPILER=clang
endif
# l'emplacement de la librairie Unity pour les tests unitaires
UNITY_ROOT=./lib

# Pour voir précisément les erreurs et avertissements
CFLAGS=-std=c99
CFLAGS += -Wextra
#CFLAGS += -Wno-misleading-indentation

# Fichier de sortie
TARGET_BASE1=all_tests
TARGET1 = $(TARGET_BASE1)$(TARGET_EXTENSION)
TARGET2 = analyser
# les fichiers nécessaires pour réaliser les tests unitaires
SRC_FILES1=\
  $(UNITY_ROOT)/unity.c \
  $(UNITY_ROOT)/unity_fixture.c \
  src/analysePGM.c \
  src/pgmImageProcessing.c \
  test/TestanalysePGM.c \
  test/TestPgmImageProcessing.c \
  test/test_runners/TestanalysePGM_Runner.c \
  test/test_runners/TestPgm_Runner.c \
  test/test_runners/all_tests.c
# les fichiers nécessaires pour compiler le programme
SRC_FILES2=\
  $(UNITY_ROOT)/unity.c \
  $(UNITY_ROOT)/unity_fixture.c \
  src/pgmImageProcessing.c \
  src/mainFile.c \
  src/analysePGM.c \
  
INC_DIRS=-Isrc -I$(UNITY_ROOT)
SYMBOLS=-DUNITY_FIXTURE_NO_EXTRAS

# quand on veut executer le makefile il suffit de faire "make all"
all: clean default

# compile les tests -> les effectue puis compile le programme
default:
	$(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES1) -o $(TARGET1) -lm
	- ./$(TARGET1) -v
	- $(C_COMPILER) $(CFLAGS) $(INC_DIRS) $(SYMBOLS) $(SRC_FILES2) -o $(TARGET2) -lm

# efface les fichiers compilés
clean:
	$(CLEANUP) $(TARGET1) $(TARGET2) truc.pgm resultats.csv

ci: CFLAGS += -Werror
ci: default
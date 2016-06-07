# Air-Hokey
######[EN]
This is a game where 2 players play against each other on a low-friction table. Air hockey requires an air-hockey table, two player-held mallets, and a puck.
######[PL]
Gra zrecznosciowa dla dwóch graczy. Gra przypomina nieco hokej na lodzie. Do gry używany jest specjalny stół, powierzchnia stołu jest pokryta otworami, przez które wydmuchiwane jest powietrze. Powstaje przy tym poduszka powietrzna, na której krążek ślizga się bez kontaktu z podłożem.
______________________________
## How to install: / Proces instalacji:
######[EN]
1. Download repository as .zip or import git project by clone Uri.
2. Download SFML v2.3.2 http://www.sfml-dev.org/files/SFML-2.3.2-windows-vc14-64-bit.zip .
3. Unpack archives.
4. Create new Win32 Console Application project in Visual Studio 2015.
5. Add all source files to created project.
6. Set project build as Debug x64.
7. In VS2015 open "Project > Properties > C++ > General > C++ > General > Additional Include Directories" and add path to SFML2.3.2\include 
8. In VS2015 open "Project > Properties > Linker > General > Additional Library Directories" and path to SFML2.3.2\lib
9. In VS2015 open "Project > Properties > Linker > Input > Additional Dependecies" and paste those values:
sfml-audio-d.lib;sfml-graphics-d.lib;sfml-network-d.lib;sfml-system-d.lib;sfml-window-d.lib;opengl32.lib;winmm.lib;gdi32.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)
10. Add all .dll files form SFML-2.3.2/bin to folder with source files.
11. Compile and run.

######[PL]
1. Pobierz repozytorium lub zimportuj projekt za pomoca clone Uri.
2. Pobierz biblioteki SFML v2.3.2 http://www.sfml-dev.org/files/SFML-2.3.2-windows-vc14-64-bit.zip .
3. Rozpakuj archiwa.
4. Stwórz nowy projekt w Visual Studio 2015 jako Win32 Console Application.
5. Dodaj pliki pliki źródłowe do utworzonego projektu.
6. Ustaw budowanie projketu jako Debug x64.
7. W VS2015 otwórz "Project > Properties > C++ > General > C++ > General > Additional Include Directories" dodaj scieżkę do SFML2.3.2\include 
8. W VS2015 otwórz "Project > Properties > Linker > General > Additional Library Directories" dodaj scieżkę do SFML2.3.2\lib
9. W VS2015 otwórz "Project > Properties > Linker > Input > Additional Dependecies" wklej następujące wartości:
sfml-audio-d.lib;sfml-graphics-d.lib;sfml-network-d.lib;sfml-system-d.lib;sfml-window-d.lib;opengl32.lib;winmm.lib;gdi32.lib;kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)
10. Dodaj wszystkie pliki .dll z folderu SFML-2.3.2/bin do folderu z plikami zródlowymi.
11. Skompiluj i uruchom projekt.

Alternatywne uruchomienie projektu można wykonać przy użyciu pliku Air-Hokey.exe w folderze /Air-Hokey. Plik .exe należy uruchamiać w tej lokalizacji, z racji tego, iż biblioteki są załączane w sposób dynamiczny.
______________________________
##Diagramy / Diagrams:
######[EN]
In folder *\Air-Hokey-master\Air-Hokey\Diagram:
- Diagram class
- Use case diagram
- Activity diagram

######[PL]
W folderze *\Air-Hokey-master\Air-Hokey\Diagram:
- Diagram klas
- Diagram przypadków użycia
- Diagram aktywności

______________________________
##Autorzy / Authors:
- Marcin Witek,
- Maciej Kulikiewicz,
- Seweryn Dudek,
- Bartłomiej Gacek



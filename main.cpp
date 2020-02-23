// Anführungsverzeichnis bedeutet, dass die hpp-Datei dort im lokalen
// Verzeichnis gespeichert ist
#include <application.hpp>

int main() {
  application gamesnake{};
  gamesnake.execute();
}

// // TODO
// - Farben als Vektoren speichern,
//     gewichtete Beimischung - raus - und reinkommen besser machen
//  -rand verbessern
// - verhindern, dass Grau verwendet wird bei Schlange oder Futter

// Anführungsverzeichnis bedeutet, dass die hpp-Datei dort im lokalen
// Verzeichnis gespeichert ist
#include <application.hpp>

int main() {
  application gamesnake{};
  gamesnake.execute();
}

// // TODO
// - verhindern, dass Grau verwendet wird bei Schlange oder Futter
// - was in welche Datei kommt, bzw. Dateien weiter aufsplitten
// was machen, wenn sich Schlange selbst beißt?

// FRAGEN AN MARKUS:
// - wie besser aufsplitten
// - wie kann man das Problem mit dem vektorlänge-anhängen besser lösen als mein
// workaround?
// - wie kann man das besser machen, dass die Schlange sofort länger wird (und
// das mit dem sich-selbst-fressen entsprechend besser funktioniert)
// - was bedeutet manchmal das Kaufmanns-Und vor den Variablennamen?

// - die Schlange soll erst einmal komplett über das Essen drüber laufen, bevor
// es angehängt wird
// - es soll immer nur das erste und das letzte Glied der Schlange geändert
// werden

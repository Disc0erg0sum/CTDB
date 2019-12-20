# CT DrawBot

![Alternativer Text](pix/IMG_1128.jpg)

> Seminar "Creative Technologists - Tracing the City" @ [University of Applied Sciences Potsdam](https://github.com/FH-Potsdam/) (Germany) winter semester 2019/2020 by [Fabian Morón Zirfas](https://fabianmoronzirfas.me)

## Assignment

Bau mit einen Arduinbo, der über [Johnny-Five](http://johnny-five.io/) an gesteuert wird.

## Usage

1. Install Node.js (Prefer LTS!).
2. [Setup your board.](http://johnny-five.io/platform-support/)
3. Get Johnny-Five: npm install johnny-five \*
4. Run your program! node index.js

## Überlegungen

### 1 Überlegung

Meine erste Überlegung für einen Zeichenroboter ist der Klassische X/Y Tisch wie bei einer CNC Desktop Fräse. Die schnellste Variante, ein null Budget X/Y-Tisch zubauen, ist meiner Meinung nach zwei alte CD Laufwerke um zu funktionieren. Leider besitze weder ich noch Leute in meinem bekannten Kreis zurzeit alte CD/DVD-Laufwerke. Weiterhin findet man Schrittmotoren und einfache Lineareinheiten in Druckern. Auf die Nachfrage in meinem Freundeskreis nach alten Druckern wurde mir ein Mimaki CG-121 angeboten. Dies ist ein größer Vinyl-Schneide-Plotter. Bei genaueren nach fragen, warum sie diesen Plotter abgeben wollen kommt heraus das es für diesen einfach keinen Aktuellen Treiber mehr gibt, er mechanisch und elektrisch noch voll Funktion tüchtig ist. Jetzt könnte ich natürlich diesen voll funktionstüchtigen Plotter schlachten, um ein eigenen Plotter daraus zu Konstoiren. Ober einfach die ganze Konstuktion belassen wie sie ist und einfach die Steuer elektronik austauschen.

### 2 Überlegung

Wenn ich jetzt schon einen fast funktionierenden Schneidplotter habe, kann ich die verbauten Schrittmotoren mit einem Arduino wie [Johnny-Five](http://johnny-five.io/) ansteuern. Was aus meiner Sicht wenig Sinn ergibt, vor dem hinter Grund dieses gerät wieder seiner ursprünglichen Funktion zuzuführen. Ein praktischer Ansatz ist es die Motoren über einen GCode Interpreter anzusteuern.
Und sich ein Arbeitsablauf für die Erzeugung des GCodes zu überlegen.

## Recherche

### Treiber für die Schrittmotoren

Nach einigen recherchieren bin ich zum Entschluss gekommen, Treiber der Firma
[TRINAMIC](https://www.trinamic.com/products/drives/) zu verwenden. Ganz Konkret habe ich erst mal den TMC2208 bestellt. Dieser ist recht günstig, müsste von den Werten funktionieren und ist wohl sehr leise.

### GCode Interpreter

GCode Interpreter gibt es viel von Kommerziell mit spezieller Hardware bis zu Unkommerziell und Open Source.
Da sich dies Projekt um ein No Budget Projekt handelt und wir einen Arduino benutzen habe ich mich für [grbl](https://github.com/grbl/grbl) entschieden.

### GCode erzeugen

GCode lässt sich aus Vektorgrafiken erzeugen. Ein kostenloses Open Source Vektorgrafikprogramm ist [Inkscape](https://inkscape.org/), für das es Erweiterungen gibt, mit denen man GCode generieren kann.

### Übertragung des GCode

Zum Schluss muss noch der generierte GCode zu dem Plotter übertragen werden. Da für gibt es ein liste von Tools auf der [grbl-Wiki](https://github.com/grbl/grbl/wiki/Using-Grbl) Seite.

## Versuche

### Stepper mit Johnny ansteuern

Um zuschauen wie man einen Schrittmotor ansteuern kann, nehmen wir einen einfachen kleinen 28BYJ-48 und ein ULN2003 als Treiber. Beide Bauteile eignen sich gut für Erste versuche, da sie in vielen Arduino-Kit’s enthalten, sie sind relativ preisgünstig, beide Bauteile können mit einer Spannung von 5V betrieben werden.

Um mit [Johnny-Five](http://johnny-five.io/) einen Stepper zu betreiben, muss auf den Arduino die [AdvancedFirmata](https://github.com/soundanalogous/AdvancedFirmata) gespielt werden.

#### 28BYJ-48

- 5V
- 330 mA
- 4 Phasen
- Unipolar
- 32 steps
- Der Motor hat ein eingebautes Getriebe, damit entsprechen 32 stepps nicht einer vollen Umdrehung der Gehäusespindel.

#### Probleme

**1.**
Die Drehrichtung des Stepper lässt sich nicht ändern.
_**Lösung:** Die Polung des Steppers tauschen._

**2.**
Ich kann nicht beide Stepper gleichzeitig ansteuern, einzeln kann ich sie ansteuern. Die Hardware ist nicht das Problem.

So kann ich beide gleich zeitig bewegen.

        stepperX.step(2000, () => {
          console.log("x bewegt");
          stepperX.cw().step(2000);
          stepperY.cw().step(2000);
          console.log("beide gleichzeig bewegt");
        });

So nicht.

        stepperX.cw().step(2000);
        stepperY.cw().step(2000);
        console.log("beide gleichzeig bewegt");

So auch nicht

        const move = () => {
          console.log("bewegen");
          stepperX.step(2000);
          stepperY.step(2000);
        };

        move();

#### Ergebnis

Johnny Five ist ein Interesantes konzept aber auf grund zuwenig Code Beispielen, in der kürze der Zeit für mich nicht Praktikabel.
Aus diesem Grund habe ich mich endschlossen in C++ mit dem Arduino Framework witer zu arbeiten. Mit der Syntaks habe ich einfach mehr erfahrung.

### Eine einfache X/Y steuerung für zwei Stepper schreiben.

Da mir die Arduino eigne IDE nicht gefällt habe ich mich entschlossen PlatformIO zu nutzen.

[**Projekt Ordner**] (./Arduino)


## Author(s)

**Jendrik Bradaczek**

- [github/](https://github.com/dISCOeRG0sUM)

## License

Copyright © 2019 Jendrik Bradaczek
Licensed under the MIT license.

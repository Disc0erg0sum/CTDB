/*
# Stepper ansteruerungs test ein

in diesem script wir getestet wie ich ein Schritmotor (28BYJ-48) mit einen Treiber (ULN2003)
in Johnny-Five ansteuern kann.

## Author
Jendrik Bradaczek

## License
Copyright © 2019 Jendrik Bradaczek
Licensed under the MIT license.

# Problem beschreibung
Jeder Stepper für sich funktioniert. Beie Stepper zu sammen gehen nicht.

*/

const { Board, Led, Stepper } = require("johnny-five"); // laden des node-Moduls
const board = new Board();
const CCW = 0; // Stepper Diration
const CW = 1; // Stepper Diration

let testLed = undefined;
let stepperX = undefined;
let stepperY = undefined;

// bordkomunikation Starten
board.on("ready", function() {
  testLed = new Led(13);
  testLed.blink(200);

  // Stepper erzeugen
  stepperX = new Stepper({
    type: Stepper.TYPE.FOUR_WIRE,
    stepsPerRev: 180,
    pins: {
      motor1: 9, // IN4
      motor2: 10, // IN2
      motor3: 11, // IN3
      motor4: 12 // IN1
    }
  });

  stepperY = new Stepper({
    type: Stepper.TYPE.FOUR_WIRE,
    stepsPerRev: 200,
    pins: {
      motor1: 5, // IN4
      motor2: 6, // IN2
      motor3: 7, // IN3
      motor4: 8 // IN1
    }
  });

  // set stepp[er to 180 rpm, CCW, with acceleration and deceleration
  stepperX
    .rpm(180)
    .direction(CCW)
    .accel(1600)
    .decel(1600);

  stepperY
    .rpm(180)
    .direction(CCW)
    .accel(1600)
    .decel(1600);

  // wenn so kann ich beide gleich zeitig bewegen.
  stepperX.step(2000, () => {
    console.log("x bewegt");
    stepperX.cw().step(2000);
    stepperY.cw().step(2000);
    console.log("beide gleichzeig bewegt");
  });

  //   // so get es nicht

  //   stepperX.cw().step(2000);
  //   stepperY.cw().step(2000);
  //   console.log("beide gleichzeig bewegt");

  //   // so auch nicht

  //   const move = () => {
  //     console.log("bewegen");
  //     stepperX.step(2000);
  //     stepperY.step(2000);
  //   };

  //   move();
});

/*
# Stepper ansteruerungs test ein

in diesem script wir getestet wie ich ein Schritmotor (28BYJ-48) mit einen Treiber (ULN2003)
in Johnny-Five ansteuern kann.

## Author
Jendrik Bradaczek

## License
Copyright © 2019 Jendrik Bradaczek
Licensed under the MIT license.

*/

const { Board, Led, Stepper } = require("johnny-five"); // laden des node-Moduls
const board = new Board();
const CCW = 0; // Stepper Diration
const CW = 1; // Stepper Diration

let testLed = undefined;
let stepper = undefined;

// bordkomunikation Starten
board.on("ready", function() {
  testLed = new Led(13);
  testLed.blink(200);

  // Stepper erzeugen
  const stepper = new Stepper({
    type: Stepper.TYPE.FOUR_WIRE,
    stepsPerRev: 32,
    pins: {
      motor1: 9,
      motor2: 10,
      motor3: 11,
      motor4: 12
    }
  });

  // set stepp[er to 180 rpm, CCW, with acceleration and deceleration
  stepper
    .rpm(180)
    .direction(CCW)
    .accel(1600)
    .decel(1600);

  // make 10 full revolutions
  stepper.step(2000, () => {
    console.log("done moving CCW");

    // once first movement is done, make 10 revolutions clockwise at previously
    //      defined speed, accel, and decel by passing an object into stepper.step
    stepper.step(
      {
        steps: 2000,
        direction: CW
      },
      () => console.log("done moving CW")
    );
  });
});

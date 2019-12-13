const j5 = require("johnny-five"); //lade die node-modul johnny-five (lade ein lib)
const bord = new j5.Board();
let led = undefined;

// das ist die funktion der alle board komunikation statfindet
bord.on("ready", function() {
  led = new j5.Led(13);
  //led.blink(50);

  let servo1 = new j5.Servo({
    pin: 9,
    range: [10, 180],
    startAt: 90
  });

  let servo2 = new j5.Servo(10);

  //servo1.sweep();
  //servo2.sweep();

  // Servo API

  // min()
  //
  // set the servo to the minimum degrees
  // defaults to 0
  //
  // eg. servo.min();

  // max()
  //
  // set the servo to the maximum degrees
  // defaults to 180
  //
  // eg. servo.max();

  // center()
  //
  // centers the servo to 90°
  //
  // servo.center();

  // to( deg )
  //
  // Moves the servo to position by degrees
  //
  // servo.to( 90 );

  // step( deg )
  //
  // step all servos by deg
  //
  // eg. array.step( -20 );

  this.repl.inject({
    //repl ist super um live die funktionen im terminal zu testen
    servo1,
    Servo2
  });
});

const j5 = require("johnny-five"); //lade die node-modul johnny-five (lade ein lib)
const bord = new j5.Board();
let led = undefined;

// das ist die funktion der alle board komunikation statfindet
bord.on("ready", function() {
  led = new j5.Led(13);
  led.blink(50);
  let servo = new j5.Servo(9);

  this.repl.inject({
    //repl ist super um live die funktionen im terminal zu testen
    servo
  });
});

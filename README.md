# AngryPigsCode

Angry Piggies — a small Matter.js physics game: slingshot a pig at wooden,
stone and glass towers to knock out the birds.

## Play

Open `index.html` in a browser (or serve the folder, e.g.
`python3 -m http.server`). Drag the pig back from the slingshot and release
to launch.

**Click while the pig is flying to dash** — one boost per pig.

There are 8 levels, each harder than the last; clearing one unlocks the next.
Every level is rated 1–3 stars: you get a star for clearing it plus one per
spare pig, so one-shotting a 3-pig level earns all three. Breaking blocks
and knocking out birds scores points, and spare pigs are worth 10,000 each.
Stars and best scores are saved in the browser.

- `Enter` presses the end-card's main button, `R` restarts the current level,
  `Esc` (or the **Levels** button) opens the level select.
- Jump to a level with the URL hash, e.g. `index.html#5`.

## Arduino joystick

You can play with a joystick module plugged into an Arduino. The sketch is written for an Uno, but any board with two analog pins works.

1. **Wire it** (5-pin KY-023 / PS2-style module):

   | Joystick | Arduino |
   |----------|---------|
   | GND      | GND     |
   | +5V      | 5V      |
   | VRx      | A0      |
   | VRy      | A2      |
   | SW       | D2      |

   Optionally, add a push button on pin D3 (with a resistor) as a second fire
   button. If it reads as always pressed, change `BUTTON_PRESSED` to `LOW` in the sketch.

2. **Upload the sketch:** open `arduino/joystick/joystick.ino` in the Arduino IDE,
   pick your board and port, and click Upload. Don't touch the stick while the
   board starts up, because the sketch reads the centre position then.
3. **Check the directions:** open Tools → Serial Monitor at 115200 baud. Pushing
   the stick right should make the first number positive, and pushing it down
   (toward you) should make the second number positive. If either is backwards,
   flip `INVERT_X` / `INVERT_Y` in the sketch and upload again. Pressing the
   stick should make the third number `1`.
4. **Close the Serial Monitor.** Only one app can use the port at a time.
5. **Open the game in Chrome or Edge** (Safari and Firefox don't support Web
   Serial). Run `python3 -m http.server` in this folder and go to
   <http://localhost:8000>. Click **🕹 Connect joystick** and pick the Arduino's port.

Controls: tilt the stick to pull the pig back (the further you tilt, the harder
the shot), press the stick to fire, and press again mid-flight to dash. On an
end card, pressing the stick presses the main button (Next level / Retry).

## Difficulty

- **Blocks:** glass breaks in 1 hit, wood in 2, stone in 3 (and stone is
  heavier, so it crushes what it falls on).
- **Birds:** red ones fall over easily, yellow ones need a falling block or a
  pig, blue ones need a solid pig hit or heavy stone. Stars mean you dazed a
  bird but didn't knock it out.
- Later levels shorten the aim preview, and the last level has none.

Levels live in the `LEVELS` array in `game.js`.

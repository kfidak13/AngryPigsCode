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

## Difficulty

- **Blocks:** glass breaks in 1 hit, wood in 2, stone in 3 (and stone is
  heavier, so it crushes what it falls on).
- **Birds:** red ones fall over easily, yellow ones need a falling block or a
  pig, blue ones need a solid pig hit or heavy stone. Stars mean you dazed a
  bird but didn't knock it out.
- Later levels shorten the aim preview, and the last level has none.

Levels live in the `LEVELS` array in `game.js`.

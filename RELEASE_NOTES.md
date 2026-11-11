# GRM Guitar 0.3.0

![GRM Guitar 0.3.0: two guitars, the second one with the first one's notes faint behind it](docs/screenshot.png)

The biggest release so far. The sound now follows measured guitars, the notes ring as long as the hands let them,
up to eight guitars live in one plugin, and the roll writes chords, patterns and harmonies.

The engine is the one of [grm-core](https://github.com/innermost47/grm-core), also available as a Python package:
[pygrm](https://pypi.org/project/pygrm/) (`pip install pygrm`).

## Sound

- **Strings lose their energy as measured strings do** (Woodhouse 2012): inside the string, in the air, in the
  bending steel, as a GRM network per string. The low partials ring longest and the high ones go first. The old
  hand-made curve, and its "Resonance (s)" setting, are gone.
- **String age**: from new strings to played ones (played strings lose their highs sooner).
- **A body that no longer sounds like a banjo.** The top now carries its braces and bridge (about 200 g), and its
  modes have the measured Q (about 50). The fundamentals that died in about 1 s now ring 2.5 to 3 times longer.
  New sliders: **Braces (g)** and **Body resonance (Q)**.
- **Wood**: 8 species with their density and stiffness (Wood Handbook), plus **Wood density** around the
  species' average.
- **Body: solid (0) to hollow (1)**: from a flat-top acoustic to a solid body.
- **Sensor** (new tab):
  - **microphone**: body and room, as before;
  - **magnetic pickup**: the string's velocity at the pickup, through the coil, cable and pot as a GRM network.
    Two measured pickups (a 1970s single coil, a hotter one), with sliders for the position and the cable;
  - **piezo** under the saddle.
- **Palm mute that acts progressively.** Its pressure no longer flips from nothing to everything near 0.05: the
  strings it lands on get the palm network's own damping, and the pressure steps are three times finer.
- **Looseness**: how far the player strays from the grid.

## The notes ring as long as the hands let them

- **Ringing by default.** An open string rings until it is played again. A fretted note rings until its string is
  played again or until the left hand needs that finger elsewhere. This holds for strums, in loops and at the loop
  point. The roll draws it as a fading trail.
- **Endings per note** (right click): let it ring, stop at its end, or mute with the hand (which stops the
  strings beside it too).
- **Hand stops**: Alt+click anywhere on the grid, on a step or between two, stops every string there.
- **When another pattern takes over**, the notes of the one before end as they were written.
- **Chords at the very start** of a song keep their pick sweep (they used to land all at once).

## Writing

- **Every chord**: 12 roots with their sharp and flat names, 16 kinds, power chords included. The left-hand
  network chooses each shape for the guitar's tuning; all 192 chords are checked playable on all 6 tunings.
- **Fill strums / arpeggio** work over the selection, at any length, and keep the chords already written (the
  pattern only adds the rhythm).
- **Notes over several strings**: drag a note's top or bottom edge, then give each note its own fret. Useful for
  barres and chord shapes on the grid.
- **Dead notes** (X), resizing from the left, transposing (+/−).
- **Harmonize** in the pattern's new **key and scale** (10 scales): the new note goes where the hand can play it.
- **Greyed places**: where the hand cannot reach with the fret being written.
- **Strumming and picking a note at the same moment** is refused (one hand).
- **Hear the note just written** (Playback tab, on by default).
- **Writing past the end** no longer changes the length or the loop. **Loop flags** in the ruler; pulling the end
  flag past the end lengthens the song.
- **Follow playhead** can be turned off.

## Patterns

- **Up to 24 patterns per guitar.**
- **MIDI keys**:
  - **Play notes**, as before;
  - **Play patterns**: C1 plays pattern 1, C#1 pattern 2… Each pattern plays its loop while its key is held, on
    every guitar that has it (a scene), or per guitar with "MIDI to guitars: Channel = guitar".
- **The host's Stop** stops the patterns held by keys.

## Several guitars

- **Up to 8 guitars in one plugin**, each with its own settings (all automatable), patterns and player.
- **Mixer**: gain, level, pan, mute, solo. Each guitar goes to the main output or to its own (enable
  "Guitar 1" to "Guitar 8" in the host, then put each guitar's effects in the host).
- **The other guitars appear faint behind the roll**, with their note names and their chords where they change. A
  shorter pattern repeats under a longer one, where it really plays.
- **Copy to guitar** (right click) and **Copy / Paste** of whole patterns.
- **The header** shows the position in the pattern and in the whole song.
- **Export WAV** mixes every guitar.

## Performance

- **Guitars in the same room share one room** (the heaviest part of the sound).
- **Lighter real-time loops.** Four guitars went from about 23 % to about 14 % of each audio block on the build
  machine.
- **The plugin no longer lets a host put it to sleep** when it gets no input.
- **A value that is not a number** can no longer silence a guitar for good.

## Compatibility

- **Sessions of 0.2.0 open as they were** (guitar 1 keeps every parameter id).
- **The plugin's codes are unchanged**, so hosts find it in existing projects. The vendor name is now
  **InnerMost47**.
- **The Python app of grm-core was the proof of concept;** this plugin is the product. It is no longer kept in step
  with it: one string's sound is still checked against the proof of concept's old loss curve, while the plugin now
  uses the measured losses.

## Tests

- **`test_core`**: 210 checks.
- **`test_physics`**: 153 checks.
- **`test_play`**: 52 checks.
- **`plugin_host_test`**: 18 checks.
- **New tools:** `plugin_cpu_test` and `editor_snapshot`.

## Known limits

- **The body has seven modes below about 1.4 kHz**: moving its settings changes the "vowel" more than a real
  guitar would.
- **Some chord shapes chosen by the hand are unusual** (still playable).
- **The magnetic pickup listens at one point.**
- **The low E fundamental on a solid body may ring shorter** than measured on electric guitars.
- **Slides, hammer-ons, pull-offs and bends** come next.

---

# GRM Guitar 0.2.0

![GRM Guitar, standalone, with the demo roll](docs/screenshot.png)

This release is about the player. The strings, body and room are the same as before. What changed is how
the guitar is played: two hands, ten fingers, a pick and a tired arm, all of them GRM networks.

## The hands are constraints

- **The left hand has four fingers.** The thumb can take the low E, a barre counts as one finger, and one
  finger can hold neighbouring strings at the same fret.
- **The stretch is a GRM network.** Each fingertip sits behind its fret, the hand pulls towards its natural
  spread, and the tension left in the network is the strain of the hand. Frets get closer up the neck, so more
  of them fit there. Fret 3 with fret 7 is hard but possible; fret 3 with fret 8 is not.
- **A pick cannot jump a string.** It cannot strike two strings without the ones between. With the fingers,
  at most five strings at once.
- **The roll refuses what no guitarist can play.** An edit that adds an impossible moment is undone and the roll
  says why ("Not playable at bar 3: left hand: stretch from fret 3 to fret 8 is too wide here"). Moments that are
  already impossible (an older song, or after switching from fingers to pick) get a red mark on the ruler.
- **Every built-in chord shape passes the check.**

## The right hand

- **Sweep.** Each string the pick pushes aside takes some of the hand's energy, so the pick slows and the
  later strings of a chord get a little less. A slow, soft strum fades across the chord; a fast one hardly does.
- **Alternate picking.** Single notes are picked down on the sixteenths of the beat and up between. Notes struck
  together with a pick are one sweep, in the arm's direction.
- **Pinch.** With the fingers, notes struck together are a pinch: the thumb comes slightly first, and each
  finger has its own force.
- **Muscle.** Every stroke costs an effort, and the arm recovers from it in about two seconds. A long run of
  sixteenths ends a little softer and slower; a stroke after a rest comes out fresh (about ±6 %).

## The palm

- **The palm is one hand, not a switch per string.** It covers the strings asked and presses half as hard on
  their neighbours. It presses harder on a harder stroke, and when it lands it stops the strings ringing under it.
  A string across the neck keeps ringing.
- **"Palm pressure" at 0 lifts the palm.** Palm-muted notes then ring free, and no palm network is solved.
- **"Palm mute (live)" mutes the roll too.** What rings is damped as the palm lands.

## How notes end

- **A fretted note stops as the finger relaxes.** An open string dies more slowly, because a hand has to
  touch it.
- **A chord is released one string after the other**, a few milliseconds apart.
- **A damped note darkens as it dies.** The high modes go first.
- **The fingers move as late as they can before a new shape**, so the notes ring until then.
- **Loops.** In a loop, the end of the roll leads into its start: the fingers change shape for the first notes
  at the end, and nothing is cut at the loop point.

## Level

- **Strong plucks no longer saturate.** The soft clipper is replaced by a peak limiter that only acts near full
  scale and recovers in 150 ms. Strong plucks (high "Force") used to drive the output into distortion; they
  now stay clean.
- **"Volume" goes from 0 to 2** (default 1).

## Editing the roll

- Multiple selection: Ctrl+click, selection rectangle (Ctrl or Shift+drag on an empty place), Ctrl+A.
- Copy, cut, paste, duplicate (Ctrl+C / X / V / D, and in the right-click menu); paste goes where you last
  clicked, and works between two instances of the plugin. Ctrl+drag a note or strum to copy it.
- Every selected object moves, resizes and changes together (drag, arrows, Shift+arrows by a bar or a string,
  wheel, digits, P for palm mute, Del).

## Fixes

- Crash when changing the arm swing (or any player setting, or a new take) while a finger noise was sounding:
  the engine kept playing a sample of the performance being replaced.

## Tests

- **New `test_play`:** 23 behaviour checks (hands, sweep, pinch, muscle, alternate picking, palm band, loop,
  note endings, live palm).
- **`test_core` (210) and `test_physics` (137)** still match the Python golden numbers. The base player and
  strum networks are unchanged.

## Known limits

- **A click at the loop point was reported but could not be reproduced offline.** If it is still heard, please
  say whether it happens in the standalone or in a host (and which one).
- **Slides, hammer-ons and pull-offs are not techniques of the roll yet.** They are planned for the next
  release, with the slide squeak on wound strings.

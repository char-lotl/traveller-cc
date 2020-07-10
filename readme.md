# Traveller Character Creator

`traveller-cc` is a command-line tool for streamlining and automating character creation in the tabletop RPG *Traveller* (Mongoose Publishing), by Gareth Hanrahan.

It is primarily aimed at distilling the process of character creation down to the choices made during that process, as well as lending more clarity to the process by automating away the parts most subject to human error. Character creation in *Traveller* is a fun and interesting process, a minigame all its own -- one best experienced without spending most of one's time flipping through tables and performing bookkeeping.

As a secondary goal, we intend to allow fully randomized, non-interactive character generation through the tool, for expedited but authentic NPC generation, as a GM tool.

## Installation

Just download the repository and use GNU `make`.

If GNU `make` is not available on your platform, your life just got a lot harder, but what you'll have to do boils down to compiling all the .cpp files into a single executable. It sure would be convenient if I provided a list of all those .cpp files, huh? Sorry, you're out of luck for now.

## Usage

If you're on a Unix-like OS, once you've built `traveller-cc`, just execute it with `./traveller-cc` from the terminal. No arguments or flags. Preferences are configurable in `pref.cfg`. Read the comments in that file for a full explanation of the role of each variable.

If you're not on a Unix-like, you presumably still generated an executable during the build process you came up with. Run it from the command line.

## Contributing

Pull requests are welcome, but I can't guarantee you I'll do anything with them. Contact me by email at `lancharlotl@gmail.com` to discuss changes.

## License

TBD. All rights reserved for now.


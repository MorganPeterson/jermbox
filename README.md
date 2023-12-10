# NOTICE

__I am moving this repository to [Sourcehut](https://git.sr.ht/~nullevoid/jermbox). That means that this repository will be archived and any future development (if any) will be done there.__

# Jermbox

A Janet native module for working with a [forked version](https://github.com/MorganPeterson/termbox_next) of nullgemm's [Termbox Next](https://github.com/nullgemm/termbox_next).

This module allows for easy buidng of terminal UIs.

## OS Requirements

This module is build and tested on Arch Linux. I can only guarantee that this will work on most linux systems.

I don't have the means to test this on any other environment than Linux. If you would like to see it work on your OS of choice then feel free to put in a PR or fork from this repo.

## Install Package

```sh
sudo jpm install https://github.com/MorganPeterson/jermbox
```

## Examples

Example usage can be found in the examples and test directory.

## Ackowledgement

This borrows heavily from sepisoad's code: [jtbox](https://github.com/sepisoad/jtbox). Their code, though, works with the original [termbox](https://github.com/nsf/termbox) which was abandoned by the author and refactored for some unknown reason.

There are a lot more additions to my module then what sepisoad had done. Hopefully, for the better.

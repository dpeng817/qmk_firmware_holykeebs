This is my fork of holykeebs' fork of the main qmk repo. In here, you'll find the settings I used to get my corne with dual trackballs configured correctly.

I found the pimoroni trackball a bit difficult to use out of the box, and thus used some custom qmk settings to get things working. However, there isn't much available about dual trackball setups.

The settings for the corne are under `keyboards/crkbd/rev1/keymaps/dpng`.

To actually flash the board:
1. Plug in right side and run `make crkbd/rev1:dpng:flash -e SIDE=right POINTING_DEVICE_POSITION=thumb_outer -j8` from the repo root.
2. Plug in left side and run `make crkbd/rev1:dpng:flash -e SIDE=left POINTING_DEVICE_POSITION=left -j8` from the repo root.
3. Plug back in the right side, and things should be working.

Note; wasn't able to get the LED switching behavior working, might return to that at a later date, but a caveat for anyone who might want to use this.

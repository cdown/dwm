This is dwm with a number of improvements, many of which have been contributed
upstream. There are a non-trivial amount of changes/refactors to core dwm code,
but I do keep the changes in sync with upstream (see the
[`sync`](https://github.com/cdown/dwm/blob/master/sync) script).

A lot of the code is unused (eg. I don't use the bar, window titles, etc.) but
in order to minimise merge conflicts, the dead code is left alone, and we just
rely on compiler code elimination to do dead code removal.

# Patches

## Written by me

- alwaysfullscreen ([merged into dwm itself](https://git.suckless.org/dwm/commit/67d76bdc68102df976177de351f65329d8683064.html))
- barperf ([merged into dwm itself](https://git.suckless.org/dwm/commit/8657affa2a61e85ca8df76b62e43cb02897d1d80.html))
- const-correctness fixes (not upstreamed)
- destroyfocus ([patch](https://dwm.suckless.org/patches/destroyfocus/))
- killunsel ([patch](https://dwm.suckless.org/patches/killunsel/))
- layoutmonitorrules ([patch](https://dwm.suckless.org/patches/layoutmonitorrules/))
- noborderflicker ([patch](https://dwm.suckless.org/patches/noborderflicker/))
- ruleperiod (not upstreamed)
- resetlayout ([patch](https://dwm.suckless.org/patches/resetlayout/))
- tagallmon (not upstreamed)
- warp v2 (not upstreamed)

## By others

- bottomstack
- column
- gaplessgrid
- keypressrelease
- movestack
- noborder (floating fix)
- pertag
- zoomswap (with some modifications around focus behaviour)

# Screenshot

It looks something like this when used along with [my
dotfiles](https://github.com/cdown/dotfiles) and [ansible
playbook](https://github.com/cdown/ansible-desktop):

![Screenshot](https://raw.githubusercontent.com/cdown/dwm/master/screenshot.png)

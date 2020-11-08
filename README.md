This is my personal fork of dwm. There are a non-trivial amount of
changes/refactors to core dwm code, but I do keep the changes in sync with
upstream (see the [`sync`](https://github.com/cdown/dwm/blob/master/sync)
script).

A lot of the code is unused (eg. I don't use the bar, window titles, etc.) but
in order to minimise merge conflicts, the dead code is left alone, and we just
rely on compiler constant folding to do dead code removal.

# Patches

## Written by me

- alwaysfullscreen (upstreamed)
- killunsel (upstreamed)
- layoutconfigrules (not upstreamed, can be sent once untangled from pertag/resetlayout)
- resetlayout (upstreamed)
- tagallmon (not upstreamed)
- warp v2 (not upstreamed)
- const-correctness fixes (sent upstream, but Hiltjo said he doesn't mind about const-correctness)

## By others

- bottomstack
- keypressrelease
- gaplessgrid
- pertag
- push_no_master
- zoomswap (with some modifications around focus behaviour)

# Screenshot

It looks something like this when used along with [my
dotfiles](https://github.com/cdown/dotfiles) and [ansible
playbook](https://github.com/cdown/ansible-desktop):

![Screenshot](https://raw.githubusercontent.com/cdown/dwm/master/screenshot.png)

WM
==

Still need a name. And a catchphrase.

Features
--------

None yet.

Building
--------

You will need the following:

- Wayland
- [swc][0] (also on the [AUR][a0])
  - [wld][1] (also on the [AUR][a1])
  - libdrm
  - libevdev
  - libxkbcommon
  - libinput
  - libudev
  - xlib (for parsing keys)
  - libxcb (for XWayland)
  - xcb-util-wm (for XWayland)
  - pixman
  - Linux >= 3.12

  [0]: https://github.com/michaelforney/swc
  [1]: https://github.com/michaelforney/wld
  [a0]: https://aur.archlinux.org/packages/swc-git/
  [a1]: https://aur.archlinux.org/packages/wld-git/

After building and installing swc, run

```
make clean && make
```

to build wm.

Usage
-----

None yet.

Todo
----

- [x] Bind the swc stuff
- [x] Produce a working Wayland display that can handle windows
- [x] Parse keybinds and commands from a config file
  - [x] Window movement
  - [x] Window warping
  - [x] Spawning
  - [x] Focus changing
  - [x] Resizing
  - [ ] Grouping stuff
  - [ ] Monitor stuff
  - [x] Reloading settings
  - [x] Quitting
  - [ ] Custom modifiers instead of using Mod4 for everything
  - [ ] Configurable Mouse actions
- [ ] Window groups
- [ ] Monitors
- [x] Settings
  - [x] Custom borders
  - [x] Custom margins
- [ ] All sorts of bugfixing, NULL-checking, etc.
- [ ] A manpage and other proper end-user documentation

Contributing
------------

The codebase is following [OpenBSD's KNF][obsd].

  [obsd]: http://www.openbsd.org/cgi-bin/man.cgi/OpenBSD-current/man9/style.9

Acknowledgements
----------------

Obviously huge thanks to [Michael Forney][mf] for building swc.

  [mf]: https://github.com/michaelforney


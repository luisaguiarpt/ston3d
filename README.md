<!-- *********************************************************************** -->
<!--                                                                         -->
<!--                                                      :::      ::::::::  -->
<!-- README.md                                          :+:      :+:    :+:  -->
<!--                                                  +:+ +:+         +:+    -->
<!-- By: josepedr <josepedr@student.42porto.com>    +#+  +:+       +#+       -->
<!--                                              +#+#+#+#+#+   +#+          -->
<!-- Created: 2026/08/20 15:43:44 by josepedr          #+#    #+#            -->
<!-- Updated: 2026/08/20 15:54:15 by josepedr         ###   ########.fr      -->
<!--                                                                         -->
<!-- *********************************************************************** -->

*This project has been created as part of the 42 curriculum by ldias-da & josepedr*


# cub3D


## ston3D
An unserious little raycaster where your mission is to wander through a maze-like authoritarian hellscape and collect every last ingredient to finally enjoy yourslef a well earned relaxing break.

Some would call it a quest. Others, an extended lunch break with questionable logistics.


The objective is simple:

- collect all the ingredients to open the closed gate
- find the exit
- enjoy the consequences of good life choices


## Compilation

The project is built with `make`.

```bash
make
```

This builds the base game which includes:

- standard raycasting gameplay
- map parsing and validation
- player movement controls
- fully explorable map

### Bonus version

```bash
make bonus
```

Builds the bonus version of the game which includes everything from the base game, plus:

- collectibles
- the gate
- extra visual elements such as the player's hands
- a minimap

### NSFW version

```bash
make nsfw
```

Builds the bonus version with the NSFW assets.


## Usage

Run the game with the `.cub` map file you wish to play:

```bash
./cub3D path/to/map.cub
```

The program expects exactly one argument: the map file path.


## Controls

### Keyboard

- `W` — move forward
- `A` — strafe left
- `S` — move backward
- `D` — strafe right
- `←` / `→` — rotate left / right
- `ESC` — exit the game

### Mouse (bonus)

- Move the mouse horizontally to rotate left or right
- Left click to consume your 'sandwich' after passing through the gate


## Maps


### Base map rules

A valid map file must:

- be a `.cub` file
- define the four wall textures at the beginning (must be `.xpm` files):
  - `NO` — followed by the texture's path
  - `SO` — followed by the texture's path
  - `EA` — followed by the texture's path
  - `WE` — followed by the texture's path
- define floor and ceiling colors `(R, G, B)`
- contain exactly one player spawn:
  - `N`, `S`, `E`, or `W` (setting the direction the player is facing)
- use only valid map characters:
  - spaces (representing a *void* space)
  - `0` (representing a *walkable* space)
  - `1` (representing a *wall*)
- be properly enclosed so the player cannot escape the map
- the map layout must be defined after the wall textures and ceiling colors are defined

### Bonus map rules

When compiling with `make bonus` or `make nsfw`, the map **must** also include bonus-specific entities.

Valid bonus characters include:

- `a`, `b` and `c` — representing the three different collectibles
- `G` representing the gate and the exit.

For bonus maps:

- there must be exactly one `a`, one `b`, and one `c`
- the `gate` must be surrounded by walls on both sides.
- the player must collect all ingredients before the gate opens and the exit becomes usable


## Resources
42Docs' entry on [MiniLibX](https://harm-smits.github.io/42docs/libs/minilibx) — understandable, straightforward and beginner friendly documentation on MiniLibX.


[Edvinas Momkus](https://github.com/Edvinas1122/) and his [cub3D project](https://github.com/Edvinas1122/cub3D) for inspiring our 'low shutter speed' trippy effect.

## AI usage
help with some of the more complex calculations that rendering requires.


help with bitmasks.


help with implementing the low shutter speed effect at the end of the game.

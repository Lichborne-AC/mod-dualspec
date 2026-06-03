# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore
## mod-dualspec
### This is a module for [AzerothCore](http://www.azerothcore.org)

# Module info

- Name: Dual Spec Command
- Module:
  + Repository: https://github.com/Lichborne-AC/mod-dualspec
- License: GNU General Public License v3.0

# Description

Adds a single player chat command, `.dualspec`, which unlocks Dual Talent
Specialization for the calling character. No trainer NPC, no 1000g cost —
the player types the command and the second talent spec is enabled.

The unlock pathway mirrors the one used by `mod-npc-services` (the
"Learn Dual Talents" gossip option): the relevant marker spells are
learned, the dual-spec activation spell is cast, and
`Player::UpdateSpecCount(2)` persists the change.

# Usage

In-game, type:

```
.dualspec
```

Behavior:

- If the server has the module disabled in config → player is told it's disabled.
- If the player is in combat → command refuses.
- If the player already has 2 specs → command reports "already unlocked" and exits.
- If the player is below **level 10** → command refuses (talent points are not
  awarded below level 10, so dual spec has nothing to spend).
- Otherwise → second talent spec is enabled and persisted to the character DB.

The command is idempotent: once unlocked, repeated calls do nothing.

# Module integration

- Includes configuration (.conf)?: Yes, copied by CMake
- Includes SQL patches?: No
- Core hooks used:
    + CommandScript (registers `.dualspec`, `SEC_PLAYER`, in-game only)

# How to install

1. Place this module under the `modules` folder of your AzerothCore source folder.
2. Re-run CMake and rebuild AzerothCore.
3. `make install`.

# Configuration

The module ships with one configuration key:

- `DualSpec.Enable` — `1` (default) enables the `.dualspec` command;
  `0` disables it (the command will tell the player it's disabled).

To change it, copy `mod_dualspec.conf.dist` to `mod_dualspec.conf` in your
server's `etc/modules/` directory and edit the value. Default settings work
out of the box; no edit is required.

The minimum level requirement (10) is hardcoded.

# Credits

* The dual-spec unlock pathway is based on the implementation in
  [`mod-npc-services`](https://github.com/azerothcore/mod-npc-services)
  (Learn Dual Talents gossip option).
* AzerothCore: [repository](https://github.com/azerothcore) -
  [website](http://azerothcore.org/) -
  [discord](https://discord.gg/PaqQRkd)

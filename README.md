# Pallet to Mt. Moon — N64 homebrew prototype

A work-in-progress low-poly N64 adventure following Pallet Town, Oak's Lab, the rival battle, Route 1, Viridian City, Viridian Forest, Pewter City, Brock, Route 3, and the blocked Mt. Moon entrance.

## Current development status
- World-space low-poly polygon environments, trainer model, location scenery, and following camera projection are in source.
- Movement, basic collision, starter selection, HP-based rival and Brock battles, badge progression, and ending gate are implemented in source.
- Starter-specific stats, health meters, early-route encounter definitions, and pure-C game-logic tests are included.
- **Not complete:** emulator boot verification, full Pokemon Stadium-style models, wild encounter integration, complete interiors, polished battle scenes, sound, and final game testing.
- **Automatic ROM builds are disabled**. The workflow can only be run manually. Do not assume any prior green build proves the game boots.

## Test logic without generating an N64 ROM
Run `sh tools/run_logic_tests.sh` on a machine with a C compiler.

## Final ROM build
The libdragon GitHub Actions workflow is manual-only until the game is ready for validation. A successful build produces a `pallet_mt_moon.z64` artifact, but actual emulator boot still requires testing.

No commercial ROM or ripped game assets are included.

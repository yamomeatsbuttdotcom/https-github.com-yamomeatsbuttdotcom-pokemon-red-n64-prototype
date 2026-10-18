# Pallet to Mt. Moon — N64 prototype

Homebrew Nintendo 64 adventure prototype inspired by the opening journey through Kanto.

**Current stage:** N64 boot and controller-input test only. This is not yet a 3D game or a playable Pokémon Red remake. The ROM build has not been verified.

## Target demo
Pallet Town → choose starter → rival battle → Route 1 → Viridian City → Viridian Forest → Pewter City → Brock battle → Route 3 → blocked Mt. Moon entrance.

## Building
The project uses the [libdragon](https://github.com/DragonMinded/libdragon) SDK. The GitHub Actions workflow attempts to compile `pallet_mt_moon.z64` and publish it as a downloadable artifact.

Visit [Actions](../../actions) to check the build result. A successful build is not the same as an emulator test.

No commercial ROMs or extracted Pokémon Stadium assets are included.

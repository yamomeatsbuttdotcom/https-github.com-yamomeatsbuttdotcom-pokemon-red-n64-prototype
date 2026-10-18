# ROM build and emulator verification

## Build readiness

The prototype source covers Pallet Town, Oak's Lab, rival battle, Route 1,
Viridian City, Viridian Forest, Pewter City, Brock, Route 3 and a blocked
Mt. Moon entrance. A successful GitHub Actions run is **not** proof that the
ROM boots in an emulator.

## Run a build

1. Open **Actions → Build N64 ROM → Run workflow** on the default branch.
2. The workflow runs `tools/run_logic_tests.sh`, builds libdragon and the
   `pallet_mt_moon.z64` ROM, and checks its N64 header.
3. Download the `pallet-mt-moon-rom` artifact from the successful run.

## Emulator smoke test (M64Plus FZ)

1. Import `pallet_mt_moon.z64` and verify the game starts without a black
   screen, exception, or immediate exit.
2. Walk north in Pallet Town and press A; choose each starter in separate
   runs and win the rival battle.
3. Walk Route 1, fight and escape wild encounters, and heal in Viridian
   using C-Up.
4. Traverse Viridian Forest, heal in Pewter, and win Brock's battle.
5. Verify the Boulder Badge is awarded, Route 3 is accessible, and the
   Mt. Moon entrance is blocked with an end-of-prototype message.
6. Check D-Pad, A, B, C-Up, and START on the Android controller mapping.

## Release gate

Do not label the ROM playable or finished until **both** the build workflow
and the emulator smoke test pass. The previous successful build did not boot
in M64Plus FZ, so the boot check is especially important.

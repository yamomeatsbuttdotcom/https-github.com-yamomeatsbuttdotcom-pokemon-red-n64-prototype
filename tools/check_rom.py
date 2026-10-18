#!/usr/bin/env python3
"""Check basic N64 ROM structure before publishing a downloadable artifact.

This is a static check, not proof that the ROM boots in an emulator.
"""
import pathlib
import struct
import sys

def main(path):
    rom = pathlib.Path(path).read_bytes()
    if len(rom) < 0x1000:
        raise SystemExit(f"FAIL: ROM too short ({len(rom)} bytes)")
    if rom[:4] != bytes.fromhex("80371240"):
        raise SystemExit(f"FAIL: unexpected N64 big-endian ROM magic: {rom[:4].hex()}")
    if len(rom) % 4:
        raise SystemExit(f"FAIL: ROM size {len(rom)} is not word aligned")
    entry = struct.unpack_from(">I", rom, 8)[0]
    if not (0x80000000 <= entry <= 0xBFFFFFFF):
        raise SystemExit(f"FAIL: implausible MIPS entry address: 0x{entry:08X}")
    name = rom[0x20:0x34].decode("ascii", errors="replace").strip(" \\x00")
    if not any(rom[0x40:0x1000]):
        raise SystemExit("FAIL: IPL3 bootcode area is entirely zero")
    print(f"PASS: N64 .z64 header; {len(rom):,} bytes; entry 0x{entry:08X}; title {name!r}")
    print("NOTE: Static validation does not prove emulator boot or gameplay.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        raise SystemExit("Usage: python3 tools/check_rom.py pallet_mt_moon.z64")
    main(sys.argv[1])

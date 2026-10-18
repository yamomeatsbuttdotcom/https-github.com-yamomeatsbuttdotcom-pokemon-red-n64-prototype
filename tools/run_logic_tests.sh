#!/bin/sh
set -eu
tmp="${TMPDIR:-/tmp}/pallet_rules_test_$$"
trap 'rm -f "$tmp"' EXIT
cc -std=c11 -Wall -Wextra -Werror -I src tests/test_game_rules.c -o "$tmp"
"$tmp"
echo "Game logic tests passed"

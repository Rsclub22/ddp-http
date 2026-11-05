#!/bin/sh
# Kompiliert und startet die Unit-Tests. Braucht kddp im PATH und die Locale de_DE.UTF-8.
set -eu
cd "$(dirname "$0")"
mkdir -p build
kddp kompiliere test.ddp -o build/test
./build/test

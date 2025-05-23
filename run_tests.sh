set -e

mkdir -p build/
./compile_tests.sh
build/test_guppy

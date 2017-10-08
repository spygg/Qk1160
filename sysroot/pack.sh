#!/bin/sh

rm -f HNApp/K1160PRO
cp -f ../Build/K1160PRO-MIPS32-Release/K1160PRO HNApp/


rm -f upgrade.tar.gz

tar czvf upgrade.tar.gz HNApp etc usr



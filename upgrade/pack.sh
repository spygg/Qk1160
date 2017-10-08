#!/bin/sh

cp -fr ../sysroot/HNApp  ./
rm -f HNApp/K1160PRO
cp -f ../build-K1160PRO-mips_32-Release/K1160PRO HNApp/

rm -fr HNApp/conf
rm -fr HNApp/db
rm -fr HNApp/*.sh

rm -f upgrade.tar.gz

tar czvf upgrade.tar.gz HNApp



if [ "" = "$1" ]; then
exit
fi

/usr/lib/x86_64-linux-gnu/qt4/bin/lupdate ../../../k1160/k1160.pro -ts $1.ts
/usr/lib/x86_64-linux-gnu/qt4/bin/linguist $1.ts
/disk2/ylguo/ingenic_buildroot/output/host/usr/bin/lrelease $1.ts -qm $1.qm

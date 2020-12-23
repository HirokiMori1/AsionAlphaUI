#!/bin/sh

FILE="/home/kufushatec/AsionAlphaUI/licenses/osslic.html"
OSSLIC="/home/kufushatec/AsionAlphaUI/licenses/osslicenses.html"

echo "<html>" > ${FILE}
echo "<head><title>OSS Licenses</title></head>" >> ${FILE}
echo "<body>" >> ${FILE}



echo "<h1>Third-party materials and licenses</h1>" >> ${FILE}

find /usr/share/doc -name copyright | \
    sed "s/\/usr\/share\/doc\///" | sed "s/\/copyright//" | \
    awk '{print "<a href=\"/usr/share/doc/" $1 "/copyright\">" $1 "</a><br>"}' | \
    sort >> ${FILE}

find /home/kufushatec/AsionAlphaUI/licenses/OSS -name COPYING.LGPL | \
    sed "s/\/home\/kufushatec\/AsionAlphaUI\/licenses\/OSS\///" | sed "s/\/COPYING.LGPL//" | \
    awk '{print "<a href=\"/home/kufushatec/AsionAlphaUI/licenses/OSS/" $1 "/COPYING.LGPL\">" $1 "</a><br>"}' | \
    sort >> ${FILE}

find /home/kufushatec/AsionAlphaUI/licenses/OSS -name LICENSE | \
    sed "s/\/home\/kufushatec\/AsionAlphaUI\/licenses\/OSS\///" | sed "s/\/LICENSE//" | \
    awk '{print "<a href=\"/home/kufushatec/AsionAlphaUI/licenses/OSS/" $1 "/LICENSE\">" $1 "</a><br>"}' | \
    sort >> ${FILE}

find /home/kufushatec/AsionAlphaUI/licenses/OSS -name PackageSummary | \
    sed "s/\/home\/kufushatec\/AsionAlphaUI\/licenses\/OSS\///" | sed "s/\/PackageSummary//" | \
    awk '{print "<a href=\"/home/kufushatec/AsionAlphaUI/licenses/OSS/" $1 "/PackageSummary\">" $1 "</a><br>"}' | \
    sort >> ${FILE}

find /home/kufushatec/AsionAlphaUI/licenses/OSS -name COPYRIGHT.txt | \
    sed "s/\/home\/kufushatec\/AsionAlphaUI\/licenses\/OSS\///" | sed "s/\/COPYRIGHT.txt//" | \
    awk '{print "<a href=\"/home/kufushatec/AsionAlphaUI/licenses/OSS/" $1 "/COPYRIGHT.txt\">" $1 "</a><br>"}' | \
    sort >> ${FILE}

find /home/kufushatec/AsionAlphaUI/licenses/OSS -name package.xml | \
    sed "s/\/home\/kufushatec\/AsionAlphaUI\/licenses\/OSS\///" | sed "s/\/package.xml//" | \
    awk '{print "<a href=\"/home/kufushatec/AsionAlphaUI/licenses/OSS/" $1 "/package.xml\">" $1 "</a><br>"}' | \
    sort >> ${FILE}

find /home/kufushatec/AsionAlphaUI/licenses/OSS -name PKG-INFO | \
    sed "s/\/home\/kufushatec\/AsionAlphaUI\/licenses\/OSS\///" | sed "s/\/PKG-INFO//" | \
    awk '{print "<a href=\"/home/kufushatec/AsionAlphaUI/licenses/OSS/" $1 "/PKG-INFO\">" $1 "</a><br>"}' | \
    sort >> ${FILE}

cat ${OSSLIC} >> ${FILE}

echo "</body>" >> ${FILE}
echo "</html>" >> ${FILE}

/usr/bin/firefox ${FILE}


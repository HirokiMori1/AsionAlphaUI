#!/bin/sh

FILE="/home/kufushatec/AsionAlphaUI/licenses/osslic.html"

echo "<html>" > ${FILE}
echo "<head><title>OSS Licenses</title></head>" >> ${FILE}
echo "<body>" >> ${FILE}

find /usr/share/doc -name copyright | \
    sed "s/\/usr\/share\/doc\///" | sed "s/\/copyright//" | \
    awk '{print "<a href=\"/usr/share/doc/" $1 "/copyright\">" $1 "<br>"}' | \
    sort >> ${FILE}

echo "</body>" >> ${FILE}
echo "</html>" >> ${FILE}

/usr/bin/firefox ${FILE}


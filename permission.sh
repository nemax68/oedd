find . -type d -exec chmod 777 {} \;

find . -type f -exec chmod 666 {} \;

chmod 777 makefile

chmod 777 .gitmodules

chmod 755 debian/rules

chmod 755 debian/oedd/DEBIAN/prerm

chmod 755 debian/oedd/DEBIAN/postrm

chmod 755 debian/oedd/DEBIAN/postinst

bin_PROGRAMS=main
pkgdata_DATA=ru_RU/LC_MESSAGES/main.mo main.1

@DX_RULES@

ru_RU/LC_MESSAGES/main.mo: main.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

%.1:    %
	-$(HELP2MAN) --no-info --output=$@ --name='@PACKAGE_NAME@' ./$<

main.po:	main.pot
	msgmerge -U $@ $<

launch_ru:
	LANGUAGE=ru_RU ./main

launch_en:
	LANGUAGE=en_US ./main

main.pot:	header.pot main.c
	xgettext -k_ -c main.c -o main.new.pot
	cp header.pot main.pot
	msgmerge -U main.pot main.new.pot

gitclean: maintainer-clean
	git clean -fd

all-local:	doxygen-doc

#!/bin/sh
# TODO: use this to handle transition
# Like: removing old apps, moving confifguration files, etc.
## remove legacy app
OLDAPP=/Applications/beta-ftopia.app
if [ -d "$OLDAPP" ]; then
	rm -rf "$OLDAPP"
fi

## quit app if running
# helpers
APPNAME=beta-ftopia
APPFILENAME=beta-ftopia.app
appRunning () {
	ps -e -o comm | grep -q $APPFILENAME
}
exitIfOk () {
	if ! appRunning; then
		exit 0
	fi
}
##
osascript -e 'tell application "'$APPNAME'" to quit'
for i in 1 2 3 4 5; do
	exitIfOk
	sleep 1
done

APPPID=`ps -e -o pid,comm | awk /$APPFILENAME'/ {print $1}'`
kill -TERM $APPPID
sleep 1
exitIfOk
kill -KILL $APPPID
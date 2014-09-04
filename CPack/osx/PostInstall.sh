#!/bin/sh

BETAFTOPIAAPP=/Applications/beta-ftopia.app

# automatically start ftopia at boot
osascript << EOF
set appPath to "$BETAFTOPIAAPP"
tell application "System Events"
	make login item at end with properties {path:appPath, hidden:true}
end tell

EOF

# TODO: Fuck you! This will break the app.
# Vincent says is something bizantine, skipping for now.
# # migrate documents from 'ftopia - X' to 'ftopia-X'
# find /Users/*/Documents -maxdepth 1 -type d -name 'beta-ftopia - *' | \
# 	while read name; do
# 		mv "$name" "`echo $name | sed 's/ - /-/g'`"
# 	done

# run the app
(
	sleep 5
	env - open "$BETAFTOPIAAPP"
) &
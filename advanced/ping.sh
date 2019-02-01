#!/bin/sh -e

#
# Harlan J Waldrop <harlan@ieee.org>
# January 13, 2018
#

DEV='/dev/ttyUSB0'

function send_random_cmd()
{
	local cmd=( 'r' 'g' 'b');
	local rand=$((RANDOM % 3))
	local chosen=${cmd[$rand]}

	echo -e "ping: $chosen\r\n"
	sudo sh -c "echo -e -n '$chosen\r\n' >> $DEV"
}

if [ -e $DEV ]; then
	# -echo  Stop terminal from pointlessly echoing what it reads
	# -onlcr Don't remap NL to CRNL
	sudo stty -F $DEV -echo -onlcr
	while sleep 1; do send_random_cmd; done;
else
	echo "Error: FTDI interface not found"
fi

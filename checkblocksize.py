#!/usr/bin/env python
# cat <dump> | ./checkblocksize.py
import sys

# Define "Expected Blocksize" and only those not matching will print
expectedsize = 2112

buf = ''
blocknum = None
while True:
	c = sys.stdin.read(1)
	if not c:
		break

	buf += c
	if buf.endswith('BLOCK '):
		if blocknum and ('expectedsize' not in globals() or len(buf) < 2112):
			print "%8d block size %5d (0x%x)"%(blocknum, len(buf)-6, len(buf)-6)
		blocknum = int(sys.stdin.read(25))
		sys.stdin.read(1) # '\n'
		buf = ''

print "last block number:", blocknum

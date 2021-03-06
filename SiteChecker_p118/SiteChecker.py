#!/usr/bin/env python

import urllib, md5, os


URL = 'http://www.linuxformat.co.uk'


print 'Reading website...'
website = urllib.urlopen(URL)
data = website.read()

md5sum = md5.new()
md5sum.update(data)
digest = md5sum.hexdigest()


if (os.path.exists('change.db')):
	file = open('change.db', 'r')
	filedata = file.read()
	if (filedata != digest):
		print 'Website has changed!'
	else:
		print 'No change to the site'

else:
	print 'Creating database...'
	file = open('change.db', 'w')
	file.write(digest)
	fi            
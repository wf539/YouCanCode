import os, string, logging
import eyeD3

def sanitize (string):
	# remove extra spaces
	string.strip()
	string=string.replace('*','+')
	string=string.replace('/','-')
	string=string.replace('\\','-')
	string=string.replace('__','_')
	string=string.replace('--','-')
	# this could all be done more efficiently with regular expressions, but this is easier to understand and extend for now
	return string

#set up logging
logger = logging.getLogger("pymusic")
logger.setLevel(logging.WARN)
#create console handler and set level to debug
handler = logging.StreamHandler()
handler.setLevel(logging.DEBUG)
#create formatter
formatter = logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
handler.setFormatter(formatter)
#add handler to logger
logger.addHandler(handler)
logger.debug("started")

# set up variables
topdir="/mnt/sda12/Music/"
unknownlist = []
wmalist = []
ogglist = []


#start here!
walklist = os.walk(topdir)




for dirs in walklist:
	if(dirs[2]):
		for file in dirs[2]:
			#clear error flag
			error_flag = False
			fullpath = os.path.join(dirs[0],file)
			#pyhton string slice the filename to get extension
			extension = file[-4:]
			if (extension !='.mp3'):
                                 #Not an mp3 file? check for other extensions?
				if (extension  == '.wma'):
					wmalist.append(fullpath)
					#logger.warn("silly wma file %s",fullpath)
				elif (extension == '.ogg'):
					ogglist.append(fullpath)
				else:	
					unknownlist.append(fullpath)
			else:
				# is it really an MP3 file?
				if eyeD3.isMp3File(fullpath):
					# read ID3V2 tag
					tag2 = eyeD3.Tag()
					tag1 = eyeD3.Tag()
					a = tag2.link(fullpath,eyeD3.ID3_V2)
					b = tag1.link(fullpath,eyeD3.ID3_V1)
					if b and not a:
						#only ID3v1 tag present
						print "version1 only"
						# create tag2 information from tag1
						print fullpath
						artist = tag1.getArtist()
						album = tag1.getAlbum()
						title = tag1.getTitle()
						print artist,album,title
						tag1.update(eyeD3.ID3_V2)
						
						#check tags are cool
					elif a and not b:
						#only ID3v2 present
						print fullpath
						artist = tag2.getArtist()
						album = tag2.getAlbum()
						title = tag2.getTitle()
						print artist,album,title
						try:
							tag2.update(eyeD3.ID3_V1_1)
						except UnicodeEncodeError:
							logger.error("tag invalid for v1.1 in file %s, change manually!", fullpath)
							error_flag = True
					elif a and b:
						#both versions
						logger.info( "both versions fine %s", fullpath)
					else:
						#no tags present
						logger.warn('this file has no tags! %s', fullpath)
						error_flag = True
						#perhaps we can create some with the information from the directory it is in!
						# maybe in another script ;)
						
					if not error_flag:	
						#decide what filneame should be
						# number-name.mp3
						title=tag2.getTitle()
						title = title.replace(' ','_')
						n=tag2.getTrackNum()
						#we have a number
						ns = str(n[0])
						if len(ns)==1:
							ns= '0'+ns
						ns=ns+'-'+title+'.mp3'
						ns = sanitize(ns)
						if (file!=ns):
							logger.warn("change filename suggested for %s, to %s!",file,ns)
							#if you want to go through with file renaming
							# the commented line below will do it!
							# but no guarantees!
							#os.rename(fullpath, os.path.join(dirs[0],ns))
				else:
					#log a warning
					logger.warn(" file %s does not seem to be a valid mp3 file",fullpath)
				logger.debug(fullpath)
	else:
		for entry in dirs[1]:
			x = dirs[1]

#output stuff
for name in ogglist:
	logger.info("ogg file found %s",name)
for name in wmalist:
	logger.info("wma file found %s",name)
for name in unknownlist:
	logger.info("unknownfile found %s",name)





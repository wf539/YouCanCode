import random
from pygame import *	# Use PyGame's functionality!

count = 0		# Variables for loop and score
score = 0

file1 = open('words.txt', 'r')		# Open our text files
file2 = open('images.txt', 'r')

f1content = file1.readlines()		# And get content
f2content = file2.readlines()

init()					# Start PyGame
screen = display.set_mode((640, 480))	# Give us a nice window
display.set_caption('Flashcard')	# And set its title


# Here's a new font object. The 'None' means: don't choose
# a specific font -- just use the system default, at size 48

font = font.Font(None, 48)


# Here's the main loop -- all the indented code from here
# will be executed 10 times

while count < 10:
	screen.fill(0)	# Fill the screen with black (colour 0)

	# Choose a random number for the picture we're going to
	# show, limited to the number of entries in images.txt
	wordnum = random.randint(0, len(f2content)-1)

	# That random number indicates the line of images.txt
	# from which we should load the image file. So if line
	# 7 is 'nepal.png', we load that! We also strip off the
	# newline character from the text file -- it breaks things.
	mainpic = image.load(f2content[wordnum].rstrip('\n'))

	# Draw our picture to the top-center of the screen
	screen.blit(mainpic, (255, 50))

	# Choose three random options, a la the text version
	options = [random.randint(0, len(f1content)-1),
		random.randint(0, len(f1content)-1),
		random.randint(0, len(f1content)-1)]

	# And make one of them the real answer
	options[random.randint(0, 2)] = wordnum

	# Now we draw the three possible answer words. We get the
	# word from our f1content[] array, and say 'True' as the
	# second option -- it means 'anti-alias me please!'. The
	# final three numbers are the colours (red, green, blue),
	# so in this case it's white.
	text1 = font.render('1 - ' + f1content[options[0]].rstrip('\n'),
		True, (255, 255, 255))
	text2 = font.render('2 - ' + f1content[options[1]].rstrip('\n'),
		True, (255, 255, 255))
	text3 = font.render('3 - ' + f1content[options[2]].rstrip('\n'),
		True, (255, 255, 255))

	# Draw those words to the screen (horiz, vertical)
	screen.blit(text1, (30, 200))
	screen.blit(text2, (30, 300))
	screen.blit(text3, (30, 400))

	# And update everything!
	display.update()

	done = False	# This is for the following loop...

	# Here we wait for a keyboard 'event' -- that is, something
	# happening at the keyboard. If a key has been pressed and
	# released (KEYUP), then we ask if it was the '1' key (K_1),
	# or 2, and so forth. When an answer key has been pressed,
	# we set 'done' to True to exit the loop.
	while not done:
		for e in event.get():
			if e.type == KEYUP:
				if e.key == K_1:
					answer = 1
					done = True
				if e.key == K_2:
					answer = 2
					done = True
				if e.key == K_3:
					answer = 3
					done = True

	# Is this right? If so, print some jolly green text
	# and increment the score!
	if options[answer-1] == wordnum:
		resulttext = font.render('Correct!', True, (50, 255, 50))
		score = score + 1
	# But if not... Boo, here's some red text
	else:
		resulttext = font.render('Wrong!', True, (255, 50, 50))

	# Show the text
	screen.blit(resulttext, (450, 300))
	display.update()

	# And wait for a keypress before the next question
	while event.wait().type != KEYDOWN: pass

	count = count + 1

# When the loop has finished, we print the score. And that's it!
print '\nYour score is:', score


from pygame import *	# Use PyGame's functionality!

ballpic = image.load('ball.png')

done = False

ballx = 0	# Ball position variables
bally = 0
ballxmove = 1
ballymove = 1

init()					# Start PyGame
screen = display.set_mode((640, 480))	# Give us a nice window
display.set_caption('Ball game')	# And set its title

while done == False:
	screen.fill(0)	# Fill the screen with black (colour 0)
	screen.blit(ballpic, (ballx, bally))	# Draw ball
	display.update()

	time.delay(1)			# Slow it down!

	ballx = ballx                              ����<<<����                                 ������                                                          �����������  �����������������������������  ���                    ���                                                          �����������                  ������
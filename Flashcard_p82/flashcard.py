import os, random

count = 0
score = 0

file1 = open('english.txt', 'r')
file2 = open('german.txt', 'r')

f1content = file1.readlines()
f2content = file2.readlines()

while count < 10:
	os.system('clear')

	wordnum = random.randint(0, len(f1content)-1)

	print 'Word:', f1content[wordnum], ''

	options = [random.randint(0, len(f2content)-1),
		random.randint(0, len(f2content)-1),
		random.randint(0, len(f2content)-1)]

	options[random.randint(0, 2)] = wordnum

	print '1 -', f2content[options[0]],
	print '2 -                             ����<<<����                                 ������                                                          �����������  �����������������������������  ���                    ���                                                          �������
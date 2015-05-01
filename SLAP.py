import webbrowser

from Tkinter import *
from PIL import ImageTk, Image
import tkFont
import ttk

#importing pygoogle, tkHyperlinkManager
from support_modules import *

import lyricsSearch
import song_artist_search

mainWindow = Tk()
mainWindow.title("Project SLAP v1.0")
mainWindow.geometry("600x600")


#declaring an object to store the user input
query = StringVar()


#dict to hold seperate results
resultSplit = {}
#dict to hold the strings that are to be googled
stuffToGoogle = {}

#function to perform google search and return the first link
def googleThis(query):
	g = pygoogle(query+" youtube")
	g.pages = 1
	return g.get_urls()[0]


#
#	function to divide the single string passed from c into seperate results and store them in "resultSplit" list
#	and initiates passStuffToExtractStuff()
#
def splitResult(given):
	k=0
	j=0
	for i in range(len(given)):
		if given[i] == "\t":
			resultSplit[k] = given[j:i]
			j = i+1
			k += 1
	passStuffToExtractStuff()


#			
#	extractStuff() gets a string, extracts the part of the string to be googled and stores it in the list "stuffToGoogle"
#	passStuffToExtractStuff() passes strings from the "resultSplit" list to extractStuff()
#	
def passStuffToExtractStuff():
	for i in range(5):
		extractStuff(resultSplit[i], i)
def extractStuff(given, n):
	for i in range(len(given)):
		if given[i] == "\n":
			stuffToGoogle[n] = given[:i]
			break


#
#	function to be called when the "Search by Lyrics" button is hit
#	lSearch() gets the string entered in the search text box and passes it to search() function from "lyricsSearch" module
#	and initiates splitResult() and showResults()
#
def lSearch():
	q = query.get()
	print "shit1"
	resultPassedFromC = lyricsSearch.search(q)
	print "shit2"
	print resultPassedFromC
	splitResult(resultPassedFromC)
	showResults()
	return
	
def aSearch():
	q = query.get()
	resultPassedFromC = song_artist_search.artistSearch(q)
	print resultPassedFromC
	splitResult(resultPassedFromC)
	showResults()
	return
	
def sSearch():
	q = query.get()
	resultPassedFromC = song_artist_search.songSearch(q)
	print "shit2"
	return


resultPassedFromC = "\"Shady XV Cypher\" - Eminem\n[Verse 1: Crooked I]\nMy name is King Crooked, I snap on you rappers often\nWhen I'm spazzin' I'm just gettin' my passion and point across\n\t\"No Flex Zone Remix\" - Karmin\n[Verse 1: Watsky]\nI'm jubilant with a stupid grin\nYour screw's loose where do you begin?\n\t\"Whiskey In A Bottle\" - Yelawolf\n[Verse 1]\nStill on that ass like\nHandcuff's up in it like\n\t\"Idle Delilah\" - Azealia Banks\n[Verse:]\nIdle Miss Delilah\nDarling, do you like beige in your\n\t\"Idle Delilah\" - Azealia Banks\n[Verse:]\nIdle Miss Delilah\nDarling, do you like beige in your\n\tEminem:Shady_XV_Cypher.txt\tKarmin:No_Flex_Zone_Remix.txt\tYelawolf:Whiskey_In_A_Bottle.txt\tAzealia_Banks:Idle_Delilah.txt\tAzealia_Banks:Idle_Delilah.txt\t"

#search icon
icon = ImageTk.PhotoImage(Image.open("icons/SearchIcon.gif"))	

#custom fonts definition
headingFont = tkFont.Font(family="Ubuntu", size=12)
resultsTextFont = tkFont.Font(family="Ubuntu", size=11)


#line1 - search query text box and search icon
searchQuery = Entry(mainWindow, textvariable= query, bd=1)
searchQuery.place(x=40, y=50, height=30, width=490)
searchIcon = Label(mainWindow, image=icon, anchor=CENTER)
searchIcon.place(x=535, y=50, height=30, width=30)


#line2 - search buttons
songSearchBut = Button(mainWindow, text= "Search by Song", bg="light blue", bd=1, command=sSearch)
songSearchBut.place(x=40, y=110, height=40, width=165)

artistSearchBut = Button(mainWindow, text= "Search by Artist", bg="light blue", bd=1, command=aSearch)
artistSearchBut.place(x=220, y=110, height=40, width=165)

lyricsSearchBut = Button(mainWindow, text= "Search by Lyrics", bg="light blue", bd=1, command=lSearch)
lyricsSearchBut.place(x=400, y=110, height=40, width=165)


#frame to hold the results
resultsFrame = LabelFrame(mainWindow, text="Results", font= headingFont)
resultsFrame.place(x=40, y=200, height=375, width=525)

#text widget that will contain the results
results = Text(resultsFrame, wrap="word", bg="#d9d9d9", bd=0)
results.place(x=5, y=0, height=350, width=500)

#vertical scroll bar in case the text overflows
vscroll = ttk.Scrollbar(resultsFrame)
vscroll.pack(side="right", fill="y")

#binding the text widget and the scrollbar
results.config(yscrollcommand=vscroll.set)
vscroll.config(command=results.yview)


#define hyperlink and linking functions
hyperlink = tkHyperlinkManager.HyperlinkManager(results)
def openBrowser(n):
	webbrowser.open_new_tab(googleThis(stuffToGoogle[n]))

#function that displays final results in the text wiget
def showResults():	
	results.insert(INSERT, "1. " + resultSplit[0])
	results.insert(INSERT, googleThis(stuffToGoogle[0]), hyperlink.add(lambda: openBrowser(0)))
	results.insert(INSERT, "\n\n2. " + resultSplit[1])
	results.insert(INSERT, googleThis(stuffToGoogle[1]), hyperlink.add(lambda: openBrowser(1)))
	results.insert(INSERT, "\n\n3." + resultSplit[2])
	results.insert(INSERT, googleThis(stuffToGoogle[2]), hyperlink.add(lambda: openBrowser(2)))
	results.insert(INSERT, "\n\n4." + resultSplit[3])
	results.insert(INSERT, googleThis(stuffToGoogle[3]), hyperlink.add(lambda: openBrowser(3)))
	results.insert(INSERT, "\n\n5." + resultSplit[4])
	results.insert(INSERT, googleThis(stuffToGoogle[4]), hyperlink.add(lambda: openBrowser(4)))

	#rendering the text widget read only
	results.config(state=DISABLED)


#to keep the window open
mainWindow.mainloop()

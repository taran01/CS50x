from sys import argv, exit
from pyfiglet import Figlet
import random

if len(argv) != 1 and len(argv) != 3:
    print("Invalid Usage")
    exit(1)

figlet = Figlet()
r = figlet.getFonts()

if len(argv) == 1:
    text = input("Input: ")
    figlet.setFont(font=random.choice(r))
    print(figlet.renderText(text))
elif argv[1] in ["-f", "--font"] and argv[2] in r:
    text = input("Input: ")
    figlet.setFont(font=argv[2])
    print(figlet.renderText(text))
else:
    print("Invalid Usage")
    exit(1)
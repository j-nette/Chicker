# Importing Libraries 
import time 
import warnings
import serial
import serial.tools.list_ports

import tkinter as tk
from tkinter import messagebox as mb
from tkinter import simpledialog as sd
from PIL import Image, ImageTk

# Constants #
MAX_PULSEWIDTH = 5000 

# Autodetect Ports #
arduino_ports = [
	p.device
    for p in serial.tools.list_ports.comports()
    if 'ESP' in p.description  
	]
if not arduino_ports:
    raise IOError("No ESP found")
if len(arduino_ports) > 1:
    warnings.warn('Multiple ESPs found - using the first')

ser = serial.Serial(arduino_ports[0])

arduinoData = serial.Serial(port=ser, baudrate=115200, timeout=.1)

# Serial Communication Function (converts data into a string to be sent via serial) #
def write_read(x: str): 
	arduinoData.write(bytes(x, 'utf-8')) 
	time.sleep(0.05) 
	#data = arduinoData.readline() 
	#return data 

# Sends kick command to rig #    
def sendKick():
  global chargeStatus

  if(chargeStatus == 1):
    pulse = sd.askstring(title="Kick Strength", prompt="Please enter a pulsewidth (0-" + str(MAX_PULSEWIDTH) + "):")
    if checkPulse(pulse) == True:
      write_read("1," + str(pulse))
      log.insert('1.0',"Kicking with a pulsewidth of " + pulse + " in 3 seconds. Please stand back.\n")
  else:
    # warning before kick
    askCharge() 
    if (chargeStatus == 1):
       sendKick()

# Sends chip command to rig #
def sendChip():
  global chargeStatus

  if(chargeStatus == 1):
    pulse = sd.askstring(title="Chip Strength", prompt="Please enter a pulsewidth (0-" + str(MAX_PULSEWIDTH) + "):")
    if checkPulse(pulse) == True:
      write_read("2," + str(pulse))
      log.insert('1.0',"Chipping with a pulsewidth of " + pulse + " in 3 seconds. Please stand back. \n")
  else:
    # warning before chip
    askCharge() 
    if (chargeStatus == 1):
       sendChip()

# Sends charge command to rig #
def sendCharge():
  log.insert('1.0',"Power board charging.\n")
  write_read("3,1")

# Warning for charging the power board #
def askCharge():
  global chargeStatus
  if chargeStatus == False:
    res = mb.askyesno("Warning","Warning: You are about to charge the power board.\nOnce charged, it will remain charged and setting \"Charge\" to low will NOT DISCHARGE it.\nDo you understand?")
    if res == True:
      chargeStatus = True
      chargeBtn.configure(background='#fa6b6b')
      chicker_tester_window.title("Chicker Tester - CHARGE IS ON")
      sendCharge()
    else:
      log.insert('1.0',"Action Cancelled\n")
  else:
    mb.showwarning("Caution", "Caution: Turning \"Charge\" off will NOT DISCHARGE the power board.\n")
    chargeStatus = False
    write_read("3,0")
    chargeBtn.configure(background=tbotYellow)
    chicker_tester_window.title("Chicker Tester")

# Checking Validity of pulsewidth value #
def checkPulse(pulse):
  if int(pulse) > MAX_PULSEWIDTH or int(pulse) < 0:
    mb.showwarning("Error", "Error: The value you entered is outside of the desired range. Please enter a value between 0 and " + str(MAX_PULSEWIDTH))
    return False
  return True


# GUI #

chargeStatus = False

# fonts and colours and stuff #
btnFont = "helvetica, 16"
normalFont = "helvetica, 12"
tbotYellow = "#F1CF49"
tbotBlue = "#1A345B"

# Tkinter Window Setup #

chicker_tester_window = tk.Tk()
chicker_tester_window.configure(background=tbotBlue)
chicker_tester_window.title("Chicker Tester")
chicker_tester_window.geometry("500x300")

log = tk.Text(chicker_tester_window, width = 40, height = 4, wrap = "word", font = normalFont)
log.insert('1.0',"Welcome to the Chicker Tester!\n")

kickBtn = tk.Button(chicker_tester_window, text = " Kick ", font = btnFont, background= tbotYellow, command = sendKick)
chipBtn = tk.Button(chicker_tester_window, text = " Chip ", font = btnFont, background= tbotYellow,command = sendChip)
chargeBtn = tk.Button(chicker_tester_window, text = "Charge", font= btnFont, background= tbotYellow, command = askCharge)

kickBtn.place(relx=0.30, rely=0.50, anchor="center")
chipBtn.place(relx=0.5, rely=0.50, anchor="center")
chargeBtn.place(relx=0.720, rely=0.50, anchor="center")
log.place(relx=0.5, rely=0.20, anchor = "center")

canvas = tk.Canvas(chicker_tester_window, width = 300, height = 50)
canvas.place(relx=0.5, rely=0.80, anchor = "center")
logo = Image.open("data/tbots_logo_no_gradient.png")
shrinkLogo = logo.resize((300, 50))
img = ImageTk.PhotoImage(shrinkLogo)
canvas.create_image(0, 0, anchor="nw", image=img)


chicker_tester_window.mainloop()
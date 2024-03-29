import tkinter as tk
from tkinter import messagebox as mb
from tkinter import simpledialog as sd
from PIL import Image, ImageTk

chargeStatus = False

# fonts and colours and stuff #
btnFont = "helvetica, 16"
normalFont = "helvetica, 12"
tbotYellow = "#F1CF49"
tbotBlue = "#1A345B"

def sendKick():
  pulse = sd.askstring(title="Pulsewidth", prompt="Please enter a pulsewidth (0-5000):")
  if checkPulse(pulse) == True:
    #do something

    log.insert('1.0',"Kicked with a pulsewidth of " + pulse + "\n")

def sendChip():
  pulse = sd.askstring(title="Pulsewidth", prompt="Please enter a pulsewidth (0-5000):")
  if checkPulse(pulse) == True:

    #do something

    log.insert('1.0',"Chipped with a pulsewidth of " + pulse + "\n")

def sendCharge():
  log.insert('1.0',"Please stand back. Power board charging in 5 seconds.\n")

  #do something

  log.insert('1.0',"Charged.\n")

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
      log.insert('1.0',"Charging Cancelled\n")
  else:
    mb.showwarning("Power board may still be charged", "Caution: Turning \"Charge\" off will NOT DISCHARGE the power board.\n")
    chargeBtn.configure(background=tbotYellow)
    chicker_tester_window.title("Chicker Tester")

def checkPulse(pulse):
  if int(pulse) > 5000 or int(pulse) < 0:
    mb.showwarning("Pulsewidth outside of range", "Error: The value you entered is outside of the desired range. Please enter a value between 0 and 5000.")
    return False
  return True


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
chargeBtn.place(relx=0.70, rely=0.50, anchor="center")
log.place(relx=0.5, rely=0.20, anchor = "center")

canvas = tk.Canvas(chicker_tester_window, width = 300, height = 50)
canvas.place(relx=0.5, rely=0.80, anchor = "center")
logo = Image.open("Thunderbots_team_logo.png")
shrinkLogo = logo.resize((300, 50))
img = ImageTk.PhotoImage(shrinkLogo)
canvas.create_image(0, 0, anchor="nw", image=img)




chicker_tester_window.mainloop()
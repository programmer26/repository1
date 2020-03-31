import pyautogui
import time
import pyperclip
import keyboard

def mute():
	pyautogui.hotkey('f5')
	time.sleep(2)
	pyautogui.click(join_now[0], join_now[1])
	pyautogui.click(mic_box[0], mic_box[1])
	time.sleep(1.5)
	pyautogui.click(msg_box[0], msg_box[1])

def kick():
	pyautogui.hotkey('f5')
	time.sleep(2)
	pyautogui.click(join[0], join[1])
	pyautogui.click(my_tab[0], my_tab[1])
	time.sleep(1.5)
	pyautogui.click(accept[0], accept[1])
	pyautogui.click(bot_tab[0], bot_tab[1])
	time.sleep(4)
	pyautogui.click(void[0], void[1])
	pyautogui.click(mic_box[0], mic_box[1])
	time.sleep(1.5)
	pyautogui.click(msg_box[0], msg_box[1])


msg_box = [1778, 148]
mic_box = [878, 977]
people_box = [1698, 139]
join = [1307, 611]
accept = [1163, 640]
bot_tab = [100, 25]
my_tab = [397, 23]
void = [1024, 858]
join_now = [1304, 608]

str = input("Press enter to continue: ")
time.sleep(5)


strings = ['https://www.youtube.com/watch?v=TNHsw8TLf6Y', 'Истинският холокост е в ада', 'Хитлер не направи нищо лошо <3']
tasheva = ['Евреите са виновни за Холокоста!\nЕвреите са виновни за Холокоста!\nЕвреите са виновни за Холокоста!\nЕвреите са виновни за Холокоста!', 'Ботеврад е в другата посока -->', 'И арабите са хора, ма! ( ͡° ͜ʖ ͡°)╭∩╮', 'Jews did 9/11 ( ͡° ͜ʖ ͡°)╭∩╮', 'Hitler did nothing wrong <3']

pyautogui.PAUSE = 0.1


pyautogui.click(join[0], join[1])
pyautogui.click(my_tab[0], my_tab[1])
time.sleep(1.5)
pyautogui.click(accept[0], accept[1])
pyautogui.click(bot_tab[0], bot_tab[1])
time.sleep(4)
pyautogui.click(void[0], void[1])
pyautogui.click(mic_box[0], mic_box[1])
time.sleep(1.5)
pyautogui.click(msg_box[0], msg_box[1])

for i in range(50):
	if keyboard.is_pressed('q'):
		mute()

	elif keyboard.is_pressed('z'):
		kick()
	else:
	    pyperclip.copy(tasheva[0])
	    pyautogui.hotkey('ctrl','v')
	    pyautogui.hotkey('enter')

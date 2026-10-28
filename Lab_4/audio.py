
import serial
import pygame
import time

SERIAL_PORT = "COM3"
BAUD_RATE = 115200

SOUND_FILE = "../Assets/I_See_You.wav"

pygame.mixer.init()
pygame.mixer.music.load(SOUND_FILE)

esp32 = serial.Serial(
    SERIAL_PORT,
    BAUD_RATE,
    timeout=1
)

time.sleep(2)

sound_playing = False

print("Listening to ESP32...")

try:
    while True:
        if esp32.in_waiting:
            message = esp32.readline().decode(
                "utf-8", errors="ignore"
            ).strip()

            print(message)

            if message == "SOUND_ON":
                if not sound_playing:
                    pygame.mixer.music.play(-1)
                    sound_playing = True

            elif message == "SOUND_OFF":
                if sound_playing:
                    pygame.mixer.music.stop()
                    sound_playing = False

except KeyboardInterrupt:
    print("Stopping...")

finally:
    pygame.mixer.music.stop()
    pygame.mixer.quit()
    esp32.close()

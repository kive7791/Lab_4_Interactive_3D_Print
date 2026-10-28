import pygame
import time

pygame.mixer.init()
pygame.mixer.music.load("../Assets/I_See_You.wav")

print("Playing test sound...")
pygame.mixer.music.play()

while pygame.mixer.music.get_busy():
    time.sleep(0.1)

pygame.mixer.quit()
print("Audio test completed.")

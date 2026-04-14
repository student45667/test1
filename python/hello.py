print ("hello world")

import geocoder
import sys
#print(sys.executable)      # shows which Python Eclipse is using
#print(sys.path)            # shows where it looks for libs



#import random
#secret = random.randint(1, 10)
#guess = int(input("Guess a number between 1 and 10: "))

#if guess == secret:
#    print("Correct!")
#else:
#    print (f"Wrong, it was {secret}")



g = geocoder.ip('me')
print(g.latlng)
print(g.city)
print(g.country)

g = geocoder.google([48.218, 16.389], method='reverse')
print(g.city)
print(g.state)
print(g.country)

import numpy as np
import matplotlib.pyplot as plt

def plot_eye(waveform, samples_per_ui, num_ui=2):
    ui_len = samples_per_ui * num_ui
    num_eyes = len(waveform) // ui_len
    eye_data = waveform[:num_eyes * ui_len].reshape(num_eyes, ui_len)

    plt.figure(figsize=(8, 5))
    for trace in eye_data:
        plt.plot(trace, color='green', alpha=0.05, linewidth=0.5)

    plt.title("Eye Diagram")
    plt.xlabel("Samples (UI)")
    plt.ylabel("Amplitude (V)")
    plt.grid(True)
    plt.tight_layout()
    #plt.savefig("eye_diagram.png", dpi=150)
    plt.show()

# ---- GENERATE FAKE WAVEFORM TO TEST ----
samples_per_ui = 100
num_bits = 500
t = np.linspace(0, num_bits, num_bits * samples_per_ui)
bits = np.random.randint(0, 2, num_bits)
waveform = np.repeat(bits, samples_per_ui).astype(float)
waveform += np.random.normal(0, 0.05, len(waveform))  # add noise

# ---- CALL THE FUNCTION ----
plot_eye(waveform, samples_per_ui)

import serial
import pandas as pd 
import matplotlib.pyplot as plt

ser = serial.Serial('/dev/ttyUSB0', 9600)

df = {'distancia' : [],  "duracao": []}
dists = [10, 15, 22, 42, 60, 100, 131, 167, 193, 270]

for dist in dists:
    input(f"Enter para comecar a coletar para {dist}. ")
    for _ in range(100):
        dt = int(ser.readline()[:-2])
        print(_, dt)
        df['distancia'].append(dist)
        df["duracao"].append(dt)
df = pd.DataFrame(df)
df.to_csv('./dist.csv')

plt.plot(df['duracao'], df['distancia'], "*")
plt.show()
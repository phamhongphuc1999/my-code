import matplotlib.pyplot as plt
import matplotlib.colors as colors

def convert(num: str) -> float:
  return float(num)

file1 = open('result_100.txt', 'r')
lines = file1.readlines()
count = 0
data = []
for line in lines:
  count += 1
  a_line = line.strip().split(',')
  _len = len(a_line)
  data.append(list(map(convert, a_line[0:_len - 1])))
file1.close()

colors_list = ['#fff33b', '#fdc70c', '#f3903f', '#ed683c', '#e93e3a']
cmap = colors.ListedColormap(colors_list)

plt.imshow(data, cmap=cmap, vmin=0, vmax=100, extent=[0, 30, 0, 30])
cbar = plt.colorbar(ticks=[0, 20, 40, 60, 80, 100])
plt.title("2D Heat Map")
plt.show()
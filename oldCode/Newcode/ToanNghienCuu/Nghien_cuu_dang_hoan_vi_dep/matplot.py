import matplotlib.pyplot as plt
import math
# Tạo list X và Y
X = [1, 2, 3]  # Tọa độ trên trục x
Y = [2688, 18816, 18816]  # Tọa độ trên trục y
s = sum(Y)
Y = [round(y / s,2) for y in Y]

# Vẽ đồ thị với 3 điểm
plt.scatter(X, Y, color='red', marker='o')
plt.xlabel('Nτ')
plt.ylabel('Частота')
#plt.title('Đồ thị với 3 điểm tại (0,0)')
plt.grid(True)

# Vẽ các điểm nối vào nhau
plt.plot(X, Y, color='blue', linestyle='-')

# Sửa độ chia nhỏ nhất của trục x và trục y
plt.xticks(ticks=X, labels=X)
plt.yticks(ticks=Y, labels=Y)

plt.show()

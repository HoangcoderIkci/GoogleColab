import numpy as np

# Giả sử row1 và row2 là hai mảng NumPy
row1 = np.array([1, 2, 3])
row2 = np.array([4, 5, 6])

# Nối chúng lại
combined = np.concatenate((row1, row2))
mt = np.zeros((3, 6), dtype=int)
mt[0] = combined
print(mt)

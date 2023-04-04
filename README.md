# Douglas-Peucker

### This project implements Douglas-Peucker algorithm to reduce the complexity of the curve, further able to be applied in image processing, simplifying the path of the robotic arm, etc.

1. Original curve: [Contour.txt](https://github.com/Chen-Si-An/Douglas-Peucker/blob/main/Contour.txt) (4980 points)

![Image](https://github.com/Chen-Si-An/Douglas-Peucker/blob/main/Contour.jpg)

After employing Douglas-Peucker algorithm, the results are shown as following, where ε indicates the distance threshold:

2. ε = 0.005: [Contour_0.005.txt](https://github.com/Chen-Si-An/Douglas-Peucker/blob/main/Contour_0.005.txt) (2138 points)

![Image](https://github.com/Chen-Si-An/Douglas-Peucker/blob/main/Contour_0.005.jpg)

3. ε = 0.01: [Contour_0.01.txt](https://github.com/Chen-Si-An/Douglas-Peucker/blob/main/Contour_0.01.txt) (1580 points)

![Image](https://github.com/Chen-Si-An/Douglas-Peucker/blob/main/Contour_0.01.jpg)

4. ε = 0.03: [Contour_0.03.txt](https://github.com/Chen-Si-An/Douglas-Peucker/blob/main/Contour_0.03.txt) (111 points)

![Image](https://github.com/Chen-Si-An/Douglas-Peucker/blob/main/Contour_0.03.jpg)

**According to above results, we can readily observe how the curve is being simplified through Douglas-Peucker algorithm.**

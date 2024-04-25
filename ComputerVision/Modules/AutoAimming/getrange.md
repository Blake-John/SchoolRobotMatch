要得到纯色图片的颜色阈值，可以使用以下步骤：

1. 读取纯色图片。你可以使用 OpenCV 的 `imread()` 函数来加载图片。

```python
import cv2

# 读取纯色图片
image = cv2.imread('solid_color.jpg')
```

2. 将图片转换为 HSV 颜色空间。HSV 颜色空间更适合处理颜色信息，因为它可以将亮度（Value）和饱和度（Saturation）与颜色（Hue）分开。

```python
# 转换为 HSV 颜色空间
hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
```

3. 计算颜色的平均值。遍历图像的所有像素，并计算像素值的平均值。

```python
# 计算颜色的平均值
average_color = hsv_image.mean(axis=0).mean(axis=0)
```

4. 根据平均颜色创建阈值范围。你可以根据需要调整阈值范围的大小。

```python
# 创建颜色阈值范围
threshold = 20  # 阈值范围大小
lower_color = (average_color[0] - threshold, average_color[1] - threshold, average_color[2] - threshold)
upper_color = (average_color[0] + threshold, average_color[1] + threshold, average_color[2] + threshold)
```

5. 应用颜色阈值，提取纯色区域。

```python
# 创建掩膜，根据颜色阈值将图像分割为黑白二值图像
mask = cv2.inRange(hsv_image, lower_color, upper_color)

# 应用掩膜到原始图像
result = cv2.bitwise_and(image, image, mask=mask)
```

最后，你可以通过 `imshow()` 函数显示原始图像和提取的纯色区域。

请注意，这些步骤是基于假设输入图片是纯色的。如果图片中有噪点或变化较大的颜色，则可能需要进行一些额外的处理步骤来提取出所需的颜色。
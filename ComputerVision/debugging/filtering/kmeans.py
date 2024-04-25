import numpy as np
import cv2

def preprocess (img) :
    img = cv2.pyrMeanShiftFiltering (img, 30, 10)
    return img

def quantize_colors(image, k=8):
    # 将图像转换为 RGB 格式
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    
    # 将图像数据转换为二维数组
    pixels = image.reshape((-1, 3))
    
    # 将图像数据转换为 float32 类型
    pixels = np.float32(pixels)
    
    # 定义停止条件
    criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 20, 0.001)
    
    # 运行 K-means 聚类算法
    _, labels, centers = cv2.kmeans(pixels, k, None, criteria, 10, cv2.KMEANS_RANDOM_CENTERS)
    
    # 将每个像素点的颜色替换为对应聚类中心的颜色
    centers = np.uint8(centers)
    quantized_image = centers[labels.flatten()]
    
    # 将一维数组转换为图像矩阵
    quantized_image = quantized_image.reshape(image.shape)
    
    return cv2.cvtColor(quantized_image, cv2.COLOR_RGB2BGR)

# 读取图像
image = cv2.imread('./2.jpg')

# 对图像进行颜色量化，将颜色减少到 4 种
quantized_image = quantize_colors(image, k=20)
shift_before_quantized = quantize_colors (preprocess (image), k = 15)
# 显示原始图像和颜色量化后的图像
cv2.imshow('Original Image', image)
cv2.imshow('Quantized Image', quantized_image)
cv2.imshow('Shift_Quantized Image', shift_before_quantized)

while cv2.waitKey (20) != 27 :
    pass
cv2.destroyAllWindows()


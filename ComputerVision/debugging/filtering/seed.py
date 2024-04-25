import cv2
import numpy as np

def region_growing(image, seed):
    # 创建一个和原始图像大小一样的掩膜图像，用于标记生长区域
    mask = np.zeros_like(image, dtype=np.uint8)
    
    # 设置种子点的颜色值
    seed_color = image[seed[1], seed[0]]
    
    # 定义生长的条件：相邻像素的颜色与种子点的颜色相似
    tolerance = 30
    
    # 初始化队列，用于存放待生长的像素点
    queue = []
    queue.append(seed)
    
    # 循环直到队列为空
    while queue:
        # 弹出队列中的第一个像素点
        current_point = queue.pop(0)
        
        # 标记当前像素点为已生长区域
        mask[current_point[1], current_point[0]] = 255
        
        # 检查当前像素点的邻域像素
        for i in range(-1, 2):
            for j in range(-1, 2):
                # 获取邻域像素的坐标
                neighbor_x = current_point[0] + i
                neighbor_y = current_point[1] + j
                
                # 检查邻域像素是否在图像范围内
                if 0 <= neighbor_x < image.shape[1] and 0 <= neighbor_y < image.shape[0]:
                    # 检查邻域像素是否未被访问且颜色与种子点颜色相似
                    if mask[neighbor_y, neighbor_x] == 0 and np.all(np.abs(image[neighbor_y, neighbor_x] - seed_color) < tolerance):
                        # 将邻域像素添加到队列中，准备生长
                        queue.append((neighbor_x, neighbor_y))
    
    return mask

# 读取图像
image = cv2.imread('./2.jpg')

# 选择种子点，这里随机选择图像中的一个像素点作为种子点
seed_point = (100, 100)

# 进行区域生长，获取生长后的区域掩膜
segmented_image = region_growing(image, seed_point)

# 将生长后的区域掩膜应用到原始图像上
result_image = cv2.bitwise_and(image, image, mask=segmented_image)

# 显示原始图像和图像分割结果
cv2.imshow('Original Image', image)
cv2.imshow('Segmented Image', result_image)
cv2.waitKey(0)
cv2.destroyAllWindows()

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

Mat quantizeColors(Mat image, int k) {
    // 将图像转换为一维向量
    Mat pixels = image.reshape(1, image.rows * image.cols);

    // 转换为浮点型
    pixels.convertTo(pixels, CV_32F);

    // 设置K-Means聚类的参数
    TermCriteria criteria(TermCriteria::EPS + TermCriteria::MAX_ITER, 100, 0.2);
    Mat labels, centers;
    kmeans(pixels, k, labels, criteria, 1, KMEANS_RANDOM_CENTERS, centers);

    // 将每个像素的颜色替换为对应的聚类中心的颜色
    Mat segmented_image = Mat::zeros(image.size(), image.type());
    for (int i = 0; i < image.rows * image.cols; ++i) {
        int cluster_idx = labels.at<int>(i);
        segmented_image.at<Vec3b>(i) = centers.at<Vec3f>(cluster_idx);
    }

    return segmented_image;
}

int main() {
    // 读取图像
    Mat image = imread("../15.jpg");
	cv::pyrMeanShiftFiltering (image, image, 30, 10);

    if (image.empty()) {
        cout << "Could not open or find the image!" << endl;
        return -1;
    }

    // 指定要减少的颜色数量
    int k = 20;

    // 进行颜色量化
    Mat quantized_image = quantizeColors(image, k);

    // 显示结果
    imshow("Original Image", image);
    imshow("Quantized Image", quantized_image);

	while (cv::waitKey (20) != 27);

    return 0;
}

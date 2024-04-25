#include "yolo.h"
#include <opencv2/dnn/dnn.hpp>

/**
 * @brief Construct a new Yolo object
 * 
 * @param modelpath ONNX模型路径
 */
Yolo::Yolo (std::string modelpath) {
    this->net = cv::dnn::readNetFromONNX (modelpath);
		// this->net = cv::dnn::readNetFromDarknet (modelpath);
}

// cv::Mat Yolo::forward ()
// {
//     cv::Mat out = this->net.forward ();
//     cv::Mat output (out.size[1], out.size[2], CV_32F, out.ptr<float> ());
//     /*
//     the result is the array of 25200 bboxes
//     for each bboxes, the structure is :
//     {x, y, width, height, confidence, class0 score, class1 score, ..., class8 score}
//     */
//     return output;
// }

// Pred Yolo::getBboxes (cv::Mat output, int width, int height)
// {
//     std::vector <cv::Rect> bboxes;
//     std::vector <float> confidences;
//     float x_factor = width / 640.0;
//     float y_factor = height / 640.0;

//     for (int i = 0; i < output.rows; i++)
//     {
//         float confi = output.at<float> (i, 4);
//         if (confi < 0.85)
//         {
//             continue;
//         }
//         float ocx = output.at<float> (i, 0);
//         float ocy = output.at<float> (i, 1);
//         float ow = output.at<float> (i, 2);
//         float oh = output.at<float> (i, 3);

//         int cx = (ocx - ow * 0.5) * x_factor;
//         int cy = (ocy - oh * 0.5) * y_factor;
//         int w = ow * x_factor;
//         int h = oh * y_factor;

//         cv::Rect bbox (cx, cy, w, h);
//         bboxes.push_back (bbox);
//         confidences.push_back (confi);
//     }
//     Pred pred;
//     pred.bboxes = bboxes;
//     pred.confidences = confidences;

//     return pred;
// }

// std::vector <cv::Rect> Yolo::NMS (Pred pred)
// {
//     std::vector <int> indices;
//     cv::dnn::NMSBoxes (pred.bboxes, pred.confidences, 0.8, 0.8, indices);
//     std::vector <cv::Rect> result;
//     for (int i = 0; i < indices.size (); i++)
//     {
//         result.push_back (pred.bboxes[indices[i]]);
//     }

//     return result;
// }

// void Yolo::detect (cv::Mat img, std::vector <cv::Rect> &result)
// {
//     // set the input img and forward
//     cv::Mat blob = cv::dnn::blobFromImage (img, 1 / 255.0, cv::Size (640, 640), cv::Scalar (), true, false);
//     this->net.setInput (blob);
//     cv::Mat out = forward ();
//     Pred predi = getBboxes (out, img.cols, img.rows);
//     result = NMS (predi);
// }


/**
 * @brief yolo 神经网络的检测函数，为了减少资源占用，将检测的函数合并成一个，若是需要分步的模块，可见 `yolo.cpp`。
 * 大致思路为 设置输入图像，前向推理，过滤bbox，使用 NMS 获取置信度最高的bbox
 * 
 * @param img 输入的用于检测目标的图像，任意大小，1-3-4 颜色通道均可
 * @param result 检测结果为引用，传出 目标检测框 ，检测框的置信度 ，目标分类id。result 为一个 `结构` ，声明于 `yolo.h` @ref `Result`
 */
void Yolo::Detect (cv::Mat img, std::vector <Result> &result)
{
    // set the input img and forward
    cv::Mat blob = cv::dnn::blobFromImage (img, 1 / 255.0, cv::Size (640, 640), cv::Scalar (), true, false);
    this->net.setInput (blob);
    cv::Mat out = this->net.forward ();
    cv::Mat output (out.size[1], out.size[2], CV_32F, out.ptr<float> ());
    /*
    the result is the array of 25200 bboxes
    for each bboxes, the structure is :
    {x, y, width, height, confidence, class0 score, class1 score, ..., class8 score}
    */

    // get the bboxes
    std::vector <cv::Rect> bboxes;
    std::vector <float> confidences;
    std::vector <int> classids;
    float x_factor = img.cols / 640.0;
    float y_factor = img.rows / 640.0;

    for (int i = 0; i < output.rows; i++)
    {
        float confi = output.at<float> (i, 4); // get the confidence
        // ignore the confidence bellow 0.8
        if (confi < 0.8)
        {
            continue;
        }

        // get the center, width and height of the bbox
        float ocx = output.at<float> (i, 0);
        float ocy = output.at<float> (i, 1);
        float ow = output.at<float> (i, 2);
        float oh = output.at<float> (i, 3);

        // convert the bbox from the img_size 640 to the normal size
        int cx = (ocx - ow * 0.5) * x_factor;
        int cy = (ocy - oh * 0.5) * y_factor;
        int w = ow * x_factor;
        int h = oh * y_factor;

        // get the iterator of the output
        auto class_score = output.ptr<int>(i);
        // get the max_score index through the iterator got above 
        int classid = std::max_element (class_score + 5, class_score + 13) - (class_score + 5);
        
        cv::Rect bbox (cx, cy, w, h);
        bboxes.push_back (bbox);
        confidences.push_back (confi);
        classids.push_back (classid);
    }

    // NMS
    std::vector <int> indices;
    cv::dnn::NMSBoxes (bboxes, confidences, 0.25, 0.45, indices);
    for (int i = 0; i < indices.size (); i++)
    {
        Result res = {bboxes[indices[i]], confidences[indices[i]], classids[indices[i]]};
        result.push_back (res);
    }
}

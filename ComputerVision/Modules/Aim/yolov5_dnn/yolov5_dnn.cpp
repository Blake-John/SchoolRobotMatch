#include "yolov5_dnn.h"

YoloV5Detector::YoloV5Detector (std::string onnxpath)
{
    this->net = cv::dnn::readNetFromONNX (onnxpath);
    // net.setPreferableBackend (cv::dnn::DNN_BACKEND_CUDA);
    // net.setPreferableTarget (cv::dnn::DNN_TARGET_CUDA);
}

void YoloV5Detector::detect (cv::Mat frame, std::vector <DetectResult> &result)
{
    // 设置输入的大小
    int w = frame.cols;
    int h = frame.rows;
    // cv::Mat img;
    // frame.copyTo (img);

    // 获取拉伸的比例
    float x_factor = w / 640.0;
    float y_factor = h / 640.0;

    // 将图像转化成 dnn 可以传入的图像， 然后前向传播，推理
    cv::Mat blob = cv::dnn::blobFromImage (frame, 1 / 255.0, cv::Size (640, 640), cv::Scalar (), true, false);
    this->net.setInput (blob);
    cv::Mat pred = this->net.forward ();

    // rows : pred.size[1] or pred.size ().width
    // cols : pred.size[2] or pred.size ().height
    cv::Mat det_output (pred.size[1], pred.size[2], CV_32F, pred.ptr<float> ());
    /*
    the result is the array of 25200 bboxes
    for each bboxes, the structure is :
    {x, y, width, height, confidence, class0 score, class1 score, ..., class8 score}
    */

   // 遍历所有结果，将 confidence 大于 confi_thre 的 bbox 取出
    // float confi_thre = 0.8;
    std::vector <cv::Rect> bboxes;
    // std::vector <int> classids;
    std::vector <float> confies;
    for (int i = 0; i < det_output.rows; i++)
    {
        float confidence = det_output.at<float> (i, 4);
        if (confidence < 0.9)
        {
            continue;
        }
        float ocx = det_output.at<float> (i, 0);
        float ocy = det_output.at<float> (i, 1);
        float ow = det_output.at<float> (i, 2);
        float oh = det_output.at<float> (i, 3);
        int cx = (ocx - 0.5 * ow) * x_factor;
        int cy = (ocy - 0.5 * oh) * y_factor;
        int w = ow * x_factor;
        int h = oh * y_factor;

        cv::Rect box;
        box.x = cx;
        box.y = cy;
        box.width = w;
        box.height = h;

        bboxes.push_back (box);
        // classids.push_back (classid);
        confies.push_back (confidence);
        // // 获取每一类的score
        // // cv::Mat classes_scores = det_output.row (i).colRange (5, 13);
        // std::vector <float> classes_scores;
        // for (int j = 5; j < 12; j++)
        // {
        //     classes_scores.push_back (det_output.at<float> (i, j));
        // }

        // int classid;
        // double score;
        // // minMaxLoc (classes_scores, 0, score, 0, classIDPoint);
        // classid = std::max_element (classes_scores.begin (), classes_scores.end ()) - classes_scores.begin ();

        // if (score > this->score_thre)
        // {
        //     float ocx = det_output.at<float> (i, 0);
        //     float ocy = det_output.at<float> (i, 1);
        //     float ow = det_output.at<float> (i, 2);
        //     float oh = det_output.at<float> (i, 3);
        //     int cx = (ocx - 0.5 * ow) * x_factor;
        //     int cy = (ocy - 0.5 * oh) * y_factor;
        //     int w = ow * x_factor;
        //     int h = oh * y_factor;

        //     cv::Rect box;
        //     box.x = cx;
        //     box.y = cy;
        //     box.width = w;
        //     box.height = h;

        //     bboxes.push_back (box);
        //     classids.push_back (classid);
        //     confies.push_back (confidence);

        // }
    }

    // NMS 去除多余 bbox
    std::vector <int> indexes;
    cv::dnn::NMSBoxes (bboxes, confies, 0.25, 0.45, indexes);
    for (int i = 0; i < indexes.size (); i++)
    {
        DetectResult res;
        int index = indexes[i];
        // int idx = classids[index];
        res.bbox = bboxes[index];
        // res.classid = idx;
        res.confi = confies[index];

        result.push_back (res);
    }    
}

void YoloV5Detector::draw (cv::Mat img, std::vector <DetectResult> res)
{
    for (DetectResult dr : res)
    {
        cv::Rect box = dr.bbox;
        cv::rectangle (img, box, cv::Scalar (255, 255, 0), 2);
    }
}
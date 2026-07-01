/**
 * ImageWatchPro 测试代码
 *
 * 本程序用于测试 ImageWatchPro 插件的功能，包含各种 cv::Mat 类型的创建和操作。
 * 使用方法：
 *   1. 确保已安装 OpenCV
 *   2. 使用 CMake 构建项目
 *   3. 在 Visual Studio 中启动调试
 *   4. 在断点处打开 Debug > Windows > ImageWatchPro 查看图像
 */

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

#include <opencv2/opencv.hpp>
#include <array>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::string findImagePath(const std::string& filename) {
    const std::vector<std::string> candidates = {
        "images/" + filename,
        "../images/" + filename,
        "../../images/" + filename,
        "../../../images/" + filename,
        "../../../../images/" + filename,
        "../../../../../test-cpp/images/" + filename,
        "../test-cpp/images/" + filename
    };

    for (const auto& path : candidates) {
        FILE* fp = nullptr;
#ifdef _WIN32
        fopen_s(&fp, path.c_str(), "rb");
#else
        fp = std::fopen(path.c_str(), "rb");
#endif
        if (fp != nullptr) {
            std::fclose(fp);
            return path;
        }
    }

    throw std::runtime_error("Cannot find image: " + filename);
}

cv::Mat toGray(const cv::Mat& image) {
    if (image.channels() == 1) {
        return image.clone();
    }

    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);
    return gray;
}

cv::Mat thresholdRange(const cv::Mat& gray, int low, int high) {
    cv::Mat mask;
    cv::inRange(gray, cv::Scalar(low), cv::Scalar(high), mask);
    return mask;
}

std::vector<std::vector<cv::Point>> findCircleContours(const cv::Mat& gray) {/*
    cv::Mat blurred;
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0.0);*/

    cv::Mat binary;
    cv::threshold(gray, binary, 80, 255, cv::THRESH_BINARY_INV);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::vector<std::vector<cv::Point>> circleContours;
    for (const auto& contour : contours) {
        const double area = cv::contourArea(contour);
        const double perimeter = cv::arcLength(contour, true);
        if (area <= 20.0 || perimeter <= 0.0) {
            continue;
        }

        const double circularity = 4.0 * CV_PI * area / (perimeter * perimeter);
        if (circularity >= 0.70) {
            circleContours.push_back(contour);
        }
    }

    return circleContours;
}

/**
 * 测试 1: 灰度图像 (CV_8UC1)
 */
cv::Mat createGrayscaleImage() {
    // 创建 256x256 的灰度渐变图像
    cv::Mat gray(2160, 3840, CV_8UC1);

    for (int y = 0; y < gray.rows; y++) {
        for (int x = 0; x < gray.cols; x++) {
            gray.at<uchar>(y, x) = static_cast<uchar>(x);
        }
    }

    return gray;  // 在此处设置断点，查看灰度图像
}

/**
 * 测试 2: BGR 彩色图像 (CV_8UC3)
 */
cv::Mat createColorImage() {
    // 创建 480x640 的彩色测试图像
    cv::Mat color(2160, 3840, CV_8UC3);

    for (int y = 0; y < color.rows; y++) {
        for (int x = 0; x < color.cols; x++) {
            // BGR 格式
            color.at<cv::Vec3b>(y, x)[0] = static_cast<uchar>(x % 256);        // B
            color.at<cv::Vec3b>(y, x)[1] = static_cast<uchar>(y % 256);        // G
            color.at<cv::Vec3b>(y, x)[2] = static_cast<uchar>((x + y) % 256);  // R
        }
    }

    return color;  // 在此处设置断点，查看彩色图像
}

/**
 * 测试 3: BGRA 图像 (CV_8UC4)
 */
cv::Mat createBGRAImage() {
    cv::Mat bgra(2160, 3840, CV_8UC4);

    for (int y = 0; y < bgra.rows; y++) {
        for (int x = 0; x < bgra.cols; x++) {
            bgra.at<cv::Vec4b>(y, x)[0] = 255;                              // B
            bgra.at<cv::Vec4b>(y, x)[1] = static_cast<uchar>(y % 256);      // G
            bgra.at<cv::Vec4b>(y, x)[2] = static_cast<uchar>(x % 256);      // R
            bgra.at<cv::Vec4b>(y, x)[3] = 128;                              // A (半透明)
        }
    }

    return bgra;  // 在此处设置断点，查看 BGRA 图像
}

/**
 * 测试 4: 16 位无符号图像 (CV_16UC1)
 */
cv::Mat create16UImage() {
    cv::Mat img16u(2160, 3840, CV_16UC1);

    for (int y = 0; y < img16u.rows; y++) {
        for (int x = 0; x < img16u.cols; x++) {
            // 值范围 0-65535
            img16u.at<ushort>(y, x) = static_cast<ushort>((x * y) % 65536);
        }
    }

    return img16u;  // 在此处设置断点，查看 16 位图像
}

/**
 * 测试 5: 32 位浮点图像 (CV_32FC1)
 */
cv::Mat create32FImage() {
    cv::Mat img32f(2160, 3840, CV_32FC1);

    for (int y = 0; y < img32f.rows; y++) {
        for (int x = 0; x < img32f.cols; x++) {
            // 值范围 0.0 - 1.0
            img32f.at<float>(y, x) = static_cast<float>(x * y) / (2160.0f * 3840.0f);
        }
    }

    return img32f;  // 在此处设置断点，查看浮点图像
}

/**
 * 测试 11: 亚像素轮廓 - vector<Point> (整数坐标)
 */
std::vector<cv::Point> createContourInt() {
    // 生成一个矩形轮廓（整数坐标），四个顶点
    std::vector<cv::Point> contour;
    contour.emplace_back(200, 200);
    contour.emplace_back(3640, 200);
    contour.emplace_back(3640, 1960);
    contour.emplace_back(200, 1960);
    return contour;  // 在此处设置断点，查看整数轮廓
}

/**
 * 测试 12: 亚像素轮廓 - vector<Point2f> (单精度浮点坐标)
 */
std::vector<cv::Point2f> createContourFloat() {
    // 生成一个亚像素精度的圆形轮廓（60个点）
    std::vector<cv::Point2f> contour;
    const float cx = 1920.5f, cy = 1080.7f, r = 300.3f;
    const int n = 60;
    for (int i = 0; i < n; i++) {
        float angle = static_cast<float>(i * 2.0 * CV_PI / n);
        contour.emplace_back(
            cx + r * std::cos(angle),
            cy + r * std::sin(angle)
        );
    }
    return contour;  // 在此处设置断点，查看单精度亚像素轮廓
}

/**
 * 测试 13: 亚像素轮廓 - vector<Point2d> (双精度浮点坐标)
 */
std::vector<cv::Point2d> createContourDouble() {
    // 生成一个椭圆轮廓（双精度），所有点在 3840x2160 范围内
    std::vector<cv::Point2d> contour;
    const double cx = 1920.0, cy = 1080.0;
    const double a = 800.0, b = 400.0;  // 长短轴
    const int n = 80;
    for (int i = 0; i < n; i++) {
        double t = static_cast<double>(i) * 2.0 * CV_PI / n;
        double x = cx + a * std::cos(t);
        double y = cy + b * std::sin(t);
        contour.emplace_back(x, y);
    }
    return contour;  // 在此处设置断点，查看双精度亚像素轮廓
}

/**
 * 测试 14: 多轮廓 - vector<vector<Point>> (整数坐标，120个子轮廓)
 */
std::vector<std::vector<cv::Point>> createMultiContourInt() {
    std::vector<std::vector<cv::Point>> contours;
    const int numContours = 120;
    const int imgW = 3840, imgH = 2160;

    for (int i = 0; i < numContours; i++) {
        std::vector<cv::Point> contour;
        // 在网格上生成矩形轮廓
        int gridCols = 12;
        int gridRows = numContours / gridCols;
        int col = i % gridCols;
        int row = i / gridCols;
        int cellW = imgW / gridCols;
        int cellH = imgH / gridRows;
        int x0 = col * cellW + 20;
        int y0 = row * cellH + 20;
        int x1 = (col + 1) * cellW - 20;
        int y1 = (row + 1) * cellH - 20;

        contour.emplace_back(x0, y0);
        contour.emplace_back(x1, y0);
        contour.emplace_back(x1, y1);
        contour.emplace_back(x0, y1);
        contours.push_back(contour);
    }

    return contours;  // 在此处设置断点，查看整数多轮廓
}

/**
 * 测试 15: 多轮廓 - vector<vector<Point2f>> (单精度浮点，120个子轮廓)
 */
std::vector<std::vector<cv::Point2f>> createMultiContourFloat() {
    std::vector<std::vector<cv::Point2f>> contours;
    const int numContours = 120;
    const float imgW = 3840.0f, imgH = 2160.0f;

    for (int i = 0; i < numContours; i++) {
        std::vector<cv::Point2f> contour;
        // 生成圆形轮廓，分布在图像上
        int gridCols = 12;
        int gridRows = numContours / gridCols;
        int col = i % gridCols;
        int row = i / gridCols;
        float cellW = imgW / gridCols;
        float cellH = imgH / gridRows;
        float cx = col * cellW + cellW / 2.0f;
        float cy = row * cellH + cellH / 2.0f;
        float radius = std::min(cellW, cellH) / 2.0f - 20.0f;

        const int n = 32;  // 每个圆 32 个点
        for (int j = 0; j < n; j++) {
            float angle = static_cast<float>(j * 2.0 * CV_PI / n);
            contour.emplace_back(
                cx + radius * std::cos(angle),
                cy + radius * std::sin(angle)
            );
        }
        contours.push_back(contour);
    }

    return contours;  // 在此处设置断点，查看单精度多轮廓
}

/**
 * 测试 16: 多轮廓 - vector<vector<Point2d>> (双精度浮点，120个子轮廓)
 */
std::vector<std::vector<cv::Point2d>> createMultiContourDouble() {
    std::vector<std::vector<cv::Point2d>> contours;
    const int numContours = 120;
    const double imgW = 3840.0, imgH = 2160.0;

    for (int i = 0; i < numContours; i++) {
        std::vector<cv::Point2d> contour;
        // 生成椭圆轮廓，随机长短轴
        int gridCols = 12;
        int gridRows = numContours / gridCols;
        int col = i % gridCols;
        int row = i / gridCols;
        double cellW = imgW / gridCols;
        double cellH = imgH / gridRows;
        double cx = col * cellW + cellW / 2.0;
        double cy = row * cellH + cellH / 2.0;
        double a = cellW / 2.0 - 30.0;  // 长轴
        double b = cellH / 2.0 - 30.0;  // 短轴
        // 交替椭圆方向
        if (i % 2 == 0) {
            std::swap(a, b);
        }

        const int n = 48;  // 每个椭圆 48 个点
        for (int j = 0; j < n; j++) {
            double t = static_cast<double>(j) * 2.0 * CV_PI / n;
            double x = cx + a * std::cos(t);
            double y = cy + b * std::sin(t);
            contour.emplace_back(x, y);
        }
        contours.push_back(contour);
    }

    return contours;  // 在此处设置断点，查看双精度多轮廓
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);  // 设置控制台输出为 UTF-8 编码
#endif

    std::cout << "=== ImageWatchPro Test Program ===" << std::endl;
    std::cout << "请在各个函数的 return 语句处设置断点" << std::endl;
    std::cout << "然后在 ImageWatchPro 面板中查看 cv::Mat 变量" << std::endl;
    std::cout << "====================================" << std::endl;

    // 测试 1: 灰度图像
    cv::Mat gray = createGrayscaleImage();
    std::cout << "[OK] 创建灰度图像: " << gray.cols << "x" << gray.rows << std::endl;

    // 测试 2: 彩色图像
    cv::Mat color = createColorImage();
    std::cout << "[OK] 创建彩色图像: " << color.cols << "x" << color.rows << std::endl;

    // 测试 3: BGRA 图像
    cv::Mat bgra = createBGRAImage();
    std::cout << "[OK] 创建 BGRA 图像: " << bgra.cols << "x" << bgra.rows << std::endl;

    // 测试 4: 16 位图像
    cv::Mat img16u = create16UImage();
    std::cout << "[OK] 创建 16 位图像: " << img16u.cols << "x" << img16u.rows << std::endl;

    // 测试 5: 浮点图像
    cv::Mat img32f = create32FImage();
    std::cout << "[OK] 创建浮点图像: " << img32f.cols << "x" << img32f.rows << std::endl;

    // 图片测试: smarties.png 转灰度
    cv::Mat smarties, smartiesGray;
    smarties = cv::imread(findImagePath("smarties.png"));
    cv::cvtColor(smarties, smartiesGray, cv::COLOR_BGR2GRAY);
    std::cout << "[OK] smarties.png -> gray: " << smartiesGray.cols << "x" << smartiesGray.rows << std::endl;

    // 图片测试: defect.png 两个灰度范围 Mask
    cv::Mat defect = cv::imread(findImagePath("defect.png"), cv::IMREAD_GRAYSCALE);
    cv::Mat defectMaskDark;
    cv::inRange(defect, 0, 30, defectMaskDark);
    cv::Rect roi(56, 59, 130, 130);
    cv::Mat imgRoi = defect(roi).clone();
    cv::Mat roiMask;
    cv::inRange(imgRoi, 80, 140, roiMask);
    cv::Mat defectMask = cv::Mat::zeros(defect.size(), CV_8UC1);
    roiMask.copyTo(defectMask(roi));
    std::cout << "[OK] defect.png masks: 0-30 and 80-140" << std::endl;

    // 图片测试: tf-card.png 灰度范围 Mask
    cv::Mat tfCard, tfCardMask;
    tfCard = cv::imread(findImagePath("tf-card.png"), 0);
    cv::threshold(tfCard, tfCardMask, 150, 255, cv::THRESH_BINARY);
    std::cout << "[OK] tf-card.png mask: 150-255" << std::endl;

    // 图片测试: circles.png 查找所有圆形轮廓
    cv::Mat circles = cv::imread(findImagePath("circles.png"), 0);
    cv::Mat circlesMask;
    cv::threshold(circles, circlesMask, 80, 500, cv::THRESH_BINARY_INV);
    std::vector<std::vector<cv::Point>> circleContours = findCircleContours(circles);
    std::cout << "[OK] circles.png circle contours: " << circleContours.size() << std::endl;

    // 测试 11: 整数轮廓
    std::vector<cv::Point> contourInt = createContourInt();
    std::cout << "[OK] 整数轮廓: " << contourInt.size() << " 个点" << std::endl;

    // 测试 12: 单精度亚像素轮廓
    std::vector<cv::Point2f> contourFloat = createContourFloat();
    std::cout << "[OK] 单精度亚像素轮廓: " << contourFloat.size() << " 个点" << std::endl;

    // 测试 13: 双精度亚像素轮廓
    std::vector<cv::Point2d> contourDouble = createContourDouble();
    std::cout << "[OK] 双精度亚像素轮廓: " << contourDouble.size() << " 个点" << std::endl;

    // 测试 14: 整数多轮廓
    std::vector<std::vector<cv::Point>> multiContourInt = createMultiContourInt();
    std::cout << "[OK] 整数多轮廓: " << multiContourInt.size() << " 个子轮廓" << std::endl;

    // 测试 15: 单精度多轮廓
    std::vector<std::vector<cv::Point2f>> multiContourFloat = createMultiContourFloat();
    std::cout << "[OK] 单精度多轮廓: " << multiContourFloat.size() << " 个子轮廓" << std::endl;

    // 测试 16: 双精度多轮廓
    std::vector<std::vector<cv::Point2d>> multiContourDouble = createMultiContourDouble();
    std::cout << "[OK] 双精度多轮廓: " << multiContourDouble.size() << " 个子轮廓" << std::endl;

    // 测试 17: cv::Point 类型变量
    cv::Point pointInt(100, 200);
    cv::Point2f pointFloat(150.5f, 250.7f);
    cv::Point2d pointDouble(300.123, 400.456);
    std::cout << "[OK] cv::Point: (" << pointInt.x << ", " << pointInt.y << ")" << std::endl;
    std::cout << "[OK] cv::Point2f: (" << pointFloat.x << ", " << pointFloat.y << ")" << std::endl;
    std::cout << "[OK] cv::Point2d: (" << pointDouble.x << ", " << pointDouble.y << ")" << std::endl;

    // 测试 18: cv::Rect 类型变量
    cv::Rect rectInt(50, 50, 200, 150);
    cv::Rect2f rectFloat(100.5f, 100.5f, 300.7f, 200.3f);
    cv::Rect2d rectDouble(150.123, 150.456, 400.789, 300.012);
    std::cout << "[OK] cv::Rect: (" << rectInt.x << ", " << rectInt.y << ", " << rectInt.width << ", " << rectInt.height << ")" << std::endl;
    std::cout << "[OK] cv::Rect2f: (" << rectFloat.x << ", " << rectFloat.y << ", " << rectFloat.width << ", " << rectFloat.height << ")" << std::endl;
    std::cout << "[OK] cv::Rect2d: (" << rectDouble.x << ", " << rectDouble.y << ", " << rectDouble.width << ", " << rectDouble.height << ")" << std::endl;

    // 测试 19: cv::RotatedRect 类型变量
    cv::RotatedRect rotatedRectInt(cv::Point2f(500, 400), cv::Size2f(300, 200), 30.0f);
    cv::RotatedRect rotatedRectFloat(cv::Point2f(1000.6f, 600.8f), cv::Size2f(400.2f, 150.0f), -45.0f);
    cv::RotatedRect rotatedRectDouble(cv::Point2f(1500.7, 800.9), cv::Size2f(250.5, 250.3), 0.0f);
    std::cout << "[OK] cv::RotatedRect1: center(" << rotatedRectInt.center.x << ", " << rotatedRectInt.center.y
              << "), size(" << rotatedRectInt.size.width << ", " << rotatedRectInt.size.height
              << "), angle(" << rotatedRectInt.angle << ")" << std::endl;
    std::cout << "[OK] cv::RotatedRect2: center(" << rotatedRectFloat.center.x << ", " << rotatedRectFloat.center.y
              << "), size(" << rotatedRectFloat.size.width << ", " << rotatedRectFloat.size.height
              << "), angle(" << rotatedRectFloat.angle << ")" << std::endl;
    std::cout << "[OK] cv::RotatedRect3: center(" << rotatedRectDouble.center.x << ", " << rotatedRectDouble.center.y
              << "), size(" << rotatedRectDouble.size.width << ", " << rotatedRectDouble.size.height
              << "), angle(" << rotatedRectDouble.angle << ")" << std::endl;

    // 测试 20: 数值数组变量（用于 Plot 功能）
    std::vector<int> vectorInt = {10, 25, 30, 45, 60, 55, 70, 85, 90, 100};
    std::vector<float> vectorFloat = {1.1f, 2.5f, 3.3f, 4.8f, 5.2f, 6.7f, 7.1f, 8.9f};
    std::vector<double> vectorDouble = {0.1, 0.5, 1.2, 2.8, 3.1, 4.5, 5.9, 7.3, 8.0, 9.5};

    std::array<int, 8> arrayInt = {100, 200, 150, 300, 250, 400, 350, 500};
    std::array<float, 8> arrayFloat = {1.5f, 3.2f, 2.8f, 4.1f, 3.9f, 5.5f, 4.7f, 6.3f};
    std::array<double, 8> arrayDouble = {0.5, 1.2, 0.8, 2.1, 1.9, 3.5, 2.7, 4.3};
    int rawArrayInt[8] = {8, 13, 21, 34, 55, 89, 144, 233};
    float rawArrayFloat[8] = {0.25f, 1.0f, 0.5f, 2.0f, 1.25f, 3.0f, 2.25f, 4.0f};
    double rawArrayDouble[8] = {-1.0, -0.2, 0.3, 1.1, 0.7, 1.8, 2.4, 2.1};

    // 一维 cv::Mat（行向量）
    cv::Mat mat1D = (cv::Mat_<double>(1, 10) << 1.0, 2.5, 3.0, 4.5, 5.0, 6.5, 7.0, 8.5, 9.0, 10.5);
    // 一维 cv::Mat（列向量）
    cv::Mat mat1DCol = (cv::Mat_<double>(10, 1) << 1.0, 2.5, 3.0, 4.5, 5.0, 6.5, 7.0, 8.5, 9.0, 10.5);

    std::cout << "[OK] std::vector<int>: " << vectorInt.size() << " elements" << std::endl;
    std::cout << "[OK] std::vector<float>: " << vectorFloat.size() << " elements" << std::endl;
    std::cout << "[OK] std::vector<double>: " << vectorDouble.size() << " elements" << std::endl;
    std::cout << "[OK] std::array<int>: " << arrayInt.size() << " elements" << std::endl;
    std::cout << "[OK] std::array<float>: " << arrayFloat.size() << " elements" << std::endl;
    std::cout << "[OK] std::array<double>: " << arrayDouble.size() << " elements" << std::endl;
    std::cout << "[OK] int raw array: " << _countof(rawArrayInt) << " elements" << std::endl;
    std::cout << "[OK] float raw array: " << _countof(rawArrayFloat) << " elements" << std::endl;
    std::cout << "[OK] double raw array: " << _countof(rawArrayDouble) << " elements" << std::endl;
    std::cout << "[OK] cv::Mat 1D: " << mat1D.cols << " elements" << std::endl;
    std::cout << "[OK] cv::Mat 1D Col: " << mat1DCol.rows << " elements" << std::endl;


    // cv::Mat 灰度转换
    cv::Mat img_gray;
    cv::cvtColor(color, img_gray, cv::COLOR_BGR2GRAY);

    // cv::Mat 浮点转换
    cv::Mat img_float;
    color.convertTo(img_float, CV_32FC3, 1.0 / 255.0);

    // cv::Mat_<T> 模板类型
    cv::Mat_<uchar> mat_template_gray = img_gray.clone();
    cv::Mat_<cv::Vec3b> mat_template_bgr = color.clone();
    cv::Mat_<cv::Vec3f> mat_template_float;
    img_float.copyTo(mat_template_float);

    std::cout << "[OK] cv::Mat gray: " << img_gray.cols << "x" << img_gray.rows << std::endl;
    std::cout << "[OK] cv::Mat float: " << img_float.cols << "x" << img_float.rows << std::endl;
    std::cout << "[OK] cv::Mat_<uchar>: " << mat_template_gray.cols << "x" << mat_template_gray.rows << std::endl;
    std::cout << "[OK] cv::Mat_<Vec3b>: " << mat_template_bgr.cols << "x" << mat_template_bgr.rows << std::endl;
    std::cout << "[OK] cv::Mat_<Vec3f>: " << mat_template_float.cols << "x" << mat_template_float.rows << std::endl;

    std::cout << "\n所有测试完成！" << std::endl;
    
    // 最终断点 - 所有变量都在作用域内
    // 在此处设置断点可以查看所有创建的图像
    return 0;
}


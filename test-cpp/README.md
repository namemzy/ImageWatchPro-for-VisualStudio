# ImageWatchPro test-cpp Demo

`test-cpp/` 是 ImageWatchPro 的公开 demo 和 smoke-test 项目，用于在 Visual Studio 调试时验证 `cv::Mat`、Mask、Contour、Geometry、Plot 和 Histogram 场景。

## 前提条件

- Visual Studio 2022 或更新版本
- CMake 3.20+
- OpenCV，并正确设置 `OpenCV_DIR`
- 已安装 ImageWatchPro VSIX

## 构建

```powershell
cd test-cpp
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
```

如 OpenCV 未被自动发现，可在配置时指定：

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DOpenCV_DIR="C:/opencv/build"
```

## 调试

1. 用 Visual Studio 打开生成的 `build/ImageWatchProTest.sln`。
2. 将 `image_watch_test` 设为启动项目。
3. 在 `main.cpp` 中标注“设置断点”的位置打断点。
4. 启动调试。
5. 程序暂停后打开 `Debug > Windows > ImageWatchPro`。
6. 查看 `cv::Mat`、Mask、轮廓、几何对象和数值序列。

## 覆盖场景

- 灰度、BGR、BGRA、16 位、32 位浮点图像
- 单通道 Mask
- 整数和浮点 OpenCV 轮廓
- 多轮廓
- `cv::Point`、`cv::Rect`、`cv::RotatedRect`
- `std::vector`、`std::array`、裸数组和一维 `cv::Mat` Plot 数据
- 单通道和多通道直方图测试素材

## 注意

Release 强优化可能导致局部变量被优化掉，调试器无法稳定读取。验证插件功能时建议先使用 Debug 配置。

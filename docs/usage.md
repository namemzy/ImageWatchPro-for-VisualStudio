# 使用指南

## 查看图像

在 Visual Studio 调试原生 C++ 程序时，断点暂停后打开 `Debug > Windows > ImageWatchPro`。支持的 `cv::Mat` 和 `cv::Mat_<T>` 变量会出现在 Locals 或 Watch 相关视图中。

## Mask 叠加

单通道图像可以作为 Mask 叠加到当前图像。默认颜色为红色，透明度为 50%。

## 轮廓和几何对象

Contour 视图用于查看 OpenCV 点、矩形、旋转矩形、单轮廓和多轮廓。整数点按像素中心显示，浮点点保持原始亚像素坐标。

## Plot 和直方图

Plot 视图用于查看一维数值序列。图像右键菜单可触发单通道或 B/G/R 通道直方图。

## 导出

导出会保存完整图像数据，并合成当前可见的 Mask、轮廓和点集。支持 PNG、BMP 和 TIFF。

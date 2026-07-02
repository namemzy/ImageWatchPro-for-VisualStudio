# ImageWatchPro for Visual Studio

ImageWatchPro 是一个面向 Visual Studio 2022/2026 的原生 C++ / OpenCV 调试可视化扩展。它让你在断点暂停时直接查看 `cv::Mat` 图像、Mask 叠加、轮廓/点集、OpenCV 几何对象、数值曲线、直方图和导出结果。

![ImageWatchPro 图标](docs/images/ImageWatchPro.png)

## 下载

请从 [GitHub Releases](https://github.com/namemzy/ImageWatchPro-for-VisualStudio/releases) 下载最新 VSIX。

当前预览版二进制文件名：`ImageWatchPro.Packaging.vsix`。

## 功能展示

- [x] `cv::Mat` / `cv::Mat_<T>` 图像查看
- [x] 单通道图像作为 Mask 叠加
- [x] OpenCV 轮廓、点集、矩形、旋转矩形
- [x] 数值折线图和散点图
- [x] 单通道灰度直方图和 B/G/R 通道直方图
- [x] 合成可见 Mask、轮廓、点集并导出 PNG/BMP/TIFF

## 快速开始

1. 安装 Visual Studio 2022 或 2026，并启用 C++ 桌面开发工作负载。
2. 从 Releases 下载 `ImageWatchPro.Packaging.vsix`。
3. 关闭 Visual Studio，运行 VSIX 安装器，然后重新打开 Visual Studio。
4. 启动一个原生 C++ / OpenCV 程序调试。
5. 在断点暂停后打开 `Debug > Windows > ImageWatchPro`。
6. 使用本仓库的 `test-cpp/` 作为 demo 和 smoke test。

## Demo / Smoke Test

```powershell
cd test-cpp
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
```

在 `main.cpp` 中带有“设置断点”提示的位置打断点，然后在 ImageWatchPro 窗口中查看变量。

## 开源协议

本仓库使用 MIT License。详情见 [LICENSE](LICENSE)。

## 反馈

请通过 GitHub Issues 提交 bug、功能建议、兼容性报告和文档问题。建议附带 Visual Studio 版本、Windows 版本、OpenCV 版本和最小复现代码。


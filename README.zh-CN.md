# ImageWatchPro for Visual Studio

ImageWatchPro 是一个面向 Visual Studio 2022/2026 的原生 C++ / OpenCV 调试可视化扩展。它让你在断点暂停时直接查看 `cv::Mat` 图像、Mask 叠加、轮廓/点集、OpenCV 几何对象、数值曲线、直方图和导出结果。

![ImageWatchPro 图标](docs/images/ImageWatchPro.png)

## 下载

请从 [GitHub Releases](https://github.com/namemzy/ImageWatchPro-for-VisualStudio/releases) 下载最新 VSIX。

当前预览版二进制文件名：`ImageWatchPro.Packaging.vsix`。

## 功能展示

| 功能 | 状态 |
| --- | --- |
| `cv::Mat` / `cv::Mat_<T>` 图像查看 | VSIX 二进制已支持 |
| 单通道图像作为 Mask 叠加 | VSIX 二进制已支持 |
| OpenCV 轮廓、点集、矩形、旋转矩形 | VSIX 二进制已支持 |
| 数值折线图和散点图 | VSIX 二进制已支持 |
| 单通道灰度直方图和 B/G/R 通道直方图 | VSIX 二进制已支持 |
| 合成可见 Mask、轮廓、点集并导出 PNG/BMP/TIFF | VSIX 二进制已支持 |

## 快速开始

1. 安装 Visual Studio 2022 或 2026，并启用 C++ 桌面开发工作负载。
2. 从 Releases 下载 `ImageWatchPro.Packaging.vsix`。
3. 关闭 Visual Studio，运行 VSIX 安装器，然后重新打开 Visual Studio。
4. 启动一个原生 C++ / OpenCV 程序调试。
5. 在断点暂停后打开 `Debug > Windows > ImageWatchPro`。
6. 使用本仓库的 `test-cpp/` 作为 demo 和 smoke test。

## Demo / Smoke Test

`test-cpp/` 同时是公开 demo 和手动验证项目，不再额外提供单独的 `demo/` 目录。

```powershell
cd test-cpp
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
```

在 `main.cpp` 中带有“设置断点”提示的位置打断点，然后在 ImageWatchPro 窗口中查看变量。

## 截图

真实 Visual Studio 界面截图后续补充。当前先放置产品图标和 `test-cpp/` 使用的 OpenCV 测试图片，作为素材位。

| 素材 | 预览 |
| --- | --- |
| 产品图标 | ![ImageWatchPro](docs/images/ImageWatchPro.png) |
| Demo 图片 | ![tf-card](docs/images/demo-tf-card.png) |
| Demo 图片 | ![circles](docs/images/demo-circles.png) |

## 开源边界

本仓库公开文档、Issue 模板和 `test-cpp/` demo/smoke-test 项目，并使用 MIT 许可证。

当前仓库不包含核心插件源码。核心 Visual Studio 扩展以免费 VSIX 二进制形式通过 GitHub Releases 发布。

## 反馈

请通过 GitHub Issues 提交 bug、功能建议、兼容性报告和文档问题。建议附带 Visual Studio 版本、Windows 版本、OpenCV 版本、最小复现代码和截图。

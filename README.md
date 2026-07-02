# ImageWatchPro for Visual Studio

[中文说明](README.zh-CN.md)

ImageWatchPro is a Visual Studio 2022/2026 debugger visualization extension for native C++ and OpenCV workflows. It helps you inspect `cv::Mat` images, masks, contours, geometry objects, numeric plots, histograms, and exported debug views while stopped at a breakpoint.

![ImageWatchPro icon](docs/images/ImageWatchPro.png)

## Download

Download the latest VSIX from [GitHub Releases](https://github.com/namemzy/ImageWatchPro-for-VisualStudio/releases).

Current preview binary: `ImageWatchPro.Packaging.vsix`.

## What You Can Inspect

- [x] `cv::Mat` / `cv::Mat_<T>` image viewer
- [x] Single-channel mask overlay
- [x] OpenCV contours, point sets, rectangles, rotated rectangles
- [x] Numeric line/scatter plots
- [x] Grayscale and B/G/R channel histograms
- [x] PNG/BMP/TIFF export with visible overlays

## Quick Start

1. Install Visual Studio 2022 or 2026 with native C++ workload.
2. Download `ImageWatchPro.Packaging.vsix` from Releases.
3. Close Visual Studio, run the VSIX installer, then reopen Visual Studio.
4. Start debugging a native C++ / OpenCV program.
5. Open `Debug > Windows > ImageWatchPro` while stopped at a breakpoint.
6. Use the `test-cpp/` project in this repository as the demo and smoke test.

## Demo / Smoke Test

```powershell
cd test-cpp
cmake -S . -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
```

Set breakpoints near the marked return statements in `main.cpp`, then inspect the variables in ImageWatchPro.

## License

This repository is licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Feedback

Please use GitHub Issues for bugs, feature requests, compatibility reports, and documentation questions. Include your Visual Studio version, Windows version, OpenCV version, and a minimal repro when possible.

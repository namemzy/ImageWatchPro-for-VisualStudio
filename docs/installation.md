# 安装指南

## 环境要求

- Windows 10/11
- Visual Studio 2022 或 Visual Studio 2026
- Visual Studio 工作负载：使用 C++ 的桌面开发
- 调试 OpenCV 项目时，需要本机项目能正常加载 OpenCV DLL 和 PDB/调试信息

## 安装 VSIX

1. 前往 GitHub Releases 下载 `ImageWatchPro.Packaging.vsix`。
2. 关闭所有 Visual Studio 实例。
3. 双击 VSIX 文件并按提示安装。
4. 重新打开 Visual Studio。
5. 调试 C++ 程序时，通过 `Debug > Windows > ImageWatchPro` 打开窗口。

## 验证安装

使用仓库内的 `test-cpp/` 项目构建 demo，在断点暂停后打开 ImageWatchPro，查看 `cv::Mat`、Mask、Contour 和 Plot 变量。

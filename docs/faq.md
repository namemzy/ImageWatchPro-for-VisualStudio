# FAQ

## 为什么仓库里没有核心插件源码？

当前阶段采用“二进制免费 + 文档/demo 开源”策略。本仓库公开文档、demo、测试代码和 issue tracker，核心 Visual Studio 扩展先以 VSIX 二进制形式发布。

## 为什么安装后 VSIX Identity 仍像原 Image Watch？

ImageWatchPro 基于 Microsoft Image Watch 增强，保留原可视化入口用于替换原调试器入口。请以 Visual Studio 中显示的 `ImageWatchPro` 名称和 Release 包为准。

## Release 调试时变量看不到怎么办？

优先检查被调试程序是否开启了强优化。局部变量可能被优化掉或布局不可读。建议先用 Debug 或 RelWithDebInfo 验证。

## `test-cpp/` 需要 OpenCV 吗？

需要。请设置 `OpenCV_DIR`，或在 CMake 配置时传入 OpenCV 安装路径。

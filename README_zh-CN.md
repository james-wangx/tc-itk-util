# tc-itk-util

![License](https://img.shields.io/badge/license-MIT-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B-00599C)
![Platform](https://img.shields.io/badge/platform-Windows-blue)
![Teamcenter](https://img.shields.io/badge/Teamcenter-2412%20%2F%202506-orange)
![Release](https://img.shields.io/github/v/release/james-wangx/tc-itk-util)
![Downloads](https://img.shields.io/github/downloads/james-wangx/tc-itk-util/total)

[English](README.md)

Teamcenter ITK 工具集 —— 常用 Teamcenter ITK 操作的 C++ 封装库，以静态库形式分发，支持 Teamcenter 2412 和 2506。

## 支持的版本

| Teamcenter | 工程目录 | SDK 环境变量 | 产物 |
| --- | --- | --- | --- |
| 2412 | `tc-itk-util-2412` | `TC2412_ROOT` | `libtcitkutil-2412.lib` |
| 2506 | `tc-itk-util-2506` | `TC2506_ROOT` | `libtcitkutil-2506.lib` |

## 环境要求

- Windows x64
- Visual Studio 2022 或更高版本（v143 工具集）
- 目标版本的 Teamcenter SDK，通过 `TC2412_ROOT` / `TC2506_ROOT` 环境变量定位
- 动态 CRT（`/MD`），Release 配置

## 构建

```powershell
msbuild tc-itk-util-2412\tc-itk-util-2412.vcxproj /p:Configuration=Release /p:Platform=x64
msbuild tc-itk-util-2506\tc-itk-util-2506.vcxproj /p:Configuration=Release /p:Platform=x64
```

每个工程输出 `bin\libtcitkutil.lib`。

## 使用方式

1. 将对应版本的 include 目录加入工程（`tc-itk-util-2412\include` 或 `tc-itk-util-2506\include`）。
2. 链接对应 Teamcenter 版本的静态库（`libtcitkutil-2412.lib` / `libtcitkutil-2506.lib`）。
3. 自行链接 Teamcenter 库——静态库不携带依赖。

### 错误约定

- 所有方法失败时抛出 `IFail`。调用方应使用 `try/catch` 捕获；若异常未被捕获，Teamcenter 框架会显示错误信息。
- `findUserById`、`findRelation`、`findRelationType` 在找不到对象时返回 `NULLTAG`。
- `convertTag2Uid` 转换失败时返回空字符串。

该库按 x64 / v143 / `/MD` / Release 编译，消费方必须使用相同配置，否则链接器会报 LNK2038（CRT 不匹配）。

## 发布

- 版本号格式：`vYYYY.MM.DD.NN`
- 一次发布包含两个压缩包：`libtcitkutil-2412-<版本号>.zip` 和 `libtcitkutil-2506-<版本号>.zip`
- 头文件在 GitHub 自动生成的 "Source code" 压缩包中
- 每个压缩包内含对应 Teamcenter 版本的静态库

## 许可证

MIT —— 详见 [LICENSE.txt](LICENSE.txt)。

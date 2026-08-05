# tc-itk-util-2412

[English](README.md)

tc-itk-util 的 Teamcenter 2412 构建。通用说明见仓库根目录
[README](../README_zh-CN.md)。

## 环境要求

- `TC2412_ROOT` 环境变量指向 Teamcenter 2412 SDK 根目录，例如 `C:\PLM\Teamcenter\2412`
- x64 / v143 / `/MD` / Release（详见根 README）

## 构建

```powershell
msbuild tc-itk-util-2412.vcxproj /p:Configuration=Release /p:Platform=x64
```

输出：`bin\libtcitkutil.lib`（发布名为 `libtcitkutil-2412.lib`）。

## 使用方式

- 包含 `include\tcitkutil`
- 链接 `libtcitkutil-2412.lib`
- 自行链接 Teamcenter 库

## 许可证

MIT —— 详见 [LICENSE.txt](../LICENSE.txt)。

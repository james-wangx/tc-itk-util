# tc-itk-util

![License](https://img.shields.io/badge/license-MIT-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B-00599C)
![Platform](https://img.shields.io/badge/platform-Windows-blue)
![Teamcenter](https://img.shields.io/badge/Teamcenter-2412%20%2F%202506-orange)
![Release](https://img.shields.io/github/v/release/james-wangx/tc-itk-util)
![Downloads](https://img.shields.io/github/downloads/james-wangx/tc-itk-util/total)

[🇨🇳 简体中文](README_zh-CN.md)

Teamcenter ITK Utilities - a C++ wrapper library over common Teamcenter ITK
operations, distributed as static libraries for Teamcenter 2412 and 2506.

## Supported Versions

| Teamcenter | Project | SDK Environment Variable | Output |
| --- | --- | --- | --- |
| 2412 | `tc-itk-util-2412` | `TC2412_ROOT` | `libtcitkutil-2412.lib` |
| 2506 | `tc-itk-util-2506` | `TC2506_ROOT` | `libtcitkutil-2506.lib` |

## Requirements

- Windows x64
- Visual Studio 2022 or later (v143 toolset)
- Teamcenter SDK for the target version, located through the `TC2412_ROOT` /
  `TC2506_ROOT` environment variables
- Dynamic CRT (`/MD`) with a Release configuration

## Build

```powershell
msbuild tc-itk-util-2412\tc-itk-util-2412.vcxproj /p:Configuration=Release /p:Platform=x64
msbuild tc-itk-util-2506\tc-itk-util-2506.vcxproj /p:Configuration=Release /p:Platform=x64
```

Each project outputs `bin\libtcitkutil.lib`.

## Usage

1. Add the matching include directory to your project (`tc-itk-util-2412\include`
   or `tc-itk-util-2506\include`).
2. Link the static library for your Teamcenter version
   (`libtcitkutil-2412.lib` / `libtcitkutil-2506.lib`).
3. Link the Teamcenter libraries yourself - a static library does not carry its
   dependencies.

### Error Contract

- All methods throw `IFail` on failure. Wrap calls in `try/catch`; if the
  exception is left uncaught, the Teamcenter framework displays the error.
- `findUserById`, `findRelation` and `findRelationType` return `NULLTAG` when
  the object is not found.
- `convertTag2Uid` returns an empty string when the conversion fails.

The library is compiled for x64 / v143 / `/MD` / Release. Consumers must use the
same configuration, otherwise the linker reports LNK2038 (CRT mismatch).

## Releases

- Version scheme: `vYYYY.MM.DD.NN`
- One release contains both archives: `libtcitkutil-2412-<version>.zip` and
  `libtcitkutil-2506-<version>.zip`
- Headers are provided in the automatically generated "Source code" archive
- Each archive contains the static library for its Teamcenter version

## License

MIT - see [LICENSE.txt](LICENSE.txt).

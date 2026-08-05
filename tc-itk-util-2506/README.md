# tc-itk-util

[简体中文](README_zh-CN.md)

Teamcenter 2506 build of tc-itk-util. See the repository root
[README](../README.md) for general information.

## Requirements

- `TC2506_ROOT` environment variable pointing to the Teamcenter 2506 SDK root,
  e.g. `C:\PLM\Teamcenter\2506`
- x64 / v143 / `/MD` / Release (see root README)

## Build

```powershell
msbuild tc-itk-util-2506.vcxproj /p:Configuration=Release /p:Platform=x64
```

Output: `bin\libtcitkutil.lib` (published as `libtcitkutil-2506.lib`).

## Usage

- Include `include\tcitkutil`
- Link `libtcitkutil-2506.lib`
- Link Teamcenter libraries yourself

## License

MIT - see [LICENSE](../LICENSE).

# Takt Utility Manager

[![license](https://img.shields.io/badge/license-MIT-yellow)](https://github.com/tqcto/TKUM/blob/master/LICENSE)

This project is wrapper library of AfterEffects SDK.
Making to optimize development creating plug-ins.

#### Operating environment

It is intended for use with Windows Visual Studio, but should work on macOS as well.
Note that GPU processing of **Metal is not supported**.

The producer's development environment is as follows:

- Windows 10
- Microsoft Visual Studio 2019
- October 2021 After Effects SDK Windows

## How to use

1. Download [AfterEffects SDK](https://adobe.io/after-effects/).

2. Open `AfterEffectsSDK/Examples/` directory.

3. Clone this repository:

```bash
> git clone https://github.com/tqcto/TKUM.git
```

4. Open the SDK project in Visual Studio.

5. Go to the Solution Explorer.

6. Add the C++ file:

```
AfterEffectsSDK/Examples/Headers/AEFX_SuiteHandlerTemplate.cpp
```

7. Select `General` in `C/C++` page.

8. Add the following paths to `Additional Include Directories`:

```
..\..\..\TKUM
```

9. Include a `TKUM.h` in project header file.

Remember to add **section 8** path for both Debug and Release!!

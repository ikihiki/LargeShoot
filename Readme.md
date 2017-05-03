# プロジェクト設定
|項目|値|
|---------------|-------------------------------------------------------|
|出力ディレクトリ|$(SolutionDir)out\\$(PlatformTarget)\\$(Configuration)\|
|中間ディレクトリ|$(SolutionDir)intermediate\\$(PlatformTarget)\\$(Configuration)\|
|インクルードディレクトリ|$(SolutionDir)lib\include\\;$(IncludePath)|
|ライブラリディレクトリ|$(SolutionDir)lib\\$(PlatformTarget)\\;$(LibraryPath)|
|C++言語標準|c++latest|
|追加のライブラリディレクトリ|$(SolutionDir)lib\\$(PlatformTarget)\\;$(SolutionDir)out\\$(PlatformTarget)\\$(Configuration)\\;%(AdditionalLibraryDirectories)

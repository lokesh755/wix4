@setlocal
@pushd %~dp0

md ..\build\artifacts
md ..\build\logs\TestResults

msbuild -Restore internal\SetBuildNumber\SetBuildNumber.proj -nologo /p:Configuration=Debug

@popd
@endlocal

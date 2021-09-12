$so_stopwatch =  [system.diagnostics.stopwatch]::StartNew()

$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk

$so_stopwatch.Stop()
$so_timeElapsed = [math]::Round($so_stopwatch.Elapsed.TotalSeconds,3)
echo "SO build completed in $timeElapsed seconds"
Exit $LASTEXITCODE

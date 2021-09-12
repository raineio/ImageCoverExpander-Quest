$so_stopwatch =  [system.diagnostics.stopwatch]::StartNew()
$qmod_stopwatch = [system.diagnostics.stopwatch]::StartNew()

# Builds a .qmod file for loading with QuestPatcher
$NDKPath = Get-Content $PSScriptRoot/ndkpath.txt

$Version = "0.1.4"

$buildScript = "$NDKPath/build/ndk-build"
if (-not ($PSVersionTable.PSEdition -eq "Core")) {
    $buildScript += ".cmd"
}

$ArchiveName = "ImageCoverExpander-$Version.qmod"
$TempArchiveName = "ImageCoverExpander-$Version.qmod.zip"

& $buildScript NDK_PROJECT_PATH=$PSScriptRoot APP_BUILD_SCRIPT=$PSScriptRoot/Android.mk NDK_APPLICATION_MK=$PSScriptRoot/Application.mk

$so_stopwatch.Stop()
$so_timeElapsed = [math]::Round($so_stopwatch.Elapsed.TotalSeconds,3)
echo "SO build completed in $so_timeElapsed seconds"

Compress-Archive -Path "./libs/arm64-v8a/libImageCoverExpander.so", "./libs/arm64-v8a/libcodegen_0_13_1.so", "./libs/arm64-v8a/libbeatsaber-hook_2_3_0.so", "imagecoverexpander.png", "./mod.json" -DestinationPath $TempArchiveName -Force
Move-Item $TempArchiveName $ArchiveName -Force

$qmod_stopwatch.Stop()
$qmod_timeElapsed = [math]::Round($qmod_stopwatch.Elapsed.TotalSeconds,3)
echo "QMOD build completed in $qmod_timeElapsed seconds"
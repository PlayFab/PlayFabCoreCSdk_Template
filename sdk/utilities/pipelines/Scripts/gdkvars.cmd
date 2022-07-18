call %BUILD_STAGINGDIRECTORY%\sdk.external\gdkvars.cmd %*
set ATGBuildProps=%BUILD_SOURCESDIRECTORY%\build\PlayFab.gdk.bwoi.props
echo %ATGBuildProps%
dir %ATGBuildProps%
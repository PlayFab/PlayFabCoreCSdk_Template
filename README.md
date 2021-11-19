# PlayFabCoreCSdk_Template
Template to be used in conjunction with the PlayFab SDK generator to generate the PlayFab Core C SDK.

## Workflow

### Clone prerequisite repositories
1. Clone the SDK Generator project (https://github.com/PlayFab/SDKGenerator)
2. Clone the PlayFabCoreCSdk_Template (this project, https://github.com/PlayFab/PlayFabCoreCSdk_Template) into the privateTemplates directory in the root of the SDK Generator repo.
3. Clone the PlayFabCoreCSdk (https://github.com/PlayFab/PlayFabCoreCSdk). Recommended that this be placed alongside the SDKGenerator, but technically it can be anywhere. Note that it is important to clone the SDK before trying re-generate it as the SDK Generator relies on a genConfig.json file in the SDK repo for some configuration parameters.

For full instructions on repository layout, see the SDK generator [readme](https://github.com/PlayFab/SDKGenerator/blob/master/README.md). The readme refers SDK templates in the "targets" directory, but that is a legacy system. New templates should be created in their own repositories and cloned into "privateTemplates".

### Create SDK Target
You will need to add a new build configuration to the SDK generator which points it to the correct SDK and Template. To do this, open the SDK Generator project and select Build->Configuration Manager. Open the "Active solution configuration" dropdown and select "new". Name it whatever (ex. XPlatC) and copy the settings from an existing configration. Next, open the SDK Generator project properties and update the script arguments "destpath" and "buildIdentifier" appropriatly (ex. " ..\sdks\PlayFabCoreCSdk", depending on where you cloned the PlayFabCoreCSdk).

At this point, if you've layed everything out correctly, you should be able to run the SDK Generator project with this new configuration to re-generate the XPlatC SDK.

### Build/Test Generated SDK
After generating the SDK, open the .sln in PlayFabCoreCSdk/build/<platform>/ to ensure it builds correctly. You can also run the TestClientApp to run some basic BVTs.

### Making changes to the SDK
If you make changes to the generated SDK, you will need to make sure those changes are copied back to the template repository before re-generating or they will be lost. The "pf-copy-from-generated.bat" script in the template repo will automatically copy all non-templated files from the generated SDK back into the template repo.

The SDK project files are also generated using *.vcxproj.ejs templates in /source/build/<platform>/ and "ProjectFiles.json" in the repo root. If you need to add/remove files from the SDK projects, update those file accordingly.

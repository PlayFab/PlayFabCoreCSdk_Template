const { assert } = require("console");
var path = require("path");
const { fileURLToPath } = require("url");

// Making resharper less noisy - These are defined in Generate.js
if (typeof getCompiledTemplate === "undefined") getCompiledTemplate = function () { };
if (typeof templatizeTree === "undefined") templatizeTree = function () { };

// Global prefix for all SDK public symbols
var globalPrefix = "PF"; 

// Calls and datatypes produced based on api.calls & api.datatypes, but rather than being categorized by service API, they are
// categorized based on feature group. This structure will be used to generate the SDK.
var SDKFeatureGroups = {};

// Object describing SDK Customizations. This structure allows overriding the SDK featureGroup and/or platform for api calls.
//
// By default calls / datatypes will be categorized into SDKFeatureGroups based on service "subgroup"(api.calls[*].subgroup).
// customizations.featureGroupOverrides gives more control over the SDK feature groups we expose and which calls appear in which header file.
// The overrides will processed in order calls->apis->subgroup (if a call matches multiple overrides, the first match will be used).
//
// By default, each api call will be enabled on all platforms. customizations.platformExclusions allows excluding individual calls, full service
// apis, or full SDK feature groups on specific platforms. For example, if customizations.platformExclusions.apis.Admin = [HC_PLATFORM_GDK], the
// entire Admin service API set will be exluded for HC_PLATFORM_GDK.
//
// customizations object loaded from customizations.json.
var customizations = {};

// Used to generate XML header doc comments. Loaded from XMLRefDocs.json
var xmlRefDocs = {};

// Test related data structures
var prerequisiteCalls = {};
var cleanupCalls = {};
var propertyReplacements = {};

exports.makeCombinedAPI = function (apis, sourceDir, apiOutputDir) {
    console.log("Generating Combined api from: " + sourceDir + " to: " + apiOutputDir);

    try {
        propertyReplacements = require(path.resolve(sourceDir, "replacements.json"));
    } catch (ex) {
        throw "The file: replacements.json was not properly formatted JSON";
    }

    customizations = parseDataFile("customizations.json");
    testCustomizations = parseDataFile("testCustomizations.json");
    xmlRefDocs = parseDataFile("XMLRefDocs.json");

    prereqsAndCleanupMap = testCustomizations.prerequisitesAndCleanup;
    callingEntityOverrides = testCustomizations.callingEntityOverrides;

    // Make SDK customizations to apis structure
    curateServiceApis(apis)

    // populate SDKFeatureGroups structure
    populateSDKFeatureGroups(apis);

    // temporarily only including auth and shared
    var tempFeatureGroups = {};
    for (var featureGroupName in SDKFeatureGroups) {
        if (featureGroupName === "Shared" || featureGroupName === "Authentication") {
            tempFeatureGroups[featureGroupName] = SDKFeatureGroups[featureGroupName];
        }
    }
    SDKFeatureGroups = tempFeatureGroups;

    // Configure test prerequisites
    setPrerequisiteAndCleanupCalls(apis);

    var locals = {
        apis: apis,
        prefix: globalPrefix,
        SDKFeatureGroups: SDKFeatureGroups,
        projectFiles: parseProjectFiles("project_files.json"),
        buildIdentifier: sdkGlobals.buildIdentifier,
        sdkVersion: sdkGlobals.sdkVersion,
        sdkDate: sdkGlobals.sdkVersion.split(".")[2],
        sdkYear: sdkGlobals.sdkVersion.split(".")[2].substr(0, 2),
        getFormattedCallDescription: getFormattedCallDescription,
        globalPrefix: globalPrefix,
        getCallDoc: getCallDoc,
        vsVer: "v141", // As C++ versions change, we may need to update this
        vsYear: "2017", // As VS versions change, we may need to update this
        winSdkVersion: "10.0.17763.0" // Which version of the Windows SDK (A VS installation option) to use
    };

    templatizeTree(locals, path.resolve(sourceDir, "source"), apiOutputDir);
    templatizeTree(locals, path.resolve(sourceDir, "utilities"), path.resolve(apiOutputDir, "utilities"));
    for (var featureGroupName in SDKFeatureGroups) {
        makeFeatureGroupFiles(SDKFeatureGroups[featureGroupName], sourceDir, apiOutputDir);
    }

    var testXMLRefDocsJsonTemplate = getCompiledTemplate(path.resolve(sourceDir, "templates/XMLRefDocs.json.ejs"));
    writeFile(path.resolve(apiOutputDir, "test/", "XMLRefDocs.json.autogen"), testXMLRefDocsJsonTemplate(locals));

    let rootFilesToCopy = [];
    rootFilesToCopy.push("ThirdPartyNotices.txt");
    rootFilesToCopy.push("LICENSE.md");
    rootFilesToCopy.push("CONTRIBUTING.md");
    rootFilesToCopy.push("SECURITY.md");

    rootFilesToCopy.forEach(file => {
        copyFile(path.resolve(sourceDir, file), path.resolve(apiOutputDir, file));
    });
};

function makeFeatureGroupFiles(featureGroup, sourceDir, apiOutputDir) {

    if (featureGroup.name === "Shared") {
        // Use just globalPrefix for shared datatypes
        var prefix = globalPrefix;
    } else {
        prefix = globalPrefix + featureGroup.name;
    }

    var locals = {
        featureGroup: featureGroup,
        prefix: prefix,
        globalPrefix: globalPrefix,
        prerequisiteCalls: prerequisiteCalls,
        cleanupCalls: cleanupCalls,
        callingEntityOverrides: callingEntityOverrides,
        requiresDynamicStorage: requiresDynamicStorage,
        getPropertyDefinition: getPropertyDefinition,
        getWrapperPropertyType: getWrapperPropertyType,
        getWrapperPropertyDefinition: getWrapperPropertyDefinition,
        getPropertyName: getPropertyName,
        canDefaultCopyConstructor: canDefaultCopyConstructor,
        getWrapConstructorInitializationList: getWrapConstructorInitializationList,
        callExclusionMacroBegin: callExclusionMacroBegin,
        callExclusionMacroEnd: callExclusionMacroEnd,
        isFixedSize: isFixedSize,
        getFormattedDatatypeDescription: getFormattedDatatypeDescription,
        getFormattedCallDescription: getFormattedCallDescription,
        getFormattedCallRemarks: getFormattedCallRemarks,
        getRequestExample: getRequestExample,
        getPublicPropertyType: getPublicPropertyType,
        getDictionaryEntryType: getDictionaryEntryType
    };

    // DataModels
    var publicDataModelsHeader = getCompiledTemplate(path.resolve(sourceDir, "templates/PFDataModels.h.ejs"));
    writeFile(path.resolve(apiOutputDir, "code/include/playFab", globalPrefix + featureGroup.name + "DataModels.h"), publicDataModelsHeader(locals));

    var publicDataModelWrappers = getCompiledTemplate(path.resolve(sourceDir, "templates/PFDataModelWrappers.h.ejs"));
    writeFile(path.resolve(apiOutputDir, "code/include/playFab/cpp", globalPrefix + featureGroup.name + "DataModelWrappers.h"), publicDataModelWrappers(locals));

    var internalDataModelsHeader = getCompiledTemplate(path.resolve(sourceDir, "templates/DataModels.h.ejs"));
    writeFile(path.resolve(apiOutputDir, "code/source/" + featureGroup.name, featureGroup.name + "DataModels.h"), internalDataModelsHeader(locals));

    var internalDataModels = getCompiledTemplate(path.resolve(sourceDir, "templates/DataModels.cpp.ejs"));
    writeFile(path.resolve(apiOutputDir, "code/source/" + featureGroup.name, featureGroup.name + "DataModels.cpp"), internalDataModels(locals));

    // Currently don't need anything except data models for Shared API
    if (featureGroup.name !== "Shared") {

        // Internal APIs
        var internalApisHeader = getCompiledTemplate(path.resolve(sourceDir, "templates/Calls.h.ejs"));
        writeFile(path.resolve(apiOutputDir, "code/source/" + featureGroup.name, featureGroup.name + ".h"), internalApisHeader(locals));

        var internalApis = getCompiledTemplate(path.resolve(sourceDir, "templates/Calls.cpp.ejs"));
        writeFile(path.resolve(apiOutputDir, "code/source/" + featureGroup.name, featureGroup.name + ".cpp"), internalApis(locals));

        // Public APIs
        var publicApisHeader = getCompiledTemplate(path.resolve(sourceDir, "templates/PFCalls.h.ejs"));
        writeFile(path.resolve(apiOutputDir, "code/include/playfab", globalPrefix + featureGroup.name + ".h"), publicApisHeader(locals));

        var publicApis = getCompiledTemplate(path.resolve(sourceDir, "templates/PFCalls.cpp.ejs"));
        writeFile(path.resolve(apiOutputDir, "code/source/" + featureGroup.name, globalPrefix + featureGroup.name + ".cpp"), publicApis(locals));
    }
}

// *************************** Internal utility methods ***************************
function parseProjectFiles(filename) {
    var fullPath = path.resolve(__dirname, filename);
    console.log("Begin reading File: " + fullPath);
    var projectFiles = null;
    try {
        projectFiles = require(fullPath);
    }
    catch (err) {
        console.log(" ***** Failed to Load: " + fullPath);
        throw err;
    }
    console.log("Finished reading: " + fullPath);
    return projectFiles;
}

function jsonEscape(str)
{
    return str.replace(/\n/g, "").replace(/\r/g, "").replace(/\t/g, "").replace(/  /g, " ").replace(/  /g, " ");
}

function parseDataFile(filename) {
    const fs = require('fs');

    let fullPath = path.resolve(__dirname, filename);
    let rawdata = fs.readFileSync(fullPath, 'utf8');
    let dataEscaped = jsonEscape(rawdata);
    let data = JSON.parse(dataEscaped);
    return data;
}

// Curate provided 'apis' object as follows:
// - Prune datatypes from apis[*].datatypes which are empty classes and update any references to them
// - Add a reference to the 'datatype' object for each 'call' object in apis[*].calls. This allows us to skip looking up the datatype by name later
// - Add a reference to the 'datatype' object for each 'property' object in apis[*].datatypes.*.properties.
// - Annotate each 'call' in apis[*].calls with "entityReturned=*" or "entityRequired=*" if the call returns/requires an SDK Entity object
// - Annotate each 'datatype' with "isInput=true" if it is used as input to a call and "isOutput=true" if it is returned from a call
function curateServiceApis(apis) {

    for (var apiIndex = 0; apiIndex < apis.length; apiIndex++) {
        var api = apis[apiIndex];
        var datatypes = api.datatypes;

        // Prune datatypes which are empty classes
        for (var typename in datatypes) {
            var datatype = datatypes[typename];
            if (datatype.properties && datatype.properties.length === 0) {
                delete datatypes[typename];
            }
        }

        // Update datatype.properties
        for (typename in datatypes) {
            datatype = datatypes[typename];
            if (datatype.properties) {
                for (var propertyIndex = datatype.properties.length - 1; propertyIndex >= 0; propertyIndex--) {
                    var property = datatype.properties[propertyIndex];

                    if (property.isclass) {
                        if (datatypes.hasOwnProperty(property.actualtype)) {
                            // If the datatype exists still (wasn't pruned above), add a reference to it in the 'property' for easy access
                            property.datatype = datatypes[property.actualtype];
                        } else {
                            // Otherwise remove the property
                            datatype.properties.splice(propertyIndex, 1);
                        }
                    } else if (property.isenum) {
                        property.datatype = datatypes[property.actualtype];
                    }
                }
            }
        }

        // Update calls
        var calls = api.calls;
        for (var callIndex = 0; callIndex < api.calls.length; callIndex++) {
            var call = calls[callIndex];

            // Don't expose 'LoginPlayer' as we will always do that by default
            if (call.name === "LoginPlayer") {
                calls.splice(callIndex, 1);
                callIndex--;
                continue;
            }

            if (call.request in datatypes) {
                call.requestDatatype = datatypes[call.request];
            } else {
                delete call.request;
            }

            if (call.result in datatypes) {
                call.resultDatatype = datatypes[call.result];
            } else {
                delete call.result;
            }

            // Note which PlayFab Entity object is required to make the call.
            if (call.auth === "EntityToken") {
                call.entityRequired = "TitlePlayer";
            }

            // Note whether a PlayFab::Entity object is created (client side only) as a result of the call. These are mostly AuthenticateWith* methods.
            // Annotate result types for these calls as internal only. The public result of a login call will always be an Entity handle; the service response
            // model will not be directly returned to clients.
            if (call.result && call.resultDatatype.name === "AuthenticateIdentityResult") {
                call.entityReturned = "TitlePlayer";
                call.resultDatatype.isInternalOnly = true;

                // Make subtypes internal only too
                for (var propertyIndex = 0; propertyIndex < call.resultDatatype.properties.length; propertyIndex++) {
                    var property = call.resultDatatype.properties[propertyIndex];
                    if (property.isclass || property.isenum) {
                        property.datatype.isInternalOnly = true;
                    }
                }
                customizeLoginRequest(call.requestDatatype);
            }
        }
    }
}

// Make several customizations to Login requests. Ideally long term the service contract can be modified so that these modifications aren't necessary,
// but for know they lead to much cleaner client APIs.
// 1) Remove titleId field since we already have that from PFInitialize and titles shouldn't need to provide it again
// 2) Remove option for encrypted request (and update other optional accordingly)
function customizeLoginRequest(requestDatatype) {
    assert(requestDatatype.properties);

    for (var i = requestDatatype.properties.length - 1; i >= 0; i--) {
        let property = requestDatatype.properties[i];
        if (property.name === "TitleId") {
            requestDatatype.properties.splice(i, 1);
        } else if (property.name === "EncryptedRequest") {
            requestDatatype.properties.splice(i, 1);
        } else if (property.name === "PlayerAccountPoolId") {
            requestDatatype.properties.splice(i, 1);
        }

        // Properties that are only marked optional because of the optional to provide an encrypted request. Change "optional" to false.
        var nonOptionalLoginProperties = new Set(["CreateAccount", "AndroidDeviceId", "CustomId", "ServerAuthCode", "DeviceId", "AuthTicket", "KongregateId", "IdentityToken",
        "IdToken", "AuthCode", "SteamTicket", "AccessToken", "XboxToken", "Password", "ServerCustomId"]);

        if (nonOptionalLoginProperties.has(property.name)) {
            property.optional = false;
        }
    }
}

// Compare two datatypes. If the types have the same type (enum vs class), the same name (datatype.name), and the same properties (datatype.properties).
// we can consider them the same in the SDK. If properties are optional in one type but not the other, consider them as always required.
// If the types meet these match requirements, deep copy each property so they are completely identical (This is needed because calls/properties still may reference
// either instance).
function doTypesMatch(type1, type2) {

    if (type1.name !== type2.name) {
        return false;
    }

    if (type1.isenum) {
        if (type2.isenum) {
            if (type1.enumvalues.length !== type2.enumvalues.length) {
                return false;
            }
            for (let i = 0; i < type1.enumvalues.length; i++) {
                if (type1.enumvalues[i].name !== type2.enumvalues[i].name) {
                    return false;
                }
            }
            return true;
        }
        else {
            return false;
        }
    }
    else {
        if (!(type1.properties.length === type2.properties.length)) {
            return false;
        }

        for (var i = 0; i < type1.properties.length; i++) {
            let property1 = type1.properties[i];
            let property2 = type2.properties[i];
            if (!(property1.name === property2.name && property1.actualtype === property2.actualtype)) {
                return false;
            }
        }

        // At this point we can consider the types equivalent, reconcile property optionalness, isInput, isOutput
        for (let i = 0; i < type1.properties.length; i++) {
            let property1 = type1.properties[i];
            let property2 = type2.properties[i];
            if (property1.optional === false || property2.optional === false) {
                property1.optional = false;
                property2.optional = false;
            }
        }
    }

    return true;
}

// Add 'datatype' to featureGroup.datatypes. If the type already exists in a different featureGroup,
// remove it from that featureGroup and add the type to SDKFeatureGroups.shared.datatypes instead (rather than to 'featureGroup').
// Also annotate datatype with appropriate prefix based on featureGroup.name & isShared flag if the datatype is used within multiple SDKFeatureGroups
function addDatatypeToFeatureGroup(datatype, featureGroup) {

    var featureGroupDatatypes = featureGroup.datatypes;
    var sharedDatatypes = SDKFeatureGroups.Shared.datatypes;

    if (featureGroupDatatypes.hasOwnProperty(datatype.name)) {
        let existingDatatype = featureGroupDatatypes[datatype.name];

        if (existingDatatype == datatype) {
            // This datatype instance has already been added. No work to do
        } else if (doTypesMatch(datatype, existingDatatype)) {
            // Apply previously added annotations (prefix, etc.) to datatype
            Object.assign(datatype, existingDatatype);
        } else {
            // Use service API name to differtiate non-matching datatypes with the same name. Serivce namespace for data models have format "PlayFab.<ServiceApi>.Models".
            // Extract ServiceApi and mangle change datatype.name to <ServiceApi><datatype.name>. Note that this isn't just a public prefix,
            // it affects both the internal and public name for the datatype.
            if (existingDatatype.name === datatype.name) {
                existingDatatype.name = existingDatatype.classNameSpace.split(".")[1] + existingDatatype.name;
            }
            datatype.name = datatype.classNameSpace.split(".")[1] + datatype.name;
            datatype.prefix = globalPrefix + featureGroup.name;
            featureGroupDatatypes[datatype.name] = datatype;
            // existingDatatype intentionally remains indexed by service name (not mangled name) so that future type collisions will still be detected
        }
    } else if (sharedDatatypes.hasOwnProperty(datatype.name)) {

        let existingDatatype = sharedDatatypes[datatype.name];

        if (existingDatatype == datatype) {
            // This datatype instance has already been added. No work to do
        } else if (doTypesMatch(datatype, existingDatatype)) {
            // Update datatype with any annotations we've added previously (publicName, isShared, etc.).
            Object.assign(datatype, existingDatatype);
        } else {
            // Can't easily handle this situation so throw error here
            throw Error("Unexpected: Type mismatch cannot be reconciled");
        }

    } else {
        // Tentatively add datatype to featureGroup[datatype]. Will be moved to SDKFeatureGroups.Shared below if we discover that it is also referenced in another featureGroup
        datatype.prefix = globalPrefix + featureGroup.name;
        featureGroupDatatypes[datatype.name] = datatype;

        // Check if the a matching datatype already exists in another featureGroupName and move to sharedDatatypes if so
        for (var otherFeatureGroupName in SDKFeatureGroups) {
            if (otherFeatureGroupName !== featureGroup.name && otherFeatureGroupName !== "Shared") {
                var otherFeatureGroupDatatypes = SDKFeatureGroups[otherFeatureGroupName].datatypes;

                if (otherFeatureGroupDatatypes.hasOwnProperty(datatype.name)) {
                    let existingDatatype = otherFeatureGroupDatatypes[datatype.name];

                    if (doTypesMatch(datatype, existingDatatype)) {
                        datatype.prefix = globalPrefix;
                        datatype.isShared = true;
                        Object.assign(existingDatatype, datatype);
                        sharedDatatypes[datatype.name] = datatype;

                        // remove from the feature group datatypes now as well
                        delete otherFeatureGroupDatatypes[datatype.name];
                        delete featureGroupDatatypes[datatype.name];

                        break;
                    }
                }
            }
        }
    }

    // Recursively add all subtypes of 'datatype' as well
    if (datatype.hasOwnProperty("properties")) {
        for (var propertyIndex = 0; propertyIndex < datatype.properties.length; propertyIndex++) {
            var property = datatype.properties[propertyIndex];
            if (property.isclass || property.isenum) {
                addDatatypeToFeatureGroup(property.datatype, featureGroup);
            }
        }
    }
}

function getOrCreateFeatureGroup(name) {
    if (!SDKFeatureGroups.hasOwnProperty(name)) {
        SDKFeatureGroups[name] = {
            "name": name,
            "datatypes": {},
            "calls": [],
            "sortedClasses": [], // subset of 'datatypes' that are classes (datatype.isclass = true), sorted such that type dependencies are honored
            "dictionaryEntryTypes": {} // subset of 'datatypes' that appear as values in a map (property.collection = map)
        }
    }
    return SDKFeatureGroups[name];
}

function populateSDKFeatureGroups(apis) {

    // Create special "Shared" feature group manually. It will hold datatypes which are referenced in multiple SDKFeatureGroups.
    let sharedFeatureGroup = getOrCreateFeatureGroup("Shared");

    for (var apiIndex = 0; apiIndex < apis.length; apiIndex++) {
        var api = apis[apiIndex];
        var apiDatatypes = api["datatypes"];

        for (var callIndex = 0; callIndex < api.calls.length; ++callIndex) {

            var call = api.calls[callIndex];

            // Modify name of "Classic" API calls to avoid conflicts & clarify that they are classic APIs.
            // Note that this is in addition to the global & featureGroup prefixes that will be added to the public SDK APIs.
            if (api.name === "Client" || api.name === "Server" || api.name === "Admin") {
                call.name = api.name + call.name;
            }

            let featureGroupName = call.subgroup;
            let featureGroupOverrides = customizations.featureGroupOverrides;

            if (featureGroupOverrides.calls.hasOwnProperty(call.name)) {
                featureGroupName = featureGroupOverrides.calls[call.name];
            } else if (featureGroupOverrides.apis.hasOwnProperty(api.name)) {
                featureGroupName = featureGroupOverrides.apis[api.name];
            } else if (featureGroupOverrides.subgroups.hasOwnProperty(call.subgroup)) {
                featureGroupName = featureGroupOverrides.subgroups[call.subgroup];
            }

            let featureGroup = getOrCreateFeatureGroup(featureGroupName);
            featureGroup.calls.push(call);

            // Add request & response types to featureGroup.datatypes
            if (call.hasOwnProperty("requestDatatype")) {
                addDatatypeToFeatureGroup(call.requestDatatype, featureGroup);
            }
            if (call.hasOwnProperty("resultDatatype")) {
                addDatatypeToFeatureGroup(call.resultDatatype, featureGroup);
            }
        }
    }

    // populate SDKFeatureGroups.*.sortedClasses and SDKFeatureGroups.*.dictionaryEntryTypes
    for (var featureGroupName in SDKFeatureGroups) {
        var featureGroup = SDKFeatureGroups[featureGroupName]
        var sortedClasses = featureGroup.sortedClasses;
        var addedTypes = new Set();

        // Add isInput/isOutput annotations
        var addAnnotation = function (datatype, annotation) {
            if (datatype.hasOwnProperty(annotation)) {
                return;
            }
            datatype[annotation] = true;
            if (datatype.properties) {
                for (var propIdx = 0; propIdx < datatype.properties.length; propIdx++) {
                    var property = datatype.properties[propIdx];
                    if (featureGroup.datatypes.hasOwnProperty(property.actualtype)) {
                        addAnnotation(featureGroup.datatypes[property.actualtype], annotation);
                    } else if (sharedFeatureGroup.datatypes.hasOwnProperty(property.actualtype)) {
                        addAnnotation(sharedFeatureGroup.datatypes[property.actualtype], annotation);
                    }
                }
            }
        };

        for (let typeKey in featureGroup.datatypes) {
            datatype = featureGroup.datatypes[typeKey];
            if (datatype.isRequest) {
                addAnnotation(datatype, "isInput")
            }
            if (datatype.isResult) {
                addAnnotation(datatype, "isOutput")
            }
        }

        var addType = function (datatype) {
            if (addedTypes.has(datatype.name) || datatype.isenum) {
                return;
            }
            // In C++, dependent types must be defined first
            if (datatype.properties) {
                for (var propIdx = 0; propIdx < datatype.properties.length; propIdx++) {
                    var property = datatype.properties[propIdx];
                    if (property.isclass && featureGroup.datatypes.hasOwnProperty(property.datatype.name)) {
                        addType(property.datatype);
                    }
                }
            }
            addedTypes.add(datatype.name);
            sortedClasses.push(datatype);
        };

        // Add all types and their dependencies
        for (let typeKey in featureGroup.datatypes) {
            addType(featureGroup.datatypes[typeKey]);
        }

        // Add all (non-primitive) types which appear as a Value in a map featureGroup.dictionaryEntryTypes (or SDKFeatureGroups.Shared.dictionaryEntryTypes as appropriate)
        for (let typeKey in featureGroup.datatypes) {
            let datatype = featureGroup.datatypes[typeKey];
            if (datatype.properties) {
                for (var propertyIndex = 0; propertyIndex < datatype.properties.length; propertyIndex++) {
                    var property = datatype.properties[propertyIndex];
                    if (property.collection === "map" && (property.isclass || property.isenum)) {
                        if (property.datatype.isShared) {
                            SDKFeatureGroups.Shared.dictionaryEntryTypes[property.datatype.name] = property.datatype;
                        } else {
                            featureGroup.dictionaryEntryTypes[property.datatype.name] = property.datatype;
                        }
                    }
                }
            }
        }
    }
}

function setPrerequisiteAndCleanupCalls() {
    for (let featureGroupName in SDKFeatureGroups) {
        for (const call of SDKFeatureGroups[featureGroupName].calls) {
            prerequisiteCalls[call.name] = [];
            cleanupCalls[call.name] = [];

            if (prereqsAndCleanupMap.hasOwnProperty(call.name)) {
                for (const prereqName of prereqsAndCleanupMap[call.name].prerequisites) {
                    prerequisiteCalls[call.name].push(SDKFeatureGroups[featureGroupName].calls.find(elem => elem.name === prereqName));
                }
                
                for (const cleanupName of prereqsAndCleanupMap[call.name].cleanup) {
                    cleanupCalls[call.name].push(SDKFeatureGroups[featureGroupName].calls.find(elem => elem.name === cleanupName));
                }
            }
        }
    }
}

// *************************** ejs-exposed methods ***************************

// Used by functions which return code snippets
var tab = "    ";

// Used to insert if platform macros to exclude output per call
function callExclusionMacroBegin(call) {
    let excludedPlatforms = new Set();
    if (customizations.platformExclusions.calls.hasOwnProperty(call.name)) {
        for (let i = 0; i < customizations.platformExclusions.calls[call.name].length; i++) {
            excludedPlatforms.add(customizations.platformExclusions.calls[call.name][i]);
        }
    }
    let apiName = call.url.split("/")[1];
    if (customizations.platformExclusions.apis.hasOwnProperty(apiName)) {
        for (let i = 0; i < customizations.platformExclusions.apis[apiName].length; i++) {
            excludedPlatforms.add(customizations.platformExclusions.apis[apiName][i]);
        }
    }
    if (customizations.platformExclusions.subgroups.hasOwnProperty(call.subgroup)) {
        for (let i = 0; i < customizations.platformExclusions.subgroups[call.subgroup].length; i++) {
            excludedPlatforms.add(customizations.platformExclusions.subgroups[call.subgroup][i]);
        }
    }

    if (excludedPlatforms.size == 0) {
        return "";
    }
    var macro = "#if "
    for (let platform of excludedPlatforms) {
        if (macro !== "#if ") {
            macro = macro + " && ";
        }
        macro = macro + "HC_PLATFORM != " + platform;
    }
    return macro + "\n";
}

// Used to insert endif platform macros to end excluded code section
function callExclusionMacroEnd(call) {
    if (callExclusionMacroBegin(call).length > 0) {
        return "#endif\n";
    }
    return "";
}

// Returns whether the C++ model for a datatype is fixed size
function isFixedSize(datatype) {
    for (var i = 0; i < datatype.properties.length; i++) {
        if (requiresDynamicStorage(datatype.properties[i])) {
            return false;
        }
    }
    return true;
}

function requiresDynamicStorage(property) {
    // An internal property is needed if the public property requires dynamic storage.
    // Dynamic storage is not required for non-optional/non-collection primitive & enum types
    var primitives = new Set(["Boolean", "int16", "uint16", "int32", "uint32", "int64", "uint64", "float", "double", "DateTime"]);

    if ((primitives.has(property.actualtype) || property.isenum) && !property.optional && !property.collection) {
        return false;
    }
    return true;
}

function getDictionaryEntryType(property) {
    var dictionaryEntryTypes = {
        "String": "String", "Boolean": "Bool", "int16": "Int16", "uint16": "Uint16", "int32": "Int32", "uint32": "Uint32",
        "int64": "Int64", "uint64": "Uint64", "float": "Float", "double": "Double", "time_t": "DateTime"
    };
    
    if (property.actualtype in dictionaryEntryTypes) {
        return globalPrefix + dictionaryEntryTypes[property.actualtype] + "DictionaryEntry";
    } else {
        return property.datatype.prefix + property.datatype.name + "DictionaryEntry";
    }
}

function getInternalPropertyType(property) {
    var type = "";

    // Service types that can be mapped directly to C++ types
    var types = {
        "String": "String", "Boolean": "bool", "int16": "int16_t", "uint16": "uint16_t", "int32": "int32_t", "uint32": "uint32_t",
        "int64": "int64_t", "uint64": "uint64_t", "float": "float", "double": "double", "DateTime": "time_t", "object": "JsonObject"
    };

    if (property.actualtype in types) {
        type = types[property.actualtype];
    } else if (property.datatype) {
        if (property.isclass) {
            type = property.datatype.name;
        } else if (property.isenum) {
            // Enums always defined in global namespace so add prefix
            type = property.datatype.prefix + property.datatype.name
        }
    } else {
        throw Error("Unrecognized property type " + property.actualtype);
    }

    // Modify type depending on collection & optional attributes. 
    if (!(property.actualtype === "object")) {
        if (property.collection === "map") {
            return "Map<String, " + type + ">";
        } else if (property.collection === "array") {
            return "Vector<" + type + ">";
        } else if (property.optional) {
            // Types which aren't nullable will be wrapped by StdExtra::optional.
            // String is an exception here - empty will represent not set(might want to revisit this design)
            if (!(type === "String" || type === "JsonObject")) {
                return "StdExtra::optional<" + type + ">";
            }
        }
    }

    return type;
}

function getPublicPropertyType(property, addConsts = true) {
    var type = "";

    // Service types that can be mapped directly to C types
    var types = {
        "String": "const char*", "Boolean": "bool", "int16": "int16_t", "uint16": "uint16_t", "int32": "int32_t", "uint32": "uint32_t",
        "int64": "int64_t", "uint64": "uint64_t", "float": "float", "double": "double", "DateTime": "time_t", "object": globalPrefix + "JsonObject"
    };

    if (property.actualtype in types) {
        type = types[property.actualtype];
    } else if (property.datatype) {
        if (!property.datatype.prefix) {
            throw Error("No prefix!");
        }
        type = property.datatype.prefix + property.datatype.name;
    } else {
        throw Error("Unrecognized property type " + property.actualtype);
    }

    // By design class properties are always pointers. Pointers will ultimately point to derived C++ internal Objects which
    // can automatically manage their cleanup & copying via destructors and copy constructors

    if (addConsts === false) {
        if (!(property.actualtype === "object")) {
            if (property.collection === "map") {
                // array of dictionary entries
                return getDictionaryEntryType(property);
            } else if (property.collection === "array") {
                if (property.isclass) {
                    // array of pointers
                    return type;
                } else {
                    return type;
                }
            } else if (property.optional) {
                // Types which aren't already nullable will be made pointer types
                if (!(type === "const char*" || type === (globalPrefix + "JsonObject"))) {
                    return type;
                }
            }
        }

        if (property.isclass) {
            return type;
        }
    }
    else {
        // Add type modifications depending on "collection" & "optional" attributes
        if (!(property.actualtype === "object")) {
            if (property.collection === "map") {
                // array of dictionary entries
                return "struct " + getDictionaryEntryType(property) + " const*";
            } else if (property.collection === "array") {
                if (property.isclass) {
                    // array of pointers
                    return type + " const* const*";
                } else {
                    return type + " const*";
                }
            } else if (property.optional) {
                // Types which aren't already nullable will be made pointer types
                if (!(type === "const char*" || type === (globalPrefix + "JsonObject"))) {
                    return type + " const*";
                }
            }
        }

        if (property.isclass) {
            return type + " const*";
        }
    }

    return type;
}

function getWrapperPropertyType(property) {
    var type = "";

    // Service types that can be mapped directly to C++ types
    var types = {
        "String": "String", "Boolean": "bool", "int16": "int16_t", "uint16": "uint16_t", "int32": "int32_t", "uint32": "uint32_t",
        "int64": "int64_t", "uint64": "uint64_t", "float": "float", "double": "double", "DateTime": "time_t", "object": "JsonObject<Alloc>"
    };

    if (property.actualtype in types) {
        type = types[property.actualtype];
    } else if (property.datatype) {
        if (property.isclass) {
            type = property.datatype.prefix + property.datatype.name + "Wrapper<Alloc>";
        } else if (property.isenum) {
            type = property.datatype.prefix + property.datatype.name
        }
    } else {
        throw Error("Unrecognized property type " + property.actualtype);
    }

    // Modify type depending on collection & optional attributes. 
    if (!(property.actualtype === "object")) {
        if (property.collection === "map") {
            if (property.isclass) {
                return "ModelDictionaryEntryVector<" + type + ", Alloc>";
            } else if (type === "String") {
                return "StringDictionaryEntryVector<Alloc>";
            } else {
                return "DictionaryEntryVector<" + getDictionaryEntryType(property) + ", Alloc>";
            }
        } else if (property.collection === "array") {
            if (property.isclass) {
                return "ModelVector<" + type + ", Alloc>";
            } else if (type === "String") {
                return "CStringVector<Alloc>";
            } else {
                return "Vector<" + type + ">";
            }
        } else if (property.optional) {
            // Types which aren't nullable will be wrapped by StdExtra::optional.
            // String is an exception here - empty will represent not set(might want to revisit this design)
            if (!(type === "String" || type === "JsonObject<Alloc>")) {
                return "StdExtra::optional<" + type + ">";
            }
        }
    }

    return type;
}

function getPropertyName(property, isPrivate, camelCase = true) {
    var name = property.name;

    // Don't allow property name to be a C++ reserved word
    if (name.localeCompare("namespace", undefined, { sensitivity: 'accent' }) === 0) {
        name = "playfab" + name;
    }

    if (camelCase)
    {
        name = name.replace(/(?:^\w|[A-Z]|\b\w|\s+)/g, function (match, index) {
            if (+match === 0) return ""; // or if (/\s+/.test(match)) for white spaces
            return index === 0 ? match.toLowerCase() : match.toUpperCase();
        });
    }

    // Special case for some property names
    if (name.startsWith("pSN")) {
        name = "P" + name.slice(1);
    } else if (name.startsWith("mAC")) {
        name = "M" + name.slice(1);
    } else if (name.startsWith("iPAddress")) {
        name = "I" + name.slice(1);
    } else if (name.startsWith("oS")) {
        name = "O" + name.slice(1);
    } else if (name.startsWith("rSA")) {
        name = "R" + name.slice(1);
    } else if (name.startsWith("uRL")) {
        name = "U" + name.slice(1);
    }

    return isPrivate ? "m_" + name : name;
}

function getPropertyDefinition(datatype, property, isInternal) {
    var output = "";

    // for public properties, add XML ref doc comments
    if (!isInternal) {
        var xmlComment = tab + "/// <summary>\n" + tab + "///"
        var propertyDescription = property.optional ? "(Optional) " : "";
        if (property.description) {
            propertyDescription += property.description.charAt(0).toUpperCase() + property.description.slice(1);
            if (!propertyDescription.endsWith(".")) {
                propertyDescription += ".";
            }
        } else {
            propertyDescription += (property.name + " property.");
        }

        xmlComment = appendToXmlDocComment(xmlComment, propertyDescription);
        xmlComment += ("\n" + tab + "/// </summary>")
        output += ("\n" + xmlComment);
    }

    if (!isInternal || datatype.isInternalOnly || requiresDynamicStorage(property)) {
        var type = isInternal ? getInternalPropertyType(property) : getPublicPropertyType(property, true);
        var propName = getPropertyName(property, datatype.isInternalOnly ? false : isInternal);
        var salAnnotations = "";
        if (!isInternal) {
            if (property.actualtype !== "object") {
                if (property.optional) {
                    salAnnotations += "_Maybenull_ ";
                }
                if (property.collection) {
                    salAnnotations += ("_Field_size_(" + propName + "Count) ");
                }
            }
            if (property.actualtype === "String" && !property.collection) {
                salAnnotations += "_Null_terminated_ ";
            }
        }

        output += ("\n" + tab + salAnnotations + type + " " + propName + ";");

        // For public collection properties add an additional "count" property
        if (property.collection && !(type === (globalPrefix + "JsonObject")) && !isInternal) {
            output += ("\n\n" + tab + "/// <summary>\n" + tab + "/// Count of " + propName + "\n" + tab + "/// </summary>");
            output += ("\n" + tab + "uint32_t " + propName + "Count;");
        }
    }

    if (!isInternal) {
        output += "\n";
    }

    return output;
}

function getWrapperPropertyDefinition(property){
    var output = "";

    if (requiresDynamicStorage(property)) {
        var type = getWrapperPropertyType(property);
        var propName = getPropertyName(property, true);
        output += ("\n" + tab + type + " " + propName + ";");
    }
    return output;
}

function getWrapperPropertyDefinition(property){
    var output = "";

    if (requiresDynamicStorage(property)) {
        var type = getWrapperPropertyType(property);
        var propName = getPropertyName(property, true);
        output += ("\n" + tab + type + " " + propName + ";");
    }
    return output;
}

function canDefaultCopyConstructor(datatype) {
    // We can default the copy construct iff there are no internal properties (i.e. no public properties reference memory outside the struct)
    if (datatype.properties) {
        for (var propIdx = 0; propIdx < datatype.properties.length; propIdx++) {
            var property = datatype.properties[propIdx];
            if (requiresDynamicStorage(property)) {
                return false;
            }
        }
    }
    return true;
}

function getWrapConstructorInitializationList(datatype) {
    var output = "ModelWrapper<" + datatype.prefix + datatype.name + ", Alloc>{ model }";
    var conjunction = ",\n" + tab + tab;

    for (var i = 0; i < datatype.properties.length; i++) {
        var property = datatype.properties[i];
        if (requiresDynamicStorage(property)) {
            var wrapperPropName = getPropertyName(property, true);
            var CPropName = getPropertyName(property, false);
            var wrapperPropType = getWrapperPropertyType(property);

            if (property.actualtype === "object") {
                output += (conjunction + wrapperPropName + "{ model." + CPropName + " }");
            } else if (property.collection) {
                output += (conjunction + wrapperPropName + "{ model." + CPropName + ", model." + CPropName + " + model." + CPropName + "Count }");
            } else if (property.actualtype === "String") {
                output += (conjunction + wrapperPropName + "{ SafeString(model." + CPropName + ") }");
            } else if (property.optional) {
                output += (conjunction + wrapperPropName + "{ model." + CPropName + " ? " + wrapperPropType + "{ *model." + CPropName + " } : StdExtra::nullopt }");
            } else {
                output += (conjunction + wrapperPropName + "{ model." + CPropName + " ? *model." + CPropName + " : decltype(*model." + CPropName + "){} }");
            }
        }
    }
    return output;
}

// appends str to existing XmlDoc comment, ensuring proper line breaks and formatting
function appendToXmlDocComment(comment, str) {
    var tabbing = comment.slice(0, comment.indexOf("///"));
    var curLineLength = comment.length - comment.lastIndexOf("\n");
    var words = str.split(" ");
    for (var i = 0; i < words.length; i++) {
        if (curLineLength > 100) {
            comment += ("\n" + tabbing + "///");
            curLineLength = tabbing.length + 3;
        }
        comment += (" " + words[i]);
        curLineLength += (words[i].length + 1);
    }
    return comment;
}

function getFormattedDatatypeDescription(datatype) {
    var output = "/// " + datatype.prefix + datatype.name + " data model.";

    if (datatype.description) {
        if (datatype.description.endsWith(".")) {
            output = appendToXmlDocComment(output, datatype.description);
        } else {
            output = appendToXmlDocComment(output, datatype.description + ".");
        }
    }

    if (datatype.hasOwnProperty("calls")) {
        var callUsage = ""; // addition info on which API calls the struct is used in
        if (datatype.isRequest) {
            callUsage += "Request object for";

        } else if (datatype.isResult) {
            callUsage += "Result payload for";
        }
        if (callUsage.length > 0) {
            for (i = 0; i < datatype.calls.length; i++) {
                // ensure proper grammer in call usage list
                if (i > 1 && i === datatype.calls.length - 1) { // Used in at least 3 calls and this is the last one
                    callUsage += ", and";
                } else if (i === 1 && datatype.calls.length === 2) { // Used in 2 calls and this is the second one
                    callUsage += " and";
                } else if (i > 0) {
                    callUsage += ",";
                }
                callUsage += (" " + prefix + datatype.calls[i] + "Async");
            }
            output = appendToXmlDocComment(output, callUsage + ".");
        }
    }

    return output;
}

function getSeeAlso(call) {
    if (call.seeAlso == undefined || call.seeAlso.length == 0) {
        return "";
    }

    var result = "See also ";
    for (var i in call.seeAlso) {
        // TODO add cref link and full API call name here
        result += call.seeAlso[i].replace(/"/g, "'").replace("/", "") + "Async";
        if (i != call.seeAlso.length - 1) {
            result += ", ";
        }
    }

    return result;
}

function getCallDoc(featureGroupName, call) {
    var asyncName = globalPrefix + featureGroupName + call.name + "Async";
    if (asyncName in xmlRefDocs) {
        return xmlRefDocs[asyncName];
    }

    var doc = {};
    if (call.summary === undefined || call.summary.length == 0) {
        doc.summary = "TODO";
    }
    else {
        doc.summary = call.summary.replace(/"/g, "'");
    }

    var remarks = (call.requestDetails !== undefined) ? call.requestDetails.replace(/"/g, "'") : "";
    var seeAlso = getSeeAlso(call);
    if (remarks.length > 0 && seeAlso.length > 0) {
        remarks += " ";
    }
    remarks += seeAlso;
    if (remarks.length > 0) {
        doc.remarks = remarks;
    }
    return doc;
}

function getFormattedCallDescription(featureGroupName, call) {
    return appendToXmlDocComment("///", getCallDoc(featureGroupName, call).summary);
}

function getFormattedCallRemarks(featureGroupName, call) {
    var formattedRemarks = "///";
    
    var callDoc = getCallDoc(featureGroupName, call);
    if (callDoc.remarks !== undefined) {
        formattedRemarks = appendToXmlDocComment(formattedRemarks, callDoc.remarks);
        if (!formattedRemarks.endsWith(".")) {
            formattedRemarks += ".";
        }
        // Leave a blank line before GetResult explanation
        formattedRemarks += ("\n///\n///");
    }

    if (!call.resultDatatype) {
        formattedRemarks = appendToXmlDocComment(formattedRemarks, "Call <see cref=\"XAsyncGetStatus\"/> to get the status of the operation.");
    } else {
        var getResultName = "";
        if (call.resultDatatype.name === "LoginResult") {
            getResultName = globalPrefix + featureGroupName + "ClientLoginGetResult";
        } else if (call.resultDatatype.name === "ServerLoginResult") {
            getResultName = globalPrefix + featureGroupName + "ServerLoginGetResult";
        } else {
            getResultName = globalPrefix + featureGroupName + call.name + "GetResult";
        }
        formattedRemarks = appendToXmlDocComment(formattedRemarks, "If successful, call <see cref=\"" + getResultName + "\"/> to get the result.");
    } 
    return formattedRemarks;
}

function jsonEscapeQuotes(input) {
    if (input !== null) {
        input = input.replace(/"/g, "\\\"");
    }
    return input;
}

function getCorrectedRequestExample(featureGroup, call) {
    var output = JSON.parse(call.requestExample);
    checkReplacements(featureGroup, output);
    return "\"" + jsonEscapeQuotes(jsonEscape(JSON.stringify(output, null, 2))) + "\"";
}

function doReplace(obj, paramName, newValue) {
    if (obj.hasOwnProperty(paramName)) {
        console.log("Replaced: " + obj[paramName] + " with " + newValue);
        obj[paramName] = newValue;
    }
};

function checkReplacements(featureGroup, obj) {
    for (var replaceCategory in propertyReplacements) {
        if (replaceCategory === "generic") {
            for (var genReplaceName1 in propertyReplacements[replaceCategory]) {
                doReplace(obj, genReplaceName1, propertyReplacements[replaceCategory][genReplaceName1]);
            }
        }
        if (replaceCategory === featureGroup.name) {
            for (var apiReplaceName in propertyReplacements[replaceCategory]) {
                if (apiReplaceName === "generic") {
                    for (var genReplaceName2 in propertyReplacements[replaceCategory][apiReplaceName]) {
                        doReplace(obj, genReplaceName2, propertyReplacements[replaceCategory][apiReplaceName][genReplaceName2]);
                    }
                }
                doReplace(obj, apiReplaceName, propertyReplacements[replaceCategory][apiReplaceName]);
            }
        }
    }
}

function getRequestExample(featureGroup, call) {
    var msg = null;
    if (call.requestExample.length > 0 && call.requestExample.indexOf("{") >= 0) {
        if (call.requestExample.indexOf("\\\"") === -1) { // I can't handle json in a string in json in a string...
            return getCorrectedRequestExample(featureGroup, call);
        } else {
            msg = "CANNOT PARSE EXAMPLE BODY: ";
        }
    }

    var props = call.requestDatatype.properties;
    var output = {};
    for (var p = 0; p < props.length; p++) {
        output[props[p].name] = props[p].jsontype;
    }

    if (msg === null) {
        msg = "AUTO GENERATED BODY FOR: ";
    }
    console.log(msg + featureGroup.name + "." + call.name);
    // console.log("    " + JSON.stringify(output, null, 2));
    return "\"" + jsonEscapeQuotes(jsonEscape(JSON.stringify(output, null, 2))) + "\"";;
}



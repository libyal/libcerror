# Library API functions testing script
#
# Version: 20160911

$TestPrefix = Split-Path -path ${Pwd}.Path -parent
$TestPrefix = Split-Path -path ${TestPrefix} -leaf
$TestPrefix = ${TestPrefix}.Substring(3)

$TestFunctions = @("get_version")

$TestToolDirectory = "..\vs2010\Release"

Function TestAPIFunction
{
	param( [string]$TestFunction, [string[]]$Options, [string]$Profile )

	$TestExecutable = "${TestToolDirectory}\${TestPrefix}_test_${TestFunction}.exe"

	Invoke-Expression ${TestExecutable}
}

foreach (${TestFunction} in ${TestFunctions})
{
	TestAPIFunction ${TestFunction}
}


# Library API type testing script
#
# Version: 20160911

$ExitSuccess = 0
$ExitFailure = 1
$ExitIgnore = 77

$TestPrefix = Split-Path -path ${Pwd}.Path -parent
$TestPrefix = Split-Path -path ${TestPrefix} -leaf
$TestPrefix = ${TestPrefix}.Substring(3)

$TestTypes = @("error")

$TestToolDirectory = "..\vs2010\Release"

Function TestAPIType
{
	param( [string]$TestType )

	$TestExecutable = "${TestToolDirectory}\${TestPrefix}_test_${TestType}.exe"

	Invoke-Expression ${TestExecutable}
}

Foreach (${TestType} in ${TestTypes})
{
	TestAPIType ${TestType}

	if (${LastExitCode} -ne ${ExitSuccess})
	{
		Break
	}
}

Exit ${LastExitCode}


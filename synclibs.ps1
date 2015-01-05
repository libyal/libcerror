# Script that synchronizes the local library dependencies
#
# Version: 20150105

$GitUrlPrefix = "https://github.com/libyal"
$LocalLibs = @("libcstring")

foreach (${LocalLib} in ${LocalLibs})
{
	git clone ${GitUrlPrefix}\${LocalLib} ${LocalLib}-${pid}

	if (Test-Path ${LocalLib}-${pid})
	{
		$LocalLibVersion = Get-Content -Path ${LocalLib}-${pid}\configure.ac | where { $_ -Match " \[[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]\]," } | % { $_ -Replace " \[([0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9])\],","$1" }

		if (Test-Path ${LocalLib})
		{
			Remove-Item -Path ${LocalLib} -Force -Recurse
		}
		New-Item -ItemType directory -Path ${LocalLib} -Force | Out-Null

		if (Test-Path ${LocalLib})
		{
			Copy-Item -Path ${LocalLib}-${pid}\${LocalLib}\*.[ch] -Destination ${LocalLib}\
			Get-Content -Path ${LocalLib}-${pid}${LocalLib}\${LocalLib}_definitions.h.in | % { $_ -Replace "@VERSION@",${LocalLibVersion} } > ${LocalLib}\${LocalLib}_definitions.h
		}
		Remove-Item -Path ${LocalLib}-${pid} -Force -Recurse
	}
}


# Script that runs the tests
#
# Version: 20160911

Set-Location -Path "tests"

Try
{
	$Lines = Get-Content "Makefile.am"
	$InTests = $FALSE

	foreach (${Line} in ${Lines})
	{
		If (${InTests})
		{
			If (-Not ${Line})
			{
				${InTests} = $FALSE

				Continue
			}
			${Line} = ${Line}.TrimStart()

			If (${Line}.EndsWith(" \"))
			{
				${Line} = ${Line}.Substring(0, ${Line}.Length - 2)
			}
			If (${Line}.EndsWith(".sh"))
			{
				${Line} = ${Line}.Substring(0, ${Line}.Length - 3)
				${Line} = ".\${Line}.ps1"
			}
			Invoke-Expression ${Line}
		}
		ElseIf (${Line}.StartsWith("TESTS = "))
		{
			${InTests} = $TRUE
		}
	}
}
Finally
{
	Set-Location -Path ".."
}


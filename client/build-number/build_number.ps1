#$scriptpath = $MyInvocation.MyCommand.Path
#$dir = Split-Path $scriptpath
#Write-host "My directory is $dir"

Write-Host Calculate new build number

$curverfilename= "build_number.h"

$curver = Get-Content $curverfilename | Out-String
# Write-Host Read content $curver

$header0 = "// Automatically generated file ! Please do not edit !`r`n"
$header1 = "#define APP_BUILD_NUMBER "
$testresult = $curver -match "(?s)$header1(?<content>.*)"
$number = $matches['content']

# Delete header from found template
# $number = $number.Replace($header1, "")

$build_number = [int]( $number )
Write-Host Current build number $build_number
$new_build_number = $build_number + 1
$Version = [string] $new_build_number

# Write header in UTF8 without BOM
$Utf8NoBomEncoding = New-Object System.Text.UTF8Encoding $False
Write-Host Next build number is $Version
[System.IO.File]::WriteAllLines($curverfilename, "// Automatically generated file !`r`n#define HASQ_BUILD_NUMBER " + $Version)

# $Version | Out-File $curverfilename
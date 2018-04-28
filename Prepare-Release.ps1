param (
    [Parameter(Mandatory = $true)][string]$Version
)

# Invalid version number
if ($Version -notmatch '\d+[\.\-]\d+[\.\-]\d+') {
    Write-Error 'Unexpected version number syntax!'
    Write-Error 'Expected syntax: Major.Minor.Patch or Major-Minor-Patch'
    Break
}

# Stop script execution on the first error
$ErrorActionPreference = 'Stop'

$basePath = '.\compiler\rush'
$versionPath = $basePath + '-v' + ($Version -replace '\.', '-')
$pathExe = $versionPath + '.exe'
$pathZip = $versionPath + '.zip'

# Build the compiler
& .\Build-Compiler.ps1

# Delete old binary
if (Test-Path -Path $pathExe) {
    Remove-Item $pathExe
}

# Copy the new binary to have the correct name containing the version number
Copy-Item -Path ($basePath + '.exe') -Destination $pathExe

# Delete old archive
if (Test-Path -Path $pathZip) {
    Remove-Item $pathZip
}

# Create an archive containing the new binary
& 'C:\Program Files\7-Zip\7z.exe' a $pathZip $pathExe

# Write hashes of the new files to the terminal
Write-Output '----'
Write-Output '## Checksum hashes'
Write-Output '- **EXE**'
Write-Output ('  - MD5: `' + (Get-FileHash -Path $pathExe -Algorithm 'MD5' | Select-Object -ExpandProperty 'Hash') + '`')
Write-Output ('  - SHA256: `' + (Get-FileHash -Path $pathExe -Algorithm 'SHA256' | Select-Object -ExpandProperty 'Hash') + '`')
Write-Output ''
Write-Output '- **ZIP**'
Write-Output ('  - MD5: `' + (Get-FileHash -Path $pathZip -Algorithm 'MD5' | Select-Object -ExpandProperty 'Hash') + '`')
Write-Output ('  - SHA256: `' + (Get-FileHash -Path $pathZip -Algorithm 'SHA256' | Select-Object -ExpandProperty 'Hash') + '`')

& explorer .\compiler\

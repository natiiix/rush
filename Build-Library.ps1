$ErrorActionPreference = "Stop"

$compiler = ".\compiler\rush.exe"
$libSource = ".\library\rushlib.rush"
$libOut = ".\library\rushlib.lib"

if (Test-Path -Path $compiler) {
    & $compiler $libSource --keep --origin -c -o $libOut
}
else {
    Write-Error -Message "No Rush compiler available!"
}

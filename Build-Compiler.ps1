$ErrorActionPreference = "Stop"

$newPath = ".\compiler\rush.exe"
$oldPath = ".\compiler\rush_old.exe"

$oldExists = Test-Path -Path $oldPath

if (Test-Path -Path $newPath) {
    if ($oldExists) {
        Remove-Item -Path $oldPath
    }

    Move-Item -Path $newPath -Destination $oldPath
    $oldExists = $true
}

if ($oldExists) {
    & $oldPath $newPath ".\compiler\main.rush" --keep
}
else {
    Write-Error -Message "No Rush compiler available!"
}

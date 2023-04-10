$folderToWatch = "C:\Users\User\OneDrive - Asia Pacific University\Deg - Sem 2\DS\assignmnent"
$filter = "*.cpp"
$cmdPath = "clang-format.exe"
$cmdArgs = "-i"

$watcher = New-Object System.IO.FileSystemWatcher
$watcher.Path = $folderToWatch
$watcher.Filter = $filter
$watcher.IncludeSubdirectories = $true
$watcher.EnableRaisingEvents = $true

$action = {
    Write-Host "File saved: $($Event.SourceEventArgs.FullPath)"
    clang-format -i $($Event.SourceEventArgs.FullPath)
}

$created = Register-ObjectEvent $watcher "Created" -Action $action
$changed = Register-ObjectEvent $watcher "Changed" -Action $action

Write-Host "Watching folder $folderToWatch for changes. Press Ctrl+C to stop."
while ($true) {
    Start-Sleep -Seconds 1
}

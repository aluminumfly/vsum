$path = [Environment]::GetFolderPath('UserProfile')
$destination = Join-Path $path '.vsum'

# create .vsum folder in user directory, move items to .vsum
New-Item -Path $destination -ItemType Directory -Force
Copy-Item -Path .\vsum.bat -Destination $destination | Out-Null
Copy-Item -Path .\src\vsum.exe -Destination $destination | Out-Null

# create new environment variable to .vsum path, this way vsum.bat is accessable from anywhere to launch the main executable
New-ItemProperty -Path "HKCU:\Environment" -Name Path -Value "$([Environment]::GetEnvironmentVariable('Path', 'User')); $destination" -PropertyType ExpandString -Force | Out-Null
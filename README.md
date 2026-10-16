# vsum

`vsum` is a simple Windows utility command to validate checksums using OpenSSL. Windows does not have a native command for this, PowerShell has [`Get-FileHash`](https://learn.microsoft.com/powershell/module/microsoft.powershell.utility/get-filehash), but that doesn't quite do the job.

## Usage

```text
vsum [filepath] [hash]
```

For example:

```text
vsum proxmox-ve_9.2-1.iso 4e88fe416df9b527624a175f24c9aa07c714d3332afb1ee3dbf3879573ef2c6c
```

## Installation

You can either compile `vsum` from source, or install the already compiled version.

First, clone the repository
```text
git clone https://github.com/aluminumfly/vsum.git
```

### Compile from source

You could use [Visual Studio](https://visualstudio.microsoft.com/) or [WSL](https://learn.microsoft.com/en-us/windows/wsl/install), but I recommend using [MSYS2 MINGW64](https://www.msys2.org/);

1. Install MSYS2 using the installer from https://www.msys2.org/

2. Once installed, open MSYS2 MINGW64 and install `gcc` and [OpenSSL](https://www.openssl.org/) with the following commands:

```text
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-x86_64-openssl
```

3. After you've successfully installed those packages, navigate to the vsum folder you've cloned
MINGW64's Windows path can be a little confusing. To return to your main drive, navigate to `/c/` inside MINGW64.

4. After you've successfully navigated to the repository, `cd` into `/src` and compile `main.c`:

```text
gcc -o vsum main.c -lcrypto
```

5. Open a PowerShell terminal and navigate to the repository, then run the installation script with `.\install.ps1`

6. If everything succeeded, close all terminals and open a new terminal. Now give `vsum` a try!

### Installing the compiled version

1. After you've cloned the repository, download the compiled version from GitHub.

2. Move the compiled version into the repository to `/src`

3. Open a PowerShell terminal, navigate to the repository and run the installation script with `.\install.ps1`

4. If everything succeeded, close all terminals and open a new terminal. Now give `vsum` a try!
# Prequesite


These are the tools needed to install this project
- Scoop (Package Manager)
- Git
- GCC Compiler

---

# Installation guide

The installation guide will be for windows user exclusively

### Scoop

1. Install Powershell on Microsoft Store
2. Install Scoop
```bash
$ Set-ExecutionPolicy RemoteSigned -Scope CurrentUser # Optional: Needed to run a remote script the first time
$ irm get.scoop.sh | iex
```

### GCC Compiler

```bash
$ scoop install gcc
```

---

# VSCode Integration

- Install `Code Runner` Extension for vscode
- Set default terminal to powershell
  1. Press `Ctrl` + `Shift` + `P`
  2. Search for `Terminal: Select Default Profile`
  3. Select Powershell
- Install `C++ Extension Pack` in the extension
- Press `Ctrl` + `Shift` + `E` to open the file explorer
- Right click a `.cpp` file you want to run, then press `run code`

---

# Daily Development
- Prettier run command

```powershell
Get-ChildItem -Path ./ -Recurse -Include *.cpp | ForEach-Object {clang-format -i $_.FullName}
```

- Compile & run file
```powershell
g++ .\main.cpp -o "main"
"./main.exe"
```



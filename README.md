# Systemnahe Programmierung 2 - 2026 - Base Project
![ProjectLogo.svg](ProjectLogo.svg)

Skeleton Workspace für die Vorlesung Systemnahe Programmierung an der DHWB Ravensburg.

## Arm Dokumentationen
### Arm Cortex-M4
- [Cortex M4 Startseite](https://developer.arm.com/Processors/Cortex-M4)
  - [ARMv7-M Architecture Reference Manual](https://developer.arm.com/documentation/ddi0403/ee/?lang=en)
  - [Arm Cortex-M4 Processor Datasheet](https://developer.arm.com/documentation/102832/0100/?lang=en)
  - [Cortex-M4 Devices Generic User Guide](https://developer.arm.com/documentation/dui0553/b/?lang=en)
  - [Arm® Cortex®-M4 Processor Technical Reference Manual](https://developer.arm.com/documentation/100166/0001?lang=en)

### Arm Application Binary Interface (ABI)
- [Arm Application Binary Interface](https://github.com/ARM-software/abi-aa)

### Nordic nRF52840 Dokumentation
- Development Kit _nRF52840 DK_
  - [nRF52840 DK Overview](https://www.nordicsemi.com/Products/Development-hardware/nrf52840-dk)
  - [nRF52840 DK Hardware Documentation](https://docs.nordicsemi.com/bundle/ug_nrf52840_dk/page/UG/dk/intro.html)
- nRF52840 Processor
  - [nRF52840 Overview](https://www.nordicsemi.com/Products/nRF52840)
  - [nRF52840 Product Specification](https://docs.nordicsemi.com/bundle/ps_nrf52840/page/keyfeatures_html5.html)
  - [nRF52840 Erratas](https://docs.nordicsemi.com/bundle?labelkey=nrf52840&labelkey=errata)

## Simuliertes Board Info
- [Nordic nRF boards (microbit)](https://www.qemu.org/docs/master/system/arm/nrf.html)

## GNU Toolchain
 - [GNU Assembler Documentation](https://sourceware.org/binutils/docs/as/index.html)
 - [GNU Linker Documentation](https://sourceware.org/binutils/docs/ld/index.html)

## Build-Umgebung
- Arm Cross-Compiler: _gcc-arm-none-eabi_
- GDB (Multi-Arch): _gdb-multiarch_
- CMake
- [Renode](https://renode.io/) ([github](https://github.com/renode/renode))
- QEMU Arm System Emulator: _qemu-system-arm_

Hinweis:
Unter anderem bei SUSE, Arch, NixOs scheint der standard GDB ein GDB-Multiarch zu sein.

### Debian/ Ubuntu Linux

Über den Paketmanager installieren:

```bash
sudo apt install \
  gcc-arm-none-eabi \
  gdb-multiarch \
  cmake \
  qemu-system-arm
```

[Renode](https://renode.io/) muss manuell installiert werden.

### Arch Linux

Über den Paketmanager installieren:

```bash
yay -S \
  arm-none-eabi-gcc \
  arm-none-eabi-gdb \
  cmake \
  qemu-system-arm
```

[Renode](https://renode.io/) muss manuell installiert werden.

### Linux-Docker Images
Wir stellen vorgefertigte Linux-Docker Images bereit.
Diese können direkt mit Docker gestartet werden:
- [Arm Cross-Compiler](https://git.thomas-vogt.de/dhbw/systemnahe-programmierung/arm-cross-compiler)
- [Arm Cross-Development Environment](https://git.thomas-vogt.de/dhbw/systemnahe-programmierung/arm-cross-development-environment)
  Enthält IDE mit VS-Code und CLion.

### Windows
- [MSYS](https://www.msys2.org/) Installer mit der Umgebung _UCRT64_ installieren.
- In der UCRT64-Shell mittel _pacman_ die Pakete installieren:
  ```bash
  pacman -S \
    ucrt64/mingw-w64-ucrt-x86_64-arm-none-eabi-gcc \
    ucrt64/mingw-w64-ucrt-x86_64-gdb-multiarch \
    ucrt64/mingw-w64-ucrt-x86_64-cmake \
    ucrt64/mingw-w64-ucrt-x86_64-qemu
  ```

[Renode](https://github.com/renode/renode/releases/latest) muss manuel installiert werden.


### macOS

```bash
brew install \
  arm-none-eabi-gcc \
  arm-none-eabi-gdb \
  cmake \
  qemu
```

## Building
Clonen des Quellcodes:

```bash
git clone \
  https://git.thomas-vogt.de/dhbw/systemnahe-programmierung/base-project-sysprog2-2026.git
```

Erstellen des Build Mittels CMake Presets:

```bash
cmake --preset arm-cortex-m4
```

Bauen Mittels CMake Presets:
```bash
cmake --build --preset arm-cortex-m4
```

## Generiertes Output analysieren (optional)
- ELF-Sections anzeige:
  ```bash
  arm-none-eabi-objdump -x cmake-build-arm-cortex-m4/testApp.elf
  ```
- ELF-File disassemblieren (mit Quellcode-Verknüpfung):
  ```bash
  arm-none-eabi-objdump -d cmake-build-arm-cortex-m4/testApp.elf
  arm-none-eabi-objdump -d -S cmake-build-arm-cortex-m4/testApp.elf
  ```

## Renode Emulator starten und mit GDB verbinden

_Renode_ und _GDB_ müssen in unterschiedlichen Konsolen (Shells) gestartet werden.

```bash
renode cmake-build-arm-cortex-m4/platform.resc
```

Falls _renode_ nicht im Pfad liegt, die ausführbare Datei über ihren _absoluten Pfad_ angeben.

**Achtung:**
Der *Build-Pfad* darf keine Leerzeichen enthalten.
Andernfalls findet Renode das Script nicht.

### Start GDB
```bash
gdb-multiarch testApp.elf -ex "target extended-remote localhost:3333" -ex "load" -ex "monitor start"
```

In manchen Distributionen kann der `gdb-multiarch` auch über den Befehl `gdb` aufgerufen werden.

## QEMU Emulator starten und mit GDB verbinden (Als Alternative zu Renode)

_QEMU_ und _GDB_ müssen in unterschiedlichen Konsolen (Shells) gestartet werden.

### QEMU Emulation Starten:
```bash
qemu-system-arm \
  -M microbit \
  -device loader,file=cmake-build-arm-cortex-m4/testApp.elf \
  -nographic \
  -S \
  -s \
  -serial mon:stdio
```
### GDB zu QEMU verbinden:
```bash
gdb-multiarch \
  cmake-build-arm-cortex-m4/testApp.elf \
  -ex "target extended-remote localhost:1234" \
  -ex "load"
```

Um QEMU zu beenden die Tastenkombination `<strg> + a` und anschließend `x` nutzen.

## GDB Tricks
Hilfreiche GDB Befehle:
- _help_ und _apropos_
- _stepi_ und _nexti_
- _info all-registers_
- _info registers_

## JetBrains CLion

### Projekt Clonen

URL:
: https://git.thomas-vogt.de/dhbw/systemnahe-programmierung/skeleton-project.git

Directory:
: Projektverzeichnis

### Profile Konfigurieren

1. *Debug*: Profil löschen
2. *arm-cortex-m4*: Profil aktivieren (*enable*)

### File Types für Assembler Datein anpassen

- Menü: _File_ -> _Settings_
- Eintrag: _Editor_ -> _File Types_
- _Assembly language file_ -> _File name Patterns_: "*.s" hinzufügen

### Debugging Konfiguration

- Menü: _Run_ -> _Edit Configurations..._
- _Add New Configuration_ -> _Embedded GDB Server_

Name:
: testApp-Renode

Target:
: testApp

Executable Binary:
: testApp

Debugger:
: "Bundeld GDB" oder den zuvor installierten GDB auswählen

Upload executable:
: never

'target remote' args:
: `tcp::3333`

GDB Server:
: Pfad zur Renode Executable

GDB Server Args:
: `$CMakeCurrentBuildDir$/platform.resc`

## Visual Studio Code

VS-Code kann über einen Workspace konfiguriert werden, welcher über die Datei "linux.code-workspace" bzw "windows.code-workspace" geöffnet werden kann.

Folgende Extensions werden benötigt:
- jkearins.action-buttons-ext
- webfreak.debug
- ms-vscode.cmake-tools
- dan-c-underwood.arm

Diese sind ebenfalls als empfohlene Extensions im Workspace definiert.

Nach Installation erkennt VScode die CMake Presets und bietet diese gleich an.
Ebenfalls werden in der Statusleiste Knöpfe, um das CMake-Projekt zu *konfigurieren* und zu *bauen*,
die QEMU-Instanz (neu) zu *starten* und gdb zu starten, hinzugefügt.

Nach Änderungen am Code muss das CMake-Projekt neu gebaut und die QEMU-Instanz neu gestartet werden.

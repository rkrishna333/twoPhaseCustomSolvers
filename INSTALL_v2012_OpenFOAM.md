# INSTALLING OpenFOAM v2012 (ESI) FROM SOURCE — QUICK GUIDE

This project (`twoPhaseCustomSolvers`) is tested **only** with OpenFOAM v2012.  
Follow the steps below on **Ubuntu 20.04 / 22.04 / 24.04**.

---

## 1) Prerequisites (packages to install)

```bash
sudo apt update
sudo apt install -y   build-essential git cmake ninja-build   flex bison zlib1g-dev libreadline-dev libncurses-dev   libxt-dev libxrender-dev libxext-dev libx11-dev   openmpi-bin libopenmpi-dev gnuplot ca-certificates curl
```

**Compilers:**  
- v2012 builds cleanly with GCC 7–9; GCC 9/11 on Ubuntu 20.04/22.04 also works.  
- If unsure, just use the system default GCC.

---

## 2) Download the v2012 source tarballs

```bash
# Use -L to follow SourceForge redirects:
cd ~
curl -L -o OpenFOAM-v2012.tgz   https://sourceforge.net/projects/openfoam/files/v2012/OpenFOAM-v2012.tgz/download

# Extract
tar -xzf OpenFOAM-v2012.tgz
```

You should now have:
```
~/OpenFOAM-v2012
```

---

## 3) Set up the environment (bashrc)

```bash
# Load the OpenFOAM environment automatically on new shells:
echo 'source $HOME/OpenFOAM-v2012/etc/bashrc' >> ~/.bashrc

# Load it for the current shell:
source ~/.bashrc

# Sanity checks (these should print valid paths):
echo $WM_PROJECT_DIR        # -> /home/<user>/OpenFOAM-v2012
echo $WM_PROJECT_USER_DIR   # -> /home/<user>/OpenFOAM/<user>-v2012
```

---

## 4) Build OpenFOAM v2012

```bash
cd ~/OpenFOAM-v2012
./Allwmake -j $(nproc)
# Some utilities are built on a second pass — harmless:
./Allwmake -j $(nproc)
```

If the build finishes without errors, v2012 is ready. This might take some time.

---

## 6) Verify OpenFOAM is usable

```bash
# Open a new shell or re-source bashrc:
source ~/.bashrc

# Basic commands should exist:
which wmake
which blockMesh

# Create the user project dir if it doesn't exist yet:
mkdir -p "$WM_PROJECT_USER_DIR"
```

---

## 7) Build the custom solvers (from this repository)

```bash
# Place/clone 'twoPhaseCustomSolvers' here:
cd "$WM_PROJECT_USER_DIR"
# (copy or git clone the repo so the path is:)
# $WM_PROJECT_USER_DIR/twoPhaseCustomSolvers

cd twoPhaseCustomSolvers
chmod +x Allwmake Allclean
./Allwmake
```
---

## 8) Run the included tutorial cases

**smoothedVofInterFoam tutorial**
```bash
cd "$WM_PROJECT_USER_DIR/twoPhaseCustomSolvers/tutorials/smoothedVofInterFoam"
./Allrun    # this will mesh and run the case automatically
```

**depthAveragedInterFoam tutorial**
```bash
cd "$WM_PROJECT_USER_DIR/twoPhaseCustomSolvers/tutorials/depthAveragedInterFoam"
./Allrun
```
---

## 10) Uninstall / clean

```bash
# Remove build artifacts for the custom solvers:
cd "$WM_PROJECT_USER_DIR/twoPhaseCustomSolvers"
./Allclean
```
---
**END OF FILE**

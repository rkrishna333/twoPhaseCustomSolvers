# twoPhaseCustomSolvers (OpenFOAM v2012)

Custom two-phase solvers and supporting libraries for **OpenFOAM v2012 (ESI)**:

- **`smoothedVofInterFoam`** — 3-D VOF solver with interface-smoothing for reduced spurious currents.  
  Detailed description and application in:  
  *Krishna et al. (2025), Physics of Fluids* ([Krishna2025_PhysicsFluids](#-citations)).
- **`depthAveragedInterFoam`** — 2-D depth-integrated solver for immiscible two-phase flow in rough fractures.  
  Detailed description and application in:  
  *Krishna et al. (2025), Journal of Fluid Mechanics* ([Krishna2025_JFM](#-citations)).


**Project layout**
```
twoPhaseCustomSolvers/
├── Allclean
├── Allwmake
├── applications/
│ └── solvers/
│ └── multiphase/
│ ├── smoothedVofInterFoam/
│ └── depthAveragedInterFoam/
└── src/
├── mySchemes/
│ └── myPhiScheme/
└── depthAveragedTransportModels/
├── twoPhaseMixture/
├── interfaceProperties/
├── twoPhaseProperties/
├── incompressible/
└── immiscibleIncompressibleTwoPhaseMixture/
```

---

## 🔧 Compatibility Notice

This code has been **tested and validated only with OpenFOAM v2012 (ESI)**.  
If you wish to adapt it for a newer OpenFOAM release, you are free to do so under the GPLv3 license — however, compatibility and validation for other versions are not guaranteed and should be verified by the user.

📥 **[Click here for the full OpenFOAM v2012 installation guide](INSTALL_v2012_OpenFOAM.md)**

---

## If you already have OpenFOAM v2012 set up
The code is designed for **minimal setup**:  
Place this folder in `$WM_PROJECT_USER_DIR`, run `./Allwmake`, and you’re ready.
```bash
source /path/to/OpenFOAM-v2012/etc/bashrc
cd "$WM_PROJECT_USER_DIR"      # e.g. /home/<user>/OpenFOAM/<user>-v2012

# Place/clone this repo here:
# $WM_PROJECT_USER_DIR/twoPhaseCustomSolvers

cd twoPhaseCustomSolvers
chmod +x Allwmake Allclean
./Allwmake
```
---
## 📖 Tutorials

Two minimal tutorials are included to demonstrate usage and provide a starting point:

### [`tutorials/smoothedVofInterFoam`](tutorials/smoothedVofInterFoam)
- Demonstrates the **3-D smoothed VOF solver**.
- Contains a basic case setup with geometry, mesh, and run script (`Allrun`).
- Shows how to control smoothing with the parameters `smoothItr` and `kSmoothItr` in `system/fvSolution`.

### [`tutorials/depthAveragedInterFoam`](tutorials/depthAveragedInterFoam)
- Demonstrates the **2-D depth-averaged solver**.
- Includes a simple fracture (same as the 3-D case) case with corresponding `Allrun` script.
- The `fvSolution` file also contains `smoothItr` and `kSmoothItr` for controlling numerical smoothing.

---

## 🔧 Smoothing parameters

Inside `system/fvSolution` for both solvers:

- **`smoothItr`** — Number of smoothing iterations for phase fraction.
- **`kSmoothItr`** — Number of smoothing iterations for curvature.



---

## 📚 Citations
If you use this code in academic work, please cite the corresponding publications:
```
@article{Krishna2025_PhysicsFluids,
  author = {Krishna, R. and Méheust, Y. and Neuweiler, I.},
  title = {Direct numerical simulations of immiscible two-phase flow in rough fractures: Impact of wetting film resolution},
  journal = {Physics of Fluids},
  volume = {36},
  number = {7},
  pages = {073326},
  year = {2025},
  doi = {10.1063/5.0217315}
}

@article{Krishna2025_JFM,
  author = {Krishna, Rahul and Méheust, Yves and Neuweiler, Insa},
  title = {A two-dimensional depth-integrated model for immiscible two-phase flow in open rough fractures},
  journal = {Journal of Fluid Mechanics},
  volume = {1011},
  pages = {A43},
  year = {2025},
  doi = {10.1017/jfm.2025.404}
}
```

---

## 👤 Author

**Rahul Krishna**   
Leibniz Universität Hannover  
krishna@hydromech.uni-hannover.de

---

## 📝 License

This code is distributed under the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html), consistent with the OpenFOAM licensing.  
You are free to use, modify, and redistribute it under the terms of the GPLv3 license.

**Note:** The associated publications are open access and available under their respective journal licenses.  
The code here implements methods described in the following papers:

- **Krishna et al. (2025)**, *Physics of Fluids* — [DOI:10.1063/5.0217315](https://doi.org/10.1063/5.0217315)  
- **Krishna et al. (2025)**, *Journal of Fluid Mechanics* — [DOI:10.1017/jfm.2025.404](https://doi.org/10.1017/jfm.2025.404)
---






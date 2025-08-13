// Solve the Momentum equation

    volScalarField d_viscosity(mixture.mu());
    surfaceScalarField rhoPhiU("rhoPhiU", rhoPhi/aperture_f);
    fvVectorMatrix QEqn
    (
        fvm::ddt(rho, Q) + beta * fvm::div(rhoPhiU, Q)
      + turbulence->divDevRhoReff(rho, Q)
      + fvm::Sp(d_viscosity * DragCoeff, Q)

    );

    QEqn.relax();

    if (pimple.momentumPredictor())
    {
        solve
        (
            QEqn
         ==
            fvc::reconstruct
            (
                (
                    mixture.surfaceTensionForce()
                  - ghf*fvc::snGrad(rho)
                  - fvc::snGrad(p_rgh)
                ) * mesh.magSf()
            ) * aperture
        );

    }

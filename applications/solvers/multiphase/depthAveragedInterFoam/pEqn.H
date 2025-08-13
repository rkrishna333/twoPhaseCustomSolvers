{
    volScalarField rAQ(1.0/QEqn.A());
    surfaceScalarField rAQf("rAQf", fvc::interpolate(rAQ));
    volVectorField HbyA(constrainHbyA(rAQ*QEqn.H(), Q, p_rgh));
    surfaceScalarField phiHbyA
    (
        "phiHbyA",
        fvc::flux(HbyA)
      + fvc::interpolate(rho*rAQ)*fvc::ddtCorr(Q, phi)
    );

    adjustPhi(phiHbyA, Q, p_rgh);

    surfaceScalarField phig
    (
        (
            mixture.surfaceTensionForce()
          - ghf*fvc::snGrad(rho)
        )*rAQf*mesh.magSf()*aperture_f
    );

    phiHbyA += phig;

    // Update the pressure BCs to ensure flux consistency
    constrainPressure(p_rgh, Q, phiHbyA, rAQf);

    while (pimple.correctNonOrthogonal())
    {
        fvScalarMatrix p_rghEqn
        (
            fvm::laplacian(rAQf*aperture_f, p_rgh) == fvc::div(phiHbyA)
        );

        p_rghEqn.setReference(pRefCell, getRefCellValue(p_rgh, pRefCell));

        p_rghEqn.solve(mesh.solver(p_rgh.select(pimple.finalInnerIter())));

        if (pimple.finalNonOrthogonalIter())
        {

            phi = phiHbyA - p_rghEqn.flux();

            p_rgh.relax();
  
            Q = HbyA + rAQ*fvc::reconstruct((phig - p_rghEqn.flux())/rAQf);

            Q.correctBoundaryConditions();
            U = Q/aperture;
            phiU = fvc::flux(U);
        }
    }

    #include "continuityErrs.H"

    p == p_rgh + rho*gh;

    if (p_rgh.needReference())
    {
        p += dimensionedScalar
        (
            "p",
            p.dimensions(),
            pRefValue - getRefCellValue(p, pRefCell)
        );
        p_rgh = p - rho*gh;
    }
}


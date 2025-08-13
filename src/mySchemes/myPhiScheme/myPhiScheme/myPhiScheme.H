/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2011-2016 OpenFOAM Foundation
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Class
    Foam::myPhiScheme

Group
    grpFvLimitedSurfaceInterpolationSchemes

Description
    Class to create the weighting-factors based on the face-flux.

    The particular differencing scheme class is supplied as a template
    argument, the weight function of which is called by the weight function
    of this class for the internal faces as well as faces of coupled
    patches (e.g. processor-processor patches). The weight function is
    supplied with the central-differencing weighting factor, the face-flux,
    the face neighbour cell values and the face area.

    This code organisation is both neat and efficient, allowing for
    convenient implementation of new schemes to run on parallelised cases.

SourceFiles
    myPhiScheme.C

\*---------------------------------------------------------------------------*/

#ifndef myPhiScheme_H
#define myPhiScheme_H

#include "limitedSurfaceInterpolationScheme.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                           Class myPhiScheme Declaration
\*---------------------------------------------------------------------------*/

template<class Type, class myPhiLimiter>
class myPhiScheme
:
    public limitedSurfaceInterpolationScheme<Type>,
    public myPhiLimiter
{
    // Private Member Functions

        //- No copy construct
        myPhiScheme(const myPhiScheme&) = delete;

        //- No copy assignment
        void operator=(const myPhiScheme&) = delete;


public:

    //- Runtime type information
    TypeName("myPhiScheme");


    // Constructors

        //- Construct from mesh, faceFlux and blendingFactor
        myPhiScheme
        (
            const fvMesh& mesh,
            const surfaceScalarField& faceFlux,
            const myPhiLimiter& weight
        )
        :
            limitedSurfaceInterpolationScheme<Type>(mesh, faceFlux),
            myPhiLimiter(weight)
        {}

        //- Construct from mesh and Istream.
        //  The name of the flux field is read from the Istream and looked-up
        //  from the mesh objectRegistry
        myPhiScheme
        (
            const fvMesh& mesh,
            Istream& is
        )
        :
            limitedSurfaceInterpolationScheme<Type>(mesh, is),
            myPhiLimiter(is)
        {}

        //- Construct from mesh, faceFlux and Istream
        myPhiScheme
        (
            const fvMesh& mesh,
            const surfaceScalarField& faceFlux,
            Istream& is
        )
        :
            limitedSurfaceInterpolationScheme<Type>(mesh, faceFlux),
            myPhiLimiter(is)
        {}


    // Member Functions

        //- Return the interpolation weighting factors
        virtual tmp<surfaceScalarField> limiter
        (
            const GeometricField<Type, fvPatchField, volMesh>&
        ) const;
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Add the patch constructor functions to the hash tables

#define makePhiSurfaceInterpolationScheme(SS, WEIGHT, TYPE)                    \
                                                                               \
typedef myPhiScheme<TYPE, WEIGHT> myPhischeme##WEIGHT_;                            \
defineTemplateTypeNameAndDebugWithName(myPhischeme##WEIGHT_, #SS, 0);            \
                                                                               \
surfaceInterpolationScheme<TYPE>::addMeshConstructorToTable                    \
<myPhiScheme<TYPE, WEIGHT>> add##SS##TYPE##MeshConstructorToTable_;              \
                                                                               \
surfaceInterpolationScheme<TYPE>::addMeshFluxConstructorToTable                \
<myPhiScheme<TYPE, WEIGHT>> add##SS##TYPE##MeshFluxConstructorToTable_;          \
                                                                               \
limitedSurfaceInterpolationScheme<TYPE>::addMeshConstructorToTable             \
<myPhiScheme<TYPE, WEIGHT>> add##SS##TYPE##MeshConstructorToLimitedTable_;       \
                                                                               \
limitedSurfaceInterpolationScheme<TYPE>::addMeshFluxConstructorToTable         \
<myPhiScheme<TYPE, WEIGHT>> add##SS##TYPE##MeshFluxConstructorToLimitedTable_;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#ifdef NoRepository
    #include "myPhiScheme.C"
#endif

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //

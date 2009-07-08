//
// This file is part of the Marble Desktop Globe.
//
// This program is free software licensed under the GNU LGPL. You can
// find a copy of this license in LICENSE.txt in the top directory of
// the source code.
//
// Copyright 2009      Patrick Spendrin <ps_ml@gmx.de>
//

#ifndef ABSTRACTPROJECTIONPRIVATE_H
#define ABSTRACTPROJECTIONPRIVATE_H


namespace Marble
{

class AbstractProjection;

class AbstractProjectionPrivate
{
  public:
    AbstractProjectionPrivate( AbstractProjection * _q );

    AbstractProjection * q;

    bool   m_repeatX;              // Map repeated in X direction.

    qreal  m_maxLat;
    qreal  m_minLat;

    GeoDataCoordinates findHorizon( const GeoDataCoordinates & previousCoords,
                                    const GeoDataCoordinates & currentCoords,
                                    const ViewportParams *viewport,
                                    TessellationFlags f = 0,
                                    int recursionCounter = 0 );

    bool globeHidesPoint( const GeoDataCoordinates &coordinates,
                          const ViewportParams *viewport );

    void manageHorizonCrossing( bool globeHidesPoint,
                                const GeoDataCoordinates& horizonCoords,
                                bool& horizonPair,
                                GeoDataCoordinates& horizonDisappearCoords,
                                bool& horizonOrphan,
                                GeoDataCoordinates& horizonOrphanCoords );

    QPolygonF processTessellation(  const GeoDataCoordinates &previousCoords,
                                    const GeoDataCoordinates &currentCoords,
                                    int count, const ViewportParams *viewport,
                                    TessellationFlags f = 0 );
};

} // namespace Marble

#endif //ABSTRACTPROJECTIONPRIVATE_H

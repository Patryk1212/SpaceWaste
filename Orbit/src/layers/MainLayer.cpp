#include "pch.h"
#include "MainLayer.h"

void MainLayer::onAttach()
{
    std::cout << "MAIN Layer Attached" << std::endl;

    fileLoader.loadFileNames();
    fileLoader.loadTLEandCreateObjects(spaceObjects);

	// download data
	// calculate info
	// create objects

    // Example: Define a location on the earth, then determine the look-angle
    // to the SDP4 satellite defined above.

    // Get the location of the satellite. The earth-centered inertial (ECI)
    // information is placed into eciSDP4.
    // Here we ask for the location of the satellite 90 minutes after
    // the TLE epoch.
    //cEciTime eciSDP4 = satSDP4.PositionEci(90.0);

    // Now create a site object. Site objects represent a location on the 
    // surface of the earth. Here we arbitrarily select a point on the
    // equator.
    //cSite siteEquator(0.0, -100.0, 0); // 0.00 N, 100.00 W, 0 km altitude

    // Now get the "look angle" from the site to the satellite. 
    // Note that the ECI object "eciSDP4" contains a time associated
    // with the coordinates it contains; this is the time at which
    // the look angle is valid.
   // cTopo topoLook = siteEquator.GetLookAngle(eciSDP4);

    // Print out the results.
    //printf("AZ: %.3f  EL: %.3f\n",
       // topoLook.AzimuthDeg(),
       // topoLook.ElevationDeg());
}

void MainLayer::PrintPosVel(const cSatellite& sat)
{
    vector<cEci> vecPos;

    // Calculate the position and velocity of the satellite for various times.
    // mpe = "minutes past epoch"
    for (int mpe = 0; mpe <= (360 * 4); mpe += 360)
    {
        // Get the position of the satellite at time "mpe"
        cEciTime eci = sat.PositionEci(mpe);

        // Push the coordinates object onto the end of the vector.
        vecPos.push_back(eci);
    }

    // Print TLE data
    printf("%s\n", sat.Name().c_str());
    printf("%s\n", sat.Orbit().TleLine1().c_str());
    printf("%s\n\n", sat.Orbit().TleLine2().c_str());

    // Header
    printf("  TSINCE            X                Y                Z\n\n");

    // Iterate over each of the ECI position objects pushed onto the
    // position vector, above, printing the ECI position information
    // as we go.
    for (unsigned int i = 0; i < vecPos.size(); i++)
    {
        printf("%8d.00  %16.8f %16.8f %16.8f\n",
            i * 360,
            vecPos[i].Position().m_x,
            vecPos[i].Position().m_y,
            vecPos[i].Position().m_z);
    }

    printf("\n                    XDOT             YDOT             ZDOT\n\n");

    // Iterate over each of the ECI position objects in the position
    // vector again, but this time print the velocity information.
    for (unsigned int i = 0; i < vecPos.size(); i++)
    {
        printf("             %16.8f %16.8f %16.8f\n",
            vecPos[i].Velocity().m_x,
            vecPos[i].Velocity().m_y,
            vecPos[i].Velocity().m_z);
    }

    printf("\n");
}

void MainLayer::onUpdate(float deltaTime)
{
	// update objects' scale etc


}

void MainLayer::onRender()
{
}

bool MainLayer::onEvent(Engine::Event& event)
{


	return true;
}

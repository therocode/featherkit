#include <fea/util/whitenoise.hpp>
#include <fea/util/voronoinoise.hpp>
#include <cmath>

namespace fea
{
	float VoronoiNoise::get2d(float x, float y, const uint8_t* perm) const
	{
		WhiteNoise white;

		int xInt = std::floor(x);//(x > 0.0f? (int)x: (int)x - 1);
		int yInt = std::floor(y);//(y > 0.0f? (int)y: (int)y - 1);

		float minDist = 2147483648.0f;
		float xCandidate = 0.0f;
		float yCandidate = 0.0f;

		// Inside each unit cube, there is a seed point at a random position.  Go
		// through each of the nearby cubes until we find a cube with a seed point
		// that is closest to the specified position.
		for (int yCur = -1; yCur <= 1; yCur++) 
		{
			for (int xCur = -1; xCur <= 1; xCur++) 
			{

				// Calculate the position and distance to the seed point inside of
				// this unit cube.
				float xPos = (xInt + xCur) + white.get2d(xInt + xCur, yInt + yCur, perm);
				float yPos = (yInt + yCur) + white.get2d(xInt + xCur, (yInt + yCur) + 1000, perm); //this should be different
				float xDist = xPos - x;
				float yDist = yPos - y;
				float dist = xDist * xDist + yDist * yDist;

				if (dist < minDist) 
				{
					// This seed point is closer to any others found so far, so record
					// this seed point.
					minDist = dist;
					xCandidate = xPos;
					yCandidate = yPos;
				}
			}
		}

		// Return the calculated distance with the displacement value applied.
		return white.get2d(std::floor(xCandidate), std::floor(yCandidate), perm);
	}
}

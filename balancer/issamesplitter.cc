#include "balancer.ih"

bool Balancer::isSameSplitter(Triple tile1, Triple tile2)
{
	if (tile1.tile == SPLN and tile2.tile == SPRN and tile1.y == tile2.y and tile1.x + 1 == tile2.x)
		return true;
	
	if (tile1.tile == SPRN and tile2.tile == SPLN and tile1.y == tile2.y and tile1.x == tile2.x + 1)
		return true;
	
	if (tile1.tile == SPLE and tile2.tile == SPRE and tile1.x == tile2.x and tile1.y + 1 == tile2.y)
		return true;
	
	if (tile1.tile == SPRE and tile2.tile == SPLE and tile1.x == tile2.x and tile1.y == tile2.y + 1)
		return true;

	if (tile1.tile == SPLW and tile2.tile == SPRW and tile1.x == tile2.x and tile1.y == tile2.y + 1)
		return true;

	if (tile1.tile == SPRW and tile2.tile == SPLW and tile1.x == tile2.x and tile1.y + 1 == tile2.y)
		return true;

	if (tile1.tile == SPLS and tile2.tile == SPRS and tile1.y == tile2.y and tile1.x == tile2.x + 1)
		return true;

	if (tile1.tile == SPRS and tile2.tile == SPLS and tile1.y == tile2.y and tile1.x + 1 == tile2.x)
		return true;


	return false;
}
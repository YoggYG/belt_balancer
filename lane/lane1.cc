#include "lane.ih"

Lane::Lane(vector<Tile> &matrix, vector<Triple> &path, size_t rows, size_t cols, size_t power, size_t underground_distance)
:
	d_rows(rows),
	d_cols(cols),
	d_power(power),
	d_path(path)
{
	size_t x = d_path.back().x;
	size_t y = d_path.back().y;
	Tile tile = d_path.back().tile;

	while (true)
	{
		// cerr << "X: " << x << "   Y: " << y << "    Item: " << item << endl;
		size_t len = 0;
		switch (tile.item)
		{
			case BN:
			case UBON:
			case SPLN:
			case SPRN: --y; break;
			case BE:
			case UBOE:
			case SPLE:
			case SPRE: ++x; break;
			case BS:
			case UBOS:
			case SPLS:
			case SPRS: ++y; break;
			case BW:
			case UBOW:
			case SPLW:
			case SPRW: --x; break;
			case UBIN:
				for (len = 2; len < underground_distance; ++len)
					if (/*y - len >= 0 && */matrix[(y - len) * d_cols + x] == UBON)
					{
						y -= len;
						break;
					}
				break;
			case UBIE:
				for (len = 2; len < underground_distance; ++len)
					if (x + len < d_cols && matrix[y * d_cols + x + len] == UBOE)
					{
						x += len;
						break;
					}
				break;
			case UBIS:
				for (len = 2; len < underground_distance; ++len)
					if (y + len < d_rows && matrix[(y + len) * d_cols + x] == UBOS)
					{
						y += len;
						break;
					}
				break;
			case UBIW:
				for (len = 2; len < underground_distance; ++len)
					if (/*x - len >= 0 && */matrix[y * d_cols + x - len] == UBOW)
					{
						x -= len;
						break;
					}
				break;
		}
		if (len == underground_distance)
		{
			// cerr << "lane1.cc: len == underground_distance\n";
			break;
		}

		if (/*x < 0 || y < 0 || */x >= d_cols || y >= d_rows) // coordinates use unsigned ints. Negative values become max_int like.
		{
			// cerr << "lane1.cc: x or y larger than bounds\n";
			break;
		}
		
		Tile newTile = matrix[y * d_cols + x];
		bool fail = true;
		switch (tile.item)
		{
			case BN:
			case UBON:
			case SPLN:
			case SPRN:
				if (newTile == BN || newTile == BE || newTile == BW || newTile == UBIN || newTile == SPLN || newTile == SPRN)
					fail = false;
				break;
			case BE:
			case UBOE:
			case SPLE:
			case SPRE:
				if (newTile == BN || newTile == BE || newTile == BS || newTile == UBIE || newTile == SPLE || newTile == SPRE)
					fail = false;
				break;
			case BS:
			case UBOS:
			case SPLS:
			case SPRS:
				if (newTile == BE || newTile == BS || newTile == BW || newTile == UBIS || newTile == SPLS || newTile == SPRS)
					fail = false;
				break;
			case BW:
			case UBOW:
			case SPLW:
			case SPRW:
				if (newTile == BN || newTile == BS || newTile == BW || newTile == UBIW || newTile == SPLW || newTile == SPRW)
					fail = false;
				break;
			case UBIN:
				if (newTile == UBON)
					fail = false;
				break;
			case UBIE:
				if (newTile == UBOE)
					fail = false;
				break;
			case UBIS:
				if (newTile == UBOS)
					fail = false;
				break;
			case UBIW:
				if (newTile == UBOW)
					fail = false;
				break;
		}
		if (fail)
		{
			// cerr << "lane1.cc: following item invalid, tile: " << tile.item << ", newTile: " << newTile.item << ", idx: " << x  + y * d_cols << "\n";
			break;
		}

		tile = newTile;
		for (auto it = d_path.begin(); it != d_path.end(); ++it)
			if (it->x == x && it->y == y)
				fail = true;
		
		if (fail)
		{
			// cerr << "lane1.cc: tile elsewhere in path\n";
			break;
		}
		
		d_path.push_back(Triple{x, y, tile});
	}
}